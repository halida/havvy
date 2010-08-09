//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: lib
//----------------------------------------------------------
#ifndef __LIB_HPP__
#define __LIB_HPP__

#include <QtGui>
#include <iostream>

// template <class T> void debug(T &msg)
// {
//     std::cout << msg << endl;
// };

void debug(QString &msg);
void debug(const char *msg);

QString getoutput(QString s);

#endif

