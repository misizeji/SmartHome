#include "moviewin.h"
#include "ui_moviewin.h"

moviewin::moviewin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::moviewin)
{
    ui->setupUi(this);

	//去除边框
    setWindowFlags(Qt::FramelessWindowHint);
    
	this->process = new QProcess;

    //设置定时器
    this->timer = new QTimer(this);
    this->timer->start(1000);
    connect(this->timer,SIGNAL(timeout()),this,SLOT(write_ask_command()));
    connect(this->process,SIGNAL(readyReadStandardOutput()),this,SLOT(get_mplayer_msg()));

}

moviewin::~moviewin()
{
    delete ui;
}

void moviewin::movie_begin()
{
	isPlay = true;
    isStop = false;
	isDoubleClick = false;
	//为了下次能够再次播放
	cur_time = 0;
	file_length = 20;
	//结束
	
	//路径都是相对于当前生成的应用程序目录
	QString common = "mplayer -idle -slave -quiet -autosync 30 -vf scale=800:480 ./media_sources/future_homelife.flv ";
    qDebug()<<"this command is "<<common;

	process->write("quit\n");
	process->close();
    process->start(common);     //开始运行程序
	
	this->cur_value = 0;
    process->write(QString("volume " + QString::number(cur_value) + " 1\n").toAscii());
}

void moviewin::mousePressEvent(QMouseEvent *ev)//鼠标按下事件
{
    pos_x_begin = ev->x();//鼠标点击的x坐标
    pos_y_begin = ev->y();//鼠标点击的y坐标

    //qDebug()<<" PressEvent x = "<<pos_x_begin<<" y = "<<pos_y_begin;
    //qDebug()<<ev->pos();//显示鼠标的pos
}

void moviewin::mouseReleaseEvent(QMouseEvent *ev)//鼠标抬起事件
{
    pos_x_end = ev->x();//鼠标点击的x坐标
    pos_y_end = ev->y();//鼠标点击的y坐标

    //qDebug()<<" ReleaseEvent x = "<<pos_x_end<<" y = "<<pos_y_end;
    //qDebug()<<ev->pos();//显示鼠标的pos
	
	mouse_deal_slots();
}

void moviewin::mouseDoubleClickEvent(QMouseEvent *ev)//鼠标双击事件
{
    //qDebug()<<" DoubleClickEvent x = "<<ev->x()<<" y = "<<ev->y();
	isDoubleClick = true;
	
	mouse_deal_slots();
}

void moviewin::mouse_deal_slots()//鼠标事件处理函数
{
	int x = pos_x_end - pos_x_begin;
	int y = pos_y_end - pos_y_begin;
	bool IsForward = false;
	bool IsAddVolume = false;
	
	//qDebug()<<" Before mouse_deal_slots x = "<<x
            //<<" y = "<<y;
	if(x < 0)
	{
		IsForward = false;
		x = 0 - x;
	}
	else
	{
		IsForward = true;	
	}
	
	if(y < 0)
	{
		IsAddVolume = true;
		y = 0 - y;
	}
	else
	{
		IsAddVolume = false;
	}
	//qDebug()<<" After mouse_deal_slots x = "<<x
            //<<" y = "<<y;
			
	if(isDoubleClick)
	{
		isDoubleClick = false;
		movie_return_slots();
	}
	else
	{
		if(x < 30 && y > 30)//设置音量
		{
			if(y < 300)
			{
				movie_volume_set((y/30),IsAddVolume);
			}
			else
			{
				movie_volume_set(100,IsAddVolume);
			}
		}
		else if(x > 30 && y < 30)//快进快退
		{
			if(IsForward)
			{
				movie_forward_slots();
			}
			else
			{
				movie_backward_slots();
			}
		}
		else
		{
			movie_PlayPause_slots();
		}
	}
}

void moviewin::write_ask_command()//写请求命令
{
    if(isPlay)
    {
        process->write("get_time_pos\n");
        process->write("get_time_length\n");
    }
}

