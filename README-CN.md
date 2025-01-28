# 虚拟桌面管理API使用文档

## 概述

该API提供了一组功能接口，用于管理Windows虚拟桌面，包括获取桌面信息、切换桌面、窗口管理和桌面控制等功能。本文档将详细介绍各接口的使用方法及功能说明。

---

## 接口分类

1. **辅助功能接口**
2. **虚拟桌面属性获取接口**
3. **虚拟桌面控制接口**
4. **窗口钉住与解绑接口**

---

## 1. 辅助功能接口

### `void update()`

**功能描述：** 更新虚拟桌面状态。

### `void reset()`

**功能描述：** 重置虚拟桌面管理状态。

---

## 2. 虚拟桌面属性获取接口

### `int count() const`

**功能描述：** 获取当前虚拟桌面的数量。

### `GUID currentDesktop() const`

**功能描述：** 获取当前虚拟桌面的GUID。

### `std::shared_ptr<InformationStructure> currentDesktopInfo() const`

**功能描述：** 获取当前虚拟桌面的详细信息。

### `std::vector<std::shared_ptr<InformationStructure>> allDesktopInfo()`

**功能描述：** 获取所有虚拟桌面的详细信息。

### `std::shared_ptr<InformationStructure> findWindow(HWND hwnd) const`

**功能描述：** 根据窗口句柄查找窗口所在的虚拟桌面信息。

### `std::shared_ptr<InformationStructure> getVirtualDesktop(int index) const`

**功能描述：** 根据索引获取虚拟桌面信息。

### `std::shared_ptr<InformationStructure> getVirtualDesktop(const _string& name) const`

**功能描述：** 根据名称获取虚拟桌面信息。

### `std::shared_ptr<InformationStructure> getVirtualDesktopEx(const _string& partialName) const`

**功能描述：** 根据部分名称模糊查找虚拟桌面。

### `int getVirtualDesktopIndex(const GUID& guid) const`

**功能描述：** 根据GUID获取虚拟桌面索引。

### `int getVirtualDesktopIndex(const _string& name) const`

**功能描述：** 根据桌面名称获取虚拟桌面索引。

---

## 3. 虚拟桌面控制接口

### 使用索引操作虚拟桌面

#### `std::shared_ptr<InformationStructure> create()`

**功能描述：** 创建一个新的虚拟桌面。

#### `bool remove(int index)`

**功能描述：** 删除指定索引的虚拟桌面。

#### `bool move(int index)`

**功能描述：** 移动窗口到指定索引的虚拟桌面。

#### `bool setName(int index, const _string& name)`

**功能描述：** 设置指定虚拟桌面的名称。

#### `bool setWallpaper(int index, const _string& path)`

**功能描述：** 设置指定虚拟桌面的壁纸。

#### `bool setAllWallpaper(const _string& path)`

**功能描述：** 设置所有虚拟桌面的壁纸。

#### `bool switchDesktop(int index, bool withAnimation = false)`

**功能描述：** 切换到指定索引的虚拟桌面，可以选择是否带有动画效果。

#### `bool moveWindow(int index, HWND hwnd)`

**功能描述：** 将窗口移动到指定索引的虚拟桌面。

#### `bool moveActiveWindow(int index)`

**功能描述：** 将活动窗口移动到指定索引的虚拟桌面。

#### `bool hasWindow(int index, HWND hwnd)`

**功能描述：** 检查指定索引的虚拟桌面是否包含特定窗口。

#### `bool moveDesktop(int index)`

**功能描述：** 移动指定索引的虚拟桌面位置。

### 使用 `IVirtualDesktop` 接口操作虚拟桌面

#### `bool remove(VirtualDesktopNS::API::IVirtualDesktop* desktop)`

**功能描述：** 删除指定虚拟桌面对象。

#### `bool move(VirtualDesktopNS::API::IVirtualDesktop* desktop)`

**功能描述：** 移动窗口到指定虚拟桌面。

#### `bool setName(VirtualDesktopNS::API::IVirtualDesktop* desktop, const _string& name)`

**功能描述：** 设置指定虚拟桌面的名称。

#### `bool setWallpaper(VirtualDesktopNS::API::IVirtualDesktop* desktop, const _string& path)`

**功能描述：** 设置指定虚拟桌面的壁纸。

#### `bool switchDesktop(VirtualDesktopNS::API::IVirtualDesktop* desktop, bool withAnimation = false)`

**功能描述：** 切换到指定虚拟桌面。

#### `bool moveWindow(VirtualDesktopNS::API::IVirtualDesktop* desktop, HWND hwnd)`

**功能描述：** 将窗口移动到指定虚拟桌面。

#### `bool moveActiveWindow(VirtualDesktopNS::API::IVirtualDesktop* desktop)`

**功能描述：** 将活动窗口移动到指定虚拟桌面。

#### `bool hasWindow(VirtualDesktopNS::API::IVirtualDesktop* desktop, HWND hwnd)`

**功能描述：** 检查指定虚拟桌面是否包含特定窗口。

---

## 4. 窗口钉住与解绑接口

### `bool pinWindowByHwnd(HWND hwnd)`

**功能描述：** 将指定窗口钉在所有虚拟桌面。

### `bool unpinWindowByHwnd(HWND hwnd)`

**功能描述：** 取消将指定窗口钉在所有虚拟桌面。

### `bool ispinWindowByHwnd(HWND hwnd)`

**功能描述：** 检查指定窗口是否被钉住。

### `bool pinActiveWindow()`

**功能描述：** 将当前活动窗口钉在所有虚拟桌面。

### `bool unpinActiveWindow()`

**功能描述：** 取消将当前活动窗口钉在所有虚拟桌面。

### `bool ispinActiveWindow()`

**功能描述：** 检查当前活动窗口是否被钉住。

---

## 使用示例

### 示例1：切换到第二个虚拟桌面

```cpp
xiaochufuji::Implement imp;
imp.switchDesktop(2, true);
```

### 示例2：创建并命名新虚拟桌面

```cpp
xiaochufuji::Implement imp;
auto new_desktop = imp.create();
```

### 示例3：移动活动窗口到第三个虚拟桌面

```cpp
xiaochufuji::Implement imp;
imp.moveActiveWindow(2);
```

### 示例4：钉住一个窗口

```cpp
HWND hwnd = FindWindow(NULL, L"窗口标题");
xiaochufuji::Implement imp;
auto new_desktop = imp.pinWindowByHwnd(hwnd);
```

---

## 注意事项

- 确保在操作前已经初始化虚拟桌面管理对象。

- 避免在不同线程中同时调用虚拟桌面管理函数，以免出现数据竞争。

- 部分接口依赖Windows特性，请确保在Windows 11 构建号为24200及以上版本运行。

- 在链接库的时候需要把`windowsapp.lib`链接上

- 当前库使用了unicode字符集和多字节编码字符集自适应调整, 请根据自身情况使用，详细请看`VirtualDesktop.h`的`defination`部分

- 本项目基于`C#: MScholtes/VirtualDesktop`进行重写和封装

- 测试平台为`Visual Studio 2022 - 17`-`C++17`, 当然你可以使用更低的版本进行构建，不过不能低于`C++11`

