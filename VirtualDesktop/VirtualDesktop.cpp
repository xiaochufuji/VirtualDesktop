#include "VirtualDesktop.h"
#include <iostream>
#include <locale>
#include <codecvt>
#include <winstring.h> 
#include <sstream>
#include <string>
#include <atlbase.h>
using namespace VirtualDesktopNS::API;

#pragma region common function defination

void IUnknownDeleter(IUnknown* instance)
{
	if (instance) {
		instance->Release();
		PRINT << "release" << std::endl;
	}
}


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
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
	std::string str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), &str[0], size_needed, nullptr, nullptr);
	return str;
#endif
}

GUID GUIDFromString(const _string& str)
{
	GUID guid;
	std::wstring _str;
#ifdef UNICODE
	_str = str;
#else
	if (std::is_same<_string, std::string>::value)
	{
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), nullptr, 0);
		_str.resize(size_needed);
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), &_str[0], size_needed);
	}
#endif
	HRESULT hr = CLSIDFromString(_str.c_str(), &guid);
	return guid;
}

std::wstring HStringToWString(const HSTRING& hstr)
{
	const wchar_t* str = WindowsGetStringRawBuffer(hstr, nullptr);
	return std::wstring(str);
}

std::string WStringToString(const std::wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
	std::string str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), &str[0], size_needed, nullptr, nullptr);
	return str;
}

std::wstring StringToWString(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), nullptr, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), &wstr[0], size_needed);
	return wstr;
}


std::string HStringToString(const HSTRING& hstr)
{
	const wchar_t* w_char = WindowsGetStringRawBuffer(hstr, nullptr);
	std::wstring w_string(w_char);
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, w_string.c_str(), static_cast<int>(w_string.size()), nullptr, 0, nullptr, nullptr);
	std::string str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, w_string.c_str(), static_cast<int>(w_string.size()), &str[0], size_needed, nullptr, nullptr);
	return str;
}

_string HStringToAutoString(const HSTRING& hstr)
{
#ifdef UNICODE
	return HStringToWString(hstr);
#else
	return HStringToString(hstr);
#endif
}

_string _stringFormat(const _string& str, int num)
{
	_string formattedString;
	_stringstream ss;
	ss << "Desktop " << num;
	formattedString = ss.str();
	return formattedString;
}

HSTRING AutoStringToHString(const _string& str) {
	HSTRING retVal{ nullptr };
#ifdef UNICODE
	WindowsCreateString(str.c_str(), str.size() + 1, &retVal);
#else
	std::wstring _str = StringToWString(str);
	WindowsCreateString(_str.c_str(), _str.size() + 1, &retVal);
#endif 
	return retVal;
}

#pragma endregion


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
		HRESULT hr = CoCreateInstance(CLSID_ImmersiveShell, NULL, CLSCTX_ALL, __uuidof(IServiceProvider), (PVOID*)&m_shell);
		if (FAILED(hr)) {
			std::cerr << "Failed to CoCreateInstance shell." << std::endl;
			return;
		}
	}
	{
		HRESULT hr = m_shell->QueryService(CLSID_VirtualDesktopManagerInternal, &m_virtualDesktopManagerInternal);
		if (FAILED(hr)) {
			resetShell();
			std::cerr << "Failed to query VirtualDesktopManagerInternal." << std::endl;
			return;
		}
	}
	{
		HRESULT hr = m_shell->QueryService(__uuidof(IVirtualDesktopManager), &m_virtualDesktopManager);
		if (FAILED(hr)) {
			resetShell();resetVirtualDesktopMangerInternal();
			std::cerr << "Failed to query VirtualDesktopManager" << std::endl;
			return;
		}
	}
	{
		HRESULT hr = m_shell->QueryService(__uuidof(IApplicationViewCollection), &m_applicationViewCollection);
		if (FAILED(hr)) {
			resetShell();resetVirtualDesktopMangerInternal();resetVirtualDesktopManger();
			std::cerr << "Failed to query ApplicationViewCollection." << std::endl;
			return;
		}
	}
	{
		HRESULT hr = m_shell->QueryService(CLSID_VirtualDesktopPinnedApps, &m_virtualDesktopPinnedApps);
		if (FAILED(hr)) {
			resetShell();resetVirtualDesktopMangerInternal();resetVirtualDesktopManger();resetApplicationViewCollection();
			std::cerr << "Failed to query VirtualDesktopPinnedApps." << std::endl;
			return;
		}
	}
	initialize();
}

