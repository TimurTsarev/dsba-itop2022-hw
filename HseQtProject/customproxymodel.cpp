#include "customproxymodel.h"

CustomProxyModel::CustomProxyModel(QObject *parent, QString name, QString votes, QString rating, QString adress,
                                   QString cuisine, QString openHours)
        : QSortFilterProxyModel{parent}
{
    nameRestaurant = name;
    numVotes = votes;
    ratingRestaurant = rating;
    adressRestaurant = adress;
    cuisineRestaurant = cuisine;
    openHoursRestaurant = openHours;
}

bool CustomProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex idx0 = sourceModel()->index(sourceRow, 1);
    QModelIndex idx1 = sourceModel()->index(sourceRow, 2);
    QModelIndex idx2 = sourceModel()->index(sourceRow, 3);
    QModelIndex idx3 = sourceModel()->index(sourceRow, 4);
    QModelIndex idx4 = sourceModel()->index(sourceRow, 5);
    QModelIndex idx5 = sourceModel()->index(sourceRow, 6);

    QVariant dataAtIndex0 = sourceModel()->data(idx0); //name
    bool isNameCorrect = nameIsCorrect(dataAtIndex0.toString());

    QVariant dataAtIndex1 = sourceModel()->data(idx1); //votes
    bool isVotesCorrect = votesIsCorrect(dataAtIndex1.toString());

    QVariant dataAtIndex2 = sourceModel()->data(idx2); //rating
    bool IsRatingCorrect = ratingIsCorrect(dataAtIndex2.toString());

    QVariant dataAtIndex3 = sourceModel()->data(idx3); //adress
    bool isAdressCorrect = adressIsCorrect(dataAtIndex3.toString());

    QVariant dataAtIndex4 = sourceModel()->data(idx4); //cuisine
    bool isCuisineCorrect = cuisineIsCorrect(dataAtIndex4.toString());

    QVariant dataAtIndex5 = sourceModel()->data(idx5); //openHours
    bool isOpenHoursCorrect = openHoursIsCorrect(dataAtIndex5.toString());

    return isNameCorrect && isVotesCorrect && IsRatingCorrect && isAdressCorrect && isCuisineCorrect &&
           isOpenHoursCorrect;
}


void CustomProxyModel::setNameOfRestaurant(QString name)
{
    nameRestaurant = name;
    invalidateFilter();
}

void CustomProxyModel::setNumberVotes(QString num)
{
    numVotes = num;
    invalidateFilter();
}

void CustomProxyModel::setRating(QString rating)
{
    ratingRestaurant = rating;
    invalidateFilter();
}

void CustomProxyModel::setAdress(QString adress)
{
    adressRestaurant = adress;
    invalidateFilter();
}

void CustomProxyModel::setCuisine(QString cuisine)
{
    cuisineRestaurant = cuisine;
    invalidateFilter();
}

void CustomProxyModel::setOpenHours(QString openHours)
{
    openHoursRestaurant = openHours;
    invalidateFilter();
}

bool CustomProxyModel::nameIsCorrect(QString name) const
{
    if (name == "")
        return true;
    return nameRestaurant.contains(name);
}

bool CustomProxyModel::votesIsCorrect(QString votes) const
{
    if (votes == "")
        return true;
    return numVotes.contains(votes);
}

bool CustomProxyModel::ratingIsCorrect(QString rating) const
{
    if (rating == "")
        return true;
    return ratingRestaurant.contains(rating);
}

bool CustomProxyModel::adressIsCorrect(QString adress) const
{
    if (adress == "")
        return true;
    return adressRestaurant.contains(adress);
}

bool CustomProxyModel::cuisineIsCorrect(QString cuisine) const
{
    if (cuisine == "")
        return true;
    return cuisineRestaurant.contains(cuisine);
}

bool CustomProxyModel::openHoursIsCorrect(QString openHours) const
{
    if (openHours == "")
        return true;
    return openHoursRestaurant.contains(openHours);
}
