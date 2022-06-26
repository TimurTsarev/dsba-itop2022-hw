#ifndef LOADDATAFILE_H
#define LOADDATAFILE_H

#include <QAbstractTableModel>

class LoadDataFile : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit LoadDataFile(QObject *parent = nullptr);

    void fillDataTableFromFile(QString path);

    void saveDataTableToFile(QString path);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void appendRow(const QList <QVariant> &row);

    void removeRow(int idx);

private:
    QList <QString> headerList;
    QList <QList<QVariant>> dataTable;
};

#endif // LOADDATAFILE_H
