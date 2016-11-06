#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwidget.h"
//#include "connection.h"
#include "options.h"

int show_pic_delay = 5;
int show_menu_delay = 30;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
/*	
	if (!createConnection())
    {
        return -1;
    }
*/
    mainWidget w;
    w.show();

    return a.exec();
}
