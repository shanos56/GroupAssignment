#include "mainwindow.h"
#include <QApplication>
#include "formstatushandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UI::FormStatusHandler status(a);

    return a.exec();
}
