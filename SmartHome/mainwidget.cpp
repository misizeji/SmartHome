#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "options.h"

#include <QDebug>
#include <QString>
#include <QPalette>
#include <QStringList>
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QMessageBox>


mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);


    //»­±³¾°Í¼Æ¬(³õÊ¼±³¾°Í¼Æ¬µÄÃû³Æ)
    this->pic_bg = ":/pic/pic_bg/3.png";

    //ÉèÖÃ¶¨Ê±Æ÷
    this->timer = new QTimer(this);
    show_pic_delay = 5;
    this->timer->start(show_pic_delay * 1000);

    //¶ÁÈ¡±³¾°Í¼Æ¬Êý×é
    this->pic_bg_list<<":/pic/pic_bg/0.png"<<":/pic/pic_bg/1.png"<<":/pic/pic_bg/2.png"
            <<":/pic/pic_bg/3.png"<<":/pic/pic_bg/4.png"<<":/pic/pic_bg/5.png";

    //È¥³ý±ß¿ò
    setWindowFlags(Qt::FramelessWindowHint);
    //this->showFullScreen();

    //Ìí¼ÓµÇÂ¼´°¿Ú
    this->login_form = new LoginForm;
    //this->login_form->setGeometry(this->geometry());

    //ÐÅºÅÓë²Û
    connect(this->timer,SIGNAL(timeout()),this,SLOT(pic_bg_show()));//±³¾°Í¼Æ¬×Ô¶¯ÇÐ»»
    connect(this->login_form,SIGNAL(bg_show()),this,SLOT(widget_show()));//±³¾°Í¼Æ¬¼ÌÐøÂÖ²¥

}

mainWidget::~mainWidget()
{
    delete ui;
}


void mainWidget::paintEvent(QPaintEvent *)//»­Í¼ÊÂ¼þ»­±³¾°Í¼Æ¬
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(pic_bg));
}

void mainWidget::mousePressEvent(QMouseEvent *ev)//Êó±ê°´ÏÂÊÂ¼þ
{
    int x = ev->x();//Êó±êµã»÷µÄx×ø±ê
    int y = ev->y();//Êó±êµã»÷µÄy×ø±ê

    qDebug()<<"x = "<<x
            <<" y = "<<y;
    qDebug()<<ev->pos();//ÏÔÊ¾Êó±êµÄpos

    this->timer->stop();

    this->hide();
    this->login_form->show();
    this->login_form->Edit_Clear();
}

void mainWidget::pic_bg_show()//±³¾°Í¼Æ¬ÏÔÊ¾º¯Êý
{
    static int pic_num = 1;
    int i = (pic_num%5);

    this->pic_bg = pic_bg_list[i];
    pic_num++;
    this->update();//Ë¢ÐÂ»­Í¼
}

void mainWidget::widget_show()//±³¾°Í¼Æ¬¼ÌÐøÂÖ²¥
{
    this->show();
    this->timer->start(show_pic_delay * 1000);
}







