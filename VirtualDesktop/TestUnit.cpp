#include "TestUnit.h"
#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <thread>
#include <chrono>

#pragma region test function
namespace xiaochufujiTest {
	using namespace xiaochufuji;
	static void test0(Implement& imp, bool test = false)
	{
		if (!test) return;
#pragma region condition
#ifdef UNICODE
		_string _count = L"desktop conut: ";
		_string _currentDesktopGUID = L"current desktop guid: ";
		_string _guid = L"\tguid: ";
		_string _name = L"\tname: ";
		_string _wallpaper = L"\twallpaper: ";
		_string _index = L"\tindex: ";
#else
		_string _count = "conut: ";
		_string _currentDesktopGUID = "current desktop guid: ";
		_string _guid = "\tguid: ";
		_string _name = "\tname: ";
		_string _wallpaper = "\twallpaper: ";
		_string _index = "\tindex: ";
#endif
#pragma endregion
		PRINT << _count << imp.count() << std::endl;
		PRINT << _currentDesktopGUID << PrintGUID(imp.currentDesktop()) << std::endl;
		for (const auto& item : imp.allDesktopInfo())
		{
			PRINT << *item;
		}
		PRINT << std::endl;
	}
	static void test1(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.create().get() != nullptr)
			PRINT << "create successed..." << std::endl;
		else
			PRINT << "create failed..." << std::endl;
		PRINT << std::endl;
	}
	static void test2(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.remove(imp.count() - 1))
			PRINT << "remove successed..." << std::endl;
		else
			PRINT << "remove failed..." << std::endl;
		PRINT << std::endl;
	}
	static void test3(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.move(1))
			PRINT << "move successed..." << std::endl;
		else
			PRINT << "move failed..." << std::endl;
		PRINT << std::endl;
	}
	static void test4(Implement& imp, bool test = false)
	{
		if (!test) return;
#pragma region condition
#ifdef UNICODE 
		_string str = L"test set name";
#else
		_string str = "test set name";
#endif
#pragma endregion
		if (imp.setName(0, str))
			PRINT << "setName successed..." << std::endl;
		else
			PRINT << "setName failed..." << std::endl;
		PRINT << std::endl;
	}
	static void test5(Implement& imp, bool test = false)
	{
		if (!test) return;
#pragma region condition
#ifdef UNICODE 
		_string path = LR"(D:\ASUS\Desktop\carousel1.jpg)";
#else
		_string path = R"(D:\ASUS\Desktop\carousel1.jpg)";
#endif
#pragma endregion
		if (imp.setWallpaper(1, path))
			PRINT << "setWallpaper successed..." << std::endl;
		else
			PRINT << "setWallpaper failed..." << std::endl;
		PRINT << std::endl;
	}
	static void test6(Implement& imp, bool test = false)
	{
		if (!test) return;
#pragma region condition
#ifdef UNICODE 
		_string path = LR"(D:\ASUS\Desktop\carousel3.jpg)";
#else
		_string path = R"(D:\ASUS\Desktop\carousel3.jpg)";
#endif
#pragma endregion
		if (imp.setAllWallpaper(path))
			PRINT << "setAllWallpaper successed..." << std::endl;
		else
			PRINT << "setAllWallpaper failed..." << std::endl;
		PRINT << std::endl;
	}
	static void test7(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.switchDesktop(2, true))
			PRINT << "switchDesktop successed..." << std::endl;
		else
			PRINT << "switchDesktop failed..." << std::endl;
		PRINT << std::endl;
	}
	static void test8(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.moveWindow(1, GetForegroundWindow()))
			PRINT << "moveWindow successed..." << std::endl;
		else
			PRINT << "moveWindow failed..." << std::endl;
		PRINT << std::endl;
	}
	static void test9(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.moveActiveWindow(1))
			PRINT << "moveActiveWindow successed..." << std::endl;
		else
			PRINT << "moveActiveWindow failed..." << std::endl;
		PRINT << std::endl;
	}
	static void test10(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.hasWindow(0, GetForegroundWindow()))
			PRINT << "hasWindow ..." << std::endl;
		else
			PRINT << "not hasWindow ..." << std::endl;
		if (imp.hasWindow(1, GetForegroundWindow()))
			PRINT << "hasWindow ..." << std::endl;
		else
			PRINT << "hasnoWindow ..." << std::endl;
		PRINT << std::endl;
	}
	static void test11(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.moveDesktop(0))
			PRINT << "moveDesktop successed ..." << std::endl;
		else
			PRINT << "moveDesktop failed ..." << std::endl;
		PRINT << std::endl;
	}
	static void test12(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.pinWindowByHwnd(((HWND)0x0000000000030432)))
			PRINT << "pinWindowByHwnd successed ..." << std::endl;
		else
			PRINT << "pinWindowByHwnd failed ..." << std::endl;
		PRINT << std::endl;
	}
	static void test13(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.unpinWindowByHwnd(((HWND)0x0000000000030432)))
			PRINT << "unpinWindowByHwnd successed ..." << std::endl;
		else
			PRINT << "unpinWindowByHwnd failed ..." << std::endl;
		PRINT << std::endl;
	}
	static void test14(Implement& imp, bool test = false)
	{
		if (!test) return;
		HWND chrome = (HWND)0x0000000000030432;
		if (imp.pinWindowByHwnd(chrome))
			PRINT << "pinWindowByHwnd successed ..." << std::endl;
		else
			PRINT << "pinWindowByHwnd failed ..." << std::endl;
		if (imp.ispinWindowByHwnd(chrome))
			PRINT << "is pin ..." << std::endl;
		else
			PRINT << "isn's pin..." << std::endl;
		if (imp.unpinWindowByHwnd(chrome))
			PRINT << "unpinWindowByHwnd successed ..." << std::endl;
		else
			PRINT << "unpinWindowByHwnd failed ..." << std::endl;
		if (imp.ispinWindowByHwnd(chrome))
			PRINT << "is pin ..." << std::endl;
		else
			PRINT << "isn's pin..." << std::endl;
		PRINT << std::endl;
	}
	static void test15(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.pinActiveWindow())
			PRINT << "pinActiveWindow successed ..." << std::endl;
		else
			PRINT << "pinActiveWindow failed ..." << std::endl;
		PRINT << std::endl;
	}
	static void test16(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.unpinActiveWindow())
			PRINT << "unpinActiveWindow successed ..." << std::endl;
		else
			PRINT << "unpinActiveWindow failed ..." << std::endl;
		PRINT << std::endl;
	}
	static void test17(Implement& imp, bool test = false)
	{
		if (!test) return;
		if (imp.pinActiveWindow())
			PRINT << "pinActiveWindow successed ..." << std::endl;
		else
			PRINT << "pinActiveWindow failed ..." << std::endl;
		if (imp.ispinActiveWindow())
			PRINT << "is active pin ..." << std::endl;
		else
			PRINT << "isn's active pin..." << std::endl;
		if (imp.unpinActiveWindow())
			PRINT << "unpinActiveWindow successed ..." << std::endl;
		else
			PRINT << "unpinActiveWindow failed ..." << std::endl;
		if (imp.ispinActiveWindow())
			PRINT << "is active pin ..." << std::endl;
		else
			PRINT << "isn's active pin..." << std::endl;
		PRINT << std::endl;
	}
	static void test18(Implement& imp, bool test = false)
	{
		if (!test) return;
		HWND clash = (HWND)0x0000000000020672;
		auto info = imp.findWindow(clash);
		if (info.get())
		{
			PRINT << *info;
		}
		PRINT << std::endl;
	}
	static void test19(Implement& imp, bool test = false)
	{
		if (!test) return;
		auto info = imp.getVirtualDesktop(0);
		if (info.get())
		{
			PRINT << *info;
		}
		PRINT << std::endl;
	}
	static void test20(Implement& imp, bool test = false)
	{
		if (!test) return;
#pragma region condition
#ifdef UNICODE 
		_string str = L"Desktop 3";
#else
		_string str = "Desktop 3";
#endif
#pragma endregion
		auto info = imp.getVirtualDesktop(str);
		if (info.get())
		{
			PRINT << *info;
		}
		PRINT << std::endl;
	}
	static void test21(Implement& imp, bool test = false)
	{
		if (!test) return;
#pragma region condition
#ifdef UNICODE 
		_string str = L"test";
#else
		_string str = "test";
#endif
#pragma endregion
		auto info = imp.getVirtualDesktopEx(str);
		if (info.get())
		{
			PRINT << *info;
		}
		PRINT << std::endl;
	}
};
#pragma endregion

