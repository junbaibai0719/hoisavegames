#include "hoisavenode.h"

HoiSaveNode::HoiSaveNode()
{
    m_updateTime = QDateTime::currentDateTime();
    m_parentId = 0;
    m_depth = 0;
    m_tag = "";
}

int HoiSaveNode::id() const
{
    return m_id;
}

void HoiSaveNode::setId(int newId)
{
    if (m_id == newId) {
        return;
    }
    m_id = newId;
    emit idChanged();
}

int HoiSaveNode::parentId() const
{
    return m_parentId;
}

void HoiSaveNode::setParentId(int newParentId)
{
    if (m_parentId == newParentId) {
        return;
    }
    m_parentId = newParentId;
    emit parentIdChanged();
}

QString HoiSaveNode::srcPath() const
{
    return m_srcPath;
}

void HoiSaveNode::setSrcPath(const QString &newSrcPath)
{
    if (m_srcPath == newSrcPath) {
        return;
    }
    m_srcPath = newSrcPath;
    emit srcPathChanged();
}

QString HoiSaveNode::filePath() const
{
    return m_filePath;
}

void HoiSaveNode::setFilePath(const QString &newFilePath)
{
    if (m_filePath == newFilePath) {
        return;
    }
    m_filePath = newFilePath;
    emit filePathChanged();
}

QDateTime HoiSaveNode::updateTime() const
{
    return m_updateTime;
}

void HoiSaveNode::setUpdateTime(const QDateTime &newUpdateTime)
{
    if (m_updateTime == newUpdateTime) {
        return;
    }
    m_updateTime = newUpdateTime;
    emit updateTimeChanged();
}

QString HoiSaveNode::player() const
{
    return m_player;
}

void HoiSaveNode::setPlayer(const QString &newPlayer)
{
    if (m_player == newPlayer) {
        return;
    }
    m_player = newPlayer;
    emit playerChanged();
}

QString HoiSaveNode::ideology() const
{
    return m_ideology;
}

void HoiSaveNode::setIdeology(const QString &newIdeology)
{
    if (m_ideology == newIdeology) {
        return;
    }
    m_ideology = newIdeology;
    emit ideologyChanged();
}

QString HoiSaveNode::date() const
{
    return m_date;
}

void HoiSaveNode::setDate(const QString &newDate)
{
    if (m_date == newDate) {
        return;
    }
    m_date = newDate;
    emit dateChanged();
}

QString HoiSaveNode::difficulty() const
{
    return m_difficulty;
}

void HoiSaveNode::setDifficulty(const QString &newDifficulty)
{
    if (m_difficulty == newDifficulty) {
        return;
    }
    m_difficulty = newDifficulty;
    emit difficultyChanged();
}

QString HoiSaveNode::version() const
{
    return m_version;
}

void HoiSaveNode::setVersion(const QString &newVersion)
{
    if (m_version == newVersion) {
        return;
    }
    m_version = newVersion;
    emit versionChanged();
}

QString HoiSaveNode::ironman() const
{
    return m_ironman;
}

void HoiSaveNode::setIronman(const QString &newIronman)
{
    if (m_ironman == newIronman) {
        return;
    }
    m_ironman = newIronman;
    emit ironmanChanged();
}

HoiSaveNode::HoiSaveNode(int id, int parentId, const QString &srcPath, const QString &filePath, const QDateTime &updateTime, const QString &player, const QString &ideology, const QString &date, const QString &difficulty, const QString &version, const QString &ironman) : m_id(id),
    m_parentId(parentId),
    m_srcPath(srcPath),
    m_filePath(filePath),
    m_updateTime(updateTime),
    m_player(player),
    m_ideology(ideology),
    m_date(date),
    m_difficulty(difficulty),
    m_version(version),
    m_ironman(ironman)
{}

QString HoiSaveNode::tag() const
{
    return m_tag;
}

void HoiSaveNode::setTag(const QString &newTag)
{
    if (m_tag == newTag) {
        return;
    }
    m_tag = newTag;
    emit tagChanged();
}

int HoiSaveNode::depth() const
{
    return m_depth;
}

void HoiSaveNode::setDepth(int newDepth)
{
    if (m_depth == newDepth) {
        return;
    }
    m_depth = newDepth;
    emit depthChanged();
}

HoiSaveNode::HoiSaveNode(int id, int parentId, const QString &srcPath, const QString &filePath, const QDateTime &updateTime, const QString &player, const QString &ideology, const QString &date, const QString &difficulty, const QString &version, const QString &ironman, const QString &tag, int depth) : m_id(id),
    m_parentId(parentId),
    m_srcPath(srcPath),
    m_filePath(filePath),
    m_updateTime(updateTime),
    m_player(player),
    m_ideology(ideology),
    m_date(date),
    m_difficulty(difficulty),
    m_version(version),
    m_ironman(ironman),
    m_tag(tag),
    m_depth(depth)
{}

QList<HoiSaveNode *> HoiSaveNode::children() const
{
    return m_children;
}

void HoiSaveNode::setChildren(const QList<HoiSaveNode *> &newChildren)
{
    if (m_children == newChildren) {
        return;
    }
    m_children = newChildren;
    emit childrenChanged();
}

void HoiSaveNode::appendChild(HoiSaveNode *saveNode)
{
    m_children.append(saveNode);
    emit childrenChanged();
}


HoiSaveNode *HoiSaveNode::parentNode() const
{
    return m_parentNode;
}

void HoiSaveNode::setParentNode(HoiSaveNode *newParentNode)
{
    if (m_parentNode == newParentNode) {
        return;
    }
    m_parentNode = newParentNode;
    emit parentNodeChanged();
}
