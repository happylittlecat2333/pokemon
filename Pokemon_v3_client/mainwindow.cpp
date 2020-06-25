#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Login *login)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAutoFillBackground(true);

    ui->setupUi(this);

//    fight = new Fight;
//    fight->hide();

    allPkmAttr = login->getAllPkm();
    username = login->getUsername();
//    Users.clear();
    mode = 0;

    pkmNum = login->getPkmNum();

    user = new User;
    admin = new User;
    user->setUser(allPkmAttr,pkmNum);
    user->setUsername(username);
    admin->setUsername("admin");


    server = new QUdpSocket(this); //创建一个QUdpSocket类对象，负责接收
    client = new QUdpSocket(this);
    port = 45454+1;
    while(true){
       if(!(server->bind(port)))
           port++;
       else break;
    }
//    connect(server, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams())); //readyRead()信号是每当有新的数据来临时就被触发

//    button_group = new QButtonGroup(this);
//    button_group->addButton (ui->radioButton_1,0);
//    button_group->addButton (ui->radioButton_2,1);
//    button_group->addButton (ui->radioButton_3,2);

//    ui->radioButton_1->setChecked(1);
    ui->label_username->setText("My Pokemon");
//    ui->label_allAttr->setText(getPkmAttr(0));

    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);  //传递主机admin的所有pokemon信息
    dsOut << VIRTUAL_PKM << username << port;
    client->writeDatagram(data.data(), data.size(),QHostAddress::Broadcast, 45454);
    if(server->waitForReadyRead (500))//判断连接超时
    {
        qDebug() << "virtual";
        this->processPendingDatagrams ();
    }
    else qDebug() << "time out";


    setComboBoxValue(1);
    setComboBoxValue(0);
    ui->comboBox_gameType->addItem("Upgrade Game");
    ui->comboBox_gameType->addItem("Duel Game");
    ui->comboBox_gameType->setCurrentIndex(0);

    hideGiveOut();

//    connect(button_group, SIGNAL(buttonClicked(int)), this,SLOT(RecvPkmID(int)));

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
//    ui->label_allAttr->setText(getPkmAttr(num));
}


QString MainWindow::getPkmAttr(unsigned int num){   //根据不同模式，返回pokemon信息（QString类型）
    Pkm* tmp = NULL;
    if(mode == 0)
        tmp = this->user->getAllPkmAttr(num);
   else if(mode == 1)   //所有用户Users的信息
        tmp = this->Users[ui->listWidget_AllUser->currentRow()-1]->getAllPkmAttr(num);
    else if(mode == 2)  //online_user的信息
        tmp = this->online_user[ui->listWidget_AllUser->currentRow()-1]->getAllPkmAttr(num);
    else if(mode == 3)  //admin的信息
        tmp = this->admin->getAllPkmAttr(num);
    else if(mode == 4)
        tmp = this->user->getAllPkmAttr(num);


    QString all;
    all = all + "name:" + tmp->name;
    all = all + "\nlevel:" + QString::number(tmp->level);
    all = all + "\nexperience:" + QString::number(tmp->experience);
    all = all + "\nblood:" + QString::number(tmp->blood);
    all = all + "\nattack:" + QString::number(tmp->attack);
    all = all + "\ndefense:" + QString::number(tmp->defense);
    all = all + "\nspeed:" + QString::number(tmp->speed);
    all = all + "\nskill:" + ATTACKKIND[tmp->skill];
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
                this->Users.append(tmp_user);   //所有用户的信息
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
        else if(data_type == VIRTUAL_PKM) {
            qDebug() << "virtual pkm";
//            virtual_pkm.clear();
//            getVirtualPkm(dsIn);
            admin->deleteAllPkm();
            while(!dsIn.atEnd()){
                admin->setUser(dsIn);
                qDebug() << "set admin";
            }
//            setComboBoxValue(1);
//            setComboBoxValue(0);

        }


    }
}

