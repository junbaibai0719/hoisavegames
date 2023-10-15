#ifndef SAVEGAMELISTENER_H
#define SAVEGAMELISTENER_H

#include <QQmlEngine>
#include <QFileSystemWatcher>


class SaveGameListener: public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QUrl listeningFolder READ listeningFolder WRITE setListeningFolder NOTIFY listeningFolderChanged FINAL)
public:
    SaveGameListener();

    QUrl listeningFolder() const;
    void setListeningFolder(const QUrl &newListeningFolder);
public slots:
    void onfileChanged(const QString &path);
    void onDirectoryChanged(const QString &path);
signals:
    void listeningFolderChanged();
    void fileChanged(const QString &path);
private:
    QUrl m_listeningFolder;

    QFileSystemWatcher *m_fileWatcher;
};

#endif // SAVEGAMELISTENER_H
