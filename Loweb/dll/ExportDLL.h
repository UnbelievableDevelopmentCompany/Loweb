#pragma once
#include <QtCore>

#ifdef Q_OS_WIN
#ifdef MAKEDLL
#define EXPORTDLL __declspec(dllexport)
#else
#define EXPORTDLL __declspec(dllimport)
#endif
#else
#define EXPORTDLL
#endif