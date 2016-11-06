#ifndef TEMPERATUREWIN_H
#define TEMPERATUREWIN_H

#include <QWidget>
#include <QPainter>
#include <QSound>
#include <QTimer>

namespace Ui {
    class TemperatureWin;
}

class TemperatureWin : public QWidget
{
    Q_OBJECT

public:
    explicit TemperatureWin(QWidget *parent = 0);
    ~TemperatureWin();
	QTimer *timer;              //定时器

signals:
    void show_main_menu();  //显示主菜单信号

private:
    Ui::TemperatureWin *ui; 
    QString Temperature_Value;
    QString Humidity_Value;
    QString recv_buf;
    QSound bells;

    int temperature_max;            //温度上限
    int temperature_min;            //温度下限
    int humidity_max;               //湿度上限
    int humidity_min;               //湿度下限
    int temperature_max_before;     //存储温度上限
    int temperature_min_before;     //存储温度下限
    int humidity_max_before;        //存储湿度上限
    int humidity_min_before;        //存储湿度下限
    int temperature_flag;           //温度的超标标志
    int humidity_flag;              //湿度的超标标志

    //温湿度响铃标志位
    int sound_tem_flag;
    int sound_tem_flag_before;
    int sound_hum_flag;
    int sound_hum_flag_before;

private slots:
	void on_Bt_Commit_clicked();
    void on_Bt_Exit_clicked();
    void TimeSlot();

protected:
    void paintEvent(QPaintEvent *);//绘制背景图


};

#endif // TEMPERATUREWIN_H
