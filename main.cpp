#include "mainwindow.h"
#include <QApplication>
#include "formstatushandler.h"
#include "tester.h"

int main(int argc, char *argv[])
{
    bool testing = false;

    if (testing == false) {
    QApplication a(argc, argv);

    UI::FormStatusHandler status(a);

    return a.exec();
    } else {
        Tester test;
        test.testAbstractAsset();
        test.testCommonEntityFactory();
        test.testCustodian();
        test.testCustodianPhone();
        test.testCustodianDepartment();
        test.testAsset();

    }
}
