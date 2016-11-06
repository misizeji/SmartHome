#ifndef MOVIEWIN_H
#define MOVIEWIN_H

#include <QWidget>
#include <QProcess>
#include <unistd.h>
#include <QString>
#include <QStringList>
#include <QPainter>
#include <QDebug>
#include <QFileDialog>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>

namespace Ui {
    class moviewin;
}

class moviewin : public QWidget
{
    Q_OBJECT

public:
    explicit moviewin(QWidget *parent = 0);
    ~moviewin();
    QTime int_to_time(int);

private:
    Ui::moviewin *ui;
    QProcess *process;      //添加linux系统命令进程
    QString fileName;       //播放视频文件名
    QTimer *timer;          //定时器

    bool isPlay;	//播放标志位
    bool isStop;	//停止标志位
    bool isDoubleClick; //是否为鼠标双击事件

    int pos_x_begin;	//按下起始坐标x
    int pos_x_end;	//抬起结束坐标x
    int pos_y_begin;	//按下起始坐标y
    int pos_y_end;	//抬起结束坐标y

    int cur_value;  //存储音量值
    int cur_time;	//当前播放时间
    int file_length;	//文件总长度

signals:
    void show_main_menu();

private slots:

    void movie_volume_set(int value,bool flag);
    void movie_forward_slots();
    void movie_PlayPause_slots();
    void movie_backward_slots();
    void movie_stop_slots();
    void movie_return_slots();
    void mouse_deal_slots();
    void write_ask_command();
    void get_mplayer_msg();

public slots:
	void movie_begin();		//电影开始播放

protected:
    void mousePressEvent(QMouseEvent *);        //鼠标点击事件
    void mouseReleaseEvent(QMouseEvent *ev);    //鼠标抬起事件
    void mouseDoubleClickEvent(QMouseEvent *ev);//鼠标双击事件
};

#endif // MOVIEWIN_H
