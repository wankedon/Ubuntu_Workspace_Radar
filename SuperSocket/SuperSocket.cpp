/**
 * @file SuperSocket.cpp
 
 * @par Copyright (c):???????????????? ????????
 * ???????????????????????????????????
 
 * @brief SuperSocket??????
 
 * @author yangqing
 
 * @date 2020:03:26
 
 * @note ????vcpkg??????????????
 
 * @version <1.0.0>
 
 */
#include "stdafx.h"
#include "SuperSocket.h"
#include "SuperSocketImpl.h"

SuperSocket::SuperSocket(const std::string& peerAddress, const SSEventCallback& callbacks)
{
	_impl = new SuperSocketImpl(peerAddress, callbacks); ///???????
}

SuperSocket::~SuperSocket()
{
	close();///????????????????????
}

SSError SuperSocket::send(const DataBlock& block)
{
	return _impl->send(block);
}

void SuperSocket::close()
{
	if (_impl)
	{
		delete _impl; ///??????????
		_impl = nullptr;
	}
}
