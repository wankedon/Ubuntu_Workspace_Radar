/**
* @file PositionSocketAPI.h

* @par Copyright (c):�е�Ƶ���ʮһ�о��� װ����ҵ��
* ��Ȩ���У�δ�����ɣ����ø��ơ�������ת����

* @brief PositionSocket��������壬����C API

* @author wangkedong

* @date 2020:07:09

* @note 

* @version <1.0.0>

*/

/**
* @mainpage PositionSocket��̬��
* @section PositionSocketAPI��飺
* @subsection PositionSocketAPIΪ��Яʽ��ŷ���Դ��鶨λϵͳ�Կ��ն�����ڵ��������ͨ�ŵĽӿ�
* @subsection ��Ҫ�����Կ��ն�����ڵ��·�ָ��������ռ��ڵ�ش�ָ�������������ݡ�
* @section CAPI PositionSocketAPI ʹ�÷�����
* @subsection step1 Step 1: ����PositionSocketAPI.h
* @subsection step2 Step 2: ����PS_InitSSLib()��ʼ����
* @subsection step3 Step 3: ����ص�����������ip��ַ������PS_CreateConnect()�������ӣ���þ��fd������
* @subsection step4 Step 4: ���øþ��fd�������ݣ�ͨ���ص�������������
* @subsection step5 Step 5: ���ٴ�������ʱ������PS_CloseConnect()�ر�����
* @subsection step6 Step 6: ����ʹ�ÿ�ʱ������PS_DeinitSSLib()�رտ⣬�ͷ���Դ
*/
#pragma once
//#ifdef __cplusplus
//extern "C"{
//#endif
#ifdef WIN32
#ifdef POSITIONSOCKET_EXPORTS
#define POSITIONSOCKET_API __declspec(dllexport)
#else
#define POSITIONSOCKET_API __declspec(dllimport)
#endif
#else
#define POSITIONSOCKET_API
#endif

namespace ZBSYB_RADAR_SOCKET
{
		/**
		* @brief API����ֵ���������ʶ
		*/
		enum PS_Error
		{
			PS_ERR_NONE = 0,	            ///<�޴���
			PS_ERR_INIT = -1,               ///<��ʼ�������
			PS_ERR_INVALID_HANDLE = -2,     ///<��Ч���
			PS_ERR_CONNECT = -3,            ///<���Ӵ���
			PS_ERR_SEND = -4,               ///<���ʹ���
			PS_ERR_OVERTIME = -5,           ///<��Ӧ��ʱ
			PS_ERR_NO_HANDLE_RESOURCE = -6, ///<�޾����Դ
			PS_ERR_CREATE_SOCKET = -7,      ///<����SOCKET����
		};

#pragma pack(1)
		/**
		* @brief �ۿؽ���ش�����֡֡ͷ
		*/
		struct FrameHeader
		{
			uint32_t syncWord;        ///<ͬ����  
			uint32_t byteLength;      ///<�ֽڳ���ֵ
			uint32_t commandID;       ///<����ID��
			uint32_t response;        ///<ָ����Ӧ��־
			uint32_t counter;         ///<ָ����Ӧ�����ۼ�ֵ
			uint32_t systemTime;      ///<ϵͳʱ��
		};

		/**
		* @brief �Լ����ش�����֡
		*/
		struct SelfDetectFrame
		{
			FrameHeader header;
			float GPSheight;         ///<GPS����
			float GPSlat;            ///<GPSγ��
			float GPSlong;           ///<GPS����
			uint8_t S_or_N;           ///<GPS�ϱ�γ
			uint8_t E_or_W;           ///<GPS������
			uint8_t statelite;        ///<GPS������
			uint8_t hour;             ///<GPSʱ
			uint8_t minute;           ///<GPS��
			uint8_t sec;              ///<GPS��
			uint8_t day;              ///<GPS��
			uint8_t month;            ///<GPS��
			uint16_t year;            ///<GPS��
			uint16_t obligate1;       ///<Ԥ��
			uint32_t obligate2;       ///<Ԥ��
			uint32_t RFSOC_PS_ver;    ///<RFSOC_PS����汾
			uint32_t RFSOC_PL_ver;    ///<RFSOC_PL����汾
			uint32_t RFSOC_det;       ///<RFSOC�ӿ��Լ�
			uint32_t DSP_ver;         ///<DSP����汾
			uint32_t DSP_det;         ///<DSPӲ���ӿ��Լ�
			uint32_t microWave_det;   ///<΢�����ջ��Լ�
			uint32_t temperature;     ///<�¶� ��Ч
			uint32_t reserved[11];    ///<Ԥ��
			uint32_t checkSum;        ///<У���
		};

