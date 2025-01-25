#include "VirtualDesktopWrapper.h"
#include <iostream>
#include <locale>
#include <codecvt>
using namespace VirtualDesktopNS::API;

_string PrintGUID(const GUID& guid)
{
	wchar_t guidString[40];
	HRESULT result = StringFromGUID2(guid, guidString, ARRAYSIZE(guidString));
	if (FAILED(result))
		return _string{};
#ifdef UNICODE
	return _string(guidString);
#else
	std::wstring wstr(guidString);
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::string str = converter.to_bytes(wstr);

	return str;
#endif
}

GUID GUIDFromString(const _string& str) {
	GUID guid;
	std::wstring _str;
	if (std::is_same<_string, std::string>::value)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		_str = converter.from_bytes(str);
	}
	HRESULT hr = CLSIDFromString(_str.c_str(), &guid);
	return guid;
}

Implement::Implement()
{
	{
		HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		if (FAILED(hr)) {
			std::cerr << "Failed to CoInitializeEx." << std::endl;
			return;
		}
	}
	{
		HRESULT hr = CoCreateInstance(CLSID_ImmersiveShell, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IServiceProvider), (PVOID*)&m_shell);
		if (FAILED(hr)) {
			std::cerr << "Failed to CoCreateInstance shell." << std::endl;
			return;
		}
	}
	{
		HRESULT hr = m_shell->QueryService(CLSID_VirtualDesktopManagerInternal, &m_virtualDesktopManagerInternal);
		if (FAILED(hr)) {
			std::cerr << "Failed to query VirtualDesktopManagerInternal." << std::endl;
			return;
		}
	}
	{
		HRESULT hr = m_shell->QueryService(CLSID_VirtualDesktopManagerInternal, &m_virtualDesktopManagerInternal);
		if (FAILED(hr)) {
			std::cerr << "Failed to query VirtualDesktopManagerInternal." << std::endl;
			return;
		}
	}
	{
		HRESULT hr = m_shell->QueryService(__uuidof(IVirtualDesktopManager), &m_virtualDesktopManager);
		if (FAILED(hr)) {
			std::cerr << "Failed to query VirtualDesktopManager" << std::endl;
			return;
		}
	}
	{

		HRESULT hr = m_shell->QueryService(__uuidof(IApplicationViewCollection), &m_pplicationViewCollection);
		if (FAILED(hr)) {
			std::cerr << "Failed to query ApplicationViewCollection." << std::endl;
			return;
		}
	}
	{
		HRESULT hr = m_shell->QueryService(CLSID_VirtualDesktopPinnedApps, &m_virtualDesktopPinnedApps);
		if (FAILED(hr)) {
			std::cerr << "Failed to query VirtualDesktopPinnedApps." << std::endl;
			return;
		}
	}
}

Implement::~Implement()
{
	if (m_shell) m_shell->Release();
	if (m_virtualDesktopManagerInternal) m_virtualDesktopManagerInternal->Release();
	if (m_virtualDesktopManager) m_virtualDesktopManager->Release();
	if (m_pplicationViewCollection) m_pplicationViewCollection->Release();
	if (m_virtualDesktopPinnedApps) m_virtualDesktopPinnedApps->Release();
	m_shell = nullptr;
	m_virtualDesktopManagerInternal = nullptr;
	m_virtualDesktopManager = nullptr;
	m_pplicationViewCollection = nullptr;
	m_virtualDesktopPinnedApps = nullptr;
	CoUninitialize();
}

void Implement::_getCount()
{
	HRESULT hr = m_virtualDesktopManagerInternal->GetCount(&m_count);
	if (FAILED(hr))
	{
		std::cerr << "Failed to get desktop count." << std::endl;
		return;
	}
}

void Implement::_getCurrentDesktop()
{
	IVirtualDesktop* desktop = NULL;
	HRESULT hr = m_virtualDesktopManagerInternal->GetCurrentDesktop(&desktop);
	if (FAILED(hr))
	{
		std::cerr << "Failed to get current desktop." << std::endl;
		return;
	}
	desktop->GetId(&m_currentDesktopGUID);
	if (FAILED(hr))
	{
		std::cerr << "Failed to get current desktop guid." << std::endl;
		return;
	}
}

void Implement::_enumerateDesktop()
{
	IObjectArray* pObjectArray = nullptr;
	HRESULT hr = m_virtualDesktopManagerInternal->GetDesktops(&pObjectArray);
	if (SUCCEEDED(hr))
	{
		UINT count;
		hr = pObjectArray->GetCount(&count);
		if (SUCCEEDED(hr))
		{
			for (UINT i = 0; i < count; i++)
			{
				IVirtualDesktop* pDesktop = nullptr;
				if (FAILED(pObjectArray->GetAt(i, __uuidof(IVirtualDesktop), (void**)&pDesktop)))
					continue;
				GUID id = { 0 };
				if (SUCCEEDED(pDesktop->GetId(&id)))
				{
					m_desktopGUIDVec.push_back(id);
				}
				pDesktop->Release();
			}
		}
		pObjectArray->Release();
	}
}
