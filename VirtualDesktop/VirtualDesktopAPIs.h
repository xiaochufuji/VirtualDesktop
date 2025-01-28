#pragma once
#include <windows.h> 
#include <objbase.h>
#include <stdint.h>
#include <winstring.h>
#include <ObjectArray.h>
#include <string>
//#include <shobjidl_core.h>
//#include <shobjidl.h>
//#include <Windows.Foundation.h>
//#include <iostream>
//using namespace ABI::Windows::Foundation;
#include <windows.ui.viewmanagement.h>
#include <wrl/client.h>
namespace VirtualDesktopNS
{
	namespace API
	{
		const GUID CLSID_ImmersiveShell = { 0xC2F03A33, 0x21F5, 0x47FA, { 0xB4, 0xBB, 0x15, 0x63, 0x62, 0xA2, 0xF2, 0x39 } };
		const GUID CLSID_VirtualDesktopManagerInternal = { 0xC5E0CDCA, 0x7B6E, 0x41B2, { 0x9F, 0xC4, 0xD9, 0x39, 0x75, 0xCC, 0x46, 0x7B } };
		const GUID CLSID_VirtualDesktopManager = { 0xAA509086, 0x5CA9, 0x4C25, { 0x8F, 0x95, 0x58, 0x9D, 0x3C, 0x07, 0xB4, 0x8A } };
		const GUID CLSID_VirtualDesktopPinnedApps = { 0xB5A399E7, 0x1C87, 0x46B8, { 0x88, 0xE9, 0xFC, 0x57, 0x47, 0xB1, 0x71, 0xBD } };


		struct Size
		{
			int X;
			int Y;
		};

		struct Rect
		{
			int Left;
			int Top;
			int Right;
			int Bottom;
		};
		enum APPLICATION_VIEW_CLOAK_TYPE : int
		{
			AVCT_NONE = 0,
			AVCT_DEFAULT = 1,
			AVCT_VIRTUAL_DESKTOP = 2
		};
		enum APPLICATION_VIEW_COMPATIBILITY_POLICY : int
		{
			AVCP_NONE = 0,
			AVCP_SMALL_SCREEN = 1,
			AVCP_TABLET_SMALL_SCREEN = 2,
			AVCP_VERY_SMALL_SCREEN = 3,
			AVCP_HIGH_SCALE_FACTOR = 4
		};

