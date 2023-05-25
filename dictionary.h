#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <QString>

class Dictionary
{
public:
    static const QString SEPARATOR;
    std::map<QString, int> *map;

    Dictionary();
    Dictionary(std::map<QString, int> *map);
    void addText(const QString *text);

    static void writeToFile(const QString *filename, Dictionary *dictionary, bool *ok = nullptr);
    static Dictionary* readFromFile(const QString *filename, bool *ok = nullptr);
};

#endif // DICTIONARY_H
