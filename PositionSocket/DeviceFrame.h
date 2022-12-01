/**
* @file DeviceFrame.h

* @par Copyright (c):�е�Ƶ���ʮһ�о��� װ����ҵ��
* ��Ȩ���У�δ�����ɣ����ø��ơ�������ת����

* @brief DeviceFrame������ͷ�ļ�

* @author wangkedong

* @date 2020:07:09

* @note ���ֽ�������ȡ��������֡

* @version <1.0.0>

*/
#pragma once
#include "PositionSocketAPI.h"
namespace ZBSYB_RADAR_SOCKET
{
	/**
	* @brief ���ֽ�������ȡ��������֡
	* @details
	*/
	class DeviceFrame
	{
	public:
		DeviceFrame(const vector<byte>& deviceStream);
		~DeviceFrame();
	public:
		bool isCmdReply() const { return size() == REPLY_FRAME_SIZE; }
		size_t size() const;
		uint32_t id() const;
		uint32_t index() const;
		ZKResult makeZKResult();
		YCResult makeYCResult();
		template<class T>
		bool makeCmdResult(T& result)
		{
			if (m_data == nullptr)
				return false;
			if (size() * sizeof(uint32_t) != sizeof(result))
				return false;
			memcpy(&result, m_data->data(), sizeof(result));
			return true;
		}
	private:
		unique_ptr<vector<uint32_t>> m_data;
	private:
		static const size_t FIXED_LENGTH = 12;
		static const size_t REPLY_FRAME_SIZE = 32;
	};
}