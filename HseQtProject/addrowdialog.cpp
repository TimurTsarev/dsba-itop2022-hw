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
    newRow.push_back(ui->VotesSpinBox->value());
    newRow.push_back(ui->RatingDoubleSpinBox->value());
    newRow.push_back(ui->AddresLineEdit->text());
    newRow.push_back(ui->CusineLineEdit->text());
    newRow.push_back(ui->CostDoubleSpinBox->value());
    newRow.push_back(ui->TimingLineEdit->text());
    double votes = newRow[1].toDouble();
    double rating = newRow[2].toDouble();
    double fairSorting = (2.5 * 500 + rating * votes) / (votes + 500);
    newRow.push_back(fairSorting);

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
