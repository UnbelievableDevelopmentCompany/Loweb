#include "getEnv.h"

char* getEnv(const char name[])
{
    char* libvar;
    size_t requiredSize;

    getenv_s(&requiredSize, NULL, 0, name);
    if (requiredSize == 0)
    {
        printf("Var doesn't exist!\n");
        exit(1);
    }

    libvar = new char[requiredSize];
    if (!libvar)
    {
        printf("Failed to allocate memory!\n");
        exit(1);
    }

    getenv_s(&requiredSize, libvar, requiredSize, name);

    return libvar;
}