		/**
		* @brief ����/ֹͣ����ش�����֡
		*/
		struct StartStopFrame
		{
			FrameHeader header;
			float GPSheight;          ///<GPS����
			float GPSlat;             ///<GPSγ��
			float GPSlong;            ///<GPS����
			uint8_t SorN;             ///<GPS�ϱ�γ
			uint8_t EorW;             ///<GPS������
			uint8_t statelite;        ///<GPS������
			uint8_t hour;             ///<GPSʱ
			uint8_t minute;           ///<GPS��
			uint8_t sec;              ///<GPS��
			uint8_t day;              ///<GPS��
			uint8_t month;            ///<GPS��
			uint16_t year;            ///<GPS��
			uint16_t msec;            ///<����
			uint32_t obligate2;       ///<Ԥ��
			uint32_t frq;             ///<Ŀ��Ƶ��
			float azi;                ///<Ŀ�귽λ��
			float ele;                ///<Ŀ�긩����
			uint32_t LO_RF;           ///<��ǰ����Ƶ�α���
			uint32_t scan_index;      ///<ɨ�����к�
			int32_t amp;              ///<Ŀ���źŹ��� int32_t
			uint32_t type;            ///<Ŀ����Ƹ�ʽ
			uint32_t fre_num;         ///<Ŀ����Ƶ������
			uint32_t PW_num;          ///<Ŀ������������
			uint32_t PRI_num;         ///<Ŀ���ظ�����������
			uint16_t fre[10];         ///<��Ƶ����ֵ
			uint16_t pw[10];          ///<��������ֵ
			uint16_t pri[10];         ///<�ظ����ڲ���ֵ
			uint16_t temperature;     ///<Ӳ���¶�
			uint16_t Vcc_PL;          ///<��ѹ
			uint16_t Vcc_LOC;         ///<��ѹ
			uint16_t obligate3;       ///<Ԥ��
			float head;               ///<GI��λ
			float pitch;              ///<GI����
			float roll;               ///<���
			float azi_j0;             ///<�����ķ�λ��
			float ele_j0;             ///<�����ĸ�����
			float amp_max;            ///<�������ֵ
			float amp_min;            ///<������Сֵ
			float amp_mean;           ///<���Ⱦ�ֵ
			uint16_t grid_pulse_num;    ///<��ǰ���а������������
			uint16_t cluster_pulse_num; ///<ǰ��������ѡ�����������
			uint16_t cw_yn;             ///<��������־0���壬1������
			uint16_t frq_max;           ///<��ǰ����Ƶ�����ֵ
			uint16_t frq_min;           ///<��ǰ����Ƶ����Сֵ
			uint16_t usResv1;           ///<Ԥ��
			uint32_t reserved[12];      ///<Ԥ��
			uint32_t checkSum;          ///<У���
		};

