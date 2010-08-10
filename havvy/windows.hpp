//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: windows
//----------------------------------------------------------
#ifndef __WINDOWS_HPP__
#define __WINDOWS_HPP__

#ifndef _AFXDLL
#define _AFXDLL
#endif

//#include <windows.h>
#include <afxwin.h>

typedef HWND WId;

int window_change(WId wid, int x, int y, int w, int h);

#endif

