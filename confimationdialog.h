#ifndef CONFIMATIONDIALOG_H
#define CONFIMATIONDIALOG_H

#include <QDialog>


namespace Ui {
class confimationDialog;
}

class confimationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit confimationDialog(QWidget *parent = 0);
    ~confimationDialog();

    void updateText(QString confirmationText);
    void confirmationYes();
    void confirmationNo();

private:
    Ui::confimationDialog *ui;
};

#endif // CONFIMATIONDIALOG_H
