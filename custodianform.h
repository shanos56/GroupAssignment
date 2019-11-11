#ifndef CUSTODIANFORM_H
#define CUSTODIANFORM_H

#include <QDialog>
#include "abstractassetregister.h"
#include "formstatus.h"
#include <memory>
#include "concretevalidators.h"
#include <QMessageBox>

namespace Ui {
class CustodianForm;
}

class CustodianForm : public QDialog
{
    Q_OBJECT

    std::shared_ptr<AbstractAssetRegister>& _reg;
    QString _id;

    std::shared_ptr<Custodian> custodian;


    void setValues(QString id);
    void setPhoneNumber ();
    void setId();
    void setName();
    void setDepartment();
    void setLastTimeEdited();
    void setLastEditedBy();


    bool savePhoneNumber();
    bool saveName();
    bool saveDepartment();
    bool saveLastTimeEdited();
    bool savelastEditedBy();

public:
    explicit CustodianForm(std::shared_ptr<AbstractAssetRegister>& reg, QString id,QWidget *parent = nullptr);
    ~CustodianForm();





signals:
    void openForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS);
    void closeForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS);
    void openForm2(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS,QString id = "");

public slots:
    void recieveId(QString);

private slots:

    void validationFailed(QString error);
    void on_save_button_clicked();

    void on_cancel_button_clicked();



private:
    Ui::CustodianForm *ui;
};

#endif // CUSTODIANFORM_H
