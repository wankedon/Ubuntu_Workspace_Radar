/**
* @file DeviceStreamBuffer.cpp
* @brief �ֽ���������
* @author װ����ҵ�������� ���˶�
* @date 2021:07:05
* @Copyright (c) 2021 �й����ӿƼ����Ź�˾����ʮһ�о���
*/ 
#include "stdafx.h"
#include "PositionSocketAPI.h"
#include "DeviceStreamBuffer.h"
namespace ZBSYB_RADAR_SOCKET
{
	DeviceStreamBuffer::DeviceStreamBuffer()
	{
	}

	DeviceStreamBuffer::~DeviceStreamBuffer()
	{
	}

	/**
	* @brief ���ݿ���뻺�壬��ȡ��������֡
	* @param[in] db �������ݿ�
	*/
	list<shared_ptr<DeviceFrame>> DeviceStreamBuffer::onDeviceData(const DataBlock& db)
	{
		list<shared_ptr<DeviceFrame>> result;
		vector<byte> temp{ (byte*)db.addr, (byte*)db.addr + db.len };
		m_bytebuffer.insert(m_bytebuffer.end(), temp.begin(), temp.end());
		while (true)
		{
			if (m_bytebuffer.size() == 0)
				break;
			auto frameList = extractFullFrame(m_bytebuffer);//+++
			if (frameList.size() == 0)
				break;
			for (auto fr : frameList)//+++
			{
				auto ptr = *fr.get();//+++
				vector<byte> fb(ptr.size() * sizeof(uint32_t));//+++
				memcpy(fb.data(), ptr.data(), ptr.size() * sizeof(uint32_t));//+++
				auto frame = make_shared<DeviceFrame>(fb);//(m_bytebuffer);
				if (frame->size() == 0)
					break;
				result.push_back(frame);
				m_bytebuffer.erase(m_bytebuffer.begin(), m_bytebuffer.begin() + frame->size() * sizeof(uint32_t));
			}//+++
		}
		return result;
	}

	/**
	* @brief ��ȡ����֡
	* @param[in] buffer �ֽ�����
	*/
	list<shared_ptr<vector<uint32_t>>> DeviceStreamBuffer::extractFullFrame(vector<byte>& byteBuffer)
	{
		list<shared_ptr<vector<uint32_t>>> frameList;
		if (byteBuffer.size() < 2 * sizeof(uint32_t))
			return frameList;
		vector<uint32_t> allFrame;
		m_headIndex = extractFrameHead(allFrame, byteBuffer);
		if (m_headIndex.size() == 0)
			return frameList;
		if (m_headIndex.size() > 1)   //�������֡ͷ
		{
			multiFrameExtract(allFrame, frameList);
		}
		else//����һ��֡ͷ
		{
			allFrame = { allFrame.begin() + m_headIndex[0],allFrame.end() };
		}
		//��֡ʣ�����ݻ������֡ͷ
		singleFrameExtract(allFrame, frameList);
		return frameList;
	}

	/**
	* @brief ��ȡ֡ͷ
	* @param[out] allFrame uint32_t����
	* @param[in]  byteBuffer �ֽ�����
	* @return vector<int> ֡ͷλ��
	*/
	vector<int> DeviceStreamBuffer::extractFrameHead(vector<uint32_t>& allFrame, vector<byte>& byteBuffer)
	{
		allFrame.resize(byteBuffer.size() / sizeof(uint32_t));
		memcpy(allFrame.data(), byteBuffer.data(), allFrame.size() * sizeof(uint32_t));
		vector<int> headIndex(0);//֡ͷλ��
		int index = 0;
		for (auto fr : allFrame)
		{
			//(fr == SYNC_WORD_ZK || fr == SYNC_WORD_YC) ? headIndex.emplace_back(index++):index++;
			if (fr == SYNC_WORD_ZK || fr == SYNC_WORD_YC)
			{
				headIndex.emplace_back(index++);
			}
			else
			{
				index++;
			}
		}
		return headIndex;
	}

	/**
	* @brief ��֡��ȡ
	* @param[out] allFrame ��ȡ֡��ʣ��uint32_t����
	* @param[out]  frameList ��ȡ������֡
	*/
	void DeviceStreamBuffer::multiFrameExtract(vector<uint32_t>& allFrame, list<shared_ptr<vector<uint32_t>>>& frameList)
	{
		if (m_headIndex.size() == 0)
			return;
		int eraseSize = 0;//���������ֽ���
		for (int i = 0; i < m_headIndex.size() - 1; i++)
		{
			vector<uint32_t> oneFrame = { allFrame.begin() + m_headIndex[i],allFrame.begin() + m_headIndex[i + 1] };
			frameList.push_back(make_shared<vector<uint32_t>>(oneFrame));
			eraseSize += allFrame[m_headIndex[i] + 1] / sizeof(uint32_t) + OTHER_LENGTH;
		}
		//��������֡
		allFrame.erase(allFrame.begin() + m_headIndex[0], allFrame.begin() + eraseSize);
	}

	/**
	* @brief ��֡��ȡ
	* @param[out] allFrame ��ȡ֡��ʣ��uint32_t����
	* @param[out]  frameList ��ȡ������֡
	*/
	void DeviceStreamBuffer::singleFrameExtract(vector<uint32_t>& allFrame, list<shared_ptr<vector<uint32_t>>>& frameList)
	{
		if (allFrame.size() < 2)
			return;
		int lastFrameSize = allFrame[1] / sizeof(uint32_t) + OTHER_LENGTH;
		if (allFrame.size() < lastFrameSize)
			return;
		vector<uint32_t> oneFrame = { allFrame.begin(),allFrame.begin() + lastFrameSize };
		frameList.push_back(make_shared<vector<uint32_t>>(oneFrame));
		//����
		allFrame.erase(allFrame.begin(), allFrame.begin() + lastFrameSize);
	}
}