#include "loadfile.h"
#include "ui_loadfile.h"
#include <Qurl>


LoadFile::LoadFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadFile)
{
    ui->setupUi(this);
}

LoadFile::~LoadFile()
{
    delete ui;
}
bool LoadFile::isLocalFile(const QString &str)
{
    return QUrl::fromUserInput(str).isLocalFile();
}


void LoadFile::on_pushButton_quit_clicked()
{
    QApplication::quit();

}

void LoadFile::on_pushButton_upload_clicked()
{

}