void Implement::initialize()
{
	reset();
	this->_getDesktopCount();
	this->_getCurrentDesktop();
	this->_enumerateDesktop();
}

Implement::~Implement()
{
	reset();
	resetShell();
	resetVirtualDesktopMangerInternal(); 
	resetVirtualDesktopManger(); 
	resetApplicationViewCollection(); 
	resetVirtualDesktopPinnedApps();
	CoUninitialize();
}

void Implement::reset()
{
	m_count = UINT32_MAX;
	m_currentDesktopGUID = {};
	m_currentDesktopinfo.reset();
	m_infoVector.clear();
}

int Implement::count() const
{
	return m_count;
}

GUID Implement::currentDesktop() const
{
	return m_currentDesktopGUID;
}

std::shared_ptr<InformationStructure> Implement::currentDesktopInfo() const
{
	return m_currentDesktopinfo;
}

std::shared_ptr<InformationStructure> Implement::findWindow(HWND hwnd) const
{
	GUID guid;
	HRESULT hr = m_virtualDesktopManager->GetWindowDesktopId(hwnd, &guid);
	if (SUCCEEDED(hr))
	{
		for (const auto& item : m_infoVector)
		{
			if (guid == item->guid)
			{
				return item;
			}
		}
	}
	return std::shared_ptr<InformationStructure>{};
}

std::shared_ptr<InformationStructure>  Implement::getVirtualDesktop(int index) const
{
	if ((m_infoVector.size() == 0) || (m_infoVector.size() > 0 && index > m_infoVector.size() - 1))
		return std::shared_ptr<InformationStructure>{};
	return m_infoVector.at(index);
}

std::shared_ptr<InformationStructure> Implement::getVirtualDesktop(const _string& name) const
{
	if ((m_infoVector.size() == 0) || (m_infoVector.size() > 0))
		return std::shared_ptr<InformationStructure>{};
	for (const auto& item : m_infoVector)
	{
		if (item->desktopName == name)
		{
			return item;
		}
	}
	return std::shared_ptr<InformationStructure>{};
}

std::shared_ptr<InformationStructure> Implement::getVirtualDesktopEx(const _string& partialName) const
{
	if ((m_infoVector.size() == 0) || (m_infoVector.size() > 0))
		return std::shared_ptr<InformationStructure>{};
	for (const auto& item : m_infoVector)
	{
		if (item->desktopName.find(partialName) != _string::npos)
		{
			return item;
		}
	}
	return std::shared_ptr<InformationStructure>{};
}

int Implement::getVirtualDesktopIndex(const GUID& guid) const
{
	if (m_infoVector.size() == 0)
		return -1;
	for (int index = 0; index < m_infoVector.size(); ++index)
	{
		if (m_infoVector.at(index)->guid == guid)
		{
			return index;
		}
	}
	return -1;
}

int Implement::getVirtualDesktopIndex(const _string& name) const
{
	if (m_infoVector.size() == 0)
		return -1;
	for (int index = 0; index < m_infoVector.size(); ++index)
	{
		if (m_infoVector.at(index)->desktopName == name)
		{
			return index;
		}
	}
	return -1;
}

std::shared_ptr<InformationStructure> Implement::create()
{
	CComPtr<IVirtualDesktop> desktop{ nullptr };
	HRESULT hr = m_virtualDesktopManagerInternal->CreateDesktop(&desktop);
	if (SUCCEEDED(hr))
	{
		initialize();
		for (const auto& item : m_infoVector)
		{
			if (desktop == item->instance)
			{
				return item;
			}
		}
	}
	return std::shared_ptr<InformationStructure>();
}

bool Implement::remove(int index)
{
	if ((m_infoVector.size() == 0) || (m_infoVector.size() > 0 && index > m_infoVector.size() - 1))
		return false;
	std::shared_ptr<InformationStructure> info = m_infoVector.at(index);
	CComPtr<IVirtualDesktop> fallback{ nullptr };
	int fallbackIndex{ -1 };
	HRESULT hr{};
	if (index == 0)
	{
		hr = m_virtualDesktopManagerInternal->GetAdjacentDesktop(info->instance, AdjacentDesktop::RightDirection, &fallback);
	}
	else
	{
		hr = m_virtualDesktopManagerInternal->GetAdjacentDesktop(info->instance, AdjacentDesktop::LeftDirection, &fallback);
	}
	if (SUCCEEDED(hr))
	{
		hr = m_virtualDesktopManagerInternal->RemoveDesktop(info->instance, fallback);
		if (SUCCEEDED(hr))	return true;
		return false;
	}
	return false;
}
bool Implement::move(int index)
{
	if ((m_infoVector.size() == 0) || (m_infoVector.size() > 0 && index > m_infoVector.size() - 1))
		return false;
	HRESULT hr = m_virtualDesktopManagerInternal->MoveDesktop(m_currentDesktopinfo->instance, index);
	if (SUCCEEDED(hr)) return true;
	return false;
}