		/**
		* @brief �������ٽ���ش�����֡
		*/
		struct LockTrackFrame
		{
			FrameHeader header;
			float GPSheight;          ///<GPS����
			float GPSlat;             ///<GPSγ��
			float GPSlong;            ///<GPS����
			uint8_t SorN;             ///<GPS�ϱ�γ
			uint8_t EorW;             ///<GPS������
			uint8_t statelite;        ///<GPS������
			uint8_t hour;             ///<GPSʱ
			uint8_t minute;           ///<GPS��
			uint8_t sec;              ///<GPS��
			uint8_t day;              ///<GPS��
			uint8_t month;            ///<GPS��
			uint16_t year;            ///<GPS��
			uint16_t obligate1;       ///<Ԥ��
			uint32_t obligate2;       ///<Ԥ��
			uint32_t frq;             ///<Ŀ��Ƶ��
			float azi;                ///<Ŀ�귽λ��
			float ele;                ///<Ŀ�긩����
			uint32_t LO_RF;           ///<��ǰ����Ƶ�α���
			uint32_t scan_index;      ///<ɨ�����к�
			int32_t amp;              ///<Ŀ���źŹ���
			uint32_t type;            ///<Ŀ����Ƹ�ʽ
			uint32_t fre_num;         ///<Ŀ����Ƶ������
			uint32_t PW_num;          ///<Ŀ������������
			uint32_t PRI_num;         ///<Ŀ���ظ�����������
			uint16_t fre[10];         ///<��Ƶ����ֵ
			uint16_t pw[10];          ///<��������ֵ
			uint16_t pri[10];         ///<�ظ����ڲ���ֵ
			uint16_t temperature;     ///<Ӳ���¶�
			uint16_t Vcc_PL;          ///<��ѹ
			uint16_t Vcc_LOC;         ///<��ѹ
			uint16_t obligate3;       ///<Ԥ��
			float head;               ///<GI��λ
			float pitch;              ///<GI����
			float roll;               ///<���
			float azi_j0;             ///<�����ķ�λ��
			float ele_j0;             ///<�����ĸ�����
			float amp_max;            ///<�������ֵ
			float amp_min;            ///<������Сֵ
			float amp_mean;           ///<���Ⱦ�ֵ
			uint32_t reserved[15];    ///<Ԥ��
			uint32_t checkSum;        ///<У���
		};

		/**
		* @brief ��λ����ش�����֡
		*/
		struct ResetFrame
		{
			FrameHeader header;
			uint32_t reserved[25];    ///<Ԥ��
			uint32_t checkSum;        ///<У���
		};

		/**
		* @brief �������ý���ش�����֡
		*/
		struct ParamConfFrame
		{
			FrameHeader header;
			uint32_t reserved[25];    ///<Ԥ��
			uint32_t checkSum;        ///<У���
		};

		/**
		* @brief GPSģ�����ý���ش�����֡
		*/
		struct GPSConfFrame
		{
			FrameHeader header;
			uint32_t reserved[25];    ///<Ԥ��
			uint32_t checkSum;        ///<У���
		};

		/**
		* @brief ��������У׼����ش�����֡
		*/
		struct CompassCalFrame
		{
			FrameHeader header;
			uint32_t reserved[25];    ///<Ԥ��
			uint32_t checkSum;        ///<У���
		};

		/**
		* @brief ���ڵ�IP���ý���ش�ָ������֡
		*/
		struct IpConfFrame
		{
			FrameHeader header;
			uint32_t reserved[25];    ///<Ԥ��
			uint32_t checkSum;        ///<У���
		};

		/**
		* @brief �͹��Ľ���ش�����֡
		*/
		struct LowPowerConFrame
		{
			FrameHeader header;
			uint32_t reserved[25];    ///<Ԥ��
			uint32_t checkSum;        ///<У���
		};

		/**
		* @brief ���ſ��ƽ���ش�����֡
		*/
		struct WaveGateSwitchFrame
		{
			FrameHeader header;
			uint32_t reserved[25];    ///<Ԥ��
			uint32_t checkSum;        ///<У���
		};

		/**
		* @brief AGC���ƽ���ش�����֡
		*/
		struct AgcControlFrame
		{
			FrameHeader header;
			uint32_t reserved[25];    ///<Ԥ��
			uint32_t checkSum;        ///<У���
		};

