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
	std::vector<TData> buffer;
	std::condition_variable condVariable;
	std::mutex mutex;
	size_t writeIndex = 0;
	std::atomic<size_t> readIndex = 0;
	
	//+------------------------------------------------------------------+
	CObjectBus(size_t size) :
		buffer(size)
	{

	}

	//+------------------------------------------------------------------+
	void Write(TData item)
	{
		std::lock_guard<std::mutex> lock(mutex);
		buffer[writeIndex] = item;
		writeIndex = (writeIndex + 1) % buffer.size();
		condVariable.notify_all();
	}
};