bool Implement::setName(int index, const _string& name)
{
	if ((m_infoVector.size() == 0) || (m_infoVector.size() > 0 && index > m_infoVector.size() - 1))
		return false;
	MyHSTRING hstr{ name };
	IVirtualDesktop* desktop = m_infoVector.at(index)->instance;
	HRESULT hr = m_virtualDesktopManagerInternal->SetDesktopName(desktop, hstr.hstr);
	if (SUCCEEDED(hr)) return true;
	return false;
}

bool Implement::setWallpaper(int index, const _string& path)
{
	if (path.empty())
		return false;
	MyHSTRING hstr{ path };
	IVirtualDesktop* desktop = m_infoVector.at(index)->instance;
	HRESULT hr = m_virtualDesktopManagerInternal->SetDesktopWallpaper(desktop, hstr.hstr);
	if (SUCCEEDED(hr)) return true;
	return false;
}

bool Implement::setAllWallpaper(const _string& path)
{
	if (path.empty())
		return false;
	MyHSTRING hstr{ path };
	HRESULT hr = m_virtualDesktopManagerInternal->UpdateWallpaperPathForAllDesktops(hstr.hstr);
	if (SUCCEEDED(hr)) return true;
	return false;
}

bool Implement::switchDesktop(int index)
{
	if ((m_infoVector.size() == 0) || (m_infoVector.size() > 0 && index > m_infoVector.size() - 1))
		return false;
	IVirtualDesktop* desktop = m_infoVector.at(index)->instance;
	HRESULT hr = m_virtualDesktopManagerInternal->SwitchDesktop(desktop);
	if (SUCCEEDED(hr)) return true;
	return false;
}

bool Implement::moveWindow(int index, HWND hwnd)
{
	if ((m_infoVector.size() == 0) || (m_infoVector.size() > 0 && index > m_infoVector.size() - 1))
		return false;
	HRESULT hr{};
	auto info = m_infoVector.at(index);
	try
	{	// the easy way (if we are owner)
		auto guid = info->guid;
		hr = m_virtualDesktopManager->MoveWindowToDesktop(hwnd, &guid);
		if (SUCCEEDED(hr))
			return true;

		throw "use IApplication";
	}
	catch (...)
	{	// window of process, but we are not the owner
		CComPtr<IApplicationView> view;
		hr = m_applicationViewCollection->GetViewForHwnd(hwnd, &view);
		if (SUCCEEDED(hr))
		{
			hr = m_virtualDesktopManagerInternal->MoveViewToDesktop(view, info->instance);
			if (SUCCEEDED(hr))
				return true;
		}
	}
	return false;
}

bool Implement::moveActiveWindow(int index)
{
	if ((m_infoVector.size() == 0) || (m_infoVector.size() > 0 && index > m_infoVector.size() - 1))
		return false;
	return moveWindow(index, GetForegroundWindow());
}


bool Implement::hasWindow(int index, HWND hwnd)
{
	if ((m_infoVector.size() == 0) || (m_infoVector.size() > 0 && index > m_infoVector.size() - 1))
		return false;
	auto info = m_infoVector.at(index);
	GUID lhs = info->guid;
	GUID rhs{};
	HRESULT hr = m_virtualDesktopManager->GetWindowDesktopId(hwnd, &rhs);
	if (SUCCEEDED(hr))
	{
		return lhs == rhs;
	}
	return false;
}

bool Implement::remove(VirtualDesktopNS::API::IVirtualDesktop* desktop)
{
	if (!desktop)
		return false;
	for (int index = 0; index < m_infoVector.size(); ++index)
	{
		if (desktop == m_infoVector.at(index)->instance)
		{
			return remove(index);
		}
	}
	return false;
}

bool Implement::move(IVirtualDesktop* desktop)
{
	if (!desktop)
		return false;
	for (int index = 0; index < m_infoVector.size(); ++index)
	{
		if (desktop == m_infoVector.at(index)->instance)
		{
			return move(index);
		}
	}
	return false;
}

