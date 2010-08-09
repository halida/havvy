//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: x11
//----------------------------------------------------------
#ifndef __X11_HPP__
#define __X11_HPP__

#include <sys/select.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <regex.h>

#include <X11/Xlib.h>
#include <X11/Xresource.h>
#include <X11/Xutil.h>

int window_change(Window wid, int x, int y, int w, int h);

#endif

