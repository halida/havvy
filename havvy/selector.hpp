//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: selector
//----------------------------------------------------------
#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include "lib.hpp"

class Selector : public QWidget {
Q_OBJECT

public:
    QRect drect;

    Selector(QWidget *p=0);
    QSize sizeHint() const;

private:
    QPoint p1;
    QPoint p2;
    int w,h;

    static const int wc = 8;
    static const int hc = 9;
    static const int margin = 3;
    static const int zoom = 3;
    static const int out_margin = 10;

    QPoint getMousePos(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

signals:
    void onSelected(QRect);

public:
    static bool getSelected(QRect &r);
};

class SelectDialog : public QDialog{
Q_OBJECT

public:
    SelectDialog(QRect &r);
private:
    QRect *rp;
private slots:
    void onSelected(QRect r);
};

#endif /* _SELECTOR_H */