		/**
		* @brief ������޿��ƽ���ش�����֡
		*/
		struct DetectThresholdFrame
		{
			FrameHeader header;
			uint32_t reserved[25];    ///<Ԥ��
			uint32_t checkSum;        ///<У���
		};

		/**
		* @brief �������¿��ƽ���ش�����֡
		*/
		struct SoftwareUpdateFrame
		{
			FrameHeader header;
			uint32_t reserved[25];   ///<Ԥ��
			uint32_t checkSum;       ///<У���
		};

		/**
		* @brief �豸״̬��ѯ����ش�����֡
		*/
		struct DeviceStatusSearchFrame
		{
			FrameHeader header;
			uint32_t reserved[25];   ///<Ԥ��
			uint32_t checkSum;       ///<У���
		};

		/**
		* @brief ��Уָ����ƽ���ش�����֡
		*/
		struct StandardCalibFrame
		{
			FrameHeader header;
			uint32_t Fre;
			uint32_t reserved[24];  ///<Ԥ��
			uint32_t checkSum;		///<У���
		};

		/**
        * @brief ��ʱָ����ƽ���ش�����֡
        */
		struct TimeDescribe
		{
			uint32_t sec;   ///<ʱ����
			uint32_t msec;  ///<ʱ�����
		};

		struct TimeDiff
		{
			int32_t sec;   ///<ʱ����
			int32_t msec;  ///<ʱ�����
		};

		struct TimeCalibFrame
		{
			FrameHeader header;  
			TimeDescribe T1_time;   ///<T1ʱ��
			TimeDescribe T2_time;   ///<T2ʱ��
			TimeDescribe T3_time;   ///<T3ʱ��
			TimeDescribe T4_time;   ///<T4ʱ��
			TimeDiff Diff_time;     ///<ʱ��� 
			float GPSheight;         ///<GPS����
			float GPSlat;            ///<GPSγ��
			float GPSlong;           ///<GPS����
			uint8_t S_or_N;           ///<GPS�ϱ�γ
			uint8_t E_or_W;           ///<GPS������
			uint8_t statelite;        ///<GPS������
			uint8_t hour;             ///<GPSʱ
			uint8_t minute;           ///<GPS��
			uint8_t sec;              ///<GPS��
			uint8_t day;              ///<GPS��
			uint8_t month;            ///<GPS��
			uint16_t year;            ///<GPS��
			uint16_t msec;            ///<GPS����
			uint32_t reserved[9];     ///<Ԥ��
			uint32_t checkSum;	      ///<У���
		};

		/**
		* @brief ��������ָ�����
		*/
		struct LockTrackParam
		{
			uint32_t listCount;          ///<������ʼƵ��
			uint32_t indexNum;           ///<��������Ƶ��
			uint32_t startFrequency;     ///<������ʼƵ��
			uint32_t endFrequency;       ///<��������Ƶ��
			uint32_t searchTime;         ///<����ѹ��ʱ��
			uint32_t searchBand;         ///<��������
			uint32_t pulseWidthStart;    ///<��������ֵ
			uint32_t pulseWidthEnd;      ///<��������ֵ
			uint32_t periodRepeatStart;  ///<�ظ���������ֵ
			uint32_t periodRepeatEnd;    ///<�ظ���������ֵ
			uint32_t targetSignalType;   ///<Ŀ���ź�����
		};

		/**
		* @brief ��������ָ�����
		*/
		struct ParamConfParam
		{
			uint32_t listCount;          ///<������ʼƵ��
			uint32_t indexNum;           ///<��������Ƶ��
			uint32_t startFrequency;     ///<������ʼƵ��
			uint32_t endFrequency;       ///<��������Ƶ��
			uint32_t searchTime;         ///<����ѹ��ʱ��
			uint32_t searchBand;         ///<��������
			uint32_t pulseWidthStart;    ///<��������ֵ
			uint32_t pulseWidthEnd;      ///<��������ֵ
			uint32_t periodRepeatStart;  ///<�ظ���������ֵ
			uint32_t periodRepeatEnd;    ///<�ظ���������ֵ
			uint32_t targetSignalType;   ///<Ŀ���ź�����
			uint32_t noiseThreshold;     ///<��������
		};
#pragma pack()

