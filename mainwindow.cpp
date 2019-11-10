#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include <QMessageBox>

MainWindow::MainWindow(std::shared_ptr<AbstractAssetRegister> reg,QWidget *parent) :
    QMainWindow(parent),
    _reg{reg},
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->fillList();


}

void MainWindow::fillList() {

    auto list = _reg.get()->allEntities();
    if (!list.isEmpty()) {
        for (auto i = list.begin();i != list.end();i++) {
            if (i->get()->type().compare("Custodian") == 0) {
                QListWidgetItem *a = new QListWidgetItem();

                std::shared_ptr<Custodian> custodian(dynamic_cast<Custodian *>(i->get()));
                a->setData(Qt::DisplayRole,QVariant(custodian->getId()));
                a->setText(custodian->getName());
                ui->Custodians_list->addItem(a);

            } else if (i->get()->type().compare("AssetType") == 0) {
                QListWidgetItem *a = new QListWidgetItem();
                std::shared_ptr<AssetType> assetType(dynamic_cast<AssetType *>(i->get()));
                a->setData(Qt::DisplayRole,QVariant(assetType->getId()));
                a->setText(assetType->getId());
                ui->AssetTypes_list->addItem(a);
            }
        }
    }

    if (ui->AssetTypes_list->count() == 0) {
        ui->AssetTypes_list->addItem("No Asset Types in asset Registry.");
    }
    if (ui->Custodians_list->count() == 0) {
         ui->AssetTypes_list->addItem("No Custodians in asset Registry.");
    }

}

void MainWindow::updateList() {
    ui->AssetTypes_list->clear();
    ui->Custodians_list->clear();
    this->fillList();
}

bool MainWindow::deleteCustodian() {

    auto list = ui->Custodians_list->selectedItems();

    QMessageBox::StandardButton reply = QMessageBox::question(this,"Are you sure.","Are you sure you want to delete "+ QString(list.length())+" Custodians?",
                          QMessageBox::Yes |QMessageBox::No );
    if (reply == QMessageBox::Yes) {
        int failures = 0;
        int success = 0;
        for (auto i = list.begin();i != list.end();i++) {
           QString val = i.i->t()->data(Qt::DisplayRole).toString();
           if (!_reg.get()->deleteEntity(val))
               failures++;
           else {
               success++;
           }
        }
        if (failures > 0) {
            QMessageBox::warning(this,"Failure","Unable to delete "+QString(failures)+" Custodians.");
        }
        this->updateList();
        return true;

    }

}
void MainWindow::editCustodian() {

    if (ui->Custodians_list->selectedItems().count() == 1) {
        this->openForm(UI::FormStatus::EDITCUSTODIAN,ui->Custodians_list->selectedItems().first()->data(Qt::DisplayRole).toString());
    }else if (ui->Custodians_list->selectedItems().count() > 1) {
        QMessageBox::warning(this,"Invalid items.", "Can only edit one custodian at a time.",QMessageBox::Ok);
    } else if (ui->Custodians_list->selectedItems().count()  == 0) {
        QMessageBox::warning(this,"Invalid items.", "Please select a custodian.",QMessageBox::Ok);
    }



}
void MainWindow::addCustodian() {
    QMap<QString,QVariant> params;
    params.insert("DateTime",QVariant(QDateTime::currentDateTime()));
    params.insert("LastEditedBy",QVariant(this->_reg->username()));

    QString id = this->_reg->generateId();
    this->_reg->storeEntity(this->_reg->getFactory()->createCustodian( id,params,this->_reg.get()));
    this->openForm(UI::EDITCUSTODIAN,id);
}


bool MainWindow::deleteAssetType() {
    auto list = ui->AssetTypes_list->selectedItems();

    QMessageBox::StandardButton reply = QMessageBox::question(this,"Are you sure.","Are you sure you want to delete "+ QString(list.length())+" Asset Types?",
                          QMessageBox::Yes |QMessageBox::No );
    if (reply == QMessageBox::Yes) {
        int failures = 0;
        int success = 0;
        for (auto i = list.begin();i != list.end();i++) {
           QString val = i.i->t()->data(Qt::DisplayRole).toString();
           if (!_reg.get()->deleteEntity(val))
               failures++;
           else {
               success++;
           }
        }
        if (failures > 0) {
            QMessageBox::warning(this,"Failure","Unable to delete "+QString(failures)+" Asset Types.");
        }
        this->updateList();
        return true;
    }
    return false;

}
void MainWindow::editAssetType() {
    if (ui->AssetTypes_list->selectedItems().count() == 1) {
        this->openForm(UI::FormStatus::EDITCUSTODIAN,ui->AssetTypes_list->selectedItems().first()->data(Qt::DisplayRole).toString());
    }else if (ui->AssetTypes_list->selectedItems().count() > 1) {
        QMessageBox::warning(this,"Invalid items.", "Can only edit one custodian at a time.",QMessageBox::Ok);
    } else if (ui->AssetTypes_list->selectedItems().count()  == 0) {
        QMessageBox::warning(this,"Invalid items.", "Please select a custodian.",QMessageBox::Ok);
    }

}
void MainWindow::addAssetType() {

    QMap<QString,QVariant> params;
    params.insert("DateTime",QVariant(QDateTime::currentDateTime()));
    params.insert("LastEditedBy",QVariant(this->_reg->username()));

    QString id = this->_reg->generateId();
    this->_reg->storeEntity(this->_reg->getFactory()->createAssetType(id,params,this->_reg.get()));
    this->openForm(UI::EDITASSETTYPE,id);
}




MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_addAssetType_button_clicked()
{
    this->addAssetType();
}

void MainWindow::on_deleteAssetType_button_clicked()
{
    this->deleteAssetType();
}

void MainWindow::on_editAssetType_button_clicked()
{
    editAssetType();
}

void MainWindow::on_addCustodian_button_clicked()
{
    addCustodian();
}

void MainWindow::on_deleteCustodian_button_clicked()
{
    deleteCustodian();
}

void MainWindow::on_editCustodian_button_clicked()
{
    editCustodian();
}