bool Implement::setName(VirtualDesktopNS::API::IVirtualDesktop* desktop, const _string& name)
{
	if ((m_infoVector.size() == 0) || !desktop)
		return false;
	MyHSTRING hstr{ name };
	HRESULT hr = m_virtualDesktopManagerInternal->SetDesktopName(desktop, hstr.hstr);
	if (SUCCEEDED(hr)) return true;
	return false;
}

bool Implement::setWallpaper(VirtualDesktopNS::API::IVirtualDesktop* desktop, const _string& path)
{
	if ((m_infoVector.size() == 0) || !desktop)
		return false;
	MyHSTRING hstr{ path };
	HRESULT hr = m_virtualDesktopManagerInternal->SetDesktopWallpaper(desktop, hstr.hstr);
	if (SUCCEEDED(hr)) return true;
	return false;
}

bool Implement::switchDesktop(VirtualDesktopNS::API::IVirtualDesktop* desktop)
{
	if ((m_infoVector.size() == 0) || !desktop)
		return false;
	HRESULT hr = m_virtualDesktopManagerInternal->SwitchDesktop(desktop);
	if (SUCCEEDED(hr)) return true;
	return false;
}

bool Implement::moveWindow(VirtualDesktopNS::API::IVirtualDesktop* desktop, HWND hwnd)
{
	if ((m_infoVector.size() == 0) || !desktop)
		return false;
	HRESULT hr{};
	for (int index = 0; index < m_infoVector.size(); ++index)
	{
		if (desktop == m_infoVector.at(index)->instance)
		{
			return moveWindow(index, hwnd);
		}
	}
	return false;
}

bool Implement::moveActiveWindow(VirtualDesktopNS::API::IVirtualDesktop* desktop)
{
	if ((m_infoVector.size() == 0) || !desktop)
		return false;
	return moveWindow(desktop, GetForegroundWindow());
}

bool Implement::hasWindow(VirtualDesktopNS::API::IVirtualDesktop* desktop, HWND hwnd)
{
	if ((m_infoVector.size() == 0) || !desktop)
		return false;
	HRESULT hr{};
	for (int index = 0; index < m_infoVector.size(); ++index)
	{
		if (desktop == m_infoVector.at(index)->instance)
		{
			return hasWindow(index, hwnd);
		}
	}
	return false;
}


bool Implement::pinWindowByHwnd(HWND hwnd)
{
	auto view = this->_getApplicationView(hwnd);
	if (!view.get())	return false;
	HRESULT hr = m_virtualDesktopPinnedApps->PinView(view.get());
	return SUCCEEDED(hr);
}

bool Implement::unpinWindowByHwnd(HWND hwnd)
{
	auto view = this->_getApplicationView(hwnd);
	if (!view.get())	return false;
	HRESULT hr = m_virtualDesktopPinnedApps->UnpinView(view.get());
	return SUCCEEDED(hr);
}

bool Implement::ispinWindowByHwnd(HWND hwnd)
{
	auto view = this->_getApplicationView(hwnd);
	if (!view.get())	return false;
	BOOL retVal = FALSE;
	HRESULT hr = m_virtualDesktopPinnedApps->IsViewPinned(view.get(), &retVal);
	return static_cast<bool>(retVal);
}

std::unique_ptr<IApplicationView, IUnknownDeleterType> Implement::_getApplicationView(HWND hwnd)
{
	IApplicationView* view = nullptr;
	HRESULT hr = m_applicationViewCollection->GetViewForHwnd(hwnd, &view);
	if (SUCCEEDED(hr))
	{
		auto retVal = std::unique_ptr<IApplicationView, IUnknownDeleterType>(view, IUnknownDeleter);
		return std::move(retVal);
	}
	return std::move(std::unique_ptr<IApplicationView, IUnknownDeleterType>(nullptr, IUnknownDeleter));
}

std::vector<std::unique_ptr<IApplicationView, IUnknownDeleterType>> Implement::_enumerateApplicationView()
{
	std::vector<std::unique_ptr<IApplicationView, IUnknownDeleterType>> retVal{};
	IObjectArray* tmpObjectArray = nullptr;
	HRESULT hr = m_applicationViewCollection->GetViews(&tmpObjectArray);
	if (SUCCEEDED(hr))
	{
		UINT count = UINT_MAX;
		hr = tmpObjectArray->GetCount(&count);
		if (FAILED(hr) || count == UINT_MAX)
		{
			std::cerr << "Failed to get the count" << std::endl;
			count = 0;
		}
		else if (SUCCEEDED(hr))
		{
			for (UINT i = 0; i < count; i++)
			{
				IApplicationView* view = nullptr;
				if (FAILED(tmpObjectArray->GetAt(i, __uuidof(IApplicationView), (void**)&view)))
					continue;
				auto view_ptr = std::unique_ptr<IApplicationView, IUnknownDeleterType>(view, IUnknownDeleter);
				retVal.push_back(std::move(view_ptr));
			}
		}
		tmpObjectArray->Release();
	}
	return retVal;
}

