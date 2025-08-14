#include <QDebug>
#include "personmodel.hpp"

PersonModel::PersonModel(QObject *po_parent)
    : QAbstractListModel{po_parent}
    , _po_dataSource{nullptr}
    , _b_signalConnected{false} {
    setDataSource(new DataSource{ this });
}

int PersonModel::rowCount(const QModelIndex &o_parent) const {
    Q_UNUSED(o_parent);
    return _po_dataSource->dataItems().size();
}

QVariant PersonModel::data(const QModelIndex &o_idx, int i_role) const {
    if (o_idx.row() < 0 || o_idx.row() >= _po_dataSource->personCount()) {
        qDebug() << "Index passed to data is invalid: " << o_idx.row();
        return QVariant{};
    }
    // Index is valid !
    Person *po_person = _po_dataSource->dataItems().at(o_idx.row());
    return i_role == NamesRole ? po_person->names()
            : i_role == FavoriteColorRole ? po_person->favoriteColor()
            : i_role == AgeRole ? po_person->age()
            : QVariant{};
}

QHash<int, QByteArray> PersonModel::roleNames() const {
    QHash<int, QByteArray> o_roles;
    o_roles[NamesRole] = "names";
    o_roles[FavoriteColorRole] = "favoriteColor";
    o_roles[AgeRole] = "age";
    return o_roles;
}

Qt::ItemFlags PersonModel::flags(const QModelIndex &o_idx) const {
    if (!o_idx.isValid()) {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEditable;
}

bool PersonModel::setData(const QModelIndex &o_idx, const QVariant &o_value, int i_role) {
    if (o_idx.row() >= _po_dataSource->personCount() || o_idx.row() < 0) {
        return false;
    }
    Person *po_person = _po_dataSource->dataItems().at(o_idx.row());
    bool b_somethingChanged{false};
    if (i_role == NamesRole) {
        b_somethingChanged = changePersonsName(po_person, o_value.toString());
    } else if (i_role == FavoriteColorRole) {
        b_somethingChanged = changePersonsFavoriteColor(po_person, o_value.toString());
    } else if (i_role == AgeRole) {
        b_somethingChanged = changePersonsAge(po_person, o_value.toInt());
    }
    if (b_somethingChanged) {
        emit dataChanged(o_idx, o_idx, QList<int>() << i_role);
    }
    return b_somethingChanged;
}

bool PersonModel::changePersonsName(Person *po_person, const QString &o_name) {
    if (po_person->names() == o_name) {
        return false;
    }
    qDebug() << "Changing the name from: " << po_person->names() << " to: " << o_name;
    po_person->setNames(o_name);
    return true;
}

bool PersonModel::changePersonsFavoriteColor(Person *po_person, const QString &o_favoriteColor) {
    if (po_person->favoriteColor() == o_favoriteColor) {
        return false;
    }
    qDebug() << "Changing the favorite color from: " << po_person->favoriteColor() << " to: " << o_favoriteColor;
    po_person->setFavoriteColor(o_favoriteColor);
    return true;
}

bool PersonModel::changePersonsAge(Person *po_person, int i_age) {
    if (po_person->age() == i_age) {
        return false;
    }
    qDebug() << "Changing the person's name from: " << po_person->age() << " to: " << i_age;
    po_person->setAge(i_age);
    return true;
}

DataSource *PersonModel::dataSource() const {
    return _po_dataSource;
}

QQmlListProperty<Person> PersonModel::persons() {
    return QQmlListProperty<Person>{this
                                    , this
                                    , &PersonModel::appendPerson
                                    , &PersonModel::personCount
                                    , &PersonModel::person
                                    , &PersonModel::clearPersons};
}

void PersonModel::setDataSource(DataSource *po_dataSource) {
    beginResetModel();
    if (_po_dataSource && _b_signalConnected) {
        _po_dataSource->disconnect();
    }
    _po_dataSource = po_dataSource;
    connect(_po_dataSource, &DataSource::prePersonAdded, this, [=](){
        const int i_idx = _po_dataSource->dataItems().size();
        beginInsertRows(QModelIndex{}, i_idx, i_idx);
    });
    connect(_po_dataSource, &DataSource::postPersonAdded, this, [=](){
        endInsertRows();
    });
    connect(_po_dataSource, &DataSource::prePersonRemoved, this, [=](int i_idx){
        beginRemoveRows(QModelIndex{}, i_idx, i_idx);
    });
    connect(_po_dataSource, &DataSource::postPersonRemoved, this, [=](){
        endRemoveRows();
    });
    _b_signalConnected = true;
    endResetModel();
}

void PersonModel::addPerson(const QString &o_name, const QString &o_favoriteColor, int i_age) {
    Person *po_person = new Person{o_name, o_favoriteColor, i_age, this};
    _po_dataSource->addPerson(po_person);
}

void PersonModel::removeLastPerson() {
    _po_dataSource->removePerson(_po_dataSource->personCount() - 1);
}

void PersonModel::appendPerson(QQmlListProperty<Person> *po_persons, Person *po_person) {
    reinterpret_cast<PersonModel *>(po_persons->data)->dataSource()->addPerson(po_person);
}

qsizetype PersonModel::personCount(QQmlListProperty<Person> *po_persons) {
    return reinterpret_cast<PersonModel *>(po_persons->data)->dataSource()->personCount();
}

Person *PersonModel::person(QQmlListProperty<Person> *po_persons, qsizetype i_idx) {
    return reinterpret_cast<PersonModel *>(po_persons->data)->dataSource()->personAt(i_idx);
}

void PersonModel::clearPersons(QQmlListProperty<Person> *po_persons) {
    reinterpret_cast<PersonModel *>(po_persons->data)->dataSource()->clearPersons();
}

void PersonModel::setPersons(QQmlListProperty<Person> &o_persons) {
    if (_o_persons == o_persons)
        return;
    _o_persons = o_persons;
    emit personsChanged(_o_persons);
}
