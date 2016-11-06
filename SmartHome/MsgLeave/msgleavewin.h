#ifndef MSGLEAVEWIN_H
#define MSGLEAVEWIN_H

#include "../t9input/t9widget.h"
#include <QWidget>

namespace Ui {
    class MsgLeaveWin;
}

class MsgLeaveWin : public QWidget
{
    Q_OBJECT

public:
    explicit MsgLeaveWin(QWidget *parent = 0);
    ~MsgLeaveWin();

signals:
    void show_main_menu();  //显示主菜单信号

private:
    Ui::MsgLeaveWin *ui;
    T9Widget *input;        //输入法添加

private slots:
    void on_Bt_LeaveMsg_clicked();
    void on_Bt_Exit_clicked();
    void EditText(QString);                             //编辑选中框
    void backSpaceText();                               //退格处理

protected:
    void paintEvent(QPaintEvent *);//绘制背景图


};

#endif // MSGLEAVEWIN_H
