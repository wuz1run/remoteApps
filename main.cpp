#include "widget.h"
#include "QCommandLineParser"
#include <QApplication>
#include "trayicon.h"
#include "qt-solution-master/qtsingleapplication/src/qtsingleapplication.h"
int main(int argc, char *argv[])
{
    QtSingleApplication a(argc, argv);

    QCommandLineParser parser;

    trayIcon icon;
    Widget w;

    parser.process(a);

    QString Path;
    if (!parser.positionalArguments().isEmpty())
    {
        Path = parser.positionalArguments().first();
    }
    // 解析启动参数，获得地址
    if (!Path.isEmpty())
    {

        w.openedFile(Path);
    }
    if (a.isRunning())
    {
        a.sendMessage("raise_window_noop");
        return EXIT_SUCCESS;
    }
    // 调用主窗口的函数，openedfile
    w.show();
    // 主窗口的show函数
    return a.exec();
}
