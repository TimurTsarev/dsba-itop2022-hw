#ifndef CUSTOMPROXYMODEL_H
#define CUSTOMPROXYMODEL_H

#include <QSortFilterProxyModel>

class CustomProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit CustomProxyModel(QObject *parent = nullptr, QString name = "", QString votes = "", QString rating = "",
                              QString adress = "",
                              QString cuisine = "", QString openHours = "");

    void setNameOfRestaurant(QString name);

    void setNumberVotes(QString num);

    void setRating(QString rating);

    void setAdress(QString adress);

    void setCuisine(QString cuisine);

    void setOpenHours(QString openHours);

    bool nameIsCorrect(QString name) const;

    bool votesIsCorrect(QString votes) const;

    bool ratingIsCorrect(QString rating) const;

    bool adressIsCorrect(QString adress) const;

    bool cuisineIsCorrect(QString cuisine) const;

    bool openHoursIsCorrect(QString openHours) const;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    signals:

private:
    QString nameRestaurant;
    QString numVotes;
    QString ratingRestaurant;
    QString adressRestaurant;
    QString cuisineRestaurant;
    QString openHoursRestaurant;

};

#endif // CUSTOMPROXYMODEL_H