std::atomic<bool> TestUnit::keepRunning = true;
TestUnit::TestUnit(int choice) : monitorThread(&TestUnit::MemoryMonitorThread)
{
	if (choice == 0)
		interfaceTest();
	else
		loopInterfaceTest();
}

TestUnit::~TestUnit()
{
	system("pause");
	keepRunning = false;  // 结束子线程循环
	if (monitorThread.joinable()) {
		monitorThread.join();
	}
	PRINT << "Memory monitoring stopped.\n";
}

void TestUnit::interfaceTest()
{
	xiaochufujiTest::test0(imp, true);
	xiaochufujiTest::test1(imp, true);
	xiaochufujiTest::test2(imp, true);
	xiaochufujiTest::test3(imp, true);
	xiaochufujiTest::test4(imp, true);
	xiaochufujiTest::test5(imp, true);	// D:\ASUS\Desktop\carousel2.jpg
	xiaochufujiTest::test6(imp, true);
	xiaochufujiTest::test7(imp, false);
	xiaochufujiTest::test8(imp, true);
	xiaochufujiTest::test9(imp, true);
	xiaochufujiTest::test10(imp, true);
	xiaochufujiTest::test11(imp, true);
	xiaochufujiTest::test12(imp, true);
	xiaochufujiTest::test13(imp, true);
	xiaochufujiTest::test14(imp, true);
	xiaochufujiTest::test15(imp, true);
	xiaochufujiTest::test16(imp, true);
	xiaochufujiTest::test17(imp, true);
	xiaochufujiTest::test18(imp, true);
	xiaochufujiTest::test19(imp, true);
	xiaochufujiTest::test20(imp, true);
	xiaochufujiTest::test21(imp, true);
}

void TestUnit::loopInterfaceTest()
{
	int count = 1000;
	while (count--)
	{
		interfaceTest();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void TestUnit::PrintMemoryUsage()
{
	PROCESS_MEMORY_COUNTERS_EX pmc;
	if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
		PRINT << "[Memory Usage] Working Set Size: " << pmc.WorkingSetSize / 1024 << " KB, ";
		PRINT << "Private Usage: " << pmc.PrivateUsage / 1024 << " KB, ";
		PRINT << "Pagefile Usage: " << pmc.PagefileUsage / 1024 << " KB\n";
	}
	else {
		std::cerr << "Failed to get memory information.\n";
	}
}

void TestUnit::MemoryMonitorThread()
{
	while (keepRunning) {
		PrintMemoryUsage();
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}
