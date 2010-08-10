//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: windows
//----------------------------------------------------------
#include "windows.hpp"

int window_change(WId wid, int x, int y, int w, int h)
{
    CWnd *pWnd = CWnd::FromHandle(wid);
    pWnd->MoveWindow(x, y, w, h);
    return 0;
} 

