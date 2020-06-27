#include "mainwindow.h"
#include "login.h"
#include "mainwindow.h"
#include "pokemon.h"
#include "high_attack.h"
#include "high_blood.h"
#include "high_defense.h"
#include "high_speed.h"
#include "user.h"
#include <windows.h>

#include <QApplication>

int main(int argc, char *argv[])
{
FreeConsole();
#if (QT_VERSION >= QT_VERSION_CHECK(5,9,0)) //适应不同分辨率
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif


    QApplication a(argc, argv);

    Login login;


    if(login.exec() == QDialog::Accepted)//模式对话框
    {
          MainWindow w(0, &login);
          w.show();
          return a.exec();
    }
    else
         return 0;
}
