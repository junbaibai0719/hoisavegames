#include "hoifileparser.h"
#include "datetimeformat.h"

QRegularExpression HoiFileParser::pattern = QRegularExpression(
            "\\s*player=\"(.*)\""
            "\\s*ideology=(.*)"
            "\\s*date=\"(.*)\""
            "\\s*difficulty=\"(.*)\""
            "\\s*version=\"(.*)\""
            "\\s*ironman=\"(.*)\"\\s*");


QProcess* HoiFileParser::save(HoiSaveNode *saveNode)
{
    QString srcPath = saveNode->srcPath();
    QString dstPath = saveNode->filePath();
    if(QFileInfo::exists(dstPath)) {
        return nullptr;
    }
    QDir saveFolder = QFileInfo(dstPath).dir();
    if(!saveFolder.exists()) {
        qDebug() << "mkdir :" << saveFolder.mkpath(saveFolder.path());
    }
    QString copyPath = HoiFileParser::baseDir(srcPath) + "/" + QFileInfo(srcPath).fileName();
    if (!QFileInfo::exists(copyPath)) {
        return nullptr;
    }
    QProcess* process = new QProcess(QCoreApplication::instance());
    process->startCommand(QString("%1/7z/7za.exe a -tzip \"%2\" -ir!\"%3\"").arg(
                              QCoreApplication::applicationDirPath(),
                              dstPath, copyPath
                          ));
    return process;
//    QObject::connect(process, &QProcess::finished, process, [p = process]() {
//        qDebug() << p->readAllStandardOutput();
//    });
}

QProcess* HoiFileParser::restore(HoiSaveNode *saveNode)
{
    QString srcPath = saveNode->srcPath();
    QString dstPath = saveNode->filePath();
    QProcess *process = new QProcess(QCoreApplication::instance());
    process->startCommand(QString("%1/7z/7za.exe  e  \"%2\" -o\"%3\" -y").arg(
                              QCoreApplication::applicationDirPath(),
                              dstPath, QFileInfo(srcPath).dir().path()
                          ));
    return process;
}

HoiSaveNode* HoiFileParser::parse(const QString &filePath)
{
    HoiSaveNode *savenode = new HoiSaveNode();
    savenode->setSrcPath(filePath);
    QString copyPath = HoiFileParser::baseDir(filePath) + "/" + QFileInfo(filePath).fileName();
    if(QFileInfo::exists(copyPath)) {
        // 不能直接覆盖文件，真滴坑
        QFile::remove(copyPath);
    }
    qDebug() <<  QFile::copy(filePath, copyPath);
    QFile copyfile(copyPath);
    copyfile.open(QFile::OpenModeFlag::ReadOnly);
    QByteArray content = copyfile.read(512);
    copyfile.close();
    QRegularExpressionMatch match = pattern.match(QString(content));
    if(match.hasMatch()) {
        savenode->setPlayer(match.captured(1));
        savenode->setIdeology(match.captured(2));
        savenode->setDate(match.captured(3));
        savenode->setDifficulty(match.captured(4));
        savenode->setVersion(match.captured(5));
        savenode->setIronman(match.captured(6));
    }
    savenode->setFilePath(
        QString("%1/%2_%3.zip").arg(
            HoiFileParser::baseDir(filePath),
            savenode->date(),
            savenode->updateTime().toString(DATETIME_NORMAL_FORMAT)
        ));
    return savenode;
}

QString HoiFileParser::baseDir(const QString &path)
{
    return QString("%1/save_games/%2").arg(
               QCoreApplication::applicationDirPath(),
               QFileInfo(path).fileName()
           );
}

HoiFileParser::HoiFileParser()
{
}
