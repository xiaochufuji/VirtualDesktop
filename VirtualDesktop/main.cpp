#include "VirtualDesktopWrapper.h"
#include <iostream>
using namespace VirtualDesktopNS::API;



int main()
{
	Implement imp;
	imp._getCount();
	imp._getCurrentDesktop();
	imp._enumerateDesktop();
	PRINT << imp.m_count << std::endl;
	PRINT << PrintGUID(imp.m_currentDesktopGUID) << std::endl;
	PRINT << std::endl;
	for (auto ite : imp.m_desktopGUIDVec)
	{
		auto str = PrintGUID(ite);
		PRINT << str << std::endl;
	}
	system("pause");
	return 0;
}
