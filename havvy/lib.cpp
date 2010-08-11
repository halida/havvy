//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: lib
//----------------------------------------------------------
#include "lib.hpp"

#include <cstdlib>

QString getoutput(QString s)
{
    QString tmpFile = "t";
    s.append("> ");
    s.append(tmpFile);

    const char *msg = s.toStdString().c_str();
    system(msg);

    QFile file(tmpFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    	return QString();

    QTextStream in(&file);
    return in.readAll();
}
