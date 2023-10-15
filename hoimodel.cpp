#include "hoimodel.h"

#include <QSqlQuery>
#include <QFile>
#include <QSqlError>
#include "hoifileparser.h"

HoiModel::HoiModel(QObject *parent): QAbstractItemModel(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("hoi.db");
    m_db.open();
    qInfo() << "db is open?:" << m_db.isOpen();
    createTable();
    initData();
}



void HoiModel::initData()
{
    QSqlQuery query;
    query.prepare("select `id`,`parent`,`src_path`,`file_path`,`update_time`,`player`,`ideology`,`date`,`difficulty`,`version`,`ironman`,`tag`,`depth` "
                  "from save_node "
                  "where src_path = ? "
                  "order by depth asc");
    query.addBindValue("C:\\Users\\lin\\Documents\\Paradox Interactive\\Hearts of Iron IV\\save games\\  1.hoi4");
    if(query.exec()) {
        int lastDepth = 0;
        QList<HoiSaveNode*> * saveNodes = new QList<HoiSaveNode*>();
        m_rows.append(saveNodes);
        QMap<int, HoiSaveNode*> nodemap;
        while (query.next()) {
            int depth = query.value(12).toInt();
            if(depth > lastDepth) {
                saveNodes = new QList<HoiSaveNode*>();
                m_rows.append(saveNodes);
                lastDepth = depth;
            }
            HoiSaveNode* node = new HoiSaveNode(
                query.value(0).toInt(),
                query.value(1).toInt(),
                query.value(2).toString(),
                query.value(3).toString(),
                query.value(4).toDateTime(),
                query.value(5).toString(),
                query.value(6).toString(),
                query.value(7).toString(),
                query.value(8).toString(),
                query.value(9).toString(),
                query.value(10).toString(),
                query.value(11).toString(),
                query.value(12).toInt()
            );
            HoiSaveNode * parentNode = nodemap.value(node->parentId(), nullptr);
            if (parentNode) {
                node->setParentNode(nodemap.value(node->parentId(), nullptr));
                parentNode->appendChild(node);
            }
            nodemap.insert(node->id(), node);
            saveNodes->append(
                node
            );
        }
    } else {
        qWarning() << query.lastError();
    }
}

void HoiModel::createTable()
{
    QSqlQuery sql;
    qDebug() << sql.exec("create table if not exists `save_node` ("
                         "`id` integer NOT NULL,"
                         "`parent` integer DEFAULT NULL,"
                         "`src_path` TEXT,"
                         "`file_path` text,"
                         "`update_time` datetime,"
                         "`player` text,"
                         "`ideology` text,"
                         "`date` text,"
                         "`difficulty` text,"
                         "`version` text,"
                         "`ironman` text,"
                         "`tag` text,"
                         "`depth` integer,"
                         "PRIMARY KEY (`id`),"
                         "CONSTRAINT `file_path` UNIQUE (`file_path` ASC)"
                         ");"
                        );
    qDebug() << sql.lastError();
    qDebug() << sql.exec(
                 "CREATE INDEX if not exists `idx_src_path`"
                 "ON `save_node` ("
                 "`src_path` COLLATE BINARY ASC"
                 "); ");
    qDebug() << sql.lastError();
}

void HoiModel::addSaveNodeFromPath(const QString &path)
{
    HoiSaveNode* savenode = HoiFileParser::parse("C:\\Users\\lin\\Documents\\Paradox Interactive\\Hearts of Iron IV\\save games\\  1.hoi4");
    QProcess * process = HoiFileParser::save(savenode);
    QObject::connect(process, &QProcess::finished, process, [ = ]() {
        if(process->exitCode()) {
            qWarning() << process->readAllStandardError();
            process->close();
            process->deleteLater();
            return;
        }
        process->close();
        process->deleteLater();
        QSqlQuery selectLastUpdateNode;
        selectLastUpdateNode.prepare("select `id`,`date`,`depth` "
                                     "from save_node where src_path = ? "
                                     "order by update_time desc limit 1");
        selectLastUpdateNode.addBindValue(savenode->srcPath());
        selectLastUpdateNode.exec();
        selectLastUpdateNode.first();
        int id = selectLastUpdateNode.value(0).toInt();
        int depth = selectLastUpdateNode.value(2).toInt();
        QString date = selectLastUpdateNode.value(1).toString();
        if(date == savenode->date()) {
            qDebug() << "not need insert";
            return;
        }
        savenode->setParentId(id);
        savenode->setDepth(depth + 1);
        QSqlQuery query;
        query.prepare("insert into `save_node` (`parent`,`src_path`,`file_path`,`update_time`,`player`,`ideology`,`date`,`difficulty`,`version`,`ironman`, `depth`) "
                      "values (?,?,?,?,?,?,?,?,?,?,?);");
        query.addBindValue(savenode->parentId());
        query.addBindValue(savenode->srcPath());
        query.addBindValue(savenode->filePath());
        query.addBindValue(savenode->updateTime());
        query.addBindValue(savenode->player());
        query.addBindValue(savenode->ideology());
        query.addBindValue(savenode->date());
        query.addBindValue(savenode->difficulty());
        query.addBindValue(savenode->version());
        query.addBindValue(savenode->ironman());
        query.addBindValue(savenode->depth());
        if(!query.exec()) {
            qWarning() << "insert save_node error:" << query.lastError();
        } else {
            qInfo() << "insert success";
        }
    });
}

QList<QString> HoiModel::listeningFiles()
{
    QSqlQuery query;
    query.prepare("select src_path from save_node group by src_path order by id ");
    QList<QString> resList;
    if(query.exec()) {
        while (query.next()) {
            resList.append(QFileInfo(query.value(0).toString()).fileName());
        }
    }
    return resList;
}

QModelIndex HoiModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex HoiModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int HoiModel::rowCount(const QModelIndex &parent) const
{
    return m_rows.size();
}

int HoiModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant HoiModel::data(const QModelIndex &index, int role) const
{
    QVariant data("");
    switch (role) {
        case Qt::DisplayRole:
            data.setValue( * (m_rows[index.row()]));
            break;
        default:
            break;
    }
    return data;
}

