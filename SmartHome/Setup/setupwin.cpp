#include "setupwin.h"
#include "ui_setupwin.h"

SetupWin::SetupWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetupWin)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    ui->spinBox_ShowPic->setValue(show_pic_delay);
    ui->spinBox_ShowMenu->setValue(show_menu_delay);


}

SetupWin::~SetupWin()
{
    delete ui;
}

void SetupWin::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/pic/pic_bg/bkg.png"));
}

void SetupWin::on_Bt_Commit_clicked()
{
    show_pic_delay = ui->spinBox_ShowPic->value();
    show_menu_delay = ui->spinBox_ShowMenu->value();
}

void SetupWin::on_Bt_Exit_clicked()
{
    on_Bt_Commit_clicked();
    emit this->show_main_menu();
    this->close();
}
