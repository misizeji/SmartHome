#include "loginform.h"
#include "ui_loginform.h"
#include "options.h"

#include <QPainter>
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QPaintEvent>
#include <QMessageBox>


//C++中插入C语言的方式
extern "C"  //是大写的 C
{

    #include "./account_register.h"
    #include "./normal_login.h"
    #include "./database/sqlite3.h"

}


LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    //去除边框
    setWindowFlags(Qt::FramelessWindowHint);
    //this->showFullScreen();

    //设置定时器
    this->timer = new QTimer(this);
	this->timer->start(1000*show_menu_delay);

    //添加键盘
    this->input = new T9Widget(ui->Edit_usrName,this);
    this->input->move(450,30);
    this->input->show();

    //添加主菜单
    this->mainmenu = new MainMenu;
    //添加消息留言显示窗口
    this->msgshow = new MsgShowWin;
	
    ui->Edit_usrName->setFocus();

    //键盘联系 信号与槽
    connect(this->input,SIGNAL(newString(QString)),this,SLOT(EditText(QString)));      //编辑选中框
    connect(this->input,SIGNAL(backSpace()),this,SLOT(backSpaceText()));               //退格键

	connect(this->msgshow,SIGNAL(mainmenu_show()),this->mainmenu,SLOT(show()));        //显示主菜单
	
    connect(this->timer,SIGNAL(timeout()),this,SLOT(on_Btn_cancel_clicked()));         //回到主宣传界面
    connect(this->mainmenu,SIGNAL(menu_exit()),this,SLOT(on_Btn_cancel_clicked()));    //回到主宣传界面

}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::paintEvent(QPaintEvent *)//画图事件画背景图片
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/pic/pic_bg/bkg.png"));
}

void LoginForm::mousePressEvent(QMouseEvent *ev)//鼠标按下事件
{
    int x = ev->x();//鼠标点击的x坐标
    int y = ev->y();//鼠标点击的y坐标

    this->timer->start(1000*show_menu_delay);


    qDebug()<<"x = "<<x
            <<" y = "<<y;
    qDebug()<<ev->pos();//显示鼠标的pos
}

void LoginForm::Edit_Clear()
{
    ui->Edit_usrName->setText("");
    ui->Edit_pwd->setText("");
    ui->Edit_usrName->setFocus();
}

void LoginForm::EditText(QString str)//编辑选中框
{
    if(ui->Edit_usrName->hasFocus() == true )   //判断焦点在哪
    {
        ui->Edit_usrName->insert(str);  //追加
    }
    else if(ui->Edit_pwd->hasFocus()==true)
    {
        ui->Edit_pwd->insert(str);
    }
}


void LoginForm::backSpaceText()    //按了退格键
{
    QString str;
    if(ui->Edit_usrName->hasFocus() == true )
    {
        str = ui->Edit_usrName->text(); //首先获得到文本框中的内容
        if(str.isEmpty() == false)
        {
            str = str.left(str.size()-1);   //字符减一
            ui->Edit_usrName->setText(str); //重新设置
        }
    }
    else if(ui->Edit_pwd->hasFocus() == true)
    {
        str = ui->Edit_pwd->text();
        if(str.isEmpty() == false)
        {
            str = str.left(str.size()-1);
            ui->Edit_pwd->setText(str);
        }
    }
}

void LoginForm::on_Btn_login_clicked()  //正常登录
{
    int ret = normal_login(ui->Edit_usrName->text().toAscii().data(),
                           ui->Edit_pwd->text().toAscii().data());
    if(ret == 1)
    {
        this->timer->stop();
        this->hide();
        //this->mainmenu->setGeometry(this->geometry());
        //this->mainmenu->show();
		this->msgshow->MsgShow();
    }
    else if(ret == 0)
    {
        QMessageBox::warning(this,"Warning","UserName or Password Error!");
    }
    else
    {
        qDebug()<<"the ret is "<<ret;
        qDebug()<<"program worng or db is not exits!!";
    }
}

void LoginForm::on_Btn_register_clicked()   //注册帐号
{
    int ret = account_register(ui->Edit_usrName->text().toAscii().data(),
                               ui->Edit_pwd->text().toAscii().data());
    if(ret == 1)
    {
        QMessageBox::warning(this,"congratulation","register successful!!");
    }
    else if(ret == 0)
    {
        QMessageBox::warning(this,"Warning","UserName Exist!!!");
    }
    else
    {
		QMessageBox::warning(this,"Warning","Input Wrong!!!");
        qDebug()<<"the ret is "<<ret;
        qDebug()<<"program worng or db is not exits!!";
    }
}

void LoginForm::on_Btn_cancel_clicked() //退出登录
{
    emit bg_show();     //发送图片轮播信号
    this->close();      //关闭本窗口
}

void LoginForm::on_checkBox_showPwd_clicked(bool checked)   //显示密码
{
    if(checked)
    {
        ui->Edit_pwd->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->Edit_pwd->setEchoMode(QLineEdit::Password);
    }
}
