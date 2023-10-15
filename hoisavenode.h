#ifndef HOISAVENODE_H
#define HOISAVENODE_H

#include <QtCore>
#include <QQmlEngine>

class HoiSaveNode: public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(int parentId READ parentId WRITE setParentId NOTIFY parentIdChanged FINAL)
    Q_PROPERTY(QString srcPath READ srcPath WRITE setSrcPath NOTIFY srcPathChanged FINAL)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged FINAL)
    Q_PROPERTY(QDateTime updateTime READ updateTime WRITE setUpdateTime NOTIFY updateTimeChanged FINAL)
    Q_PROPERTY(QString player READ player WRITE setPlayer NOTIFY playerChanged FINAL)
    Q_PROPERTY(QString ideology READ ideology WRITE setIdeology NOTIFY ideologyChanged FINAL)
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged FINAL)
    Q_PROPERTY(QString difficulty READ difficulty WRITE setDifficulty NOTIFY difficultyChanged FINAL)
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged FINAL)
    Q_PROPERTY(QString ironman READ ironman WRITE setIronman NOTIFY ironmanChanged FINAL)
    Q_PROPERTY(QString tag READ tag WRITE setTag NOTIFY tagChanged FINAL)
    Q_PROPERTY(int depth READ depth WRITE setDepth NOTIFY depthChanged FINAL)
    Q_PROPERTY(QList<HoiSaveNode*> children READ children WRITE setChildren NOTIFY childrenChanged FINAL)
    Q_PROPERTY(HoiSaveNode* parentNode READ parentNode WRITE setParentNode NOTIFY parentNodeChanged FINAL)
public:
    HoiSaveNode();
    HoiSaveNode(int id, int parentId, const QString &srcPath, const QString &filePath, const QDateTime &updateTime, const QString &player, const QString &ideology, const QString &date, const QString &difficulty, const QString &version, const QString &ironman);
    HoiSaveNode(int id, int parentId, const QString &srcPath, const QString &filePath, const QDateTime &updateTime, const QString &player, const QString &ideology, const QString &date, const QString &difficulty, const QString &version, const QString &ironman, const QString &tag, int depth);

    int id() const;
    void setId(int newId);
    int parentId() const;
    void setParentId(int newParentId);

    QString srcPath() const;
    void setSrcPath(const QString &newSrcPath);

    QString filePath() const;
    void setFilePath(const QString &newFilePath);

    QDateTime updateTime() const;
    void setUpdateTime(const QDateTime &newUpdateTime);

    QString player() const;
    void setPlayer(const QString &newPlayer);

    QString ideology() const;
    void setIdeology(const QString &newIdeology);

    QString date() const;
    void setDate(const QString &newDate);

    QString difficulty() const;
    void setDifficulty(const QString &newDifficulty);

    QString version() const;
    void setVersion(const QString &newVersion);

    QString ironman() const;
    void setIronman(const QString &newIronman);

    QString tag() const;
    void setTag(const QString &newTag);

    int depth() const;
    void setDepth(int newDepth);

    QList<HoiSaveNode *> children() const;
    void setChildren(const QList<HoiSaveNode *> &newChildren);
    void appendChild(HoiSaveNode * saveNode);

    HoiSaveNode *parentNode() const;
    void setParentNode(HoiSaveNode *newParentNode);

signals:
    void idChanged();
    void parentIdChanged();

    void srcPathChanged();

    void filePathChanged();

    void updateTimeChanged();

    void playerChanged();

    void ideologyChanged();

    void dateChanged();

    void difficultyChanged();

    void versionChanged();

    void ironmanChanged();

    void tagChanged();

    void depthChanged();

    void childrenChanged();

    void parentNodeChanged();

private:
    int m_id;
    int m_parentId;
    QString m_srcPath;
    QString m_filePath;
    QDateTime m_updateTime;
    QString m_player;
    QString m_ideology;
    QString m_date;
    QString m_difficulty;
    QString m_version;
    QString m_ironman;
    QString m_tag;
    int m_depth;
    QList<HoiSaveNode *> m_children;
    HoiSaveNode *m_parentNode = nullptr;
};

#endif // HOISAVENODE_H
