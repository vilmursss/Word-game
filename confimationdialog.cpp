#include "confimationdialog.h"
#include "ui_confimationdialog.h"
#include "addword.h"

addWord aW;

confimationDialog::confimationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confimationDialog)
{
    ui->setupUi(this);
    connect(ui->yes,&QPushButton::clicked,
            this,confirmationYes);
    connect(ui->no,&QPushButton::clicked,
            this,confirmationNo);
}

confimationDialog::~confimationDialog()
{
    delete ui;
}

void confimationDialog::confirmationYes() {

    bool response = true;

    aW.saveWordResponse(response);
    close();
}

void confimationDialog::confirmationNo() {
    bool response = false;

    aW.saveWordResponse(response);
    close();


}

void confimationDialog::updateText(QString confirmationText){

    ui->text->setText(confirmationText);
}