void Implement::resetShell()
{
	if (m_shell)
	{
		m_shell->Release();
		m_shell = nullptr;
	}
}

void Implement::resetVirtualDesktopManger()
{
	if (m_virtualDesktopManager)
	{
		m_virtualDesktopManager->Release();
		m_virtualDesktopManager = nullptr;
	}
}

void Implement::resetVirtualDesktopMangerInternal()
{
	if (m_virtualDesktopManagerInternal)
	{
		m_virtualDesktopManagerInternal->Release();
		m_virtualDesktopManagerInternal = nullptr;
	}
}

void Implement::resetApplicationViewCollection()
{
	if (m_applicationViewCollection)
	{
		m_applicationViewCollection->Release();
		m_applicationViewCollection = nullptr;
	}
}

void Implement::resetVirtualDesktopPinnedApps()
{
	if (m_virtualDesktopPinnedApps)
	{
		m_virtualDesktopPinnedApps->Release();
		m_virtualDesktopPinnedApps = nullptr;
	}
}

void Implement::_getDesktopCount()
{
	if (!m_virtualDesktopManagerInternal) return;
	HRESULT hr = m_virtualDesktopManagerInternal->GetCount(&m_count);
	if (FAILED(hr))
	{
		std::cerr << "Failed to get desktop count." << std::endl;
		return;
	}
}

void Implement::_getCurrentDesktop()
{
	if (!m_virtualDesktopManagerInternal) return;
	CComPtr<IVirtualDesktop> desktop = NULL;
	HRESULT hr = m_virtualDesktopManagerInternal->GetCurrentDesktop(&desktop);
	if (SUCCEEDED(hr))
	{
		hr = desktop->GetId(&m_currentDesktopGUID);
		if (FAILED(hr)) 
		{
			std::cerr << "Failed to get current desktop." << std::endl;
		}
	}
}

void Implement::_enumerateDesktop()
{
	if (!m_virtualDesktopManagerInternal) return;
	IObjectArray* tmpObjectArray = nullptr;
	HRESULT hr = m_virtualDesktopManagerInternal->GetDesktops(&tmpObjectArray);
	if (SUCCEEDED(hr))
	{
		UINT count = UINT_MAX;
		hr = tmpObjectArray->GetCount(&count);
		if (FAILED(hr) || count == UINT_MAX)
		{
			std::cerr << "Failed to get the count" << std::endl;
			count = 0;
		}
		else if (SUCCEEDED(hr))
		{
			for (UINT index = 0; index < count; index++)
			{
				std::shared_ptr<InformationStructure> tmp = std::make_shared<InformationStructure>();
				IVirtualDesktop* tmpDesktop = nullptr;
				if (FAILED(tmpObjectArray->GetAt(index, __uuidof(IVirtualDesktop), (void**)&tmpDesktop)))
					continue;
				GUID id = { 0 };
				if (SUCCEEDED(tmpDesktop->GetId(&id)))
				{
					tmp->guid = id;
				}
				MyHSTRING name;
				if (SUCCEEDED(tmpDesktop->GetName(&(name.hstr))))
				{
					_string _name(HStringToAutoString(name.hstr));
					if (_name.empty())  _name = _stringFormat(_name, index + 1);
					tmp->desktopName = _name;
				}
				MyHSTRING wallPaperPath;
				if (SUCCEEDED(tmpDesktop->GetWallpaperPath(&(wallPaperPath.hstr))))
				{
					_string _wallPaperPath(HStringToAutoString(wallPaperPath.hstr));
					tmp->wallpaperPath = _wallPaperPath;
				}
				//BOOL isRemote{ false };
				//if (SUCCEEDED(tmpDesktop->IsRemote(&isRemote)))
				//{
				//	tmp->isRemote = static_cast<bool>(isRemote);
				//}
				tmp->index = index;
				tmp->instance = tmpDesktop;
				if (id == m_currentDesktopGUID)
				{
					m_currentDesktopinfo = tmp;
				}
				m_infoVector.emplace_back(tmp);
			}
		}
		tmpObjectArray->Release();
	}
}

