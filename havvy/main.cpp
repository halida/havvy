//-*-coding:utf-8-*-
//----------------------------------------------------------
// module: main
//----------------------------------------------------------
#include <QApplication>
#include "main_view.hpp"

int main(int argc,char ** argv){
    QApplication app(argc, argv);
    MainView mv(app);
    mv.show();
    app.exec();
}





