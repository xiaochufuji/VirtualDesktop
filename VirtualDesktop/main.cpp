#include "VirtualDesktopAPIs.h"
#include <iostream>
using namespace VirtualDesktops::API;

int main()
{
	IVirtualDesktopManagerInternal* VirtualDesktopManagerInternal = nullptr;
	IVirtualDesktopManager* VirtualDesktopManager = nullptr;
	IApplicationViewCollection* ApplicationViewCollection = nullptr;
	IVirtualDesktopPinnedApps* VirtualDesktopPinnedApps = nullptr;
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED); // Initialize COM library

	IServiceProvider10* shell = nullptr;
	HRESULT hr = CoCreateInstance(CLSID_ImmersiveShell, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&shell));
	if (FAILED(hr)) {
		std::cerr << "Failed to create ImmersiveShell instance." << std::endl;
		return;
	}

	hr = shell->QueryService(CLSID_VirtualDesktopManagerInternal, IID_PPV_ARGS(&VirtualDesktopManagerInternal));
	if (FAILED(hr)) {
		std::cerr << "Failed to query VirtualDesktopManagerInternal." << std::endl;
		return;
	}

	hr = CoCreateInstance(CLSID_VirtualDesktopManager, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&VirtualDesktopManager));
	if (FAILED(hr)) {
		std::cerr << "Failed to create VirtualDesktopManager instance." << std::endl;
		return;
	}

	hr = shell->QueryService(__uuidof(IApplicationViewCollection), IID_PPV_ARGS(&ApplicationViewCollection));
	if (FAILED(hr)) {
		std::cerr << "Failed to query ApplicationViewCollection." << std::endl;
		return;
	}

	hr = shell->QueryService(CLSID_VirtualDesktopPinnedApps, IID_PPV_ARGS(&VirtualDesktopPinnedApps));
	if (FAILED(hr)) {
		std::cerr << "Failed to query VirtualDesktopPinnedApps." << std::endl;
		return;
	}

	// Release the shell as it's no longer needed
	shell->Release();

	return 0;
}