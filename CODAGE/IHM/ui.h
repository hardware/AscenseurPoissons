#ifndef UI_H
#define UI_H

#include <QWidget>

namespace Ui {
class UI;
}

class UI : public QWidget
{
    Q_OBJECT
    
public:
    explicit UI(QWidget *parent = 0);
    ~UI();
    
private:
    Ui::UI *ui;
};

#endif // UI_H