		/**
		* @brief ͨ��״̬
		*/
		enum ChannelState
		{
			CONNECTED,     ///<����
			DISCONNECTED,  ///<�Ͽ�����
		};

		/**
		* @brief �ش��տؽ������֡
		*/
		struct ZKResult
		{
			SelfDetectFrame* selfdetectframe; ///<�Լ���
			StartStopFrame* startstopframe;   ///<����ֹͣ���
			LockTrackFrame* locktrackframe;   ///<�������ٽ��
		};

		/**
		* @brief �ش�ң������֡
		*/
		struct YCResult
		{
			size_t length;   ///<ң�����ݳ���
			uint32_t* data;  ///<ң��������ʼ��ַ
		};

		/**
		* @brief �Զ�������
		*/
		typedef void CHANNEL_STATE_CALLBACK(ChannelState state, void* userPointer);
		typedef void ZK_RESULT_CALLBACK(const ZKResult* zkResult, void* userPointer);
		typedef void YC_RESULT_CALLBACK(const YCResult* ycResult, void* userPointer);

		/**
		* @brief �ۿػص���������
		*/
		struct ZKCallbacks
		{
			CHANNEL_STATE_CALLBACK* cbCon;
			ZK_RESULT_CALLBACK* cbResult;
		};

		/**
		* @brief ң��ص���������
		*/
		struct YCCallbacks
		{
			CHANNEL_STATE_CALLBACK* cbCon;
			YC_RESULT_CALLBACK* cbResult;
		};

		/**
		* @brief �ص���������
		*/
		struct SessionHandler
		{
			void* userPointer;
			ZKCallbacks cbZK;
			YCCallbacks cbYC;
		};

		/**
		* @brief ��ʼ���� ʹ�ÿ�ʱ����һ�����õĺ�����������һ��
		*/
		POSITIONSOCKET_API PS_Error PS_InitSSLib();

		/**
		* @brief �رտ⣬���һ�����õĺ�����������һ��
		* @details ���ô˺���֮�󣬳���PS_InitSSLib(),�����ٵ�������C�ӿں���
		*/
		POSITIONSOCKET_API PS_Error PS_DeinitSSLib();

		/**
		* @brief ��������
		* @param[out] fd ���
		* @param[in] peerAddress ��������ַIP�Ͷ˿��ַ���������"192.168.1.33:8080"
		* @param[in] handler �ص��������ϣ��ص������ɿͻ���������Ӧ��Ӧ����
		* @return Error
		* @retval ERR_NONE ERR_CONNECT
		*/
		POSITIONSOCKET_API PS_Error PS_CreateConnect(int* fd, const char* peerAddress, const SessionHandler* handler);

		/**
		* @brief �����Լ�ָ��
		* @param[out] selfdetectframe �Լ�ش����
		* @param[in] fd ���
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendSelfDetect(int fd);

		/**
		* @brief ��������/ָֹͣ��
		* @param[in] fd ���
		* @param[in] option 1������������0:ֹͣ����
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendStartStop(int fd, uint32_t option);

		/**
		* @brief ������������ָ��
		* @param[in] fd ���
		* @param[in] locktrack ��������ָ�����
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendLockTrack(int fd, const LockTrackParam* locktrack);

		/**
		* @brief ���͸�λָ��
		* @param[out] resetframe ��λ�ش����
		* @param[in] fd ���
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendReset(ResetFrame* resetframe, int fd);

		/**
		* @brief ���Ͳ�������ָ��
		* @param[out] paramconfframe �������ûش����
		* @param[in] fd ���
		* @param[in] paramconf ��������ָ�����
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendParaConf(ParamConfFrame* paramconfframe, int fd, const ParamConfParam* paramconf);

		/**
		* @brief ����GPSģ������ָ��
		* @param[out] gpsconfframe GPSģ�����ûش����
		* @param[in] fd ���
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendGPSModConf(GPSConfFrame* gpsconfframe, int fd);

		/**
		* @brief ���͵�������У׼ָ��
		* @param[out] compasscalframe ��������У׼�ش����
		* @param[in] fd ���
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendCompassCalib(CompassCalFrame* compasscalframe, int fd);

		/**
		* @brief ���ͼ��ڵ�IP����ָ��
		* @param[out] ipconfframe  ���ڵ�IP���ûش����
		* @param[in] fd ���
		* @param[in] address IP��ַ
		* @return Error
		* @retval ERR_NONE
		*/
		POSITIONSOCKET_API PS_Error PS_SendIPConf(IpConfFrame* ipconfframe, int fd, uint32_t address);

