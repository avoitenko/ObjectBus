#pragma once

#include <mutex>
#include <format>

#define LOCK(x) std::lock_guard<std::mutex> lock(x)
std::mutex printMutex;

//+------------------------------------------------------------------+
struct TData
{
public:
	TData() = default;
	TData(const int64_t _value) : value(_value) {}
	int64_t value;
	//size_t index;
};

//+------------------------------------------------------------------+
template <typename S, typename... Args>
void print(const S& format, Args&&... args)
{
	LOCK(printMutex);
	std::string formattedText;

	//---
	try
	{
		formattedText = std::vformat(format, std::make_format_args(args...));
	}
	catch (std::exception& e)
	{
		formattedText = "exception " + std::string(e.what());
	}

	//--- thread number
	std::thread::id threadId = std::this_thread::get_id();
	std::size_t threadNumber = std::hash<std::thread::id>{}(threadId);

	//---
	std::string strOut = std::format("thread {:<8} {}", (threadNumber & 0xFFFFFF), formattedText);
	std::cout << strOut.c_str() << std::endl;
}
