#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QFile>
#include <QHash>

class Logger
{
private:
    static QFile* logFile;

    static QHash<QtMsgType, QString> msgTypeNames;

public:
    static void init();

    static void destroy();

    static void logMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
};

#endif // LOGGER_H
