#include "fileutils.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>


const QString FileUtils::DICT_FILE_FILTER = "Dictionary(*.dict)";

QString FileUtils::readFile(const QString *filename, bool *ok)
{
    qInfo() << "Reading file " << *filename;
    QFile file(*filename);
    QString text;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            text.append(stream.readLine()+"\n");
        }
        file.close();
        *ok = true;
    } else {
        *ok = false;
        qWarning() << "Could not open file " << *filename;
    }
    return text;
}
