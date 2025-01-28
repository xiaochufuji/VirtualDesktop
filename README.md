# Virtual Desktop API Documentation

## Overview
This document provides a detailed description of the available functions in the Virtual Desktop API. The API enables managing virtual desktops and interacting with desktop environments on Windows systems.

---

## Table of Contents
1. [Other Functions](#other-functions)
2. [Virtual Desktop Value Getters](#virtual-desktop-value-getters)
3. [Virtual Desktop Control](#virtual-desktop-control)
   - [Using Index](#using-index)
   - [Using IVirtualDesktop](#using-ivirtualdesktop)
4. [Virtual Desktop Pin/Unpin Functions](#virtual-desktop-pin-unpin-functions)

---

## Other Functions
### `update()`
Updates the internal state and retrieves the latest virtual desktop information.

### `reset()`
Resets the API to its initial state, clearing any cached information.

---

## Virtual Desktop Value Getters

### `int count() const`
Returns the number of virtual desktops available.

### `GUID currentDesktop() const`
Returns the GUID of the currently active virtual desktop.

### `std::shared_ptr<InformationStructure> currentDesktopInfo() const`
Retrieves detailed information about the current virtual desktop.

### `std::vector<std::shared_ptr<InformationStructure>> allDesktopInfo()`
Returns information for all available virtual desktops.

### `std::shared_ptr<InformationStructure> findWindow(HWND hwnd) const`
Finds the virtual desktop containing a specific window.
- **Parameters:**
  - `hwnd`: Handle to the window.
- **Returns:** A shared pointer to the `InformationStructure` of the virtual desktop.

### `std::shared_ptr<InformationStructure> getVirtualDesktop(int index) const`
Retrieves information about a virtual desktop by its index.

### `std::shared_ptr<InformationStructure> getVirtualDesktop(const _string &name) const`
Retrieves information about a virtual desktop by its name.

### `std::shared_ptr<InformationStructure> getVirtualDesktopEx(const _string &partialName) const`
Retrieves information about a virtual desktop based on a partial match of its name.

### `int getVirtualDesktopIndex(const GUID& guid) const`
Returns the index of a virtual desktop identified by its GUID.

### `int getVirtualDesktopIndex(const _string& name) const`
Returns the index of a virtual desktop identified by its name.

---

## Virtual Desktop Control
### Using Index

#### `std::shared_ptr<InformationStructure> create()`
Creates a new virtual desktop and returns information about it.

#### `bool remove(int index)`
Removes the virtual desktop at the specified index.

#### `bool move(int index)`
Moves a virtual desktop to a different position in the desktop list.

#### `bool setName(int index, const _string& name)`
Sets the name of a virtual desktop at the specified index.

#### `bool setWallpaper(int index, const _string& path)`
Sets the wallpaper for the virtual desktop at the specified index.

#### `bool setAllWallpaper(const _string& path)`
Sets the same wallpaper for all virtual desktops.

#### `bool switchDesktop(int index, bool withAnimation = false)`
Switches to the virtual desktop at the specified index.
- **Parameters:**
  - `index`: The desktop index.
  - `withAnimation`: Whether to use animation during the switch.

#### `bool moveWindow(int index, HWND hwnd)`
Moves a window to the specified virtual desktop.

#### `bool moveActiveWindow(int index)`
Moves the currently active window to the specified virtual desktop.

#### `bool hasWindow(int index, HWND hwnd)`
Checks if a window is on the specified virtual desktop.

#### `bool moveDesktop(int index)`
Moves the virtual desktop at the specified index.

### Using IVirtualDesktop

#### `bool remove(VirtualDesktopNS::API::IVirtualDesktop* desktop)`
Removes the specified virtual desktop.

#### `bool move(VirtualDesktopNS::API::IVirtualDesktop* desktop)`
Moves the specified virtual desktop to a different position.

#### `bool setName(VirtualDesktopNS::API::IVirtualDesktop* desktop, const _string& name)`
Sets the name for the specified virtual desktop.

#### `bool setWallpaper(VirtualDesktopNS::API::IVirtualDesktop* desktop, const _string& path)`
Sets the wallpaper for the specified virtual desktop.

#### `bool switchDesktop(VirtualDesktopNS::API::IVirtualDesktop* desktop, bool withAnimation = false)`
Switches to the specified virtual desktop.

#### `bool moveWindow(VirtualDesktopNS::API::IVirtualDesktop* desktop, HWND hwnd)`
Moves a window to the specified virtual desktop.

#### `bool moveActiveWindow(VirtualDesktopNS::API::IVirtualDesktop* desktop)`
Moves the currently active window to the specified virtual desktop.

#### `bool hasWindow(VirtualDesktopNS::API::IVirtualDesktop* desktop, HWND hwnd)`
Checks if a window is on the specified virtual desktop.

---

## Virtual Desktop Pin/Unpin Functions

### `bool pinWindowByHwnd(HWND hwnd)`
Pins the window with the specified handle to all virtual desktops.

### `bool unpinWindowByHwnd(HWND hwnd)`
Unpins the window with the specified handle from all virtual desktops.

### `bool ispinWindowByHwnd(HWND hwnd)`
Checks if the window with the specified handle is pinned to all virtual desktops.

### `bool pinActiveWindow()`
Pins the currently active window to all virtual desktops.

### `bool unpinActiveWindow()`
Unpins the currently active window from all virtual desktops.

### `bool ispinActiveWindow()`
Checks if the currently active window is pinned to all virtual desktops.

---

## Usage Examples
### Example 1: Switch to the second virtual desktop
```cpp
xiaochufuji::Implement imp;
imp.switchDesktop(2, true);
```
### Example 2: Create and name a new virtual desktop
```cpp
xiaochufuji::Implement imp;
auto new_desktop = imp.create();
```
### Example 3: Move the active window to the third virtual desktop
```
xiaochufuji::Implement imp;
imp.moveActiveWindow(2);
```
### Example 4: Pin a window
```cpp
HWND hwnd = FindWindow(NULL, L"Window Title");
xiaochufuji::Implement imp;
auto new_desktop = imp.pinWindowByHwnd(hwnd);
```

---

## Notes

- Ensure that the virtual desktop management object is properly initialized before performing operations.

- Avoid calling virtual desktop management functions simultaneously from different threads to prevent data races.

- Some interfaces depend on Windows features; ensure that your system runs on Windows 11 with build number 24200 or later.

- When linking the library, ensure that `windowsapp.lib` is included.

- This library adapts to both Unicode and multi-byte character encodings. Please adjust accordingly based on your project requirements. See the `defination` section in `VirtualDesktop.h` for details.

- This project is a C++ rewrite and encapsulation based on the `C#: MScholtes/VirtualDesktop` library.

- The test platform is `Visual Studio 2022 - 17` with `C++17`. You may use lower versions, but it must support at least `C++11`.
