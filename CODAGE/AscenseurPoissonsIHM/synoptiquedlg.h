#ifndef SYNOPTIQUEDLG_H
#define SYNOPTIQUEDLG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>

class SynoptiqueDlg : public QWidget
{
    Q_OBJECT

public:
    explicit SynoptiqueDlg(QWidget *parent = 0);

private:
    QVBoxLayout *VLMain;
    QLabel *LBSchema;
    QProgressBar *PrBAscenseur;
    
signals:
    
public slots:
    
};

#endif // SYNOPTIQUEDLG_H
