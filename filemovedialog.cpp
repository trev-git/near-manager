#include "filemovedialog.h"
#include "ui_filemovedialog.h"

#include <QFile>
#include <QMessageBox>

FileMoveDialog::FileMoveDialog(QString _src, QString _dst, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileMoveDialog),
    src(_src),
    dst(_dst)
{
    ui->setupUi(this);
    ui->lineEdit->setText(_dst);
}

FileMoveDialog::~FileMoveDialog()
{
    delete ui;
}

void FileMoveDialog::on_buttonBox_accepted()
{
    if (!QFile::rename(this->src, this->dst))
    {
        QMessageBox::critical(this, "Move error", "Error moving file: " + this->src);
    }
}
