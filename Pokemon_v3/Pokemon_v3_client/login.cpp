#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    server = new QUdpSocket(this); //创建一个QUdpSocket类对象
    client = new QUdpSocket(this);
    port = 45454+1;
    while(true){    //绑定接收端口
       if(!(server->bind(port)))
           port++;
       else break;
    }
}


Login::~Login()
{
    delete ui;
    server->close();
    client->close();
    delete server;
    delete client;
}


void Login::processPendingDatagrams()
{
    QByteArray datagIn;    //存放接收的数据
    datagIn.resize(server->pendingDatagramSize()); //pendingDatagramSize为返回第一个在等待读取报文的size，让dataIn的大小为等待处理的数据报的大小，这样才能接收到完整的数据
    server->readDatagram(datagIn.data(), datagIn.size());  //接收数据报，将其存放到dataIn中

    QDataStream dsIn(&datagIn, QIODevice::ReadWrite);
    QString username;
    QString password;
    unsigned int log_type;
    dsIn >> log_type;

    if(log_type == SIGN_IN_SUCESS){
        QMessageBox::information (this,"Sign In","Login Success","OK");
        dsIn >> this->win;
        dsIn >> this->lose;
        for(int i=0; !dsIn.atEnd(); i++)    //加载用户的pokemon信息
            setAttrAll(dsIn, i);
        server->close();
        client->close();
        delete server;
        delete client;
        accept();
    }
    else if(log_type == SIGN_UP_SUCCESS){
        QMessageBox::information (this,"Sign Up","Sign Up Success","OK");
        dsIn >> this->win;
        dsIn >> this->lose;
        for(int i=0; i<3; i++)  //加载用户的pokemon信息
            setAttrAll(dsIn, i);
        server->close();
        client->close();
        delete server;
        delete client;
        accept();
    }
    else if(log_type == NAME_EXIST){
        QMessageBox::critical(this, "Sign Up Error", "Name Already Exist, try a new username");
    }
    else if(log_type == USER_NONE){
        QMessageBox::critical(this, "Sign In Error", "Username does not exit");
    }
    else if(log_type == PWD_ERROR){
        QMessageBox::critical(this, "Sign In Error", "Password does not correct");
    }

}

void Login::setAttrAll(QDataStream &dsIn, unsigned int num)  //加载pokemon信息
{
    pkmNum++;
    Pkm *tmp = new Pkm;
    dsIn >> tmp->name;
    dsIn >> tmp->level;
    dsIn >> tmp->experience;
    dsIn >> tmp->attack;
    dsIn >> tmp->blood;
    dsIn >> tmp->defense;
    dsIn >> tmp->speed;
    dsIn >> tmp->kind;
    dsIn >> tmp->skill;

    attrAll[num] = tmp;
}



void Login::on_pushButton_signIn_clicked()  //登录事件处理
{
    QString username = ui->lineEditName->text();
    QString password = ui->lineEditPwd->text();

    this->username = username;
    if(!username.isEmpty() && !password.isEmpty()){
       QByteArray dataOut;
       QDataStream dsOut(&dataOut, QIODevice::ReadWrite);
       dsOut << SIGN_IN << username << password << port;
       client->writeDatagram(dataOut.data(), dataOut.size(), QHostAddress::Broadcast, 45454);

       if(server->waitForReadyRead(600))
           processPendingDatagrams();
       else
           QMessageBox::critical(this, "Sign In failed", "Sign In TimeOut");
    }
    else
        QMessageBox::critical(this, "No Input", "No Username or Password, please fill in");
}


void Login::on_pushButton_signUp_clicked()  //注册事件处理
{
    QString username = ui->lineEditName->text();
    QString password = ui->lineEditPwd->text();

    this->username = username;
    if(!username.isEmpty() && !password.isEmpty()){
       QByteArray dataOut;
       QDataStream dsOut(&dataOut, QIODevice::ReadWrite);
       dsOut << SIGN_UP << username << password << port;
       client->writeDatagram(dataOut.data(), dataOut.size(), QHostAddress::Broadcast, 45454);   //Pokemon_server端的port为45454

       if(server->waitForReadyRead(600))
           processPendingDatagrams();
       else
           QMessageBox::critical(this, "Sign Up failed", "Sign Up TimeOut");
    }
    else
        QMessageBox::critical(this, "No Input", "No Username or Password, please fill in");

}


void Login::on_pushButton_clicked() //退出
{
    this->~Login();
}
