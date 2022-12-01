/**
 * @file Actor.cpp
 
 * @par Copyright (c):�е�Ƶ���ʮһ�о��� װ����ҵ��
 * ��Ȩ���У�δ�����ɣ����ø��ơ�������ת��
 
 * @brief actor��ʵ��
 
 * @author yangqing
 
 * @date 2020:03:26
 
 * @note ����vcpkg�ṩ��ͷ�ļ��Ͷ�̬��
 
 * @version <1.0.0>
 
 */
#include "stdafx.h"
#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor(void)
{
	
}

/**
 * @brief ��̬������Ϊpipe�ĺ�̨�̺߳�������װactorFunc
 * @detail
 * @param[in] pipe actor��pipe socket
 * @param[in] args this ָ�� 
 * @return 
 * @retval 
 */
void Actor::actorFuncWrap(zsock_t *pipe, void *args)
{
	Actor* self = (Actor*)args;
	self->actorFunc(pipe);
}

/**
 * @brief ���麯��
 * @details ������ʵ����һ������������������̨�̷߳������ź�
 * @param[int] pipe ����socket
 * @return 
 * @retval 
 */
void Actor::actorFunc(zsock_t *pipe)
{
	zsock_signal(pipe, 0); ///0 is OK
}

/**
 * @brief ��������
 * @details
 * @param[int] msg �����͵���Ϣ
 * @param[out] 
 * @return 
 * @retval 
 */
int Actor::sendMsg(zmsg_t** msg)
{
	return zmsg_send(msg, actor);
}


/**
 * @brief ��������
 * @details ���ò���
 * @param[int] 
 * @param[out] 
 * @return zmsg_t*
 * @retval ���յ�����Ϣ
 */
zmsg_t* Actor::receiveMsg()
{
	return zmsg_recv(actor);
}
