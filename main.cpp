#include <iostream>
#include <thread>
#include <chrono>
#include <random>

#include "ObjectBus.h"
#include "ObjectReader.h"

//+------------------------------------------------------------------+
inline void busWrite(CObjectBus& bus)
{
	std::random_device rd;
	std::mt19937 generator(rd()); // Mersenne Twister engine with a seed from random_device

	while (true)
	{
		//---
		std::uniform_int_distribution<int> distribution(0, 32767);
		int value = distribution(generator);

		//---
		size_t index = bus.Write(TData(value));
		print("write index: {:<3} value: {}", index, value);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

//+------------------------------------------------------------------+
inline void busRead(CObjectReader& reader)
{
	reader.StartReading();

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		try
		{
			TData data = reader.ReadNext();

			print("read  index: {:<3} value: {}", reader.Index(), data.value);
		}
		catch (std::runtime_error& e)
		{
			//--- error handling
			print("read exception: {}", e.what());
		}
	}
}


//+------------------------------------------------------------------+
int main()
{
	//---
	CObjectBus bus(100);
	CObjectReader reader(bus);

	//---
	std::thread thWriter1(busWrite, std::ref(bus));
	std::thread thWriter2(busWrite, std::ref(bus));
	thWriter1.join();
	thWriter2.join();

	//---
	/*
	std::thread thReader1(busRead, std::ref(reader));
	std::thread thReader2(busRead, std::ref(reader));

	thReader1.join();
	thReader2.join();
	*/

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//reader.StopReading();

	//---
	return 0;
}