#pragma once
#include "VirtualDesktopAPIs.h"
#include <string>
#include <iostream>
#include <vector>

#pragma region define

#define xiaochufuji VirtualDesktopNS::API::
#ifdef UNICODE
using _string = std::wstring;
using _stringstream = std::wstringstream;
#define PRINT  std::wcout
#else 
using _string = std::string;
using _stringstream = std::stringstream;
#define PRINT std::cout
#endif 

#pragma endregion

#pragma region common function declare

void IUnknownDeleter(IUnknown* instance);
using IUnknownDeleterType = decltype(&IUnknownDeleter);
_string PrintGUID(const GUID& guid);
GUID GUIDFromString(const _string& str);
std::wstring HStringToWString(const HSTRING& hstr);
std::string WStringToString(const std::wstring& wstr);
std::wstring StringToWString(const std::string& str);
std::string HStringToString(const HSTRING &hstr);
_string HStringToAutoString(const HSTRING& hstr);
_string _stringFormat(const _string& str, int num);
HSTRING AutoStringToHString(const _string& str);

struct InformationStructure
{
	GUID guid{};
	_string desktopName{};
	_string wallpaperPath{};
	bool isRemote{ false };
	int index{ -1 };
	VirtualDesktopNS::API::IVirtualDesktop* instance{ nullptr };
	~InformationStructure()
	{
		if (instance)
		{
			instance->Release();
		}
	}
};
struct MyHSTRING
{
	MyHSTRING() = default;
	MyHSTRING(const _string& str) : hstr{ AutoStringToHString(str) } {};
	~MyHSTRING() { WindowsDeleteString(hstr); };
	HSTRING hstr{ nullptr };
};

#pragma endregion


class Implement
{
	using IUnknown_ptr = std::shared_ptr<IUnknown> ;
public:
	Implement();
	~Implement();

public:
#pragma region other function
	void initialize();
	void reset();
#pragma endregion

#pragma region virtual desktop value getter
	int count() const;
	GUID currentDesktop() const;
	std::shared_ptr<InformationStructure> currentDesktopInfo() const;
	std::shared_ptr<InformationStructure> findWindow(HWND hwnd) const;
	std::shared_ptr<InformationStructure> getVirtualDesktop(int index) const;
	std::shared_ptr<InformationStructure> getVirtualDesktop(const _string &name) const;
	std::shared_ptr<InformationStructure> getVirtualDesktopEx(const _string &partialName) const;
	int getVirtualDesktopIndex(const GUID& guid) const;
	int getVirtualDesktopIndex(const _string& name) const;
#pragma endregion

#pragma region virtual desktop control
#pragma region use index
	std::shared_ptr<InformationStructure> create();
	bool remove(int index);
	bool move(int index);
	bool setName(int index, const _string& name);
	bool setWallpaper(int index, const _string& path);
	bool setAllWallpaper(const _string& path);
	bool switchDesktop(int index);
	bool moveWindow(int index, HWND hwnd);
	bool moveActiveWindow(int index);
	bool hasWindow(int index, HWND hwnd);
#pragma endregion
#pragma region use IVirtualDesktop
	bool remove(VirtualDesktopNS::API::IVirtualDesktop* desktop);
	bool move(VirtualDesktopNS::API::IVirtualDesktop* desktop);
	bool setName(VirtualDesktopNS::API::IVirtualDesktop* desktop, const _string& name);
	bool setWallpaper(VirtualDesktopNS::API::IVirtualDesktop* desktop, const _string& path);
	bool switchDesktop(VirtualDesktopNS::API::IVirtualDesktop* desktop);
	bool moveWindow(VirtualDesktopNS::API::IVirtualDesktop* desktop, HWND hwnd);
	bool moveActiveWindow(VirtualDesktopNS::API::IVirtualDesktop* desktop);
	bool hasWindow(VirtualDesktopNS::API::IVirtualDesktop* desktop, HWND hwnd);
#pragma endregion
#pragma endregion

#pragma region virtual desktop pin unpin ispin
	bool pinWindowByHwnd(HWND hwnd);
	bool unpinWindowByHwnd(HWND hwnd);
	bool ispinWindowByHwnd(HWND hwnd);
#pragma endregion

public:
	
	void _getDesktopCount();
	void _getCurrentDesktop();
	void _enumerateDesktop();
	std::unique_ptr<VirtualDesktopNS::API::IApplicationView, IUnknownDeleterType> _getApplicationView(HWND hwnd);
	std::vector<std::unique_ptr<VirtualDesktopNS::API::IApplicationView, IUnknownDeleterType>> _enumerateApplicationView();
	_string _getApplicationId(HWND hwnd);

private:
	void resetShell();
	void resetVirtualDesktopManger();
	void resetVirtualDesktopMangerInternal();
	void resetApplicationViewCollection();
	void resetVirtualDesktopPinnedApps();

public:
	uint32_t m_count{ UINT32_MAX };
	GUID m_currentDesktopGUID{};
	std::shared_ptr<InformationStructure> m_currentDesktopinfo{};
	std::vector<std::shared_ptr<InformationStructure>> m_infoVector{};

public:
	IServiceProvider* m_shell { nullptr };
	VirtualDesktopNS::API::IVirtualDesktopManagerInternal* m_virtualDesktopManagerInternal { nullptr };
	VirtualDesktopNS::API::IVirtualDesktopManager* m_virtualDesktopManager { nullptr };
	VirtualDesktopNS::API::IApplicationViewCollection* m_applicationViewCollection { nullptr };
	VirtualDesktopNS::API::IVirtualDesktopPinnedApps* m_virtualDesktopPinnedApps { nullptr };
};