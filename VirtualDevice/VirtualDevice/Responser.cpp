
#include "precompile.h"
#include "Responser.h"

Responser::Responser()
	:scanIdx(0)
{
}

Responser::~Responser()
{
}

shared_ptr<ReplyFrame> Responser::onRequest(const NetBlock* data)
{
	shared_ptr<ReplyFrame> result(parse(data));
	if (result != nullptr)
	{
		result->print();
		auto id = result->id();
		//һЩ���⴦��
		if (id == START_STOP_ID || id == LOCK_TRACK_ID)
		{
			lastMeasurementFrame = make_shared<ReplyFrame>(*result);
			result = nullptr;
			scanIdx = 0;
		}
		else if (id == SELF_DETECT_ID)//�Լ�ָ����ֹͣ�ش����
		{
			lastMeasurementFrame = nullptr;
			buffer.clear();
			scanIdx = 0;
		}
	}
	return result;
}

shared_ptr<ReplyFrame> Responser::onTimer()	//ģ��һ��ɨ��
{
	if (lastMeasurementFrame != nullptr)
	{
		lastMeasurementFrame->randomGene(scanIdx);
		scanIdx++;
	}
	return lastMeasurementFrame;
}

shared_ptr<ReplyFrame>  Responser::parse(const NetBlock* data)
{
	if (type.empty())
	{
		//assert(data->len == 3);
		type = (char*)(data->addr);
		return nullptr;
	}
	vector<byte> temp{ (byte*)data->addr, (byte*)data->addr + data->len };
	if (buffer.empty())
	{
		auto result = make_shared<ReplyFrame>(temp);
		if (result->size() == 0)
		{
			buffer = temp;	//�ݴ���
			return nullptr;
		}
		else
		{
			return result;
		}
	}
	else
	{
		buffer.insert(buffer.end(), temp.begin(), temp.end());
		auto result = make_shared<ReplyFrame>(buffer);
		if (result->size() == 0)
		{
			return nullptr;
		}
		else
		{
			buffer.clear();	//�建��
			return result;
		}
	}
}

