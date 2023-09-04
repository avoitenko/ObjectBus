#pragma once

#include "ObjectBus.h"
#include "Data.h"

//class CObjectBus;

//+------------------------------------------------------------------+
class CObjectReader
{
    CObjectBus& bus;
    size_t index;

public:
    
    //+------------------------------------------------------------------+
    CObjectReader(CObjectBus& bus) :
        bus(bus), 
        index(bus.readIndex++ % bus.buffer.size()) 
    {
    
    }
    
    //+------------------------------------------------------------------+
    TData ReadNext()
    {
        std::unique_lock<std::mutex> lock(bus.mutex);
        bus.condVariable.wait(lock, [this] { return index != bus.writeIndex; });
        TData item = bus.buffer[index];
        index = (index + 1) % bus.buffer.size();
        if (index == bus.writeIndex) {
            throw std::runtime_error("Read operation is too slow");
        }
        return item;
    }
    
    //+------------------------------------------------------------------+
    void StopReading()
    {
        bus.condVariable.notify_all();
    }
};