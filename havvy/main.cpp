//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: main
//----------------------------------------------------------
#include <QApplication>
#include "main_view.hpp"

int main(int argc,char ** argv){
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    MainView mv(app);
    mv.show();
    app.exec();
}





