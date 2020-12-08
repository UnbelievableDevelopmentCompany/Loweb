#include "generateRandomString.h"

QString generateRandomString(quint64 size)
{
    QString res = "";

    for (quint64 i = 0; i < size; ++i)
    {
        quint8 num = QRandomGenerator::global()->generate() % (128-33) + 33;
        res += char(num);
    }

    return res;
}
