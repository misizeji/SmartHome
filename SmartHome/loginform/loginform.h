#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "../MsgShow/msgshowwin.h"
#include "../t9input/t9widget.h"
#include "../mainmenu/mainmenu.h"



namespace Ui {
    class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

private:
    Ui::LoginForm *ui;
    T9Widget *input;        //输入法添加
    MainMenu *mainmenu;     //主菜单添加
	MsgShowWin *msgshow;    //留言显示窗口
    QTimer *timer;          //定时器

signals:
    void bg_show();         //图片轮播继续播放

public slots:
    void Edit_Clear();      //清空帐号密码输入框

private slots:
    void on_checkBox_showPwd_clicked(bool checked);     //显示密码
    void on_Btn_cancel_clicked();                       //退出当前窗口
    void on_Btn_register_clicked();                     //注册帐号
    void on_Btn_login_clicked();                        //正常登录
    void EditText(QString);                             //编辑选中框
    void backSpaceText();                               //退格处理


protected:
    void paintEvent(QPaintEvent *);//绘制背景图
    void mousePressEvent(QMouseEvent *);//鼠标点击事件

};

#endif // LOGINFORM_H