void MainWindow::getVirtualPkm(QDataStream& dsIn) //废弃
{
    while(!dsIn.atEnd()){
        Pkm *tmp = new Pkm;
        dsIn >> tmp->name;
//        qDebug() << tmp->name;
        dsIn >> tmp->level;
//        qDebug() << tmp->level;
        dsIn >> tmp->experience;
        dsIn >> tmp->attack;
//        qDebug() << tmp->attack;
        dsIn >> tmp->blood;
        dsIn >> tmp->defense;
        dsIn >> tmp->speed;
        dsIn >> tmp->kind;
        dsIn >> tmp->skill;
//        qDebug() << "setUser";
        virtual_pkm.append(tmp);
    }
}

void MainWindow::setComboBoxValue(unsigned int Is_my_pkm)
{
    qDebug() << "seting combo box";
    if(Is_my_pkm){
        mode = 4;
        ui->comboBox_myPkm->clear();
        qDebug() << "user pkm num" << user->getPkmNum();
        for(int i=0; i<user->getPkmNum(); i++)
            ui->comboBox_myPkm->addItem(user->getPkmByIndex(i)->name);

        ui->comboBox_myPkm->setCurrentIndex(0);
        ui->label_myPkmAttr->setText(this->getPkmAttr(0));
        ui->label_myPic->setStyleSheet("#label_myPic{border-image:url(:/Pokemon_picture/"+
                                       this->user->getPkmByIndex(0)->name+".png);}");
    }
    else{
        mode = 3;
        ui->comboBox_opPkm->clear();
        qDebug() << "admin pkm num" << admin->getPkmNum();
        for(int i=0; i<admin->getPkmNum(); i++)
            ui->comboBox_opPkm->addItem(admin->getPkmByIndex(i)->name);
        ui->comboBox_opPkm->setCurrentIndex(0);
        ui->label_opPkmAttr->setText(this->getPkmAttr(0));
        ui->label_opPic->setStyleSheet("#label_opPic{border-image:url(:/Pokemon_picture/"+
                                       this->admin->getPkmByIndex(0)->name+".png);}");
    }

}

void MainWindow::updateUserPkm()
{
    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);
    dsOut << PKM_DATA << username << port;//发送类型，用户名以及端口号
    user->sendAllPkmAttr(dsOut);
    client->writeDatagram(data.data(), data.size(),QHostAddress::Broadcast, 45454);

}

