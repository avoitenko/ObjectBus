#pragma once

#include <condition_variable>
#include <vector>
#include <atomic>
#include <exception>
#include "Data.h"

//+------------------------------------------------------------------+
class CObjectBus
{
public:
	std::vector<TData> circleBuffer;
	std::condition_variable condVariable;
	std::mutex mutex;
	std::atomic<size_t> readIndex = 0;
	std::atomic<size_t> writeIndex = 0;

	//+------------------------------------------------------------------+
	CObjectBus(size_t size) :
		circleBuffer(size)
	{

	}

	//+------------------------------------------------------------------+
	size_t Write(TData item)
	{
		LOCK(mutex);
		//std::unique_lock<std::mutex> lock(mutex);
		//condVariable.wait(lock, [this] { return (writeIndex + 1) % circleBuffer.size() != readIndex.load(); });
		circleBuffer[writeIndex] = item;
		writeIndex = (writeIndex + 1) % circleBuffer.size();
		condVariable.notify_all();
		//---
		return writeIndex;
	}
};
