#include "addrowdialog.h"
#include "ui_addrowdialog.h"
#include <QMessageBox>

AddRowDialog::AddRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRowDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Add row");

    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(saveAddedRow()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    }

void AddRowDialog::saveAddedRow()
{
    newRow.push_back(ui->NameLineEdit->text());
    newRow.push_back(ui->VotesLineEdit->text().toInt());
    newRow.push_back(ui->RatingLineEdit->text().toDouble());
    newRow.push_back(ui->AddresLineEdit->text());
    newRow.push_back(ui->CusineLineEdit->text());
    newRow.push_back(ui->CostLineEdit->text().toDouble());
    newRow.push_back(ui->TimingLineEdit->text());

    accept();
    }


const QList<QVariant>& AddRowDialog::getNewRow()
{
    return newRow;
    }


AddRowDialog::~AddRowDialog()
{
    delete ui;
    }
