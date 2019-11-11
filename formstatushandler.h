#ifndef FORMSTATUSHANDLER_H
#define FORMSTATUSHANDLER_H

#include <QObject>
#include <QStack>
#include <QDialog>
#include <QDebug>
#include <QApplication>
#include "login.h"
#include "mainwindow.h"
#include "assetregister.h"
#include "assettypeform.h"
#include "custodianform.h"
#include "assetform.h"
#include "userpropertyform.h"
namespace UI {
class FormStatusHandler: public QObject
{

    Q_OBJECT


    QStack<FormStatus> status;
    QStack<std::shared_ptr<QDialog>> dialogs;
    QStack<int> toBeDeleteddialogs;
    QApplication &_app;

    std::shared_ptr<AbstractAssetRegister> _reg;

    std::shared_ptr<MainWindow> _window;



    bool mainWindowOpen = false;

    void printStatus (UI::FormStatus stat = NULLSTATUS);


    void addDialog (FormStatus stat, QString id = "");

    void closeDialog(FormStatus stat);

    std::shared_ptr<QDialog> getDialog(FormStatus stat);

   void  printDialog();

    void showWindow();

    void hideWindow(int at);

    bool closeDialog(int index);

    void closeApplication ();

    void setSignals(std::shared_ptr<QDialog> form);


public:
    explicit FormStatusHandler(QApplication &app, QObject *parent = nullptr): _app{app} {
        this->setParent(parent);
        onload();

    }

    FormStatus getStatus();

    void onload ();


signals:
    void sendIdToCustodian(QString id);
    void sendIdToAssetType(QString id);
    void sendIdToAsset(QString id);

public slots:
    void setStatus(UI::FormStatus stat);
    void setStatus2(UI::FormStatus stat, QString id);
    void closeStatus(UI::FormStatus stat = NULLSTATUS);









};
}

#endif // FORMSTATUSHANDLER_H
