#ifndef MSGSHOWWIN_H
#define MSGSHOWWIN_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QString>
#include <QDebug>
#include <QFile>

#define SHOW 1
#define HIDE 0

namespace Ui {
    class MsgShowWin;
}

class MsgShowWin : public QWidget
{
    Q_OBJECT

public:
    explicit MsgShowWin(QWidget *parent = 0);
    ~MsgShowWin();

private:
    Ui::MsgShowWin *ui;
    QTimer *ShowTimer;
    int flag;

signals:
    void mainmenu_show();

protected:
    void paintEvent(QPaintEvent *ev);
    void mousePressEvent(QMouseEvent *ev);        //鼠标点击事件
    void mouseReleaseEvent(QMouseEvent *ev);    //鼠标抬起事件

private slots:
    void DoShowMsg();

public slots:
    void MsgShow();

};

#endif // MSGSHOWWIN_H
