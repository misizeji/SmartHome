#ifndef USERMNGWIN_H
#define USERMNGWIN_H

#include <QWidget>

namespace Ui {
    class UserMngWin;
}

class UserMngWin : public QWidget
{
    Q_OBJECT

public:
    explicit UserMngWin(QWidget *parent = 0);
    ~UserMngWin();

private:
    Ui::UserMngWin *ui;
};

#endif // USERMNGWIN_H
