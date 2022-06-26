#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loaddatafile.h"
#include <qsortfilterproxymodel.h>
#include <QTransposeProxyModel>
#include "customproxymodel.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private
    slots:
            void loadFile();

    void on_addRowButton_clicked();

    void on_saveButton_clicked();

    void on_chooseRestaurant_textChanged(const QString &arg1);

    void on_deleteButton_clicked();

    void showAbout();

    void on_chooseRating_textChanged(const QString &arg1);

    void on_chooseVotes_textChanged(const QString &arg1);

    void on_chooseAdress_textChanged(const QString &arg1);

    void on_chooseCuisine_textChanged(const QString &arg1);

    void on_chooseOpenHours_textChanged(const QString &arg1);

    void on_Cost_textChanged(const QString &arg1);

    void on_chooseFairRating_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    LoadDataFile *_loadFile;
    QSortFilterProxyModel *proxyModel;
    size_t _shownDetailsColumn;
};
#endif // MAINWINDOW_H
