#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

#include "../ledcontrol/ledcntlwin.h"
#include "../GPRSMsg/gprsmsgwin.h"
#include "../MovieWin/moviewin.h"
#include "../MsgLeave/msgleavewin.h"
#include "../Setup/setupwin.h"
#include "../Temperature/temperaturewin.h"
#include "../usermng/usermngwin.h"

namespace Ui {
    class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private:
    Ui::MainMenu *ui;

    //UserMngWin *UsrMng;         //用户管理菜单
    LedCntlWin *LedCntl;        //led灯控制窗口
    GPRSMsgWin *GprsMsg;        //GPRS模块发送信息
    TemperatureWin *TemCntl;    //温湿度检测控制
    MsgLeaveWin *MsgLeave;      //留言窗口
    moviewin *MovieWin;         //添加播放器窗口
    SetupWin *Setup;            //添加设置窗口

signals:
    void menu_exit();         //菜单退出按钮

private slots:
    void on_Bt_Setup_clicked();
    void on_Bt_Movie_clicked();
    void on_Bt_MsgLeave_clicked();
    void on_Bt_Tem_clicked();
    void on_Bt_GPRSMsg_clicked();
    void on_Bt_LedSet_clicked();
    void on_Bt_UserMng_clicked();
    void on_Bt_Exit_clicked();
    void main_menu_show();      //显示主菜单窗口



};

#endif // MAINMENU_H
