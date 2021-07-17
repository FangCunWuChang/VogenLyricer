#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(QFile::exists(":/source/wqy-microhei.ttc")){
          int fontId = QFontDatabase::addApplicationFont(":/source/wqy-microhei.ttc");
          qDebug("fontFile = %s",qPrintable(":/source/wqy-microhei.ttc"));
          qDebug("fontId = %d",fontId);
          QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);
          qDebug("msyh = %s",qPrintable(msyh));
          QFont font(msyh);
          QApplication::setFont(font);
        }else{
          qDebug("未找到字体：%s",qPrintable(":/source/wqy-microhei.ttc"));
        }
    MainWindow w;
    w.show();
    return a.exec();
}
