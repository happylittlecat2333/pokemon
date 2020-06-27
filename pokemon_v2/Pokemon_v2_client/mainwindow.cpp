#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Login *login)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAutoFillBackground(true);

    ui->setupUi(this);

    allPkmAttr = login->getAllPkm();
    username = login->getUsername();
//    Users.clear();
    mode = 0;


    server = new QUdpSocket(this); //创建一个QUdpSocket类对象，负责接收
    client = new QUdpSocket(this);
    port = 45454+1;
    while(true){
       if(!(server->bind(port)))
           port++;
       else break;
    }
//    connect(server, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams())); //readyRead()信号是每当有新的数据来临时就被触发

    button_group = new QButtonGroup(this);
    button_group->addButton (ui->radioButton_1,0);
    button_group->addButton (ui->radioButton_2,1);
    button_group->addButton (ui->radioButton_3,2);

    ui->radioButton_1->setChecked(1);
    ui->label_username->setText("My Pokemon");
    ui->label_allAttr->setText(getPkmAttr(0));


    connect(button_group, SIGNAL(buttonClicked(int)), this,SLOT(RecvPkmID(int)));

}


MainWindow::~MainWindow()
{

    delete ui;
    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);
    dsOut << SIGN_OUT << username << port;
    client->writeDatagram(data.data(), data.size(), QHostAddress::LocalHost, 45454);
    while(allPkmAttr!= NULL)
        delete allPkmAttr[-1];
    delete server;
    delete client;

}

void MainWindow::RecvPkmID(int num){
    ui->label_allAttr->setText(getPkmAttr(num));
}


QString MainWindow::getPkmAttr(unsigned int num){
    Pkm* tmp = NULL;
    if(mode == 0)
        tmp = allPkmAttr[num];
   else if(mode == 1)
        tmp = this->Users[ui->listWidget_AllUser->currentRow()-1]->getAllPkmAttr(num);
    else if(mode == 2)
        tmp = this->online_user[ui->listWidget_AllUser->currentRow()-1]->getAllPkmAttr(num);

    QString all;
    all = all + "name:" + tmp->name;
    all = all + "\nlevel:" + QString::number(tmp->level);
    all = all + "\nexperience:" + QString::number(tmp->experience);
    all = all + "\nattack:" + QString::number(tmp->attack);
    all = all + "\ndefense:" + QString::number(tmp->defense);
    all = all + "\nblood:" + QString::number(tmp->blood);
    all = all + "\nspeed:" + QString::number(tmp->speed);
    return all;

}



void MainWindow::processPendingDatagrams()
{
    qDebug() << "mainwindow processing";
    while(server->hasPendingDatagrams()){
        QByteArray datagIn;    //存放接收的数据
        datagIn.resize(server->pendingDatagramSize()); //pendingDatagramSize为返回第一个在等待读取报文的size，让dataIn的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        server->readDatagram(datagIn.data(), datagIn.size());  //接收数据报，将其存放到dataIn中

        QDataStream dsIn(&datagIn, QIODevice::ReadWrite);
        QString username;
        QString password;
        unsigned int port;
        unsigned int data_type;

//        QByteArray dataOut;
//        QDataStream dsOut(&dataOut,QIODevice::ReadWrite);
//        QSqlQuery query;

        dsIn >> data_type;

        if(data_type == ALL_USER){
            qDebug() << "all user";
            Users.clear();
            while(!dsIn.atEnd()) {
                User *tmp_user  = new User;
                dsIn >> username;
                qDebug() << username;
                tmp_user->setUsername(username);
                for(int i=0;i<3;i++){
                    tmp_user->setUser(dsIn);
                }
                this->Users.append(tmp_user);
            }
            qDebug() << "all user over";
       }
       else if(data_type == ONLINE_USER){
            qDebug() << "Online user";
            online_user.clear();
            while(!dsIn.atEnd()) {
                User *tmp_user  = new User;
                dsIn >> username;
                qDebug() << username;
                tmp_user->setUsername(username);
                for(int i=0;i<3;i++){
                    tmp_user->setUser(dsIn);
                }
                this->online_user.append(tmp_user);
            }
            qDebug() << "all user over";
        }


    }
}

void MainWindow::on_listWidget_AllUser_currentRowChanged(int currentRow)
{
    if(currentRow >= 1){
    if(mode==1 && currentRow<Users.length()) ui->label_username->setText (tr("%1's Pokemon").arg(this->Users[currentRow-1]->getUsername()));
    else if(mode==2 && currentRow<online_user.length()) ui->label_username->setText (tr("%1's Pokemon").arg(this->online_user[currentRow-1]->getUsername()));
    ui->radioButton_1->setChecked (true);
    ui->label_allAttr->setText (this->getPkmAttr(0));
    }
}

void MainWindow::on_pushButton_allUser_clicked()
{
    mode = 1;
    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);
    dsOut << ALL_USER << username << port;//发送类型，用户名以及端口号
    client->writeDatagram(data.data(), data.size(),QHostAddress::Broadcast, 45454);

    if(server->waitForReadyRead (5000))//判断连接超时
    {
        this->processPendingDatagrams ();
        qDebug() << "all push";
        ui->listWidget_AllUser->clear ();
        ui->listWidget_AllUser->addItem ("Username");
        qDebug() << Users.length();

        for(int i=0;i<Users.length();i++)
            ui->listWidget_AllUser->addItem (tr("%1").
                                          arg (this->Users[i]->getUsername()));
        ui->listWidget_AllUser->setCurrentRow (1);
        ui->label_username->setText (tr("%1's Pokemon").arg(this->Users[0]->getUsername()));

    }
    else
         QMessageBox::critical (this,"Get Data Failed","Connect Failed","OK");

}

void MainWindow::on_pushButton_myPkm_clicked()
{
    mode = 0;
    ui->label_username->setText("My Pokemon");
    ui->radioButton_1->setChecked(true);
    ui->label_allAttr->setText(this->getPkmAttr(0));
}


void MainWindow::on_pushButton_LogOut_clicked()
{
    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);
    dsOut << SIGN_OUT << username << port;//发送类型，用户名以及端口号
    client->writeDatagram(data.data(), data.size(),QHostAddress::Broadcast, 45454);
    this->~MainWindow();
}

void MainWindow::on_pushButton_onlineUser_clicked()
{
    mode = 2;
    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);
    dsOut << ONLINE_USER << username << port;//发送类型，用户名以及端口号
    client->writeDatagram(data.data(), data.size(),QHostAddress::Broadcast, 45454);

    if(server->waitForReadyRead (5000))//判断连接超时
    {
        this->processPendingDatagrams ();
        qDebug() << "all push online";
        ui->listWidget_AllUser->clear ();
        ui->listWidget_AllUser->addItem ("Username");
        qDebug() << online_user.length();
        ui->label_allUser->setText("Online User");
        for(int i=0;i<online_user.length();i++)
            ui->listWidget_AllUser->addItem (tr("%1").
                                          arg (this->online_user[i]->getUsername()));
        ui->listWidget_AllUser->setCurrentRow (1);
        ui->label_username->setText (tr("%1's Pokemon").arg(this->online_user[0]->getUsername()));

    }
    else
         QMessageBox::critical (this,"Get Data Failed","Connect Failed","OK");

}
