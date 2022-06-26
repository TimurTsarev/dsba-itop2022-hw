#include "loaddatafile.h"
#include <QFile>
#include <QTextStream>

LoadDataFile::LoadDataFile(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void LoadDataFile::fillDataTableFromFile (QString path)
{
    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    QString firstline = inputStream.readLine();
    for (QString& item : firstline.split(";"))
    {
        headerList.append(item);
    }
    headerList.append("FairSorting");

    while(!inputStream.atEnd())
    {
        QString line = inputStream.readLine();

        int numVotes = 0;
        double rating = 0;

        QList<QVariant> dataRow;
        int columnIdx = 0;
        for(QString& item : line.split(";"))
        {
            if (columnIdx == 0
                    || columnIdx == 3
                    || columnIdx == 4)
            {
                dataRow.append(item.toLower());
            } else if (columnIdx == 1)
            {
                QStringList a = item.split(" ");
                dataRow.append(a[0].toInt());
                numVotes = a[0].toInt();
            } else if (columnIdx == 2)
            {
                dataRow.append(item.toDouble());
                rating = item.toDouble();
            } else if (columnIdx == 5)
            {
                QString s;
                for (int i = 0; i < item.size(); ++i)
                {
                    if (item[i].isDigit())
                        s += item[i];
                }
                dataRow.append(s.toDouble());
            } else if (columnIdx == 6)
            {
                item.replace("вЂ“", "-");
                dataRow.append(item.toLower());
            }
            ++columnIdx;
        }
        double fairSorting = (2.5 * 500 + rating * numVotes) / (numVotes + 500);
        dataRow.append(fairSorting);
       dataTable.append(dataRow);
    }
    inputFile.close();
}

void LoadDataFile::saveDataTableToFile(QString path)
{
    QFile outputFile(path);
    outputFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream outputStream(&outputFile);

    bool first = true;
    for (QString& item : headerList) {
        if (first)
        {
            outputStream << item;
            first = false;
        }
        else
        {
            outputStream << ",";
            outputStream << item;
        }
    }
    outputStream << "\n";

    for (QList<QVariant>& row: dataTable)
    {
        bool first = true;
        for (QVariant& item : row) {
            if (first)
            {
                outputStream << item.toString();
                first = false;
            }
            else
            {
                outputStream << ",";
                outputStream << item.toString();
            }
        }
        outputStream << "\n";
    }

    outputFile.close();
}

QVariant LoadDataFile::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headerList[section];
    }
    return QVariant();
}

bool LoadDataFile::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

int LoadDataFile::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return dataTable.size();
}

int LoadDataFile::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (dataTable.empty())
    {
        return 0;
    }
    return dataTable[0].size();
}

QVariant LoadDataFile::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        int row = index.row();
        int col = index.column();
        return dataTable[row][col];
    }
    return QVariant();
}

bool LoadDataFile::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
            int row = index.row();
            int col = index.column();
            dataTable[row][col] = value;
            emit dataChanged(index, index, {role});
            return true;
        }
        return false;
}

Qt::ItemFlags LoadDataFile::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }

void LoadDataFile::appendRow(const QList<QVariant> &row)
{
     size_t newRowNumber = rowCount();
     beginInsertRows(QModelIndex(), newRowNumber, newRowNumber);
     dataTable.append(row);
     endInsertRows();
    }


void LoadDataFile::removeRow(int idx)
{
     beginRemoveRows(QModelIndex(), idx, idx);
     dataTable.removeAt(idx);
     endRemoveRows();
    }
