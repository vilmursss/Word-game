#include "confirmationdialog.h"
#include "ui_confirmationdialog.h"
#include "addword.h"

confirmationDialog::confirmationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmationDialog)
{
    ui->setupUi(this);
}

confirmationDialog::~confirmationDialog()
{
    delete ui;
}
