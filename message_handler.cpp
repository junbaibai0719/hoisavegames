#include "message_handler.h"
#include <QDir>
#include <QMutex>
#include <QFile>
#include <QThread>
#include <QProcess>
#include <QDateTime>
#include <QtCore>

/**
 *  日志写入文件，保留输出到控制台功能
 * @brief handleMsg
 * @param type
 * @param context
 * @param msg
 */
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    std::cout << &mutex << std::endl;
    mutex.lock();
    QString msgType;
    switch (type) {
        case QtDebugMsg:
            msgType = QString("DEBUG:");
            break;
        case QtInfoMsg:
            msgType = QString("INFO");
            break;
        case QtWarningMsg:
            msgType = QString("WARNING:");
            break;
        case QtCriticalMsg:
            msgType = QString("CRITICAL:");
            break;
        case QtFatalMsg:
            msgType = QString("FATAL:");
            break;
        default:
            msgType = QString("DEBUG:");
    }
    QString contextInfo = QString("Process:%1 Thread:%2 File:%3 Func:%4 Line:%5").arg(
                              QString::number(getpid()),
                              QString::number(quintptr(QThread::currentThreadId())),
                              QFileInfo(QString(context.file)).fileName(),
                              QString(context.function),
                              QString::number(context.line)
                          );
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString strMessage = QString("%1 %2 %3 %4").arg(strDateTime, contextInfo, msgType, msg);
    std::cout << strMessage.toStdString() << std::endl;
    QString logFilePath(QCoreApplication::instance()->applicationDirPath() + "/log/"  + QString(QDateTime::currentDateTime().toString("yyyy-MM-dd").append(".log")));
    std::cout << QDir(QFileInfo(logFilePath).path()).mkpath(QFileInfo(logFilePath).path());
    QFile file(logFilePath);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();
    mutex.unlock();
}
