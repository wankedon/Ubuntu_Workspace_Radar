/**
 * @file SuperSocketAPI.h
 
 * @par Copyright (c):�е�Ƶ���ʮһ�о��� װ����ҵ��
 * ��Ȩ���У�δ�����ɣ����ø��ơ�������ת��
 
 * @brief SuperSocket��������壬����C API
 
 * @author yangqing
 
 * @date 2020:03:26
 
 * @note ����vcpkg�ṩ��ͷ�ļ��Ͷ�̬��
 
 * @version <1.0.0>
 
 */

/**
 * @mainpage SuperSocket��
 * @section CAPI c style API ʹ�÷���
 * @subsection c_step1 Step 1: ����SuperSocketAPI.h��SuperSocket.h��ʹ��SS_InitSSLib()��ʼ����
 * @subsection c_step2 Step 2: ����ip��ַ�ͻص��������ϣ�����SuperSocket���캯��������һ��SuperSocket����
 * @subsection c_step3 Step 3: ���øö��������ݣ�ͨ����Ļص���������������
 *
 * @section CppAPI c++ style APIʹ�÷���
 * @subsection cpp_step1 Step 1: ����SuperSocketAPI.h��ʹ��SS_InitSSLib()��ʼ����
 * @subsection cpp_step2 Step 2: ����ip��ַ�ͻص��������ϣ�����SS_CreateSocket�����һ��fd������
 * @subsection cpp_step3 Step 3: ���ø�fd�������ݣ�ͨ����Ļص���������������
 * @subsection cpp_step4 Step 4: ���ٴ�������ʱ������SS_DestroySocket()�ر�����
 * ## ����ʹ�ÿ�ʱ����SS_DeinitSSLib()�رտ⣬�ͷ���Դ
 */
#pragma once
#ifdef WIN32
#ifdef SUPERSOCKET_EXPORTS
#define SUPERSOCKET_API __declspec(dllexport)
#else
#define SUPERSOCKET_API __declspec(dllimport)
#endif
#else
#define SUPERSOCKET_API
#endif

namespace SuperSocketLib
{
	/**
	 * @brief API����ֵ���������ʶ
	 *
	 */
	enum SSErrorCode
	{
		SS_ERR_NONE = 0,	///<�޴���
		SS_ERR_INVALID_HANDLE = -1,	///< ��Ч�ľ�������C API
		SS_ERR_NOT_CONNECTED = -2,	///< ��δ������Ч����
		SS_ERR_HANDLE_CLOSED = -3,	///< ����ر�
		SS_ERR_SEND = -4,			///< �������ݹ��̳��ִ���
		SS_ERR_NOT_IMPLEMENTED = -5,	///<API δʵ��
		SS_ERR_INIT = -6,			///< ���ʼ������
		SS_ERR_CREATE = -7,			///< socket��������
	};

	/**
	* @brief ��������ݿ�ṹ��
	*/
	struct NetBlock
	{
		size_t len;	///< ���ݿ鳤��
		void* addr;	///< ���ݿ��ַ
	};
	
	struct NodeId
	{
		bool operator==(const NodeId& id) const
		{
			return (this->idLength == id.idLength)
				&& (memcmp(id.id, this->id, this->idLength) == 0);
		}
		bool operator<(const NodeId& id) const
		{
			if (id.idLength != this->idLength)
				return this->idLength < id.idLength;
			else
				return (memcmp(this->id, id.id, this->idLength) < 0);
		}
		NodeId()
		{
			strcpy(id, "invalidNodeId");
			idLength = 0;
		}
		NodeId(const void* data, size_t length)
		{
			if (length + 1 < sizeof(id))
			{
				idLength = length;
				memcpy(id, data, length);
				id[idLength] = 0;
			}
			else
			{
				strcpy(id, "invalidNodeId");
				idLength = 0;
			}
		}
		size_t idLength;
		char id[128];
	};

	typedef void SS_CONNECT_CALLBACK(const NodeId* id, void* userPointer);
	typedef void SS_DISCONNECT_CALLBACK(const NodeId* id, void* userPointer);
	typedef void SS_SEND_CALLBACK(SSErrorCode err, const NodeId* to, void* userPointer);
	typedef void SS_RECEIVE_CALLBACK(const NetBlock* data, const NodeId* from, void* userPointer);

	/**
	* @brief �ص���������
	*
	*/
	struct EventHandler
	{
		void* userPointer;
		SS_CONNECT_CALLBACK* cbConnect;	///<���ӻص�����socket����������ʱ����
		SS_DISCONNECT_CALLBACK* cbDisconnect;	///<�Ͽ��ص�����socket�Ͽ�ʱ����
		SS_SEND_CALLBACK* cbSend;	///<�������ݻص�������ѿͻ������ݿ��͵�ϵͳ������ʱ����
		SS_RECEIVE_CALLBACK* cbReceive;	///<�������ݻص�����socket���յ�����ʱ���ã��ͻ��ӻص�������DataBlock��ȡ����
	};

	/**
	 * @brief ��ʼ���� ʹ�ÿ�ʱ����һ�����õĺ�����������һ��
	 */
	SUPERSOCKET_API SSErrorCode SS_InitSSLib();

	/**
	 * @brief �رտ⣬���һ�����õĺ�����������һ��
	 * @details ���ô˺���֮�󣬳���SS_InitSSLib(),�����ٵ�������C�ӿں���
	 */
	SUPERSOCKET_API SSErrorCode SS_DeinitSSLib();


	SUPERSOCKET_API SSErrorCode SS_CreateServerSocket(int* fd, const char* listenAddr, const EventHandler* handler);
	/**
	 * @brief ����һ��socket������һ������
	 * @param[out] fd �ú�������ʱ����socket�������ò���
	 * @param[in] peerAddr ��������ַIP�Ͷ˿��ַ���������"192.168.1.33:8080"
	 * @param[in] callbacks �ص��������ϣ��ص������ɿͻ���������Ӧ���������¼�����Ӧ����
	 * @return SSError ������
	 * @retval SS_ERR_NONE or SS_ERR_CREATE
	 */
	SUPERSOCKET_API SSErrorCode SS_CreateClientSocket(int* fd, const char* peerAddr, const EventHandler* handler);

	/**
	 * @brief ����һ��socket
	 * @param[int] fd socket���
	 * @return SSError ������
	 * @retval SS_ERR_NONE or SS_ERR_INVALID_HANDLE
	 */
	SUPERSOCKET_API SSErrorCode SS_DestroySocket(int fd);

	/**
	 * @brief ��������
	 * @detail �ͻ����븺�𽫴����͵���������һ��DataBlock��Ȼ���䴫��ú������ɿ⸺���͸�Զ��
	 * @param[in] fd socket���
	 * @param[in] block �����͵����ݿ�
	 * @return SSError ������
	 * @retval SS_ERR_NONE or SS_ERR_INVALID_HANDLE or SS_ERR_SEND
	 */
	SUPERSOCKET_API SSErrorCode SS_SendBlock(int fd, const NetBlock* data, const NodeId* to);
}

