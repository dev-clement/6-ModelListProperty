#include <QDebug>
#include "datasource.hpp"

DataSource::DataSource(QObject *parent)
    : QObject{parent} {
    // addPerson("Jamie Lannister", "red", 33);
    // addPerson("Marry Lane", "cyan", 26);
    // addPerson("Steve Moors", "yellow", 44);
    // addPerson("Victor Trunk", "dodgerblue", 30);
    // addPerson("Ariel Geeny", "blue", 33);
    // addPerson("Knut Vikran", "lightblue", 26);
}

QList<Person *> DataSource::dataItems() const {
    return _o_persons;
}

void DataSource::addPerson(Person *po_person) {
    emit prePersonAdded();
    _o_persons.append(po_person);
    emit postPersonAdded();
}

void DataSource::addPerson(const QString &o_name, const QString &o_favoriteColor, const int i_age) {
    Person *po_person = new Person{o_name, o_favoriteColor, i_age, this};
    addPerson(po_person);
}

int DataSource::personCount() {
    return _o_persons.count();
}

Person *DataSource::personAt(int i_idx) {
    return _o_persons.at(i_idx);
}

void DataSource::clearPersons() {
    _o_persons.clear();
}

void DataSource::removeLastPerson() {
    removePerson(_o_persons.size() - 1);
}

void DataSource::removePerson(int i_idx) {
    if (i_idx < 0 || i_idx >= _o_persons.size()) {
        return ;
    }
    emit prePersonRemoved(i_idx);
    _o_persons.removeAt(i_idx);
    emit postPersonRemoved();
}
