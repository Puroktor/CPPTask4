#include "logger.h"
#include <QDateTime>

QFile* Logger::logFile = nullptr;
QHash<QtMsgType, QString> Logger::msgTypeNames = {
    {QtMsgType::QtDebugMsg,		"Debug   "},
    {QtMsgType::QtInfoMsg,		"Info    "},
    {QtMsgType::QtWarningMsg,	"Warning "},
    {QtMsgType::QtCriticalMsg,	"Critical"},
    {QtMsgType::QtFatalMsg,		"Fatal   "}
};

void Logger::init() {
    if (logFile != nullptr) {
        return;
    }

    logFile = new QFile;
    logFile->setFileName("./logs.log");
    logFile->open(QIODevice::Append | QIODevice::Text);
    logFile->resize(0);

    qInstallMessageHandler(Logger::logMessage);
}

void Logger::destroy() {
    if (logFile != nullptr) {
        logFile->close();
        delete logFile;
    }
}

void Logger::logMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg) {

    QString log = QString("%1 | %2 | %3 | %4 | %5 | %6\n")
        .arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"))
        .arg(Logger::msgTypeNames.value(type))
        .arg(context.line)
        .arg(QString(context.file)
            .section('\\', -1))
        .arg(QString(context.function)
            .section('(', -2, -2)
            .section(' ', -1)
            .section(':', -1))
        .arg(msg);

    logFile->write(log.toLocal8Bit());
    logFile->flush();
}
