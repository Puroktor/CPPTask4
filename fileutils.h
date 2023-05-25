#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>

class FileUtils
{
public:
    static const QString DICT_FILE_FILTER;

    static QString readFile(const QString *filename, bool *ok = nullptr);
};

#endif // FILEUTILS_H
