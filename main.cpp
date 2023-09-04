#include <iostream>
#include <thread>
#include "ObjectBus.h"
#include "ObjectReader.h"

//+------------------------------------------------------------------+
inline void write_to_bus(CObjectBus& bus, TData data)
{
	bus.Write(data);
}

//+------------------------------------------------------------------+
inline void read_from_bus(CObjectReader& reader)
{
	try
	{
		TData data = reader.ReadNext();
	}
	catch (std::runtime_error& e)
	{

		//--- error handling
		printf(e.what());
	}
}


//+------------------------------------------------------------------+
int main()
{
	//---
	CObjectBus bus(100);
	CObjectReader reader(bus);

	//---
	std::thread thWriter(write_to_bus, std::ref(bus), TData(123));
	std::thread thReader(read_from_bus, std::ref(reader));

	//---
	thWriter.join();
	thReader.join();

	//---
	return 0;
}