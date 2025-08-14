#ifndef PERSON_HPP
#define PERSON_HPP

#include <QtQml>
#include <QObject>
#include <QString>

class Person : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString names READ names WRITE setNames NOTIFY namesChanged)
    Q_PROPERTY(QString favoriteColor READ favoriteColor WRITE setFavoriteColor NOTIFY favoriteColorChanged)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
public:
    explicit Person(QObject *parent = nullptr);
    Person(const QString &o_names, const QString &o_favoriteColor, int i_age, QObject *po_parent = nullptr);

    QString names() const;
    QString favoriteColor() const;
    int age() const;
    void setNames(const QString &o_names);
    void setFavoriteColor(const QString &o_favoriteColor);
    void setAge(int i_age);

signals:
    void namesChanged(const QString &o_name);
    void favoriteColorChanged(const QString &o_favoriteColor);
    void ageChanged(int i_age);

private:
    QString _o_names;
    QString _o_favoriteColor;
    int     _i_age;
};

#endif // PERSON_HPP
