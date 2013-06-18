#ifndef JOURNALEVENEMENTS_H
#define JOURNALEVENEMENTS_H

#include <QFile>
#include <QStringList>
#include <QApplication>
#include <QDateTime>
#include <QTextStream>

class JournalEvenements
{

    QStringList listeLignes;

public:
    JournalEvenements();

    bool ajouterLog(QString ligne, QString niveau);

};

#endif // JOURNALEVENEMENTS_H
