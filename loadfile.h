#ifndef LOADFILE_H
#define LOADFILE_H

#include <QDialog>

namespace Ui {
class LoadFile;
}

class LoadFile : public QDialog
{
    Q_OBJECT

public:
    explicit LoadFile(QWidget *parent = nullptr);
    ~LoadFile();

    bool isLocalFile(const QString &str);

private slots:


    void on_pushButton_quit_clicked();

    void on_pushButton_upload_clicked();

private:
    Ui::LoadFile *ui;
};

#endif // LOADFILE_H
