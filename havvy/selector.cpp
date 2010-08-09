//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: selector
//----------------------------------------------------------
#include "selector.hpp"

#include <cstdlib>
#include <algorithm>
#include <iostream>

Selector::Selector(QWidget *p)
    :QWidget(p),
     drect(QApplication::desktop()->screenGeometry()),
     p1(-1,-1),
     p2(-1,-1),
     w(drect.width() / wc / zoom),
     h(drect.height() / hc / zoom)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    
    QString msg = QString("caculate grid: %1, %2, %3, %4") \
	.arg(w) .arg(h)					   \
	.arg(drect.width()) .arg(drect.height());
    debug(msg);
}

QSize Selector::sizeHint() const
{
    return QSize(drect.width() / zoom + out_margin*2,
		 drect.height() / zoom + out_margin*2);
}

QPoint Selector::getMousePos(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    x -= out_margin;
    y -= out_margin;
    x /= w;
    y /= h;
    return QPoint(x, y);
}

void Selector::mousePressEvent(QMouseEvent *event)
{
    p1 = getMousePos(event);
    p2 = getMousePos(event);
    update();
}

void Selector::mouseReleaseEvent(QMouseEvent *event)
{
    p2 = getMousePos(event);
    update();

    int x = std::min(p1.x(), p2.x());
    int y = std::min(p1.y(), p2.y());
    int bw = abs(p1.x() - p2.x()) + 1;
    int bh = abs(p1.y() - p2.y()) + 1;

    p1 = QPoint(-1,-1);
    p2 = QPoint(-1,-1);

    emit onSelected(QRect(x * zoom * this->w,
			  y * zoom * this->h,
			  bw * zoom * this->w,
			  bh * zoom * this->h));
}

void Selector::mouseMoveEvent(QMouseEvent *event)
{
    p2 = getMousePos(event);
    update();
}

void Selector::paintEvent(QPaintEvent *event)
{
    //debug("painting..");
    QPainter painter(this);

    for (int i=0; i<wc; i++)
	{
            for (int j=0; j<hc; j++)
		{
		    if (i <= std::max(p1.x(), p2.x()) &&
			i >= std::min(p1.x(), p2.x()) &&
			j <= std::max(p1.y(), p2.y()) &&
			j >= std::min(p1.y(), p2.y()))
			{
			    painter.setBrush(Qt::red);
			}
		    else
			{
			    painter.setBrush(Qt::NoBrush);
			};
		    
		    painter.drawRect(w*i + margin + out_margin,
				     h*j + margin + out_margin,
				     w - margin,
				     h - margin);
		}
	}
}

SelectDialog::SelectDialog(QRect &r)
    :rp(&r)
{
    Selector *selector = new Selector(this);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(selector);

    connect(selector, SIGNAL(onSelected(QRect)),
	    this, SLOT(onSelected(QRect)));
}

void SelectDialog::onSelected(QRect r){
    *rp = r;
    this->accept();
};

bool Selector::getSelected(QRect &r)
{
    SelectDialog dlg(r);
    int result = dlg.exec();
    return (result == QDialog::Accepted);
}
