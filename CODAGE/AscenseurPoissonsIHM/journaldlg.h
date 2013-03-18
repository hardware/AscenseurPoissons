#ifndef JOURNALDLG_H
#define JOURNALDLG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>

class JournalDlg : public QWidget
{
    Q_OBJECT

public:
    explicit JournalDlg(QWidget *parent = 0);
    
private:
    QVBoxLayout *VLMain;
    QListWidget *LWLogs;

signals:
    
public slots:
    
};

#endif // JOURNALDLG_H
