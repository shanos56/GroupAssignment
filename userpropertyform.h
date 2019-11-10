#ifndef USERPROPERTYFORM_H
#define USERPROPERTYFORM_H

#include <QDialog>
#include "abstractassetregister.h"
#include <QInputDialog>
#include <QMessageBox>
#include "formstatus.h"
#include <memory>

namespace Ui {
class UserPropertyForm;
}

class UserPropertyForm : public QDialog
{
    Q_OBJECT

    enum statuses {ASSETTYPE,ASSET};
    statuses status;

    std::shared_ptr<AbstractAssetRegister> _reg;
    QString _id;
    std::shared_ptr<UserPropertyDefinition> _def;

    std::shared_ptr<UserPropertyValidator> _currentValidator;

    std::shared_ptr<Asset> _asset;
    std::shared_ptr<AssetType> _assetType;

    std::shared_ptr<UserProperty> _userProperty;

    void successfullyAddedValidator();

public:
    explicit UserPropertyForm(std::shared_ptr<AbstractAssetRegister> reg, QString id,QWidget *parent = nullptr);
    ~UserPropertyForm();

    void setValidators();

    void addPhoneValidator();
    void addDepartmentValidator();
    void addCustomValidator();
    void addMaximumValidator();
    void addMinimumValidator();


    void saveValue();

signals:
    void openForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS);
    void closeForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS);
    void openForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS,QString id = "");

private slots:
    void on_validator_currentIndexChanged(const QString &arg1);

    void on_AddProperty_button_clicked();

    void on_cancel_button_clicked();

    void on_addValidator_button_clicked();

private:
    Ui::UserPropertyForm *ui;
};

#endif // USERPROPERTYFORM_H
