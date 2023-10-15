#ifndef HOIFILEPARSER_H
#define HOIFILEPARSER_H

#include <QRegularExpression>
#include "hoisavenode.h"

class HoiFileParser
{
public:
    static QRegularExpression pattern;
    static QProcess* save(HoiSaveNode *saveNode);
    static QProcess* restore(HoiSaveNode *saveNode);
    static HoiSaveNode* parse(const QString &filePath);
    static QString baseDir(const QString &path);
private:
    HoiFileParser();

};

#endif // HOIFILEPARSER_H
