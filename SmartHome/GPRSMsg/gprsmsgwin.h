#ifndef GPRSMSGWIN_H
#define GPRSMSGWIN_H

#include "../t9input/t9widget.h"
#include <QWidget>
#include <QMessageBox>

namespace Ui {
    class GPRSMsgWin;
}

class GPRSMsgWin : public QWidget
{
    Q_OBJECT

public:
    explicit GPRSMsgWin(QWidget *parent = 0);
    ~GPRSMsgWin();

private:
    Ui::GPRSMsgWin *ui;
    T9Widget *input;        //输入法添加


signals:
    void show_main_menu();  //显示主菜单信号

public slots:
	void Edit_Clear();
	
private slots:
    void on_Bt_send_clicked();
    void on_Bt_Exit_clicked();
    void EditText(QString);                             //编辑选中框
    void backSpaceText();                               //退格处理


protected:
    void paintEvent(QPaintEvent *);//绘制背景图

};

#endif // GPRSMSGWIN_H
