#include "generateRandomCSRFToken.h"

QString Loweb::Utils::generateRandomCSRFToken(quint64 size)
{
    QString res = "";
    QString symbols = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (quint64 i = 0; i < size; ++i)
    {
        quint8 num = QRandomGenerator::global()->generate() % (symbols.size()-1);
        res += symbols[num];
    }

    return res;
}
