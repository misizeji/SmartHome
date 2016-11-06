#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "./loginform/loginform.h"

namespace Ui {
    class mainWidget;
}

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = 0);
    ~mainWidget();

private:
    Ui::mainWidget *ui;
    QTimer *timer;              //¶¨Ê±Æ÷
    QString pic_bg;             //±³¾°Í¼Æ¬Ãû³Æ
    QStringList pic_bg_list;    //½¨Á¢×Ö·û´®Í¼Æ¬Êý×é
    LoginForm *login_form;      //µÇÂ¼´°¿Ú




private slots:
    void pic_bg_show();     //±³¾°Í¼Æ¬×Ô¶¯ÇÐ»»º¯Êý
    void widget_show();     //±³¾°Í¼Æ¬¼ÌÐøÂÖ²¥



protected:
    void paintEvent(QPaintEvent *);//»æÖÆ±³¾°Í¼
    void mousePressEvent(QMouseEvent *);//Êó±êµã»÷ÊÂ¼þ


};

#endif // MAINWIDGET_H
