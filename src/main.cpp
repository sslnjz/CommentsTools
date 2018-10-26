#include "SMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);

    qRegisterMetaType<QVector<QString>>("QVector<QString>");

    SMainWindow w;
    w.show();

    return a.exec();
}
