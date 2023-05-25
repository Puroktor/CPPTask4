#include "dictionary.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

const QString Dictionary::SEPARATOR = " = ";

Dictionary::Dictionary()
{
    map = new std::map<QString, int>;
}

Dictionary::Dictionary(std::map<QString, int> *map) : map(map)
{
}

void Dictionary::addText(const QString *text)
{
    qInfo() << "Adding text to dictionary";
    QStringList list = text->split(QRegExp("\\s+"), QString::SkipEmptyParts);

    Q_FOREACH(const auto& word, list)
    {
        auto pos = map->find(word);
        int count = pos == map->end() ? 0 : pos->second;
        (*map)[word] = count + 1;
    }
}

void Dictionary::writeToFile(const QString *filename, Dictionary *dictionary, bool *ok)
{
    qInfo() << "Saving Dictionary into " << *filename;
    QFile file(*filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        for (const auto& entry : *(dictionary->map))
        {
            QString record = QString("%1%2%3\n")
                    .arg(entry.first, SEPARATOR)
                    .arg(entry.second);
            out << record;
        }
        file.close();
        *ok = true;
    }
    else
    {
        *ok = false;
        qWarning() << "Could not open dictionary file" << *filename;
    }
}

Dictionary* Dictionary::readFromFile(const QString *filename, bool *ok)
{
    qInfo() << "Reading Dictionary from " << *filename;
    std::map<QString, int> *map = new std::map<QString, int>;
    QFile file(*filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        *ok = true;
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            QStringList record = stream.readLine().split(SEPARATOR);
            if (record.size() != 2)
            {
                *ok = false;
                qCritical() << "Invalid dictionary record size. Expected 2, got " << record.size();
                break;
            }
            bool converted;
            int count = record[1].toInt(&converted);
            if (!converted)
            {
                *ok = false;
                qCritical() << "Could not convert wird count into int " << record[1];
                break;
            }
            (*map)[record[0]] = count;

        }
        file.close();
    }
    else
    {
        *ok = false;
        qWarning() << "Could not open dictionary file " << *filename;
    }

    if (!ok)
        map->clear();
    return new Dictionary(map);
}