		enum AdjacentDesktop
		{
			LeftDirection = 3,
			RightDirection = 4
		};
		//MIDL_INTERFACE("92CA9DCD-5622-4BBA-A805-5E9F541BD8C9")
		//	IObjectArray : public IUnknown
		//{
		//public:
		//	virtual HRESULT STDMETHODCALLTYPE GetCount(UINT * count) = 0;
		//	virtual HRESULT STDMETHODCALLTYPE GetAt(UINT index, GUID* iid, void** obj) = 0;
		//};
		// Define the GUID for IApplicationView interface
		MIDL_INTERFACE("372E1D3B-38D3-42E4-A15B-8AB2B178F513")
			IApplicationView : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE SetFocus() = 0;
			virtual HRESULT STDMETHODCALLTYPE SwitchTo() = 0;
			//virtual HRESULT STDMETHODCALLTYPE TryInvokeBack(IAsyncCallback* callback) = 0;
			virtual HRESULT STDMETHODCALLTYPE TryInvokeBack(void* callback) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetThumbnailWindow(HWND* hwnd) = 0;
			//virtual HRESULT STDMETHODCALLTYPE GetMonitor(IImmersiveMonitor** immersiveMonitor) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMonitor(void** immersiveMonitor) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetVisibility(bool* visibility) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetCloak(APPLICATION_VIEW_CLOAK_TYPE cloakType, int unknown) = 0;
			//virtual HRESULT STDMETHODCALLTYPE GetPosition(GUID* guid, IApplicationViewPosition** position) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetPosition(GUID* guid, void** position) = 0;
			//virtual HRESULT STDMETHODCALLTYPE SetPosition(IApplicationViewPosition* position) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetPosition(void* position) = 0;
			virtual HRESULT STDMETHODCALLTYPE InsertAfterWindow(HWND hwnd) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetExtendedFramePosition(Rect* rect) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetAppUserModelId(LPWSTR* id) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetAppUserModelId(LPWSTR* id) = 0;
			virtual HRESULT STDMETHODCALLTYPE IsEqualByAppUserModelId(HSTRING id, int* result) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetViewState(uint32_t* state) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetViewState(uint32_t state) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetNeediness(int* neediness) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetLastActivationTimestamp(ULONGLONG* timestamp) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetLastActivationTimestamp(ULONGLONG timestamp) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetVirtualDesktopId(GUID* guid) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetVirtualDesktopId(GUID* guid) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetShowInSwitchers(int* flag) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetShowInSwitchers(int flag) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetScaleFactor(int* factor) = 0;
			virtual HRESULT STDMETHODCALLTYPE CanReceiveInput(BOOL* canReceiveInput) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetCompatibilityPolicyType(APPLICATION_VIEW_COMPATIBILITY_POLICY* flags) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetCompatibilityPolicyType(APPLICATION_VIEW_COMPATIBILITY_POLICY flags) = 0;
			//virtual HRESULT STDMETHODCALLTYPE GetSizeConstraints(IImmersiveMonitor* monitor, SIZE* size1, SIZE* size2) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetSizeConstraints(void* monitor, SIZE* size1, SIZE* size2) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetSizeConstraintsForDpi(uint32_t dpi, SIZE* size1, SIZE* size2) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetSizeConstraintsForDpi(uint32_t* dpi, SIZE* size1, SIZE* size2) = 0;
			virtual HRESULT STDMETHODCALLTYPE OnMinSizePreferencesUpdated(HWND hwnd) = 0;
			//virtual HRESULT STDMETHODCALLTYPE ApplyOperation(IApplicationViewOperation* operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE ApplyOperation(void* operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE IsTray(BOOL* isTray) = 0;
			virtual HRESULT STDMETHODCALLTYPE IsInHighZOrderBand(BOOL* isInHighZOrderBand) = 0;
			virtual HRESULT STDMETHODCALLTYPE IsSplashScreenPresented(BOOL* isSplashScreenPresented) = 0;
			virtual HRESULT STDMETHODCALLTYPE Flash() = 0;
			virtual HRESULT STDMETHODCALLTYPE GetRootSwitchableOwner(IApplicationView** rootSwitchableOwner) = 0;
			virtual HRESULT STDMETHODCALLTYPE EnumerateOwnershipTree(IObjectArray** ownershipTree) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetEnterpriseId(HSTRING* enterpriseId) = 0;
			virtual HRESULT STDMETHODCALLTYPE IsMirrored(BOOL* isMirrored) = 0;

			// Unknown methods (based on the original interface, could be placeholders)
			virtual HRESULT STDMETHODCALLTYPE Unknown1(int* unknown) = 0;
			virtual HRESULT STDMETHODCALLTYPE Unknown2(int* unknown) = 0;
			virtual HRESULT STDMETHODCALLTYPE Unknown3(int* unknown) = 0;
			virtual HRESULT STDMETHODCALLTYPE Unknown4(int* unknown) = 0;
			virtual HRESULT STDMETHODCALLTYPE Unknown5(int* unknown) = 0;
			virtual HRESULT STDMETHODCALLTYPE Unknown6(int unknown) = 0;
			virtual HRESULT STDMETHODCALLTYPE Unknown7() = 0;
			virtual HRESULT STDMETHODCALLTYPE Unknown8(int* unknown) = 0;
			virtual HRESULT STDMETHODCALLTYPE Unknown9(int unknown) = 0;
			virtual HRESULT STDMETHODCALLTYPE Unknown10(int unknownX, int unknownY) = 0;
			virtual HRESULT STDMETHODCALLTYPE Unknown11(int unknown) = 0;
			virtual HRESULT STDMETHODCALLTYPE Unknown12(SIZE* size1) = 0;
		};

