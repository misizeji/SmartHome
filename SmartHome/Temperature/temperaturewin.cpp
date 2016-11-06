#include "temperaturewin.h"
#include "ui_temperaturewin.h"

extern "C"  //是大写的 C
{
    #include "init.h"
}

TemperatureWin::TemperatureWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemperatureWin),bells("./media_sources/warning.wav")
{
    ui->setupUi(this);

    //去除边框
    setWindowFlags(Qt::FramelessWindowHint);
    //this->showFullScreen();

    //报警标志位
    this->sound_tem_flag = 0;
    this->sound_tem_flag_before = 0;
    this->sound_hum_flag = 0;
    this->sound_hum_flag_before = 0;

    //温湿度初始值
    this->temperature_max_before = 30;
    this->temperature_min_before = 0;
    this->humidity_max_before = 30;
    this->humidity_min_before = 0;
    this->temperature_flag = 0;
    this->humidity_flag = 0;

    //设置显示值
    ui->spinBox_TemMax->setValue(temperature_max_before);
    ui->spinBox_TemMin->setValue(temperature_min_before);
    ui->spinBox_WetMax->setValue(humidity_max_before);
    ui->spinBox_WetMin->setValue(humidity_min_before);

    //定时器
    this->timer = new QTimer(this);

	this->timer->start(1000);

    //信号与槽
    connect(timer,SIGNAL(timeout()),this,SLOT(TimeSlot()));


}

TemperatureWin::~TemperatureWin()
{
    delete ui;
}


void TemperatureWin::paintEvent(QPaintEvent *)//画图事件画背景图片
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/pic/pic_bg/bkg.png"));
}


void TemperatureWin::TimeSlot()//定时器处理函数
{
    //温湿度检测
    char *Value_recv = init();
    recv_buf = QString(QLatin1String(Value_recv));
    this->Temperature_Value = recv_buf.section(",",0,0);
    this->Humidity_Value = recv_buf.section(",",1,1);
    this->temperature_max = recv_buf.section(",",2,2).toInt();
    this->humidity_max = recv_buf.section(",",3,3).toInt();
    this->temperature_min = recv_buf.section(",",4,4).toInt();
    this->humidity_min = recv_buf.section(",",5,5).toInt();
    this->temperature_flag = recv_buf.section(",",6,6).toInt();
    this->humidity_flag = recv_buf.section(",",7,7).toInt();

    //设置目前温湿度值
    ui->Lb_TemValue->setText(Temperature_Value.left(5));
    ui->Lb_WetValue->setText(Humidity_Value.left(5));

    //对比设置的温湿度上下限
    if((temperature_max_before != temperature_max)||
        (temperature_min_before != temperature_min)||
        (humidity_min_before != humidity_min)||
        (humidity_max_before != humidity_max))
    {
        ui->spinBox_TemMin->setValue(temperature_min);
        ui->spinBox_TemMax->setValue(temperature_max);
        ui->spinBox_WetMin->setValue(humidity_min);
        ui->spinBox_WetMax->setValue(humidity_max);

        //存储温湿度上下限
        temperature_max_before = temperature_max;
        temperature_min_before = temperature_min;
        humidity_min_before = humidity_min;
        humidity_max_before = humidity_max;
    }

    //温度报警及字体设置
    if(this->temperature_flag == 1)
    {
        ui->Lb_Tem->setPixmap((QPixmap(":/ico/pic_ico/tem_warn.png")));
        QPalette p;	//新建配置
        p.setColor(QPalette::WindowText,Qt::red);	//设置字体颜色粉色
        ui->Lb_TemValue->setPalette(p);
        this->sound_tem_flag = 1;
    }
    else
    {
        ui->Lb_Tem->setPixmap((QPixmap(":/ico/pic_ico/tem.png")));
        QPalette p;	//新建配置
        p.setColor(QPalette::WindowText,Qt::green);	//设置字体颜色粉色
        ui->Lb_TemValue->setPalette(p);
        this->sound_tem_flag = 0;
    }

    //湿度报警及字体设置
    if(this->humidity_flag == 1)
    {
        ui->Lb_Wet->setPixmap(QPixmap(":/ico/pic_ico/wet_warn.png"));
        QPalette p;	//新建配置
        p.setColor(QPalette::WindowText,Qt::red);	//设置字体颜色粉色
        ui->Lb_WetValue->setPalette(p);
        this->sound_hum_flag = 1;
    }
    else
    {
        ui->Lb_Wet->setPixmap(QPixmap(":/ico/pic_ico/wet.png"));
        QPalette p;	//新建配置
        p.setColor(QPalette::WindowText,Qt::green);	//设置字体颜色粉色
        ui->Lb_WetValue->setPalette(p);
        this->sound_hum_flag = 0;
    }

    //报警音检测播放
    if(((sound_tem_flag != sound_tem_flag_before)||(sound_hum_flag != sound_hum_flag_before))
        &&((sound_tem_flag == 1)||(sound_hum_flag == 1)))
    {
        bells.setLoops(6);
        bells.play();
        sound_tem_flag_before = sound_tem_flag;
        sound_hum_flag_before = sound_hum_flag;
    }
    else if(((sound_tem_flag != sound_tem_flag_before)||(sound_hum_flag != sound_hum_flag_before))
        &&((sound_tem_flag == 0)||(sound_hum_flag == 0)))
    {
        bells.stop();
        sound_tem_flag_before = sound_tem_flag;
        sound_hum_flag_before = sound_hum_flag;
    }
    else
    {
        ;
    }
}

void TemperatureWin::on_Bt_Commit_clicked()//设置温湿度上下限
{

    QString commit_buf = QString("%1,%2,%3,%4").arg(ui->spinBox_TemMax->value()).arg(ui->spinBox_WetMax->value()).
               arg(ui->spinBox_TemMin->value()).arg(ui->spinBox_WetMin->value());
    QString recv_buf = QString(QLatin1String(real_time(commit_buf.toLatin1().data())));
    this->Temperature_Value = recv_buf.section(",",0,0);
    this->Humidity_Value = recv_buf.section(",",1,1);
    this->temperature_max = recv_buf.section(",",2,2).toInt();
    this->humidity_max = recv_buf.section(",",3,3).toInt();
    this->temperature_min = recv_buf.section(",",4,4).toInt();
    this->humidity_min = recv_buf.section(",",5,5).toInt();
    this->temperature_flag = recv_buf.section(",",6,6).toInt();
    this->humidity_flag = recv_buf.section(",",7,7).toInt();
	
	ui->spinBox_TemMin->setValue(temperature_min);
    ui->spinBox_TemMax->setValue(temperature_max);
    ui->spinBox_WetMin->setValue(humidity_min);
    ui->spinBox_WetMax->setValue(humidity_max);
    //设置目前温湿度值
    ui->Lb_TemValue->setText(Temperature_Value.left(5));
    ui->Lb_WetValue->setText(Humidity_Value.left(5));

}

void TemperatureWin::on_Bt_Exit_clicked()//返回主界面
{
    emit this->show_main_menu();
	this->timer->stop();
    this->close();
}