void moviewin::get_mplayer_msg()//获取MPlayer消息
{
    while(process->canReadLine())
    {
        QString message(process->readLine());
        QStringList message_list = message.split("=");
          if(message_list[0] == "ANS_TIME_POSITION")
        {
            cur_time = message_list[1].toDouble();//toInt();
            cur_time = cur_time + 1;
            QTime time = int_to_time(cur_time);
            qDebug()<<"time_pos ="<<time.toString("hh:mm:ss");
            //label->setText(time.toString("hh:mm:ss"));
            //horizontalSlider->setValue(100 * curr_time / file_length);
        }
        else if(message_list[0] == "ANS_LENGTH")
        {
            file_length = message_list[1].toDouble();//toInt();
            QTime time = int_to_time(file_length);
            qDebug()<<"file_length ="<<time.toString("hh:mm:ss");
            //label_2->setText(time.toString("hh:mm:ss"));
        }
    }
	
	if(cur_time >= file_length && (!isStop))
	{
		qDebug()<<"in the end func";
		//为了下次能够再次播放
		cur_time = 0;
		file_length = 20;
		//结束
		movie_stop_slots();
	}
}

void moviewin::movie_volume_set(int value,bool flag)//设置音量
{
    //qDebug()<<"the vloume is "<<value;
    if(flag)
    {
        cur_value = cur_value + value;
		if(cur_value > 100)
		{
			cur_value = 100;
		}
        process->write(QString("volume " + QString::number(cur_value) + " 1\n").toAscii());
    }
    else
    {
        cur_value = cur_value - value;
		if(cur_value < 0)
		{
			cur_value = 0;
		}
        process->write(QString("volume " + QString::number(cur_value) + " 1\n").toAscii());
    }
	qDebug()<<"the cur_vloume is "<<cur_value;
}

void moviewin::movie_forward_slots()//快进
{
    if(process && process->state() == QProcess::Running )
    {
		if(cur_time > (file_length - 5))
		{
			if((cur_time + 2) < file_length)
			{
				process->write(QString("seek " + QString::number(file_length - (cur_time + 2)) + "\n").toAscii());
			}
		}
		else
		{
			process->write("seek 5\n");
		}
        isPlay = true;
		movie_volume_set(0,true);//重新设置音量
    }
    else
    {
        qDebug()<<"process is not running!!!";
    }
}

void moviewin::movie_PlayPause_slots()//暂停
{
    if(!isPlay)//当前没在播放
    {
        if(isStop)
        {	
			/*
			qDebug()<<" begin the new file ";
            QString common = "mplayer -idle -slave -quiet -autosync 30 -vf scale=800:480 ./media_sources/future_homelife.flv ";
            process->close();
            process->start(common);
            isStop = false;
			*/
		}
        else
        {
            process->write("pause\n");
        }
        isPlay = true;
    }
    else//当前正在播放
    {
        process->write("pause\n");
        isPlay = false;
    }
	
	if(isPlay)
	{
		movie_volume_set(0,true);//重新设置音量
	}
}

void moviewin::movie_backward_slots()//快退
{
    if(process && process->state() == QProcess::Running )
    {
		if(cur_time < 5)
		{
			process->write(QString("seek " + QString::number(- cur_time) + "\n").toAscii());
		}
        else
		{
			process->write("seek -5\n");
		}
        isPlay = true;
		movie_volume_set(0,true);//重新设置音量
    }
    else
    {
        qDebug()<<"process is not running!!!";
    }
}

void moviewin::movie_stop_slots()//停止播放
{
    if(!isStop)
    {
        process->write("quit\n");
        process->close();
        isPlay = false;
        isStop = true;
    }
    else
    {
        qDebug()<<"it is already stop !!!";
    }
}
void moviewin::movie_return_slots()//退出函数
{
    movie_stop_slots();
    emit this->show_main_menu();
    this->close();
}

QTime moviewin::int_to_time(int second)
{
    int sec = 0, min = 0, hour = 0;
    QTime time;
    if(second < 60)
    {
        sec = second;
        min = 0;
        hour = 0;
    }
    if(second >= 60 && second < 3600)
    {
        sec = second % 60;
        min = second / 60;
        hour = 0;
    }
    if(second >= 3600)
    {
        sec = second % 60;
        min = (second / 60) % 60;
        hour = second / 3600;
    }

    time.setHMS(hour,min,sec);
    return time;
}