void MainWindow::on_listWidget_AllUser_currentRowChanged(int currentRow)
{
    if(currentRow >= 1){
    if(mode==1 && currentRow<Users.length()) ui->label_username->setText (tr("%1's Pokemon").arg(this->Users[currentRow-1]->getUsername()));
    else if(mode==2 && currentRow<online_user.length()) ui->label_username->setText (tr("%1's Pokemon").arg(this->online_user[currentRow-1]->getUsername()));
//    ui->radioButton_1->setChecked (true);
//    ui->label_allAttr->setText (this->getPkmAttr(0));
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
//    ui->radioButton_1->setChecked(true);
//    ui->label_allAttr->setText(this->getPkmAttr(0));
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

void MainWindow::on_comboBox_myPkm_currentIndexChanged(int index)
{
    mode = 4;
    if(index < 0 || index >= user->getPkmNum()) return;
    ui->label_myPkmAttr->setText(this->getPkmAttr(index));
    ui->label_myPic->setStyleSheet("#label_myPic{border-image:url(:/Pokemon_picture/"+
                                   this->user->getPkmByIndex(index)->name+".png);}");

}


void MainWindow::on_comboBox_opPkm_currentIndexChanged(int index)
{

    mode = 3;
    if(index < 0 || index >= admin->getPkmNum()) return;
    ui->label_opPkmAttr->setText(this->getPkmAttr(index));
    ui->label_opPic->setStyleSheet("#label_opPic{border-image:url(:/Pokemon_picture/"+
                                   this->admin->getPkmByIndex(index)->name+".png);}");

}


void MainWindow::on_comboBox_gameType_currentIndexChanged(int index)
{
    if(index <0 || index >=2) return;
    this->game_type = index;
}

void MainWindow::on_pushButton_fight_clicked()
{
    unsigned int type = ui->comboBox_gameType->currentIndex();
    unsigned int userPkmIndex = ui->comboBox_myPkm->currentIndex();
    unsigned int opPkmIndex = ui->comboBox_opPkm->currentIndex();
//    fight = new Fight(0, type, user,userPkmIndex, admin, opPkmIndex);
//    fight = new Fight;
//    fight->show();
//    fight->fightBegin(type, user,userPkmIndex, admin, opPkmIndex);
//    fight->show();
//    setComboBoxValue(1);
//    setComboBoxValue(0);
    fightBegin(type, user,userPkmIndex, admin, opPkmIndex);
    qDebug() << "after: user pkm num:" << user->getPkmNum();
//    updateUserPkm();

}

void MainWindow::recResult()
{

    qDebug() << "after: user pkm num:" << user->getPkmNum();


}

void MainWindow::showGameType()
{
    ui->pushButton_fight->show();
    ui->comboBox_gameType->show();
    ui->label_gameType->show();
    ui->comboBox_myPkm->show();
    ui->comboBox_opPkm->show();
    ui->label_mySel->show();
    ui->label_opSel->show();
    ui->label_mySkill->clear();
    ui->label_opSkill->clear();
    ui->progressBar_myBlood->setValue(0);
    ui->progressBar_opBlood->setValue(0);
}

void MainWindow::hideGameType()
{
    ui->pushButton_fight->hide();
    ui->comboBox_gameType->hide();
    ui->label_gameType->hide();
    ui->comboBox_myPkm->hide();
    ui->comboBox_opPkm->hide();
    ui->label_mySel->hide();
    ui->label_opSel->hide();
}

void MainWindow::showGiveOut()
{
    ui->comboBox_giveOut->show();
    ui->label_giveOut->show();
    ui->pushButton_select->show();
}

void MainWindow::hideGiveOut()
{
    ui->comboBox_giveOut->hide();
    ui->label_giveOut->hide();
    ui->pushButton_select->hide();
}


void MainWindow::fightBegin(unsigned int game_type, User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex)
{

//    ui->label_giveOut->hide();
//    ui->comboBox_giveOut->hide();
//    ui->pushButton_select->hide();

    hideGameType();
    unsigned int tmp_level = user->getAllPkmAttr(userPkmIndex)->level;
    qDebug() << "Game Start";
//    Pkm* myPkm = user->getPkmByIndex(userPkmIndex);
//    Pkm* opPkm = opponent->getPkmByIndex(opPkmIndex);

//    ui->label_myPkmAttr->setText(user->getPkmAttrByIndex(userPkmIndex));
//    ui->label_opPkmAttr->setText(opponent->getPkmAttrByIndex(opPkmIndex));
//    ui->label_myPkmPic->setStyleSheet("#label_myPkmPic{border-image:url(:/Pokemon_picture/"+
//                                   user->getAllPkmAttr(userPkmIndex)->name+".png);}");
//    ui->label_opPkmPic->setStyleSheet("#label_opPkmPic{border-image:url(:/Pokemon_picture/"+
//                                   opponent->getAllPkmAttr(opPkmIndex)->name+".png);}");
    bool IsWin = false;


    if(game_type == 0){
        ui->label_gameType->setText("Upgrade Game");
        IsWin = fightProgress(user, userPkmIndex, opponent, opPkmIndex);
        if(IsWin){
            user->addExperience(userPkmIndex, opponent->getAllPkmAttr(opPkmIndex)->level);
            qDebug() << opponent->getAllPkmAttr(opPkmIndex)->level;
            if(tmp_level != user->getAllPkmAttr(userPkmIndex)->level)
                QMessageBox::information (this,"Pokemon Upgrade", "Level Up : " + QString::number(user->getAllPkmAttr(userPkmIndex)->level),"OK");
        }
        else
            QMessageBox::information (this,"Game Over", "return to menu","OK");
//        hideGiveOut();

        setComboBoxValue(1);
        setComboBoxValue(0);
        showGameType();

    }
    else if(game_type == 1){
        ui->label_gameType->setText("Duel Game");
        IsWin = fightProgress(user, userPkmIndex, opponent, opPkmIndex);
        if(IsWin){
            user->addExperience(userPkmIndex, opponent->getAllPkmAttr(opPkmIndex)->level);
            user->appendPkm(opponent->getAllPkmAttr(opPkmIndex));
            qDebug() << "append Pkm success";
            qDebug() << user->getPkmNum();
            QMessageBox::information (this,"Pokemon Get", "name" + user->getAllPkmAttr(user->getPkmNum())->name,"OK");
            showGameType();
        }
        else{
            showGiveOut();
            QMessageBox::information (this,"Pokemon Loss", "choose one pokemon to give out","OK");
            giveOutPkm(user);
        }
    }
//    showGameType();
}

bool MainWindow::fightProgress(User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex)
{
    Pkm* myPkm = user->getPkmByIndex(userPkmIndex);
    Pkm* opPkm = opponent->getPkmByIndex(opPkmIndex);

    int myCurrentBlood = myPkm->blood;
    int opCurrentBlood = opPkm->blood;

    qDebug() << "myCurrentBlood" << myCurrentBlood;
    ui->progressBar_myBlood->setRange(0, myCurrentBlood);
    ui->progressBar_opBlood->setRange(0, opCurrentBlood);
    ui->progressBar_myBlood->setValue(myCurrentBlood);
    ui->progressBar_opBlood->setValue(opCurrentBlood);

    ui->label_myPkmAttr->setText("My Blood: " + QString::number(myCurrentBlood) + " / " + QString::number(myPkm->blood));
    ui->label_opPkmAttr->setText("Opponent Blood: " + QString::number(opCurrentBlood) + " / " + QString::number(opPkm->blood));


    int Is_over = 0, User_win=0;
    while(!Is_over){
        int mySpeed = myPkm->speed;
        int opSpeed = myPkm->speed;

        int my_attack_times=1, op_attack_times=1;
        if(mySpeed >= opSpeed)  //允许speed快的，多次攻击
            my_attack_times = mySpeed / opSpeed;
        else
            op_attack_times = opSpeed / mySpeed;

        qsrand (QTime::currentTime ().msec () * (myPkm->experience+214));
        unsigned int p = (qrand()+5) % 10 + 1; //p->1~10
        while(my_attack_times){
            my_attack_times--;
            qDebug() << "my attack";

            ui->label_mySkill->clear();


            delay(2);
            p = ((p+1)*(p+1)) % 10 + 1;
            int damage = user->attackOpponent(userPkmIndex);
            if(damage == -1){ //出技能
            ui->label_mySkill->setText(ATTACKKIND[myPkm->skill] + "!!!");
            if(myPkm->kind != opPkm->kind)
                if(myPkm->skill != defense_attack)
                    damage = myPkm->attack * 1.3;
                else
                    myCurrentBlood += myPkm->blood * 0.2;
            else
                damage = myPkm->attack * 0.8;
            }
            else ui->label_mySkill->setText("NORMAL ATTACK");
            if(p <= 2){  //0.2暴击
                damage = damage * 1.2;
                ui->label_mySkill->setText("CRIT ATTACK!!!");

            }
            if(p == 8){ //0.1闪避
                damage = 0;
                ui->label_mySkill->setText("ATTACK MISS!!!");

            }
            int recDamage = damage - opPkm->defense;
            if(recDamage >= 0)
                opCurrentBlood -= recDamage;
            if(opCurrentBlood <= 0){
                User_win = 1;
                Is_over = 1;
                my_attack_times = op_attack_times = 0;
            }
            ui->progressBar_opBlood->setValue(opCurrentBlood);
            qDebug() << "opCurrentBlood" << opCurrentBlood;
            ui->label_myPkmAttr->setText("My Blood: " + QString::number(myCurrentBlood) + " / " + QString::number(myPkm->blood));
            ui->label_opPkmAttr->setText("Opponent Blood: " + QString::number(opCurrentBlood) + " / " + QString::number(opPkm->blood));


        }

       while(op_attack_times){
            op_attack_times--;
            qDebug() << "opponent attack";


            ui->label_opSkill->clear();
            delay(2);

//            unsigned int p = (qrand() + 5) % 10 + 1; //p->1~10
            p = ((p+1)*(p+1)) % 10 + 1;
            int damage = opponent->attackOpponent(opPkmIndex);
            if(damage == -1){ //出技能
                 ui->label_opSkill->setText(ATTACKKIND[opPkm->skill] + "!!!");
                if(myPkm->kind != opPkm->kind){
                    if(opPkm->skill != defense_attack)
                        damage = opPkm->attack * 1.3;
                    else
                        opCurrentBlood += opPkm->blood * 0.2;
                }
                else
                    damage = opPkm->attack * 0.8;
            }
            else ui->label_opSkill->setText("NORMAL ATTACK");
            if(p <= 2){  //0.2暴击
                damage = damage * 1.2;
                ui->label_opSkill->setText("CRIT ATTACK!!!");
            }
            if(p == 8) {//0.1闪避
                damage = 0;
                ui->label_opSkill->setText("ATTACK MISS!!!");
            }
            int recDamage = damage - myPkm->defense;
            if(recDamage >= 0)
                myCurrentBlood -= recDamage;
            if(myCurrentBlood <= 0){
                User_win = 0;
                Is_over = 1;
                my_attack_times = op_attack_times = 0;
            }
            ui->progressBar_myBlood->setValue(myCurrentBlood);
            qDebug() << "myCurrentBlood" << myCurrentBlood;
            ui->label_myPkmAttr->setText("My Blood: " + QString::number(myCurrentBlood) + " / " + QString::number(myPkm->blood));
            ui->label_opPkmAttr->setText("Opponent Blood: " + QString::number(opCurrentBlood) + " / " + QString::number(opPkm->blood));

        }
    }

    if(User_win == 1){
        QMessageBox::information (this,"Game Over","You Win!!!","OK");
    }
    else
        QMessageBox::information (this,"Game Over","You Lose!!!","OK");
    return User_win;



}


void MainWindow::giveOutPkm(User *user)
{
//    ui->label_giveOut->show();
//    ui->pushButton_select->show();
    int pkmNum = user->getPkmNum();
    ui->comboBox_giveOut->clear();
    if(pkmNum >= 3){
        unsigned int p = qrand() % pkmNum;
        for(int i=0;i<3;i++){
            ui->comboBox_giveOut->addItem(user->getAllPkmAttr(p)->name);
            p = (p + 1) % pkmNum;
        }
    }
    else
        for(int i=0;i<pkmNum;i++)
            ui->comboBox_giveOut->addItem(user->getAllPkmAttr(i)->name);
//    ui->comboBox_giveOut->show();
    ui->comboBox_giveOut->setCurrentIndex(0);
}





void MainWindow::delay(int time)
{
    QTime dieTime= QTime::currentTime().addSecs(time);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::on_pushButton_select_clicked()
{
    unsigned int pkm_index = ui->comboBox_giveOut->currentIndex();
    user->popPkmByIndex(pkm_index);
    QMessageBox::critical(this, "Pop pokemon", "pop pokemon complete", "OK");
    updateUserPkm();
    setComboBoxValue(1);
    setComboBoxValue(0);
    hideGiveOut();
    showGameType();
}

void MainWindow::on_pushButton_clicked()
{
    user->addExperience(ui->comboBox_myPkm->currentIndex(), 5);
    setComboBoxValue(0);
    setComboBoxValue(1);
}