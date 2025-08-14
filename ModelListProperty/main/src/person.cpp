#include "person.hpp"

Person::Person(QObject *parent): QObject{parent} {}

Person::Person(const QString &o_names, const QString &o_favoriteColor, int i_age, QObject *po_parent)
    : QObject{ po_parent }
    , _o_names{o_names}
    , _o_favoriteColor{ o_favoriteColor }
    , _i_age{ i_age } {

}

QString Person::names() const {
    return _o_names;
}

QString Person::favoriteColor() const {
    return _o_favoriteColor;
}

int Person::age() const {
    return _i_age;
}

void Person::setNames(const QString &o_names) {
    if (_o_names == o_names)
        return;
    _o_names = o_names;
    emit namesChanged(_o_names);
}

void Person::setFavoriteColor(const QString &o_favoriteColor) {
    if (_o_favoriteColor == o_favoriteColor)
        return;
    _o_favoriteColor = o_favoriteColor;
    emit favoriteColorChanged(_o_favoriteColor);
}

void Person::setAge(int i_age) {
    if (_i_age == i_age)
        return;
    _i_age = i_age;
    emit ageChanged(_i_age);
}
