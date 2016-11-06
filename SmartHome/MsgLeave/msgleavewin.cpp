#include "msgleavewin.h"
#include "ui_msgleavewin.h"


#include <QPainter>
#include <QMessageBox>

extern "C"  //是大写的 C
{
    #include "msgsnd.h"
}

MsgLeaveWin::MsgLeaveWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgLeaveWin)
{
    ui->setupUi(this);

    //去除边框
    setWindowFlags(Qt::FramelessWindowHint);
    //this->showFullScreen();

    //添加键盘
    this->input = new T9Widget(ui->Ed_LeaveMsg,this);
    this->input->move(450,30);
    this->input->show();


    //键盘联系 信号与槽
    connect(this->input,SIGNAL(newString(QString)),this,SLOT(EditText(QString)));      //编辑选中框
    connect(this->input,SIGNAL(backSpace()),this,SLOT(backSpaceText()));               //退格键

}

MsgLeaveWin::~MsgLeaveWin()
{
    delete ui;
}

void MsgLeaveWin::paintEvent(QPaintEvent *)//画图事件画背景图片
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/pic/pic_bg/bkg.png"));
}

void MsgLeaveWin::EditText(QString str)//编辑选中框
{
    if(ui->Ed_LeaveMsg->hasFocus() == true )   //判断焦点在哪
    {
        ui->Ed_LeaveMsg->insertPlainText(str);  //追加
    }
}


void MsgLeaveWin::backSpaceText()    //按了退格键
{
    QString str;
    if(ui->Ed_LeaveMsg->hasFocus() == true )
    {
        str = ui->Ed_LeaveMsg->toPlainText(); //首先获得到文本框中的内容
        if(str.isEmpty() == false)
        {
            str = str.left(str.size()-1);   //字符减一
            ui->Ed_LeaveMsg->setText(str); //重新设置
        }
    }
}

void MsgLeaveWin::on_Bt_Exit_clicked()
{
    emit this->show_main_menu();
    this->close();
}

void MsgLeaveWin::on_Bt_LeaveMsg_clicked()
{
    int ret = msg_send(ui->Ed_LeaveMsg->toPlainText().toAscii().data());
    ui->Ed_LeaveMsg->setText("");

    if(ret == 0)
    {
        QMessageBox::warning(this,"congratulation"," successful!!");
    }
    else
    {
        QMessageBox::warning(this,"congratulation"," failed!!");
    }
}
