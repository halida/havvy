//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: tray
//----------------------------------------------------------
#include "tray.hpp"

Tray::Tray()
    :QSystemTrayIcon(QIcon("logo.ico"))     
{
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), 
	    this, SLOT(processEvent(QSystemTrayIcon::ActivationReason)));
}

void Tray::processEvent(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
	{
	    emit onClicked();
	};
}




