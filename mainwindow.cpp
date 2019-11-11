#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include <QMessageBox>
#include "custodianform.h"
#include "custodian.h"

MainWindow::MainWindow(std::shared_ptr<AbstractAssetRegister>& reg,QWidget *parent) :
    QMainWindow(parent),
    _reg{reg},
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->fillList();
    this->setWindowTitle("Dashboard");


}

void MainWindow::fillList() {

    auto list = _reg.get()->allEntities();
    if (!list.isEmpty()) {
        for (auto i = list.begin();i != list.end();i++) {
            if (i->get()->type().compare("Custodian") == 0) {
                ui->Custodians_list->addItem(i->get()->getId());
            } else if (i->get()->type().compare("AssetType") == 0) {
                ui->AssetTypes_list->addItem(i->get()->getId());
            } else if (i->get()->type().compare("Asset") == 0) {
                ui->Asset_list->addItem(i->get()->getId());
            }
        }
    }

    if (ui->Asset_list->count() == 0) {
        ui->Asset_list->addItem("No Assets in asset Registry.");
    }


    if (ui->AssetTypes_list->count() == 0) {
        ui->AssetTypes_list->addItem("No Asset Types in asset Registry.");
    }
    if (ui->Custodians_list->count() == 0) {
         ui->Custodians_list->addItem("No Custodians in asset Registry.");
    }

}

void MainWindow::updateList() {
    ui->AssetTypes_list->clear();
    ui->Custodians_list->clear();
    ui->Asset_list->clear();
    this->fillList();
}

bool MainWindow::deleteCustodian() {

    auto list = ui->Custodians_list->selectedItems();

    QMessageBox::StandardButton reply = QMessageBox::question(this,"Are you sure.","Are you sure you want to delete "+ QString::number(list.length())+" Custodians?",
                          QMessageBox::Yes |QMessageBox::No );
    if (reply == QMessageBox::Yes) {
        int failures = 0;
        int success = 0;

        for (auto i = list.begin();i != list.end();i++) {

           QString val = i.i->t()->text();
           if (!_reg.get()->deleteEntity(val)) {

               failures++;
           } else {
               success++;
           }
        }
        if (failures > 0) {
            QMessageBox::warning(this,"Failure","Unable to delete "+QString::number(failures)+" Custodians.");
        }
        this->updateList();
        return true;

    }

}
void MainWindow::editCustodian() {

    if (ui->Custodians_list->selectedItems().count() == 1) {
        emit this->openForm2(UI::FormStatus::EDITCUSTODIAN,ui->Custodians_list->selectedItems().first()->text());
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

    emit this->openForm2(UI::EDITCUSTODIAN,id);
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
        emit this->openForm2(UI::FormStatus::EDITASSETTYPE,ui->AssetTypes_list->selectedItems().first()->text());
    }else if (ui->AssetTypes_list->selectedItems().count() > 1) {
        QMessageBox::warning(this,"Invalid items.", "Can only edit one Asset type at a time.",QMessageBox::Ok);
    } else if (ui->AssetTypes_list->selectedItems().count()  == 0) {
        QMessageBox::warning(this,"Invalid items.", "Please select an asset type.",QMessageBox::Ok);
    }

}
void MainWindow::addAssetType() {

    QMap<QString,QVariant> params;
    params.insert("DateTime",QVariant(QDateTime::currentDateTime()));
    params.insert("LastEditedBy",QVariant(this->_reg->username()));


    QString id = this->_reg->generateId();

    auto a = this->_reg->getFactory();

    this->_reg->storeEntity(this->_reg->getFactory()->createAssetType(id,params,this->_reg.get()));

    emit openForm2(UI::EDITASSETTYPE,id);
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
