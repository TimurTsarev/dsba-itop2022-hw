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
    QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    //QObject::connect(ui->addRowButton, SIGNAL(clicked()), this, SLOT(addRowSlot));
    //QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveButon()));


    _loadFile = new LoadDataFile(this);
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(_loadFile);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);

    proxyModel2 = new QSortFilterProxyModel(this);
    proxyModel2->setSourceModel(_loadFile);
    //ui->tableView_2->setModel(proxyModel2);



    _transposeModel = new QTransposeProxyModel(this);
    _transposeModel->setSourceModel(_loadFile);
    ui->tableView_2->setModel(_transposeModel);

//    for(int i = 1; i < _transposeModel->columnCount(); ++i)
//    {
//        ui->tableView_2->hideColumn(i);
//    }
//    _shownDetailsColumn = 0;


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
    proxyModel2->setSourceModel(_loadFile);
    ui->tableView->setModel(proxyModel);
    _transposeModel->setSourceModel(_loadFile);
    for(int i = 1; i < _transposeModel->columnCount(); ++i)
    {
        ui->tableView_2->hideColumn(i);
    }
    _shownDetailsColumn = 0;

}


void MainWindow::on_addRowButton_clicked()
{
    AddRowDialog newRow(this);
    if (newRow.exec() == QDialog::Accepted)
    {
        _loadFile->appendRow(newRow.getNewRow());
    }
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
    proxyModel2->setFilterRegularExpression(QRegularExpression(arg1));
    _transposeModel->setSourceModel(proxyModel2);
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
