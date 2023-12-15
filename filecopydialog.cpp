#include "filecopydialog.h"
#include "ui_filecopydialog.h"

#include <QFile>
#include <QMessageBox>

FileCopyDialog::FileCopyDialog(QString _src, QString _dst, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileCopyDialog),
    src(_src),
    dst(_dst)
{
    ui->setupUi(this);
}

FileCopyDialog::~FileCopyDialog()
{
    delete ui;
}

void FileCopyDialog::on_buttonBox_accepted()
{
    if (!QFile::copy(this->src, this->dst + "/" + this->ui->lineEdit->text()))
    {
        QMessageBox::critical(this, "Copy error", "Error copying file: " + this->src);
    }
}
