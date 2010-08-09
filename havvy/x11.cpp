//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: x11
//----------------------------------------------------------
#include "x11.hpp"

#define SIZE_USEHINTS (1L << 0)

Display *display = 0;

void initDisplay()
{
    if (display == 0)
	display = XOpenDisplay(getenv("DISPLAY"));
}

int _is_success(const char *funcname, int code) {
  if (code != 0)
    fprintf(stderr, "%s failed (code=%d)\n", funcname, code);
  return code;
}

int window_change(Window wid, int x, int y, int w, int h) {
    initDisplay();
    XWindowChanges wc;
    wc.x = x;
    wc.y = y;
    wc.width = w;
    wc.height = h;
    int ret = XConfigureWindow(display, wid, CWX | CWY | CWWidth | CWHeight, &wc);
    XFlush(display);
    return _is_success("XConfigureWindow", ret == 0);
}


