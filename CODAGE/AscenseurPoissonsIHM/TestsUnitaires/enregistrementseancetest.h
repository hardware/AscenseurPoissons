#ifndef ENREGISTREMENTSEANCETEST_H
#define ENREGISTREMENTSEANCETEST_H

#include <QObject>
#include <QtTest/QTest>

class EnregistrementSeanceTest : public QObject
{
    Q_OBJECT

public:
    explicit EnregistrementSeanceTest(QObject *parent = 0);
    
signals:
    
public slots:
    
};

QTEST_MAIN(EnregistrementSeanceTest)

#endif // ENREGISTREMENTSEANCETEST_H
