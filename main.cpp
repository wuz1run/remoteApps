#include "widget.h"
#include "QCommandLineParser"
#include <QApplication>
#include "QMessageBox"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCommandLineParser parser;
    Widget w;
    parser.process(a);
    QString Path;
    QString extend;
    if(!parser.positionalArguments().isEmpty())
    {
        Path=parser.positionalArguments().first();
    }
    if(!Path.isEmpty())
    {
        w.openedLnk(Path);
    }
     w.show();
    return a.exec();
}
