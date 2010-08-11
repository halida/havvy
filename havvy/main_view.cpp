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
    :QWidget(0, Qt::Dialog | Qt::WindowStaysOnTopHint)
{
    l.addWidget(&tab);
    setLayout(&l);

    tab.addTab(&selector, "&select");
    tab.addTab(&configer, "&config");

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
    tab.setCurrentIndex(0);
    show();
    raise();
    setFocus();
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

void MainView::onSelect(QRect r)
{
    int x = r.x();
    int y = r.y();
    int w = r.width();
    int h = r.height();

    qDebug("selecting: %d, %d, %d, %d", x, y, w, h);
    hide();

    WId id = QxtWindowSystem::activeWindow();
    if (id <= 1) {
	//wrong id..
	qDebug("wrong id: %d", static_cast<int>(id));
	return;
    }
    QString title = QxtWindowSystem::windowTitle(id);

    qDebug() << "window_id:" << id << ", window_title: " << title;

    //not size desktop!
    if (title == "x-nautilus-desktop") return;

    qDebug("move to: %d, %d, size as: %d, %d", x, y, w, h);
    window_change(id, x, y, w, h);
}

void MainView::about(){
    qDebug("about");
    AboutDialog dlg;
    dlg.exec();
}
