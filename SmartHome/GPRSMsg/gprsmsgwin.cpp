#include "gprsmsgwin.h"
#include "ui_gprsmsgwin.h"


#include <QPainter>

extern "C"  //是大写的 C
{
    #include "gprs.h"
}

GPRSMsgWin::GPRSMsgWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GPRSMsgWin)
{
    ui->setupUi(this);

    //去除边框
    setWindowFlags(Qt::FramelessWindowHint);
    //this->showFullScreen();

    //添加键盘
    this->input = new T9Widget(ui->Ed_TelNum,this);
    this->input->move(450,30);
    this->input->show();

	ui->Ed_TelNum->setFocus();
	
    //键盘联系 信号与槽
    connect(this->input,SIGNAL(newString(QString)),this,SLOT(EditText(QString)));      //编辑选中框
    connect(this->input,SIGNAL(backSpace()),this,SLOT(backSpaceText()));               //退格键

}

GPRSMsgWin::~GPRSMsgWin()
{
    delete ui;
}


void GPRSMsgWin::paintEvent(QPaintEvent *)//画图事件画背景图片
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/pic/pic_bg/bkg.png"));
}


void GPRSMsgWin::EditText(QString str)//编辑选中框
{
    if(ui->Ed_TelNum->hasFocus() == true )   //判断焦点在哪
    {
        ui->Ed_TelNum->insert(str);  //追加
    }
    else if(ui->Ed_Msg->hasFocus()==true)
    {
        ui->Ed_Msg->insertPlainText(str);
    }
}


void GPRSMsgWin::backSpaceText()    //按了退格键
{
    QString str;
    if(ui->Ed_TelNum->hasFocus() == true )
    {
        str = ui->Ed_TelNum->text(); //首先获得到文本框中的内容
        if(str.isEmpty() == false)
        {
            str = str.left(str.size()-1);   //字符减一
            ui->Ed_TelNum->setText(str); //重新设置
        }
    }
    else if(ui->Ed_Msg->hasFocus() == true)
    {
        str = ui->Ed_Msg->toPlainText();
        if(str.isEmpty() == false)
        {
            str = str.left(str.size()-1);
            ui->Ed_Msg->setText(str);
        }
    }
}


void GPRSMsgWin::on_Bt_Exit_clicked()//回到主界面
{
    emit this->show_main_menu();
    this->close();
}

void GPRSMsgWin::Edit_Clear()
{
    ui->Ed_TelNum->setText("");
    ui->Ed_Msg->setText("");
    ui->Ed_TelNum->setFocus();
}

void GPRSMsgWin::on_Bt_send_clicked()//发送信息按钮
{
    QString str_num = ui->Ed_TelNum->text();
    QString str_msg = ui->Ed_Msg->toPlainText();
    int ret = gprs_deal(str_num.toLatin1().data(),str_msg.toLatin1().data());
	
	if(ret == 0)
	{
		QMessageBox::warning(this,"congratulation","send successful!!");
	}
	else
	{
		QMessageBox::warning(this,"Warning","Input wrong,send failed!!");
	}
	Edit_Clear();
}
