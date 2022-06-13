#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loaddatafile.h"
#include <qsortfilterproxymodel.h>
#include <QTransposeProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
   void loadFile();

   void on_addRowButton_clicked();

   void on_saveButton_clicked();

   void on_chooseRestaurant_textChanged(const QString &arg1);

   void on_deleteButton_clicked();

   void showAbout();

private:
    Ui::MainWindow *ui;
    LoadDataFile *_loadFile;
    QSortFilterProxyModel *proxyModel;
    QSortFilterProxyModel *proxyModel2;
    QTransposeProxyModel *_transposeModel;
    size_t _shownDetailsColumn;
};
#endif // MAINWINDOW_H
