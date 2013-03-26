#ifndef PROGRAMMATIONSEANCETEST_H
#define PROGRAMMATIONSEANCETEST_H

#include <QObject>
#include <QtTest/QTest>

class ProgrammationSeanceTest : public QObject
{
    Q_OBJECT

public:
    explicit ProgrammationSeanceTest(QObject *parent = 0);
    
signals:
    
public slots:
    
};

QTEST_MAIN(ProgrammationSeanceTest)

#endif // PROGRAMMATIONSEANCETEST_H
