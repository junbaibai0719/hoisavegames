#ifndef HOIMODEL_H
#define HOIMODEL_H

#include <QQmlEngine>
#include <QAbstractItemModel>

#include <QSqlDatabase>
#include "hoisavenode.h"

class HoiModel: public QAbstractItemModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    HoiModel(QObject *parent = nullptr);
private:
    void initData();
    void createTable();

public slots:
    void addSaveNodeFromPath(const QString &path);
    QList<QString> listeningFiles();

private:
    QSqlDatabase m_db;
    QList<QList<HoiSaveNode *> *> m_rows;

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;


};

#endif // HOIMODEL_H
