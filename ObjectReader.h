#pragma once

#include "ObjectBus.h"
#include "Data.h"

//+------------------------------------------------------------------+
class CObjectReader
{
	CObjectBus& bus;
	size_t index;

public:
	size_t Index() { return index; }
	
	//+------------------------------------------------------------------+
	CObjectReader(CObjectBus& bus) :
		bus(bus),
		index(bus.readIndex++ % bus.circleBuffer.size())
	{
		print("CObjectReader");
	}

	//+------------------------------------------------------------------+
	size_t StartReading()
	{
		LOCK(bus.mutex);
		if (bus.writeIndex == 0)
		{
			index = bus.circleBuffer.size() - 1;
		}
		else
		{
			index = bus.writeIndex - 1;
		}
		return index;
	}

	//+------------------------------------------------------------------+
	TData ReadNext()
	{
		//---
		LOCK(bus.mutex);
		//bus.condVariable.wait(lock, [this] { return index != bus.writeIndex; });

		//---
		TData item = bus.circleBuffer[index];
		index = (index + 1) % bus.circleBuffer.size();
		if (index == bus.writeIndex)
		{
			throw std::runtime_error("slow reading");
		}

		//---
		//item.index = index;
		return item;
	}

	//+------------------------------------------------------------------+
	void StopReading()
	{
		bus.condVariable.notify_all();
	}
};