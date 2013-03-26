#ifndef APPAREILLAGESTEST_H
#define APPAREILLAGESTEST_H

#include <QObject>
#include <QtTest/QTest>

class AppareillagesTest : public QObject
{
    Q_OBJECT

public:
    explicit AppareillagesTest(QObject *parent = 0);
    
signals:
    
public slots:
    
};

QTEST_MAIN(AppareillagesTest)

#endif // APPAREILLAGESTEST_H
