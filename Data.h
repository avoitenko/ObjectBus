#pragma once

#include <mutex>

#define LOCK(x) (std::lock_guard<std::mutex> lock(x))

//+------------------------------------------------------------------+
struct TData
{
public:
	TData() = default;
	TData(double _value) :value(_value) {}
private:
	double value;
};
