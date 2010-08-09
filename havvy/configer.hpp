//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: configer
//----------------------------------------------------------
#ifndef __CONFIGER_HPP__
#define __CONFIGER_HPP__
#include "lib.hpp"
#include "ui_configer.h"

typedef struct {
    QKeySequence seq;
    QRect rect;
}LocalShortcut;

class Configer : public QWidget {
Q_OBJECT

public:
    Configer(QWidget *parent=0);
    ~Configer();
    QString shortcut;
    bool checkKey(QKeySequence keySeq, QRect &r);

private:
    QSettings settings;
    QRect currentArea;
    QList<LocalShortcut> shortcuts;

    void keyPressEvent(QKeyEvent *e);
    void checkCanSetLocalShortcut();				    
    void updateView();
				 
private slots:
    void on_pbSetGlobalShortcut_clicked();
    void on_pbSetLocalShortcut_clicked();
    void on_pbSetArea_clicked();
    void on_pbRemove_clicked();
    void on_pbAbout_clicked();
private:
    Ui::Form ui;

signals:
    void onSetGlobalShortcut(QString &);
};

#endif