		MIDL_INTERFACE("1841C6D7-4F9D-42C0-AF41-8747538F10E5")
			IApplicationViewCollection : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetViews(IObjectArray * *array) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetViewsByZOrder(IObjectArray** array) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetViewsByAppUserModelId(HSTRING id, IObjectArray** array) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetViewForHwnd(HWND hwnd, IApplicationView** view) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetViewForApplication(void* application, IApplicationView** view) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetViewForAppUserModelId(HSTRING id, IApplicationView** view) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetViewInFocus(void* view) = 0;
			virtual HRESULT STDMETHODCALLTYPE Unknown1(void* view) = 0;
			virtual void STDMETHODCALLTYPE RefreshCollection() = 0;
			virtual HRESULT STDMETHODCALLTYPE RegisterForApplicationViewChanges(void* listener, int* cookie) = 0;
			virtual HRESULT STDMETHODCALLTYPE UnregisterForApplicationViewChanges(int cookie) = 0;
		};

		MIDL_INTERFACE("3F07F4BE-B107-441A-AF0F-39D82529072C")
			IVirtualDesktop : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE IsViewVisible(IApplicationView * view, BOOL * result) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetId(GUID* id) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetName(HSTRING* string) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetWallpaperPath(HSTRING* wallpaperPath) = 0;
			virtual HRESULT STDMETHODCALLTYPE IsRemote(BOOL* result) = 0;
		};

		MIDL_INTERFACE("53F5CA0B-158F-4124-900C-057158060B27")
			IVirtualDesktopManagerInternal : public IUnknown
		{
		public:
			//virtual HRESULT STDMETHODCALLTYPE GetCount(UINT* pCount) = 0;
			//virtual HRESULT STDMETHODCALLTYPE MoveViewToDesktop(IApplicationView* view, IVirtualDesktop* desktop) = 0;
			//virtual HRESULT STDMETHODCALLTYPE CanViewMoveDesktops(IApplicationView* view) = 0;
			//virtual HRESULT STDMETHODCALLTYPE GetCurrentDesktop(IVirtualDesktop** desktop) = 0;
			//virtual HRESULT STDMETHODCALLTYPE GetDesktops(IObjectArray** desktops) = 0;
			//virtual HRESULT STDMETHODCALLTYPE GetAdjacentDesktop(IVirtualDesktop* from, int direction, IVirtualDesktop** desktop) = 0;
			//virtual HRESULT STDMETHODCALLTYPE SwitchDesktop(IVirtualDesktop* desktop) = 0;
			//virtual HRESULT STDMETHODCALLTYPE SwitchDesktopAndMoveForegroundView(IVirtualDesktop* desktop) = 0;
			//virtual HRESULT STDMETHODCALLTYPE CreateDesktop(IVirtualDesktop** desktop) = 0;
			//virtual HRESULT STDMETHODCALLTYPE MoveDesktop(IVirtualDesktop* desktop, int nIndex) = 0;
			//virtual HRESULT STDMETHODCALLTYPE RemoveDesktop(IVirtualDesktop* desktop, IVirtualDesktop* fallback) = 0;
			//virtual HRESULT STDMETHODCALLTYPE FindDesktop(const GUID& desktopid, IVirtualDesktop** desktop) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetCount(UINT * pCount) = 0;
			virtual HRESULT STDMETHODCALLTYPE MoveViewToDesktop(IApplicationView* pView,IVirtualDesktop* pDesktop) = 0;
			virtual HRESULT STDMETHODCALLTYPE CanViewMoveDesktops(IApplicationView* pView,int* pfCanViewMoveDesktops) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetCurrentDesktop(IVirtualDesktop** desktop) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDesktops(IObjectArray** ppDesktops) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetAdjacentDesktop(IVirtualDesktop* pDesktopReference,AdjacentDesktop uDirection,IVirtualDesktop** ppAdjacentDesktop) = 0;
			virtual HRESULT STDMETHODCALLTYPE SwitchDesktop(IVirtualDesktop* pDesktop) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateDesktop(IVirtualDesktop** ppNewDesktop) = 0;
			virtual HRESULT STDMETHODCALLTYPE MoveDesktop(IVirtualDesktop* desktop, int nIndex) = 0;
			virtual HRESULT STDMETHODCALLTYPE RemoveDesktop(IVirtualDesktop* pRemove,IVirtualDesktop* pFallbackDesktop) = 0;
			virtual HRESULT STDMETHODCALLTYPE FindDesktop(GUID desktopId,IVirtualDesktop** ppDesktop) = 0;

			virtual HRESULT STDMETHODCALLTYPE GetDesktopSwitchIncludeExcludeViews(IVirtualDesktop* desktop, IObjectArray** unknown1, IObjectArray** unknown2) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetDesktopName(IVirtualDesktop* desktop, HSTRING name) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetDesktopWallpaper(IVirtualDesktop* desktop, HSTRING path) = 0;
			virtual HRESULT STDMETHODCALLTYPE UpdateWallpaperPathForAllDesktops(HSTRING path) = 0;
			virtual HRESULT STDMETHODCALLTYPE CopyDesktopState(IApplicationView* pView0, IApplicationView* pView1) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateRemoteDesktop(HSTRING path, IVirtualDesktop** desktop) = 0;
			//virtual HRESULT STDMETHODCALLTYPE SwitchRemoteDesktop(IVirtualDesktop* desktop, IntPtr switchtype) = 0;
			virtual HRESULT STDMETHODCALLTYPE SwitchRemoteDesktop(IVirtualDesktop* desktop, void* switchtype) = 0;
			virtual HRESULT STDMETHODCALLTYPE SwitchDesktopWithAnimation(IVirtualDesktop* desktop) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetLastActiveDesktop(IVirtualDesktop** desktop) = 0;
			virtual HRESULT STDMETHODCALLTYPE WaitForAnimationToComplete() = 0;
		};

		MIDL_INTERFACE("A5CD92FF-29BE-454C-8D04-D82879FB3F1B")
			IVirtualDesktopManager : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE IsWindowOnCurrentVirtualDesktop(HWND topLevelWindow, BOOL * result) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetWindowDesktopId(HWND topLevelWindow, GUID* desktopId) = 0;
			virtual HRESULT STDMETHODCALLTYPE MoveWindowToDesktop(HWND topLevelWindow, GUID* desktopId) = 0;
		};

		MIDL_INTERFACE("4CE81583-1E4C-4632-A621-07A53543148F")
			IVirtualDesktopPinnedApps : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE IsAppIdPinned(HSTRING appId, BOOL * result) = 0;
			virtual HRESULT STDMETHODCALLTYPE PinAppID(HSTRING appId) = 0;
			virtual HRESULT STDMETHODCALLTYPE UnpinAppID(HSTRING appId) = 0;
			virtual HRESULT STDMETHODCALLTYPE IsViewPinned(IApplicationView* applicationView, BOOL* result) = 0;
			virtual HRESULT STDMETHODCALLTYPE PinView(IApplicationView* applicationView) = 0;
			virtual HRESULT STDMETHODCALLTYPE UnpinView(IApplicationView* applicationView) = 0;
		};



		MIDL_INTERFACE("6D5140C1-7436-11CE-8034-00AA006009FA")
			IServiceProvider10 : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE QueryService(REFGUID service, REFGUID riid, void** ppvObject) = 0;
		};
	}
}
