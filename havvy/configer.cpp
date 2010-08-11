//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: configer
//----------------------------------------------------------
#include "configer.hpp"
#include "selector.hpp"
#include "about.hpp"

Configer::Configer(QWidget *parent)
    :QWidget(parent),
     settings("halida-production", "havvy")
{
    ui.setupUi(this);
    shortcut = settings.value("globalshortcuts", "F12").toString();
    int size = settings.value("shortcut/size", 0).toInt();
    for (int i=0; i< size; i++){
	QString name = "shortcut" + QString(i);
	LocalShortcut lsc;
	QString seq = settings.value(name + "/seq").toString();
	lsc.seq = QKeySequence(seq);
	lsc.rect = settings.value(name + "/rect").toRect();
	shortcuts.push_back(lsc);
    };
    updateView();

    ui.leGlobalShortcut->setText(shortcut);
}

Configer::~Configer(){
    qDebug("save settings");
    settings.setValue("globalshortcuts", ui.leGlobalShortcut->text());
    settings.setValue("shortcut/size", shortcuts.size());
    for (int i=0; i< shortcuts.size(); i++){
	QString name = "shortcut" + QString(i);
	LocalShortcut lsc = shortcuts[i];
	settings.setValue(name + "/seq", lsc.seq.toString());
	settings.setValue(name + "/rect", lsc.rect);
    };
}


void Configer::on_pbSetGlobalShortcut_clicked()
{
    shortcut = ui.leGlobalShortcut->text();
    ui.pbSetGlobalShortcut->setEnabled(false);
    emit onSetGlobalShortcut(shortcut);
}

void Configer::on_pbSetArea_clicked()
{
    QRect r;
    if (!Selector::getSelected(r)) return;
    QString area = QString("%1,%2,%3,%4").arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height());
    ui.leArea->setText(area);
    currentArea = r;
    checkCanSetLocalShortcut();
}

void Configer::checkCanSetLocalShortcut()
{
    if (ui.leArea->text().isEmpty() || ui.leLocalShortcut->text().isEmpty()){
	ui.pbSetLocalShortcut->setEnabled(false);
    } else {
	ui.pbSetLocalShortcut->setEnabled(true);
    };
}

void Configer::keyPressEvent(QKeyEvent *e)
{
    QString key;
    Qt::KeyboardModifiers mod = QApplication::keyboardModifiers();
    QKeySequence keySeq (e->key() + mod);
    key = keySeq.toString();
    qDebug()<<key;

    if (ui.leGlobalShortcut == focusWidget())
	{
	    ui.leGlobalShortcut->setText(key);
	    ui.pbSetGlobalShortcut->setEnabled(true);
	}
    else if(ui.leLocalShortcut == focusWidget())
	{
	    ui.leLocalShortcut->setText(key);
	    checkCanSetLocalShortcut();
	}
}

void Configer::on_pbRemove_clicked()
{
    int index = ui.lwShortcuts->currentRow();
    if (index < 0) return;
    ui.lwShortcuts->takeItem(index);
    shortcuts.removeAt(index);
}

void Configer::on_pbSetLocalShortcut_clicked()
{
    QKeySequence seq(ui.leLocalShortcut->text());
    LocalShortcut ls = {seq, currentArea};
    shortcuts.push_front(ls);
    updateView();

    //clean up
    ui.leLocalShortcut->clear();
    ui.leArea->clear();
    checkCanSetLocalShortcut();
}

bool Configer::checkKey(QKeySequence keySeq, QRect &r)
{
    for (int i = 0; i < shortcuts.size(); ++i) {
	if(keySeq.matches(shortcuts.at(i).seq) == QKeySequence::ExactMatch)
	    {
		r = shortcuts.at(i).rect;
		return true;
	    }
    }
    return false;
}

void Configer::updateView()
{
    ui.lwShortcuts->clear();
    for(int i=0; i<shortcuts.size(); i++){
	LocalShortcut lsc = shortcuts[i];
	QRect &r = lsc.rect;
	QString area = QString("%1,%2,%3,%4")				\
	    .arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height());
	QString item = QString("%1\t%2")		\
	    .arg(lsc.seq.toString())			\
	    .arg(area);
	ui.lwShortcuts->addItem(item);
    }
}

void Configer::on_pbAbout_clicked()
{
    AboutDialog dlg;
    dlg.exec();
}
