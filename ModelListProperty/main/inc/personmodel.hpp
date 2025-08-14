#ifndef PERSONMODEL_HPP
#define PERSONMODEL_HPP

#include <QtQml>
#include <QObject>
#include <QQmlListProperty>
#include <QAbstractListModel>
#include "datasource.hpp"

class PersonModel : public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(DataSource *dataSources READ dataSource WRITE setDataSource NOTIFY dataSourceChanged)
    Q_PROPERTY(QQmlListProperty<Person> persons READ persons WRITE setPersons NOTIFY personsChanged)
    Q_CLASSINFO("DefaultProperty", "persons")

    enum {
        NamesRole = Qt::UserRole + 1
        , FavoriteColorRole
        , AgeRole
    };
public:
    explicit PersonModel(QObject *po_parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &o_parent) const;
    QVariant data(const QModelIndex &o_idx, int i_role) const;
    QHash<int, QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex &o_idx) const;
    bool setData(const QModelIndex &o_idx, const QVariant &o_value, int i_role);

    // Property methods
    DataSource *dataSource() const;
    QQmlListProperty<Person> persons();

    void setPersons(QQmlListProperty<Person> &o_persons);
    void setDataSource(DataSource *po_dataSource);

    // Function to edit the person's object
    bool changePersonsName(Person *po_person, const QString &o_name);
    bool changePersonsFavoriteColor(Person *po_person, const QString &o_favoriteColor);
    bool changePersonsAge(Person *po_person, int i_age);

    // Helper functions
    Q_INVOKABLE void addPerson(const QString &o_name, const QString &o_favoriteColor, const int i_age);
    Q_INVOKABLE void removeLastPerson();

signals:
    void dataSourceChanged();
    void personsChanged(const QQmlListProperty<Person> &o_persons);

private:
    // Methods
    static void appendPerson(QQmlListProperty<Person> *po_persons, Person *po_person);
    static qsizetype personCount(QQmlListProperty<Person> *po_persons);
    static Person *person(QQmlListProperty<Person> *po_person, qsizetype i_idx);
    static void clearPersons(QQmlListProperty<Person> *po_persons);

private:
    DataSource *_po_dataSource;
    bool _b_signalConnected;
    QQmlListProperty<Person> _o_persons;
};

#endif // PERSONMODEL_HPP
