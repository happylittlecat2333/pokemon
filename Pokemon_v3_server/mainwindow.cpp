#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAutoFillBackground(true);

    ui->setupUi(this);
    max_id = 1;
    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QSQLITE");
//    db->setHostName("localhost");
    db->setDatabaseName("pokemon.db");
//    db->setUserName("xue");
//    db->setPassword("123");
    if(!db->open()){
        qDebug() << "Open pokemon_sql error!!";
    }

    QSqlQuery query;
//         query.exec("create table student (id int primary key, namevchar)");
        query.exec("drop table users");
        query.exec("drop table pokemon");
        query.exec("create table users (username vchar primary key, password vchar)");
        query.exec("CREATE TABLE pokemon (  \
                     id     int,    \
                     user	vchar , \
                     name	vchar,  \
                     level	int,    \
                     experience	int,    \
                     attack	int,    \
                     blood	int,    \
                     defense int,   \
                     speed	int,    \
                     kind	int,    \
                     skill	int)");

//       query.exec("insert into pokemon values (0,'xue2' ,'pokemon-test',0,0,0,0,0,0,0,0)");
        query.exec("insert into users ('admin', 'admin');");


    server = new QUdpSocket(this);
    client = new QUdpSocket(this);
    server->bind(45454, QUdpSocket::ShareAddress);
    connect(server, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

    adminPkmNum = 0;
    user = new User;

}

MainWindow::~MainWindow()
{

    delete ui;
    delete pokemon;
    delete server;
    delete client;
    delete db;
}




void MainWindow::processPendingDatagrams()
{
    while(server->hasPendingDatagrams()){
        QByteArray datagIn;    //存放接收的数据
        datagIn.resize(server->pendingDatagramSize()); //pendingDatagramSize为返回第一个在等待读取报文的size，让dataIn的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        server->readDatagram(datagIn.data(), datagIn.size());  //接收数据报，将其存放到dataIn中

        QDataStream dsIn(&datagIn, QIODevice::ReadWrite);
        QString username;
        QString password;
        unsigned int port;
        unsigned int log_type;

        QByteArray dataOut;
        QDataStream dsOut(&dataOut,QIODevice::ReadWrite);
        QSqlQuery query;

        dsIn >> log_type >> username;

        if(log_type == SIGN_IN || log_type == SIGN_UP){
            dsIn >> password >> port;
        }
        if(log_type == SIGN_UP){
            query.exec("select * from users where username=\"" + username + "\";");
            if(query.next()) dsOut << NAME_EXIST;
            else{
                query.exec ("insert into users values(\""+username+"\",\""+password+"\");");
                qDebug() << "SIGN_UP" << username << password;
                createPokemon(username, 1);
                dsOut << SIGN_UP_SUCCESS;
                sendPekemon(dsOut, username);
                appendUserFromSql(username);
            }
            client->writeDatagram(dataOut.data(), dataOut.size(), QHostAddress::Broadcast, port);
            qDebug() << "client";
        }
        else if(log_type == SIGN_IN) {
            query.exec("select * from users where username=\"" + username + "\";");
            if(!query.next()) dsOut << USER_NONE;
            else{
                QString my_pwd = query.value(1).toString();
                if(my_pwd != password)
                    dsOut << PWD_ERROR;
                else{
                    dsOut << SIGN_IN_SUCESS;
                    sendPekemon(dsOut, username);
                    appendUserFromSql(username);
                }
            }
            client->writeDatagram(dataOut.data(), dataOut.size(), QHostAddress::Broadcast, port);
        }
        else if(log_type == SIGN_OUT){
            dsIn >> port;
            int index;
            for(index=0;index<online_user.length();index++){
                if(online_user[index]->getUsername() == username)
                    break;
            }
            online_user.removeAt(index);
            qDebug() << username << " Log out" << "online length:" << online_user.length();
        }
        else if(log_type == ALL_USER){
            dsIn >> port;
            sendAllUser(port);
        }
        else if(log_type == ONLINE_USER){
            dsIn >> port;
            sendOnlineUser(port);
        }
        else if(log_type == VIRTUAL_PKM){
            dsIn >> port;
            dsOut << VIRTUAL_PKM;
            qDebug() << "send admin pkm";
            if(adminPkmNum <= 15)
                for(int i=0; i<6;i++){
                     createPokemon("admin",i);
                     adminPkmNum+=3;
                }
            sendPekemon(dsOut, "admin");
            client->writeDatagram(dataOut.data(), dataOut.size(), QHostAddress::Broadcast, port);
        }
        else if(log_type == PKM_DATA){
            dsIn >> port;
            qDebug() << "update user pkm";
            updateUserPkm(dsIn, username);
        }
    }
}

void MainWindow::appendUserFromSql(QString username)    //在线用户增加，新增一个online_user
{
    User* tmp_user = new User;
    tmp_user->setUsername(username);
    QSqlQuery query;
    query.exec ("select * from pokemon where user=\""+username+"\";");
    qDebug() << "append online user";
    while(query.next())
    {
       Pkm* tmp_pkm = new Pkm;
       tmp_pkm->name = query.value(2).toString();
       qDebug() << tmp_pkm->name;

       tmp_pkm->level = query.value(3).toUInt();
       tmp_pkm->experience = query.value(4).toUInt();
       tmp_pkm->attack = query.value(5).toUInt();
       tmp_pkm->blood = query.value(6).toUInt();
       tmp_pkm->defense = query.value(7).toUInt();
       tmp_pkm->speed = query.value(8).toUInt();
       tmp_pkm->kind = query.value(9).toUInt();
       tmp_pkm->skill = query.value(10).toUInt();
       tmp_user->appendPkm(tmp_pkm);
    }
    online_user.append(tmp_user);
    qDebug() << tmp_user->getUsername();
    qDebug() << "online user count:" << online_user.length();

}

