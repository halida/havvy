//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: main_view
//----------------------------------------------------------
#include "main_view.hpp"

#include <QxtWindowSystem>
#include "about.hpp"

#ifdef Q_WS_X11
#include "x11.hpp"
#endif

#ifdef Q_WS_WIN
#include "windows.hpp"
#endif

const QString TITLE = "havvy";

MainView::MainView(QApplication &app)
{
    addTab(&selector, "&select");
    addTab(&configer, "&config");

    connect(&selector, SIGNAL(onSelected(QRect)),
	    this, SLOT(onSelect(QRect)));
    connect(&configer, SIGNAL(onSetGlobalShortcut(QString &)), 
	    this, SLOT(setGlobalShortcut(QString &)));

    setWindowTitle(TITLE);

    quitAction = new QAction(this->tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));

    aboutAction = new QAction(this->tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(quitAction);
    trayIconMenu->addAction(aboutAction);

    tray.setContextMenu(trayIconMenu);
    connect(&tray, SIGNAL(onClicked()), this, SLOT(appear()));
    tray.show();

    connect(&shortcut, SIGNAL(activated()), 
		     this, SLOT(appear()));
    this->setGlobalShortcut(configer.shortcut);
    appear();
}

void MainView::setGlobalShortcut(QString &seq)
{
    shortcut.setShortcut(QKeySequence(seq));
}

void MainView::appear()
{
    //move to the middle of desktop
    move(selector.drect.width()/2 - size().width()/2,
	 selector.drect.height()/2 - size().height()/2);
    setCurrentIndex(0);
    show();
    raise();
}
 
void MainView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
	{
	    hide();
	    return;
	}
    Qt::KeyboardModifiers mod = QApplication::keyboardModifiers();
    QKeySequence keySeq (event->key() + mod);
    QRect r;
    if (!configer.checkKey(keySeq, r)) return;
    onSelect(r);
}

void MainView::closeEvent(QCloseEvent *event)
{
    if (tray.isVisible())
	{
            hide();
            event->ignore();
	}
}

void MainView::cmd(QString cmd)
{
    debug("on cmd:");
    debug(cmd);
    getoutput(cmd);
}

void MainView::onSelect(QRect r)
{
    int x = r.x();
    int y = r.y();
    int w = r.width();
    int h = r.height();

    QString msg = QString("selecting: %1,%2,%3,%4") \
	.arg(x) .arg(y) .arg(w) .arg(h);
    debug(msg);
    hide();

    WId id = QxtWindowSystem::activeWindow();
    if (id <= 0) return;

    QString title = QxtWindowSystem::windowTitle(id);

    //msg = QString("window_id: %1, window_title: %2").arg(id).arg(title);
    //debug(msg);

    //not size desktop!
    if (title == "x-nautilus-desktop") return;

    msg = QString("move to: %1, %2, size as: %3, %4").arg(x).arg(y).arg(w).arg(h);
    debug(msg);
    window_change(id, x, y, w, h);
}

void MainView::about(){
    debug("about");
    AboutDialog dlg;
    dlg.exec();
}
