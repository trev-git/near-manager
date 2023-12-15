#include "nearmanager.h"
#include "ui_nearmanager.h"
#include "filecopydialog.h"
#include "filemovedialog.h"

#include <QDebug>
#include <QMessageBox>

NearManager::NearManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NearManager)
{
    ui->setupUi(this);
    leftFsModel = new QFileSystemModel;
    rightFsModel = new QFileSystemModel;
    leftDir = new QDir;
    rightDir = new QDir;
    isHidden = true;

    leftDir->setPath(QDir::homePath());
    rightDir->setPath(QDir::homePath());
    ui->leftDirectoryName->setText(leftDir->absolutePath());
    ui->rightDirectoryName->setText(rightDir->absolutePath());

    ui->leftDirectoryView->setModel(leftFsModel);
    ui->leftDirectoryView->setRootIndex(leftFsModel->setRootPath(leftDir->absolutePath()));
    ui->rightDirectoryView->setModel(rightFsModel);
    ui->rightDirectoryView->setRootIndex(rightFsModel->setRootPath(rightDir->absolutePath()));

    connect(this->ui->leftDirectoryView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &NearManager::onSelectionChanged);
    connect(this->ui->rightDirectoryView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &NearManager::onSelectionChanged);
}

NearManager::~NearManager()
{
    delete ui;
    delete leftFsModel;
    delete rightFsModel;
}

void NearManager::on_leftBackButton_clicked()
{
    if (leftDir->cdUp())
    {
        ui->leftDirectoryView->setRootIndex(leftFsModel->setRootPath(leftDir->absolutePath()));
        ui->leftDirectoryName->setText(leftDir->absolutePath());
    }
}

void NearManager::on_rightBackButton_clicked()
{
    if (rightDir->cdUp())
    {
        ui->rightDirectoryView->setRootIndex(rightFsModel->setRootPath(rightDir->absolutePath()));
        ui->rightDirectoryName->setText(rightDir->absolutePath());
    }
}

void NearManager::on_leftDirectoryView_doubleClicked(const QModelIndex &index)
{
    if (leftFsModel->isDir(index))
    {
        leftDir->cd(leftFsModel->filePath(index));
        ui->leftDirectoryView->setRootIndex(index);
        ui->leftDirectoryName->setText(leftFsModel->filePath(index));
    }
}

void NearManager::on_rightDirectoryView_doubleClicked(const QModelIndex &index)
{
    if (rightFsModel->isDir(index))
    {
        rightDir->cd(rightFsModel->filePath(index));
        ui->rightDirectoryView->setRootIndex(index);
        ui->rightDirectoryName->setText(rightFsModel->filePath(index));
    }
}

void NearManager::on_actionCopy_triggered()
{
    QItemSelectionModel *leftItemSelection = this->ui->leftDirectoryView->selectionModel();
    QItemSelectionModel *rightItemSelection = this->ui->rightDirectoryView->selectionModel();

    if (leftItemSelection->hasSelection())
    {
        FileCopyDialog copyDialog(leftFsModel->fileInfo(leftItemSelection->currentIndex()).absoluteFilePath(), this->ui->rightDirectoryName->text());
        copyDialog.exec();
    }

    if (rightItemSelection->hasSelection())
    {
        FileCopyDialog copyDialog(rightFsModel->fileInfo(rightItemSelection->currentIndex()).absoluteFilePath(), this->ui->leftDirectoryName->text());
        copyDialog.exec();
    }
}

void NearManager::on_actionMove_triggered()
{
    QItemSelectionModel *leftItemSelection = this->ui->leftDirectoryView->selectionModel();
    QItemSelectionModel *rightItemSelection = this->ui->rightDirectoryView->selectionModel();

    if (leftItemSelection->hasSelection())
    {
        QFileInfo file(leftFsModel->fileInfo(leftItemSelection->currentIndex()));
        FileMoveDialog moveDialog(file.absoluteFilePath(), this->ui->rightDirectoryName->text() + "/" + file.fileName());
        moveDialog.exec();
    }

    if (rightItemSelection->hasSelection())
    {
        QFileInfo file(leftFsModel->fileInfo(rightItemSelection->currentIndex()));
        FileMoveDialog moveDialog(file.absoluteFilePath(), this->ui->leftDirectoryName->text() + "/" + file.fileName());
        moveDialog.exec();
    }
}

void NearManager::on_actionShow_hidden_files_triggered()
{
    if (isHidden)
    {
        this->leftFsModel->setFilter(QDir::Filter::Hidden | QDir::Filter::AllEntries | QDir::Filter::NoDotAndDotDot);
        this->rightFsModel->setFilter(QDir::Filter::Hidden | QDir::Filter::AllEntries | QDir::Filter::NoDotAndDotDot);
        isHidden = !isHidden;
    }
    else
    {
        this->leftFsModel->setFilter(QDir::Filter::AllEntries | QDir::Filter::NoDotAndDotDot);
        this->rightFsModel->setFilter(QDir::Filter::Hidden | QDir::Filter::AllEntries | QDir::Filter::NoDotAndDotDot);
        isHidden = !isHidden;
    }
}

void NearManager::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    // I Will Kill your Entire family if this PIEce of COde won't WORK!!!!
    if (sender() == this->ui->leftDirectoryView->selectionModel())
    {
        this->ui->rightDirectoryView->selectionModel()->clearSelection();
    }
    else if (sender() == this->ui->rightDirectoryView->selectionModel())
    {
        this->ui->leftDirectoryView->selectionModel()->clearSelection();
    }
}
