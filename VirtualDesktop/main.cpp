#include "VirtualDesktop.h"
#include <iostream>
using namespace VirtualDesktopNS::API;
#include <windows.foundation.h>
#include <wrl/client.h>
#include <iostream>

using namespace Microsoft::WRL;
using namespace Windows::Foundation;

// 需要定义一个函数返回 HSTRING 类型
HSTRING GetName() {
	// 使用 WindowsCreateString 创建一个 HSTRING
	HSTRING result;
	WindowsCreateString(L"Hello from WRL", 15, &result);  // 16 是字符串的长度
	return result;
}


int main()
{
	Implement imp;
	{
		PRINT << imp.m_count << std::endl;
		PRINT << PrintGUID(imp.m_currentDesktopGUID) << std::endl;
		PRINT << std::endl;
	}
	{
		for (const auto& ite : imp.m_infoVector)
		{
			PRINT << PrintGUID(ite->guid) << std::endl;
		}
		PRINT << std::endl;
	}
	{
		for (const auto& ite : imp.m_infoVector)
		{
			PRINT << ite->desktopName << std::endl;
		}
		PRINT << std::endl;
	}
	{
		for (const auto& ite : imp.m_infoVector)
		{
			PRINT << ite->wallpaperPath << std::endl;
		}
		PRINT << std::endl;
	}
	{
		HWND hwnd = (HWND)0x0000000000020672;
		imp.pinWindowByHwnd(hwnd);
		PRINT << imp.ispinWindowByHwnd(hwnd) << std::endl;
		imp.unpinWindowByHwnd(hwnd);
		PRINT << imp.ispinWindowByHwnd(hwnd) << std::endl;
		PRINT << std::endl;
	}
	{
		PRINT << imp.getVirtualDesktopIndex("123") << std::endl;
		PRINT << imp.getVirtualDesktop(0)->desktopName << std::endl;
		PRINT << std::endl;
	}
	{
		//imp.create();
	}
	{
		auto desktop = imp.findWindow(GetForegroundWindow());
		PRINT << PrintGUID(desktop->guid) << std::endl;
		PRINT << desktop->desktopName << std::endl;
	}
	{
		//auto a = imp.remove(1);	
	}
	{
		imp.move(2);
	}
	{
		imp.setName(0, "mydesktop");
	}
	{
		//imp.setWallpaper(imp.currentDesktopInfo()->index, R"(D:\ASUS\Desktop\carousel2.jpg)");
	}
	{
		imp.setAllWallpaper(R"(D:\ASUS\Desktop\carousel2.jpg)");
	}
	{
		//imp.switchDesktop(4);
	}
	{
		imp.moveWindow(2, (HWND)0x0000000000020672);
	}


	system("pause");
	return 0;
}
