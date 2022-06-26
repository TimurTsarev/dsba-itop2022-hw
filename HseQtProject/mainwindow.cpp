#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addrowdialog.h"
#include "aboutdialog.h"
#include <QFileDialog>
#include <QDialog>
#include <QSortFilterProxyModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Restaurants");
    QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));


    _loadFile = new LoadDataFile(this);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(_loadFile);

    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->splitter_4->setStretchFactor(0, 0);
    ui->splitter_4->setStretchFactor(1, 0);
    ui->splitter_4->setStretchFactor(2, 0);
    ui->splitter_4->setStretchFactor(3, 1);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadFile()
{
    delete _loadFile;

    _loadFile = new LoadDataFile(this);
    QString fileName = QFileDialog::getOpenFileName(this, "Load file", "../", "Data (*.csv)");

    _loadFile->fillDataTableFromFile(fileName);

    proxyModel->setSourceModel(_loadFile);
    ui->tableView->setModel(proxyModel);

}


void MainWindow::on_addRowButton_clicked()
{
    AddRowDialog newRow(this);
    if (newRow.exec() == QDialog::Accepted)
    {
        _loadFile->appendRow(newRow.getNewRow());
    }
    int lastRow = _loadFile->rowCount() - 1;
    QModelIndex baseIdx = _loadFile->index(lastRow, 0);
    QModelIndex proxyIdx = proxyModel->mapFromSource(baseIdx);
    ui->tableView->setCurrentIndex(proxyIdx);
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File",
                                                    "../",
                                                    "Data (*.csv)");
    _loadFile->saveDataTableToFile(fileName);
}




void MainWindow::on_chooseRestaurant_textChanged(const QString &arg1)
{
    proxyModel->setFilterRegularExpression(QRegularExpression(arg1.toLower()));
    proxyModel->setFilterKeyColumn(0);
    ui->tableView->setModel(proxyModel);
}

void MainWindow::on_chooseRating_textChanged(const QString &arg1)
{
    //QValidator *validator = new QDoubleValidator(this);
    proxyModel->setFilterRegularExpression(QRegularExpression(arg1));
    proxyModel->setFilterKeyColumn(2);
    //ui->chooseRating->setValidator(validator);
    ui->tableView->setModel(proxyModel);
}


void MainWindow::on_chooseVotes_textChanged(const QString &arg1)
{
    QValidator *validator = new QIntValidator(this);
    proxyModel->setFilterRegularExpression(QRegularExpression(arg1));
    proxyModel->setFilterKeyColumn(1);
    ui->chooseVotes->setValidator(validator);
    ui->tableView->setModel(proxyModel);
}



void MainWindow::on_chooseAdress_textChanged(const QString &arg1)
{
    proxyModel->setFilterRegularExpression(QRegularExpression(arg1.toLower()));
    proxyModel->setFilterKeyColumn(3);
    ui->tableView->setModel(proxyModel);
}


void MainWindow::on_chooseCuisine_textChanged(const QString &arg1)
{
    proxyModel->setFilterRegularExpression(QRegularExpression(arg1.toLower()));
    proxyModel->setFilterKeyColumn(4);
    ui->tableView->setModel(proxyModel);
}

void MainWindow::on_chooseOpenHours_textChanged(const QString &arg1)
{
    proxyModel->setFilterRegularExpression(QRegularExpression(arg1.toLower()));
    proxyModel->setFilterKeyColumn(6);
    ui->tableView->setModel(proxyModel);
}


void MainWindow::on_deleteButton_clicked()
{
    QModelIndex idx1 = ui->tableView->currentIndex();
    QModelIndex idx4 = proxyModel->mapToSource(idx1);
    _loadFile->removeRow(idx4.row());
}

void MainWindow::showAbout()
{
    AboutDialog d;
    d.exec();
}



void MainWindow::on_Cost_textChanged(const QString &arg1)
{
    QValidator *validator = new QDoubleValidator(this);
    proxyModel->setFilterRegularExpression(QRegularExpression(arg1.toLower()));
    proxyModel->setFilterKeyColumn(5);
    ui->chooseRating->setValidator(validator);
    ui->tableView->setModel(proxyModel);
}


void MainWindow::on_chooseFairRating_textChanged(const QString &arg1)
{
    //QValidator *validator = new QDoubleValidator(this);
    proxyModel->setFilterRegularExpression(QRegularExpression(arg1.toLower()));
    proxyModel->setFilterKeyColumn(7);
    //ui->chooseRating->setValidator(validator);
    ui->tableView->setModel(proxyModel);
}

