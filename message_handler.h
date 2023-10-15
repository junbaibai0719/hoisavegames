#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H



#include <QMessageLogContext>
#include <iostream>


#ifdef _WIN32
    #include <process.h>
#else
    #include "unistd.h"
#endif

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif // MESSAGE_HANDLER_H
