#ifndef DATASOURCE_HPP
#define DATASOURCE_HPP

#include <QList>
#include <QObject>
#include "person.hpp"

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = nullptr);

    QList<Person *> dataItems() const;

    void addPerson(Person *po_person);
    Q_INVOKABLE void addPerson(const QString &o_name = "Added person", const QString &o_favoriteColor = "yellowgreen", const int i_age = 23);
    Q_INVOKABLE void removePerson(int i_idx);
    Q_INVOKABLE void removeLastPerson();
    int personCount();
    Person *personAt(int i_idx);
    void clearPersons();

signals:
    void prePersonAdded();
    void postPersonAdded();
    void prePersonRemoved(int i_idx);
    void postPersonRemoved();

private:
    QList<Person *> _o_persons;
};

#endif // DATASOURCE_HPP
