#ifndef NEARMANAGER_H
#define NEARMANAGER_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QItemSelectionModel>

QT_BEGIN_NAMESPACE
namespace Ui { class NearManager; }
QT_END_NAMESPACE

class NearManager : public QMainWindow
{
    Q_OBJECT

public:
    NearManager(QWidget *parent = nullptr);
    ~NearManager();

private slots:
    void on_leftBackButton_clicked();

    void on_rightBackButton_clicked();

    void on_leftDirectoryView_doubleClicked(const QModelIndex &index);

    void on_rightDirectoryView_doubleClicked(const QModelIndex &index);

    void on_actionCopy_triggered();

    void on_actionMove_triggered();

    void on_actionShow_hidden_files_triggered();

    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void on_actionCreate_new_directory_triggered();

private:
    Ui::NearManager *ui;
    QFileSystemModel *leftFsModel;
    QFileSystemModel *rightFsModel;
    QDir *leftDir;
    QDir *rightDir;
    bool isHidden;
};
#endif // NEARMANAGER_H
