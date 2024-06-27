#include "widget.h"
#include "QCommandLineParser"
#include <QApplication>
#include "QMessageBox"
#include "trayicon.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCommandLineParser parser;
    trayIcon icon;
    Widget w;
    parser.process(a);
    QString Path;
    if(!parser.positionalArguments().isEmpty())
    {
        Path=parser.positionalArguments().first();
    }
    //解析启动参数，获得地址
    if(!Path.isEmpty())
    {
        w.openedFile(Path);
    }
    //调用主窗口的函数，openedfile
     w.show();
    //主窗口的show函数
    return a.exec();
}
