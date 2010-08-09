//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: main_view
//----------------------------------------------------------
#ifndef __MAIN_VIEW_HPP__
#define __MAIN_VIEW_HPP__

#include "lib.hpp"
#include "tray.hpp"
#include "selector.hpp"
#include "configer.hpp"

#include <QxtGlobalShortcut>

class MainView : public QTabWidget {
Q_OBJECT

private:
    Tray tray;
    Selector selector;
    Configer configer;
    QAction *quitAction;
    QAction *aboutAction;
    QMenu *trayIconMenu;
    QxtGlobalShortcut shortcut;

    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
    void cmd(QString cmd);
    
public:
    MainView(QApplication &app);

public slots:
    void appear();
    void about();

private slots:
    void onSelect(QRect r);
    void setGlobalShortcut(QString &seq);
};

#endif

