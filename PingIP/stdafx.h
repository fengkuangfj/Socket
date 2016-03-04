// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO: 在此处引用程序需要的其他头文件
#include <conio.h>
#include <iostream>
#include <winsock2.h>

#include "..\\..\\Public\\ModulePath\\ModulePath.h"
#include "..\\..\\Public\\ProcessControl\\ProcessControl.h"
#include "..\\..\\Public\\PrintfEx\\PrintfEx.h"
#include "..\\..\\Public\\StringInternal\\StringInternal.h"
#include "..\\..\\Public\\CommandLine\\CommandLine.h"

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "ws2_32.lib")
