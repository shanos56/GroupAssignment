#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "abstractassetregister.h"
#include "formstatus.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    std::shared_ptr<AbstractAssetRegister> _reg;

    void fillList();
    void updateList();

public:
    explicit MainWindow(std::shared_ptr<AbstractAssetRegister> reg, QWidget *parent = nullptr);
    ~MainWindow();


    bool deleteCustodian();
    void editCustodian();
    void addCustodian();


    bool deleteAssetType();
    void editAssetType();
    void addAssetType();

signals:
    void openForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS);
    void closeForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS);
    void openForm(const UI::FormStatus stat = UI::FormStatus::NULLSTATUS,QString id = "");

private slots:
    void on_AssetTypes_2_itemPressed(QListWidgetItem *item);

    void on_AssetType_add_clicked();

    void on_addAssetType_button_clicked();

    void on_deleteAssetType_button_clicked();

    void on_editAssetType_button_clicked();

    void on_addCustodian_button_clicked();

    void on_deleteCustodian_button_clicked();

    void on_editCustodian_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
