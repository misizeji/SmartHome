#include "usermngwin.h"
#include "ui_usermngwin.h"

UserMngWin::UserMngWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserMngWin)
{
    ui->setupUi(this);
}

UserMngWin::~UserMngWin()
{
    delete ui;
}
