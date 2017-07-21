#ifndef CONFIRMATIONDIALOG_H
#define CONFIRMATIONDIALOG_H

#include <QDialog>

namespace Ui {
class confirmationDialog;
}

class confirmationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit confirmationDialog(QWidget *parent = 0);
    ~confirmationDialog();

private:
    Ui::confirmationDialog *ui;
};

#endif // CONFIRMATIONDIALOG_H
