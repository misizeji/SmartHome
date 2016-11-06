#ifndef LEDCNTLWIN_H
#define LEDCNTLWIN_H

#include <QWidget>
#include <QPainter>
#include <QTimer>


namespace Ui {
    class LedCntlWin;
}

class LedCntlWin : public QWidget
{
    Q_OBJECT

public:
    explicit LedCntlWin(QWidget *parent = 0);
    ~LedCntlWin();

private:
    Ui::LedCntlWin *ui;
    QTimer *timer;      //¶¨Ê±Æ÷

    int led_state;      //µÆ×´Ì¬
    bool IsLed1;        //led1×´Ì¬¼ü
    bool Isled2;        //led2×´Ì¬¼ü
    bool Isled3;        //led3×´Ì¬¼ü


signals:
    void show_main_menu();  //ÏÔÊ¾Ö÷²Ëµ¥ÐÅºÅ

private slots:
    void TimeroutSlot();           //¶¨Ê±Æ÷´¦Àíº¯Êý
    void on_Bt_LedAll_clicked();
    void on_Bt_Led3_clicked();
    void on_Bt_Led2_clicked();
    void on_Bt_Led1_clicked();
    void on_Bt_Exit_clicked();

protected:
    void paintEvent(QPaintEvent *);//»æÖÆ±³¾°Í¼


};

#endif // LEDCNTLWIN_H
