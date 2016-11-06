#include "msgshowwin.h"
#include "ui_msgshowwin.h"


MsgShowWin::MsgShowWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgShowWin)
{
    ui->setupUi(this);

    //去除边框
    setWindowFlags(Qt::FramelessWindowHint);

    //设置定时器
    ShowTimer = new QTimer(this);
	
    connect(ShowTimer,SIGNAL(timeout()),this,SLOT(DoShowMsg()));

}

MsgShowWin::~MsgShowWin()
{
    delete ui;
}

void MsgShowWin::paintEvent(QPaintEvent *)//画图事件画背景图片
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/pic/pic_bg/bkg.png"));
}

void MsgShowWin::mousePressEvent(QMouseEvent *)
{
    this->ShowTimer->stop();
}

void MsgShowWin::mouseReleaseEvent(QMouseEvent *)
{
    this->ShowTimer->start(100);
}

void MsgShowWin::MsgShow()
{
    /* 读取短消息 */
	QFile file("./msg_leave");
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug()<<"can't open the file !"<<endl;
	}
	while(!file.atEnd())
	{
		QString str(file.readAll());
		qDebug()<<str;
		ui->textBrowser->setText(str);
    }
	
	this->setWindowOpacity(0);
    this->show();
    this->flag = SHOW;
    this->ShowTimer->start(100);
}

void MsgShowWin::DoShowMsg()
{
    static double tS = 0.00;
    static double tH = 1.00;
    if(flag == SHOW)
    {
        if(tS > 1)
        {
            this->ShowTimer->stop();
            tS = 0.0;
            flag = HIDE;
            this->ShowTimer->start(100);
            return;
        }
        this->setWindowOpacity(tS);
        tS += 0.05;
    }
    else if(flag == HIDE)
    {
        if(tH < 0)
        {
            this->ShowTimer->stop();
            tH = 1.0;
            this->hide();
            emit this->mainmenu_show();
            return;
        }
        this->setWindowOpacity(tH);
        tH -= 0.05;
    }
}
