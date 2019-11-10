#ifndef ASSETFORM_H
#define ASSETFORM_H

#include <QDialog>
#include <memory>
#include "abstractassetregister.h"
#include "formstatus.h"
#include <QMessageBox>


namespace Ui {
class AssetForm;
}

class AssetForm : public QDialog
{
    Q_OBJECT

    void setId();
    void purchaseDate();
    void serialNo();
    void brand();
    void model();
    void purchasePrice();
    void disposalDate();
    void assetType();
    void lastEditedBy();
    void lastTimeEdited();
    void custodian();

    bool savePurchaseDate();
    bool saveSerialNo();
    bool saveBrand();
    bool saveModel();
    bool savePurchasePrice();
    bool saveDisposalDate();
    bool saveAssetType();
    bool saveCustodian();
    void saveLastEditedBy();
    void saveLastTimeEdited();



    std::shared_ptr<AbstractAssetRegister> _reg;
    QString _id;
    std::shared_ptr<Asset> _asset;

public:
    explicit AssetForm(std::shared_ptr<AbstractAssetRegister> reg, QString id, QWidget *parent = nullptr);
    ~AssetForm();


signals:
    void openForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS);
    void closeForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS);
    void openForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS,QString id = "");

private slots:
    void on_addProperty_button_clicked();

    void on_save_button_clicked();

    void on_cancel_button_clicked();

private:
    Ui::AssetForm *ui;
};

#endif // ASSETFORM_H
