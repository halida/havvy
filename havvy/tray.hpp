//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: tray
//----------------------------------------------------------
#ifndef __TRAY_HPP__
#define __TRAY_HPP__

#include "lib.hpp"

class Tray : public QSystemTrayIcon {
Q_OBJECT

public:
    Tray();

private slots:    
    void processEvent(QSystemTrayIcon::ActivationReason reason);

signals:
    void onClicked(void);
};

#endif

