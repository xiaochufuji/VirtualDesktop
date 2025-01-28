#pragma once
#include "VirtualDesktop.h"
#include <thread>
#include <atomic>
class TestUnit
{
public:
	TestUnit() = delete;
	TestUnit(int choice = 0);
	~TestUnit();
	void interfaceTest();
	void loopInterfaceTest();
	static void PrintMemoryUsage();
	static void MemoryMonitorThread();

private:
	xiaochufuji::Implement imp;
	static std::atomic<bool> keepRunning;
	std::thread monitorThread; 
};

