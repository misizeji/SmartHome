#ifndef SETUPWIN_H
#define SETUPWIN_H

#include <QWidget>
#include <QPainter>
#include "options.h"

namespace Ui {
    class SetupWin;
}

class SetupWin : public QWidget
{
    Q_OBJECT

public:
    explicit SetupWin(QWidget *parent = 0);
    ~SetupWin();

private:
    Ui::SetupWin *ui;

protected:
    void paintEvent(QPaintEvent *);//绘制背景图

signals:
    void show_main_menu();  //显示主菜单信号

private slots:
    void on_Bt_Exit_clicked();
    void on_Bt_Commit_clicked();
};

#endif // SETUPWIN_H
