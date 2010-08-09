//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: about
//----------------------------------------------------------
#ifndef __ABOUT_HPP__
#define __ABOUT_HPP__

#include "ui_about.h"

class AboutDialog : public QDialog{
Q_OBJECT
public:
    AboutDialog(QWidget *parent=0);

private:
    Ui::AboutDialog ui;
};

#endif

