/**
* @file stdafx.h

* @par Copyright (c):�е�Ƶ���ʮһ�о��� װ����ҵ��
* ��Ȩ���У�δ�����ɣ����ø��ơ�������ת����

* @brief Ԥ����ͷ�ļ�

* @author wangkedong

* @date 2020:06:04

* @note 

* @version <1.0.0>

*/
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
//#include <windows.h>
#include "SuperSocket.h"
#include "SuperSocketAPI.h"
#include <functional>
#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <vector>
#include <map>
#include <list>
#include "assert.h"
#include <czmq.h>
#include <mutex>
#include <condition_variable>
using namespace std;
namespace ZBSYB_RADAR_SOCKET
{
	/**
	* @brief ����ID��
	*/
	enum CommandID
	{
		SYNC_WORD_ZK = 0X7E7E4141,
		SYNC_WORD_YC = 0XA5A54141,
		BYTE_LENGTH = 116,
		SELF_DETECT_ID = 0X10000001,	         ///< �Լ�ָ��
		START_STOP_ID = 0X10000002,	             ///< ����/ָֹͣ��
		LOCK_TRACK_ID = 0X10000003,	             ///< ��������
		RESET_ID = 0X10000004,	                 ///< ��λָ��
		PARA_CONFIG_ID = 0X10000005,			 ///< ��������ָ��
		GPS_MODUL_CONFIG_ID = 0X10000006,	     ///< GPSģ������
		COMPASS_CALIBRATION_ID = 0X10000007,	 ///< ��������У׼
		IP_CONFIG_ID = 0X10000008,			     ///< ���ڵ�IP����
		LOW_POWER_CONSUMPTION_ID = 0X10000009,   ///< �͹���ָ��
		WAVE_GATE_SWITCH_ID = 0X20000001,		 ///< ���ſ���
		AGC_CONTROL_ID = 0X20000002,			 ///< AGC����
		DETECT_THRESHOLD_ADJUST_ID = 0X20000003, ///< ������޵���
		TIME_CALIBRATION_ID = 0X20000004,	     ///< ��ʱ����
		SOFTWARE_UPDATE_ID = 0X20000005,		 ///< ��������
		DEVICE_STATUS_SEARCH = 0X20000006,       ///< �豸״̬��ѯ
		STANDARD_CALIBRATION_ID = 0X30000001,	 ///< ��Уָ��
	};

	// TODO: reference additional headers your program requires here
}