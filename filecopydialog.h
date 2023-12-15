#ifndef FILECOPYDIALOG_H
#define FILECOPYDIALOG_H

#include <QDialog>

namespace Ui {
class FileCopyDialog;
}

class FileCopyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileCopyDialog(QString _src, QString _dst, QWidget *parent = nullptr);
    ~FileCopyDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FileCopyDialog *ui;
    QString src;
    QString dst;
};

#endif // FILECOPYDIALOG_H