		/**
		* @brief ���͵͹���ָ��
		* @param[out] lowpowerconframe  �͹��Ļش����
		* @param[in] fd ���
		* @param[in] option 1������͹��ģ�0:�˳��͹���
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendLowPower(LowPowerConFrame* lowpowerconframe, int fd, uint32_t option);

		/**
		* @brief ���Ͳ��ſ���ָ��
		* @param[out] wavegateswitchframe  ���ſ��ƻش����
		* @param[in] fd ���
		* @param[in] option 1������0:��
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendWaveGate(WaveGateSwitchFrame* wavegateswitchframe, int fd, uint32_t option);

		/**
		* @brief ����AGC����ָ��
		* @param[out] agccontrolframe  AGC���ƻش����
		* @param[in] fd ���
		* @param[in] option 1��������0:�ջ�
		* @param[in] agcvalue AGC��ֵ
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendAGCCtrl(AgcControlFrame* agccontrolframe, int fd, uint32_t option, uint32_t agcvalue);

		/**
		* @brief ���ͼ�����޿���ָ��
		* @param[out] detectthresholdframe  ������޿��ƻش����
		* @param[in] fd ���
		* @param[in] value �������ֵ
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendDetectThrd(DetectThresholdFrame* detectthresholdframe, int fd, uint32_t value);

		/**
		* @brief ������������ָ��
		* @param[out] softwareupdateframe  �������¿��ƻش����
		* @param[in] fd ���
		* @param[in] option �������¿�ʼ����ָ�0xAA����ʼ��0xBB:����
		* @param[in] type �������� 0xAA:FPGA������0xDD:DSP���� 0xCA:У׼����
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendSoftwareUpdate(SoftwareUpdateFrame* softwareupdateframe, int fd, uint32_t option, uint32_t type);

		/**
		* @brief �����豸״̬��ѯָ��
		* @param[out] devicestatussearchframe �豸״̬��ѯ�ش����
		* @param[in] fd ���
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendDeviceStatusSearch(DeviceStatusSearchFrame* devicestatussearchframe, int fd);

		/**
		* @brief ���ͱ�У����ָ��
		* @param[out] standardcalibframe ��Уָ����ƻش����
		* @param[in] fd ���
		* @param[in] frqvalue Ƶ��ֵ
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendStandardCalib(StandardCalibFrame* standardcalibframe, int fd, uint32_t frqvalue);

		/**
		* @brief ���Ͷ�ʱָ��
		* @param[out] timeCalibFrame ��ʱָ����ƻش����
		* @param[in] fd ���
		* @param[in] ntpAddress ��ʱ������ip
		* @return Error
		* @retval ERR_NONE ERR_SEND ERR_OVERTIME
		*/
		POSITIONSOCKET_API PS_Error PS_SendTimeCalib(TimeCalibFrame* timeCalibFrame, int fd, uint32_t ntpAddress);

		/**
		* @brief �ر�����
		* @param[in] fd ���
		* @return Error
		* @retval ERR_NONE
		*/
		POSITIONSOCKET_API PS_Error PS_CloseConnect(int fd);
}

//#ifdef __cplusplus
//}
//#endif