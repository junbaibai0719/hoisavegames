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
    Q_PROPERTY(QString currentFileName READ currentFileName WRITE setCurrentFileName NOTIFY currentFileNameChanged FINAL)
    Q_PROPERTY(bool restoring READ restoring WRITE setRestoring NOTIFY restoringChanged FINAL)
    Q_PROPERTY(QList<QString> listeningFiles READ listeningFiles WRITE setListeningFiles NOTIFY listeningFilesChanged FINAL)
public:
    HoiModel(QObject *parent = nullptr);
private:
    void initData();
    void createTable();
    void initListeningFiles();

public slots:
    void addSaveNodeFromPath(const QString &path);
    void restore(HoiSaveNode * node);

private:
    QSqlDatabase m_db;
    QList<QList<HoiSaveNode *> *> m_rows;

    // QAbstractItemModel interface
    QString m_currentFileName;

    bool m_restoring;

    QList<QString> m_listeningFiles;

public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;


    QString currentFileName() const;
    void setCurrentFileName(const QString &newCurrentFileName);
    bool restoring() const;
    void setRestoring(bool newRestoring);

    QList<QString> listeningFiles() const;
    void setListeningFiles(const QList<QString> &newListeningFiles);

signals:
    void currentFileNameChanged();
    void restoringChanged();
    void notify(const QString & title, const QString & msg);
    void listeningFilesChanged();
};

#endif // HOIMODEL_H
