#include "savegamelistener.h"

#include <QDir>
#include <QFile>

SaveGameListener::SaveGameListener()
{
    m_fileWatcher = new QFileSystemWatcher(this);
    QObject::connect(m_fileWatcher,
                     &QFileSystemWatcher::fileChanged,
                     this,
                     &SaveGameListener::onfileChanged);
    QObject::connect(m_fileWatcher,
                     &QFileSystemWatcher::directoryChanged,
                     this,
                     &SaveGameListener::onDirectoryChanged);
}

QUrl SaveGameListener::listeningFolder() const
{
    return m_listeningFolder;
}

void SaveGameListener::setListeningFolder(const QUrl &newListeningFolder)
{
    if (m_listeningFolder == newListeningFolder) {
        return;
    }
    qDebug() << newListeningFolder;
    m_listeningFolder = newListeningFolder;
    m_fileWatcher->removePaths(m_fileWatcher->directories());
    m_fileWatcher->addPath(m_listeningFolder.toLocalFile());
    qDebug() << QDir(m_listeningFolder.toLocalFile()).entryList();
    QFileInfoList files = QDir(m_listeningFolder.toLocalFile()).entryInfoList();
    for (int i = 0; i < files.size(); ++i) {
        if(!files.at(i).isFile()) {
            continue;
        }
        m_fileWatcher->addPath(files.at(i).filePath());
    }
    qDebug() << m_fileWatcher->files();
    emit listeningFolderChanged();
}

void SaveGameListener::onfileChanged(const QString &path)
{
    if(!m_fileWatcher->files().contains(path) && !QFileInfo::exists(path)) {
        m_fileWatcher->addPath(path);
    }
//    qDebug() << QFileInfo(path).lastModified() << QDateTime::currentDateTime();
//    qDebug() << QFileInfo(path).lastModified().msecsTo(QDateTime::currentDateTime());
//    if(QFileInfo(path).lastModified().msecsTo(QDateTime::currentDateTime()) > 0) {
    emit this->fileChanged(path);
//    }
}

void SaveGameListener::onDirectoryChanged(const QString &path)
{
    QFileInfoList fileInfoList = QDir(m_listeningFolder.toLocalFile()).entryInfoList();
    for (int i = 0; i < fileInfoList.size(); ++i) {
        if(!fileInfoList.at(i).isFile()) {
            continue;
        }
        if (m_fileWatcher->files().contains(fileInfoList.at(i).filePath())) {
            continue;
        }
        if(fileInfoList.at(i).filePath().endsWith("_temp.hoi4")) {
            continue;
        }
        qInfo() << "add file: " << path << " : " << m_fileWatcher->addPath(fileInfoList.at(i).filePath());
    }
}