void MainWindow::sendPekemon(QDataStream& dsOut, QString user)  //发送user的所有pokemon的信息
{

    QSqlQuery query;
    query.exec ("select * from pokemon where user=\""+user+"\";");
//    qDebug() << "send";
    while(query.next ())
    {
       dsOut << query.value(2).toString();  //pokemon name
//       qDebug() << query.value(2).toString();
       for(int i=3; i<=10; i++)
           dsOut << query.value(i).toUInt();    //其他pokemon属性

    }
//    qDebug() << "send over";
}

void MainWindow::sendAllUser(unsigned int port) //从数据库返回所有用户信息（用户名，所有精灵）
{
    QByteArray dataOut;
    QDataStream Out(&dataOut,QIODevice::ReadWrite);
    QSqlQuery query;
    Out << ALL_USER;
    query.exec("select * from users");
    while(query.next()) {
        Out << query.value(0).toString();   //先发用户名
//        qDebug() << query.value(0).toString();
        sendPekemon(Out, query.value(0).toString());    //再发所有精灵
    }
    client->writeDatagram(dataOut.data(), dataOut.size(), QHostAddress::Broadcast, port);
}

void MainWindow::sendOnlineUser(unsigned int port)  //从online_user中返回数据
{
    QByteArray dataOut;
    QDataStream Out(&dataOut,QIODevice::ReadWrite);
    QSqlQuery query;
    Out << ONLINE_USER;
    qDebug() << "send online user";
    qDebug() << "online user count:" << online_user.length();
    for(int i=0; i<online_user.length(); i++){
        online_user[i]->sendAllPkmAttr(Out);
    }
    client->writeDatagram(dataOut.data(), dataOut.size(), QHostAddress::Broadcast, port);
}


void MainWindow::setSql(QString user, Pkm* pokemon) //设置pokemon数据库的内容
{
    QSqlQuery query;
    qDebug() << "set";
    QString sqlString=tr("insert into pokemon values(%1,'%2','%3',%4,%5,%6,%7,%8,%9,%10,%11);").
            arg(max_id).arg (user).arg (pokemon->name).arg (pokemon->level).arg (pokemon->experience).
            arg (pokemon->attack).arg (pokemon->blood).arg (pokemon->defense).arg (pokemon->speed).
            arg (pokemon->kind).arg (pokemon->skill);
    query.exec (sqlString);
    max_id++;
    qDebug() << "set over";
}


void MainWindow::createPokemon(QString username,unsigned int create_level)  //生成PKM，写入pokemon数据库
{
    qsrand(QTime(0,0,0,0).msecsTo((QTime::currentTime()))); //生成随机种子

    for(int i=0; i<3; i++){ //每人3只精灵
        qDebug() << "create " << i << "pokemon";
        unsigned int kind = qrand() % 4;
        SKILL skill =   SKILL((qrand()+2) % 4);
        switch (kind) {
        case HIGH_ATTACK:
            pokemon = new high_attack(skill);
            break;
        case HIGH_BLOOD:
            pokemon = new high_blood(skill);
            break;
        case HIGH_DEFENSE:
            pokemon = new high_defense(skill);
            break;
        case HIGH_SPEED:
            pokemon = new high_speed(skill);
            break;
        }
        if(username == "admin"){    //主机admin返回所有等级的精灵（1-15）
            pokemon->setLevel(create_level*3+i+1);
        }
        Pkm* attrAll = pokemon->getAttr();  //获得精灵的参数，方便写入sql
        setSql(username, attrAll);
        delete attrAll;
        delete pokemon;
        pokemon = NULL;
        qDebug() << "create over";
     }
}

void MainWindow::updateUserPkm(QDataStream& dsIn, QString username) //更新用户在数据库的所有pokemon信息
{
    QSqlQuery query;
    qDebug() << "update";
    query.exec("delete from pokemon where user="+username); //先清除旧数据
    QString user_name;
    dsIn >> user_name;
    user->setUsername(user_name);
    user->deleteAllPkm();
    qDebug() << "updating " << user_name;
    while(!dsIn.atEnd())    //把传来的数据dsIn赋值到user中（pokemon信息）
        user->setUser(dsIn);
    for(int i=0;i < user->getPkmNum();i++){     //通过user中的信息，写入pokemon数据库
        Pkm* pokemon = user->getPkmByIndex(i);
        QString sqlString=tr("insert into pokemon values(%1,'%2','%3',%4,%5,%6,%7,%8,%9,%10,%11);").
        arg(max_id).arg (user->getUsername()).arg (pokemon->name).arg (pokemon->level).arg (pokemon->experience).
        arg (pokemon->attack).arg (pokemon->blood).arg (pokemon->defense).arg (pokemon->speed).
        arg (pokemon->kind).arg (pokemon->skill);
        query.exec (sqlString);
        max_id++;
    }
    qDebug() << "set over";
}

void MainWindow::on_pushButton_2_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery("select * from pokemon");
        QTableView *view = new QTableView;
        view->setModel(model);
        view->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery("select * from users");
        QTableView *view = new QTableView;
        view->setModel(model);
        view->show();
}

void MainWindow::on_pushButton_clicked()
{
    this->~MainWindow();
}
