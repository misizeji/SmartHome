#include "mainmenu.h"
#include "ui_mainmenu.h"


#include <QPainter>

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    //去除边框
    setWindowFlags(Qt::FramelessWindowHint);
    //this->showFullScreen();

    //添加用户管理菜单
    //this->UsrMng = new UserMngWin;
    //添加led灯控制窗口
    this->LedCntl = new LedCntlWin;
    //添加GPRS模块远程发送短信
    this->GprsMsg = new GPRSMsgWin;
    //添加温湿度控制菜单窗口
    this->TemCntl = new TemperatureWin;
    //添加本地留言窗口
    this->MsgLeave = new MsgLeaveWin;
    //添加电影播放器窗口
    this->MovieWin = new moviewin;
    //添加设置窗口
    this->Setup = new SetupWin;

    //信号与槽 显示主菜单
    //connect(this->UsrMng,SIGNAL(show_main_menu()),this,SLOT(main_menu_show()));
    connect(this->LedCntl,SIGNAL(show_main_menu()),this,SLOT(main_menu_show()));
    connect(this->GprsMsg,SIGNAL(show_main_menu()),this,SLOT(main_menu_show()));
    connect(this->TemCntl,SIGNAL(show_main_menu()),this,SLOT(main_menu_show()));
    connect(this->MsgLeave,SIGNAL(show_main_menu()),this,SLOT(main_menu_show()));
    connect(this->MovieWin,SIGNAL(show_main_menu()),this,SLOT(main_menu_show()));
    connect(this->Setup,SIGNAL(show_main_menu()),this,SLOT(main_menu_show()));


}

MainMenu::~MainMenu()
{
    delete ui;
}


void MainMenu::main_menu_show()//显示主菜单
{
    this->show();      //显示主菜单窗口
}

void MainMenu::on_Bt_Exit_clicked()//退出菜单
{
    emit menu_exit();   //菜单退出
    this->close();      //关闭本窗口
}

void MainMenu::on_Bt_UserMng_clicked()//用户管理菜单
{
    //this->close();
    //this->UsrMng->show();
}

void MainMenu::on_Bt_LedSet_clicked()//led灯控制
{
    this->close();
    this->LedCntl->show();
}

void MainMenu::on_Bt_GPRSMsg_clicked()//GPRS远程发送短信
{
    this->close();
    this->GprsMsg->show();
}

void MainMenu::on_Bt_Tem_clicked()//温湿度控制窗口
{
    this->close();
    this->TemCntl->show();
}

void MainMenu::on_Bt_MsgLeave_clicked()//留言窗口
{
    this->close();
    this->MsgLeave->show();
}

void MainMenu::on_Bt_Movie_clicked()//电影播放窗口
{
    this->close();
    this->MovieWin->show();
    this->MovieWin->movie_begin();
}

void MainMenu::on_Bt_Setup_clicked()
{
    this->close();
    this->Setup->show();
}
