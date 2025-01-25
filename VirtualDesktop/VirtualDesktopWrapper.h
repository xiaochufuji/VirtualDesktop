#pragma once
#include "VirtualDesktopAPIs.h"
#include <string>
#include <iostream>
#include <vector>

#define xiaochufuji VirtualDesktopNS::API::
#ifdef UNICODE
using _string = std::wstring;
#define PRINT  std::wcout
#else 
using _string = std::string;
#define PRINT std::cout
#endif 

_string PrintGUID(const GUID& guid);
GUID GUIDFromString(const _string& str);
class Implement
{
public:
	Implement();
	~Implement();
public:
	void _getCount();
	void _getCurrentDesktop();
	void _enumerateDesktop();

public:
	uint32_t m_count{ UINT32_MAX };
	GUID m_currentDesktopGUID{};
	std::vector<GUID> m_desktopGUIDVec{};
public:
	IServiceProvider* m_shell = nullptr;
	VirtualDesktopNS::API::IVirtualDesktopManagerInternal* m_virtualDesktopManagerInternal = nullptr;
	VirtualDesktopNS::API::IVirtualDesktopManager* m_virtualDesktopManager = nullptr;
	VirtualDesktopNS::API::IApplicationViewCollection* m_pplicationViewCollection = nullptr;
	VirtualDesktopNS::API::IVirtualDesktopPinnedApps* m_virtualDesktopPinnedApps = nullptr;
};