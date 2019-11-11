#ifndef ASSETTYPEFORM_H
#define ASSETTYPEFORM_H

#include <QDialog>
#include "abstractassetregister.h"
#include "formstatus.h"
#include <QMessageBox>


namespace Ui {
class AssetTypeForm;
}

class AssetTypeForm : public QDialog
{
    Q_OBJECT

    std::shared_ptr<AbstractAssetRegister> _reg;
    QString _id;
    std::shared_ptr<AssetType> _assetType;
    std::shared_ptr<Asset> _asset;

public:
    explicit AssetTypeForm(std::shared_ptr<AbstractAssetRegister> reg, QString id, QWidget *parent = nullptr);
    ~AssetTypeForm();


    void setId();

    void setLastEditedBy();

    void setLastTimeEdited();

    void setAssets();
    
    void setPropertyDefinitions();

    void saveLastEditedBy();

    void saveLastTimeEdited();

    void onload();


signals:
    void openForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS);
    void closeForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS);

    void openForm2(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS,QString id = "");
public slots:
    void recieveId(QString);



private slots:
    void on_addAsset_button_clicked();

    void on_deleteAsset_button_clicked();

    void on_addDefinition_button_clicked();

    void on_deleteDefinition_button_clicked();

    void on_save_button_clicked();

    void on_cancel_button_clicked();

private:
    Ui::AssetTypeForm *ui;
};

#endif // ASSETTYPEFORM_H
