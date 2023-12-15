#ifndef FILEMOVEDIALOG_H
#define FILEMOVEDIALOG_H

#include <QDialog>

namespace Ui {
class FileMoveDialog;
}

class FileMoveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileMoveDialog(QString _src, QString _dst, QWidget *parent = nullptr);
    ~FileMoveDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FileMoveDialog *ui;
    QString src;
    QString dst;
};

#endif // FILEMOVEDIALOG_H
