#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <chrono>
#include <random>

MainWindow::MainWindow(QWidget *parent, Login *login)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAutoFillBackground(true);

    ui->setupUi(this);

//    fight = new Fight;
//    fight->hide();

    allPkmAttr = login->getAllPkm();    //从登录界面传递pokemon数据到此界面
    username = login->getUsername();

    mode = 0;   //初始化，显示用户信息

    pkmNum = login->getPkmNum();    //用户的pokemon个数

    user = new User;
    admin = new User;   //主机信息
    user->setUser(allPkmAttr,pkmNum);   //加载所有pokemon到用户中
    user->setUsername(username);
    user->win = login->win;
    user->lose = login->lose;
    admin->setUsername("admin");

    server = new QUdpSocket(this); //创建一个QUdpSocket类对象，负责接收
    client = new QUdpSocket(this);
    port = 45454+1;
    while(true){
       if(!(server->bind(port)))
           port++;
       else break;
    }


    QByteArray data;
    QDataStream dsOut(&data, QIODevice::ReadWrite);  //传递主机admin的所有pokemon信息
    dsOut << VIRTUAL_PKM << username << port;
    client->writeDatagram(data.data(), data.size(),QHostAddress::Broadcast, 45454);
    if(server->waitForReadyRead (500))//判断连接超时
        this->processPendingDatagrams ();
    else qDebug() << "time out";

    ui->label_username->setText("My Pokemon");  //主界面初始化
    setComboBoxValue(1);
    setComboBoxValue(0);
    ui->comboBox_gameType->addItem("Upgrade Game");
    ui->comboBox_gameType->addItem("Duel Game");
    ui->comboBox_gameType->setCurrentIndex(0);
    ui->progressBar_myBlood->hide();
    ui->progressBar_opBlood->hide();
    hideGiveOut();
}


MainWindow::~MainWindow()   //退出
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


QString MainWindow::getPkmAttr(unsigned int num){   //根据不同mode模式，返回pokemon信息，用于设置Text中的内容（QString类型）
    Pkm* tmp = NULL;
    if(mode == 0)       //初始化
        tmp = this->user->getPkmByIndex(num);
   else if(mode == 1)   //所有用户Users的信息
        tmp = this->Users[ui->listWidget_AllUser->currentRow()-1]->getPkmByIndex(num);
    else if(mode == 2)  //online_user的信息
        tmp = this->online_user[ui->listWidget_AllUser->currentRow()-1]->getPkmByIndex(num);
    else if(mode == 3)  //admin的信息
        tmp = this->admin->getPkmByIndex(num);
    else if(mode == 4)  //用户的信息
        tmp = this->user->getPkmByIndex(num);

    QString all;
    all = all + "name: " + tmp->name;
    all = all + "\nlevel: " + QString::number(tmp->level);
    all = all + "\nexperience: " + QString::number(tmp->experience);
    all = all + "\nblood: " + QString::number(tmp->blood);
    all = all + "\nattack: " + QString::number(tmp->attack);
    all = all + "\ndefense: " + QString::number(tmp->defense);
    all = all + "\nspeed: " + QString::number(tmp->speed);
    all = all + "\nskill: " + ATTACKKIND[tmp->skill];
    return all;
}


void MainWindow::processPendingDatagrams()  //处理传来的数据
{
    while(server->hasPendingDatagrams()){
        QByteArray datagIn;    //存放接收的数据
        datagIn.resize(server->pendingDatagramSize()); //pendingDatagramSize为返回第一个在等待读取报文的size，让dataIn的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        server->readDatagram(datagIn.data(), datagIn.size());  //接收数据报，将其存放到dataIn中

        QDataStream dsIn(&datagIn, QIODevice::ReadWrite);
        QString username;
        QString password;
        unsigned int data_type;

        dsIn >> data_type;

        if(data_type == ALL_USER){
            Users.clear();
            while(!dsIn.atEnd()) {
                User *tmp_user  = new User;
                dsIn >> username;
                dsIn >> tmp_user->win;
                dsIn >> tmp_user->lose;
                tmp_user->setUsername(username);
                unsigned int pokemon_num = 0;
                dsIn >> pokemon_num;
                for(unsigned int i=0;i<pokemon_num;i++){ //加载pokemon
                    tmp_user->setUser(dsIn);
                }
                this->Users.append(tmp_user);   //所有用户的信息
            }
       }
       else if(data_type == ONLINE_USER){
            online_user.clear();
            while(!dsIn.atEnd()) {
                User *tmp_user  = new User;
                dsIn >> username;
                dsIn >> tmp_user->win;
                dsIn >> tmp_user->lose;
                tmp_user->setUsername(username);
                unsigned int pokemon_num = 0;
                dsIn >> pokemon_num;
                for(unsigned int i=0;i<pokemon_num;i++){ //加载pokemon
                    tmp_user->setUser(dsIn);
                }
                this->online_user.append(tmp_user); //online users
            }
        }
        else if(data_type == VIRTUAL_PKM) {
            admin->deleteAllPkm();
            while(!dsIn.atEnd()){
                admin->setUser(dsIn);   //主机虚拟pokemon
            }
        }
    }
}


void MainWindow::setComboBoxValue(unsigned int Is_my_pkm)   //设置用户或admin的所有信息（combobox、label）
{
    if(Is_my_pkm){  //用户
        mode = 4;
        ui->comboBox_myPkm->clear();
        for(int i=0; i<user->getPkmNum(); i++)  //我方所有pokemon
            ui->comboBox_myPkm->addItem(user->getPkmByIndex(i)->name);

        ui->comboBox_myPkm->setCurrentIndex(0);
        ui->label_myPkmAttr->setText(this->getPkmAttr(0));  //返回pokemon信息（QString类型）
        ui->label_myPic->setStyleSheet("#label_myPic{border-image:url(:/Pokemon_picture/"+
                                       this->user->getPkmByIndex(0)->name+".png);}");
    }
    else{   //主机admin
        mode = 3;
        ui->comboBox_opPkm->clear();
        for(int i=0; i<admin->getPkmNum(); i++) //admin所有pokemon
            ui->comboBox_opPkm->addItem(admin->getPkmByIndex(i)->name);

        ui->comboBox_opPkm->setCurrentIndex(0);
        ui->label_opPkmAttr->setText(this->getPkmAttr(0));
        ui->label_opPic->setStyleSheet("#label_opPic{border-image:url(:/Pokemon_picture/"+
                                       this->admin->getPkmByIndex(0)->name+".png);}");
    }
}

void MainWindow::updateUserPkm()    //在server端数据库中，更新user自己的pokemon信息
{
    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);
    dsOut << PKM_DATA << username << port;//发送类型，用户名以及端口号
    user->sendAllPkmAttr(dsOut);
    client->writeDatagram(data.data(), data.size(),QHostAddress::Broadcast, 45454);
}


void MainWindow::on_pushButton_LogOut_clicked()     //登出
{
    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);
    dsOut << SIGN_OUT << username << port;//发送类型，用户名以及端口号
    client->writeDatagram(data.data(), data.size(),QHostAddress::Broadcast, 45454);
    this->~MainWindow();
}

void MainWindow::on_pushButton_allUser_clicked()    //根据所有用户Users，设置listWidget
{
    mode = 1;
    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);
    dsOut << ALL_USER << username << port;//发送类型，用户名以及端口号
    client->writeDatagram(data.data(), data.size(),QHostAddress::Broadcast, 45454);

    if(server->waitForReadyRead (5000))//判断连接超时
    {
        this->processPendingDatagrams ();
        ui->listWidget_AllUser->clear ();
        ui->listWidget_AllUser->addItem ("Username: "); //重新设置所有用户的列表
        ui->label_allUser->setText("All User");

        for(int i=0;i<Users.length();i++)
            ui->listWidget_AllUser->addItem (tr("%1").
                                          arg (this->Users[i]->getUsername()));
        ui->listWidget_AllUser->setCurrentRow (1);
    }
    else
         QMessageBox::critical (this,"Get Data Failed","Connect Failed","OK");
}


void MainWindow::on_pushButton_onlineUser_clicked() //根据所有在线用户online_user，设置listWidget
{
    mode = 2;
    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);
    dsOut << ONLINE_USER << username << port;//发送类型，用户名以及端口号
    client->writeDatagram(data.data(), data.size(),QHostAddress::Broadcast, 45454);

    if(server->waitForReadyRead (5000))//判断连接超时
    {
        this->processPendingDatagrams ();
        ui->listWidget_AllUser->clear ();
        ui->listWidget_AllUser->addItem ("Username:");//重新设置在线用户的列表
        ui->label_allUser->setText("Online User");

        for(int i=0;i<online_user.length();i++)
            ui->listWidget_AllUser->addItem (tr("%1").
                                          arg (this->online_user[i]->getUsername()));
        ui->listWidget_AllUser->setCurrentRow (1);
    }
    else
         QMessageBox::critical (this,"Get Data Failed","Connect Failed","OK");

}


void MainWindow::on_pushButton_fight_clicked()  //进入比赛界面，开始比赛
{
    unsigned int type = ui->comboBox_gameType->currentIndex();
    unsigned int userPkmIndex = ui->comboBox_myPkm->currentIndex();
    unsigned int opPkmIndex = ui->comboBox_opPkm->currentIndex();

    fightBegin(type, user,userPkmIndex, admin, opPkmIndex);
    updateUserPkm();    //比赛完更新用户数据
}


void MainWindow::on_comboBox_myPkm_currentIndexChanged(int index)   //更新显示用户user的pokemon信息（label）
{
    mode = 4;
    if(index < 0 || index >= user->getPkmNum()) return;
    ui->label_myPkmAttr->setText(this->getPkmAttr(index));
    ui->label_myPic->setStyleSheet("#label_myPic{border-image:url(:/Pokemon_picture/"+
                                   this->user->getPkmByIndex(index)->name+".png);}");
}


void MainWindow::on_comboBox_opPkm_currentIndexChanged(int index)   //更新显示主机admin的pokemon信息（label）
{
    mode = 3;
    if(index < 0 || index >= admin->getPkmNum()) return;
    ui->label_opPkmAttr->setText(this->getPkmAttr(index));
    ui->label_opPic->setStyleSheet("#label_opPic{border-image:url(:/Pokemon_picture/"+
                                   this->admin->getPkmByIndex(index)->name+".png);}");
}


void MainWindow::on_comboBox_gameType_currentIndexChanged(int index)    //选择游戏类型
{
    if(index <0 || index >=2) return;
    this->game_type = index;
}


void MainWindow::on_listWidget_AllUser_currentRowChanged(int currentRow)  //在所有用户中选中其中一个用户，展示用户信息
{
    if(currentRow >= 1){
        if(mode==1 && currentRow<=Users.length()){  //all user
            float win = this->Users[currentRow-1]->win;
            float lose = this->Users[currentRow-1]->lose;
            float win_rate = win / (win + lose);
            ui->label_user_winRate->setText (tr("win: %1\nloss: %2\nwin_rate: %3")
                                             .arg(win).arg(lose).arg(win_rate));
            ui->label_user_badget->setText(this->Users[currentRow-1]->getUserBadget());
        }
        else if(mode==2 && currentRow<=online_user.length()){   //online user
            float win = this->online_user[currentRow-1]->win;
            float lose = this->online_user[currentRow-1]->lose;
            float win_rate = win / (win + lose);
            ui->label_user_winRate->setText (tr("win: %1\nloss: %2\nwin_rate: %3")
                                             .arg(win).arg(lose).arg(win_rate));
            ui->label_user_badget->setText(this->online_user[currentRow-1]->getUserBadget());
        }
    }
}


void MainWindow::showGameType() //展示主界面
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
    ui->progressBar_myBlood->hide();
    ui->progressBar_opBlood->hide();
    ui->label_gameType->setText("game type: ");
}

void MainWindow::hideGameType() //进入对战模式，切换对战界面
{
    ui->pushButton_fight->hide();
    ui->comboBox_gameType->hide();
    ui->label_gameType->hide();
    ui->comboBox_myPkm->hide();
    ui->comboBox_opPkm->hide();
    ui->label_mySel->hide();
    ui->label_opSel->hide();
    ui->progressBar_myBlood->show();
    ui->progressBar_opBlood->show();
}

void MainWindow::showGiveOut()  //决斗赛中，展示选择要送出的pokemon
{
    ui->comboBox_giveOut->show();
    ui->label_giveOut->show();
    ui->pushButton_select->show();
    ui->comboBox_giveOut->setCurrentIndex(0);
}

void MainWindow::hideGiveOut()  //隐藏决斗赛中，送出pokemon界面
{
    ui->comboBox_giveOut->hide();
    ui->label_giveOut->hide();
    ui->pushButton_select->hide();
}




void MainWindow::fightBegin(unsigned int game_type, User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex) //开始比赛
{
    hideGameType();
    unsigned int tmp_level = user->getPkmByIndex(userPkmIndex)->level;
    bool IsWin = false;

    if(game_type == 0){         //升级赛
        ui->label_gameType->setText("Upgrade Game");
        IsWin = fightProgress(user, userPkmIndex, opponent, opPkmIndex);    //比赛过程，返回比赛结果
        if(IsWin){
            user->win++;
            user->addExperience(userPkmIndex, opponent->getPkmByIndex(opPkmIndex)->level);  //用户pokemon增加经验值
            if(tmp_level != user->getPkmByIndex(userPkmIndex)->level)   //如果pokemon升级，提示
                QMessageBox::information (this,"Pokemon Upgrade", "Level Up : " + QString::number(user->getPkmByIndex(userPkmIndex)->level),"OK");
        }
        else{
            user->lose++;
            QMessageBox::information (this,"Game Over", "return to menu","OK");
        }

        setComboBoxValue(1);    //重新设置用户或admin的所有pokemon信息（更新所有label）
        setComboBoxValue(0);
        showGameType();     //进入主界面

    }
    else if(game_type == 1){    //决斗赛
        ui->label_gameType->setText("Duel Game");
        IsWin = fightProgress(user, userPkmIndex, opponent, opPkmIndex);    //比赛过程，返回比赛结果
        if(IsWin){
            user->win++;
            user->addExperience(userPkmIndex, opponent->getPkmByIndex(opPkmIndex)->level);  //用户pokemon增加经验值
            user->appendPkm(opponent->getPkmByIndex(opPkmIndex));   //获得对方的pokemon，提示获得的pokemon
            QMessageBox::information (this,"Pokemon Get", "Get Pokemon: " + user->getPkmByIndex(user->getPkmNum()-1)->name,"OK");
            showGameType();
            setComboBoxValue(1);    //重新设置用户或admin的所有pokemon信息（更新所有label）
            setComboBoxValue(0);
        }
        else{
            user->lose++;
            showGiveOut();  //展示选择要送出的pokemon
            QMessageBox::information (this,"Pokemon Loss", "choose one pokemon to give out","OK");
            giveOutPkm(user);   //送出一个pokemon
        }
    }
}

bool MainWindow::fightProgress(User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex)
{
    Pkm* myPkm = user->getPkmByIndex(userPkmIndex);
    Pkm* opPkm = opponent->getPkmByIndex(opPkmIndex);

    int myCurrentBlood = myPkm->blood;
    int opCurrentBlood = opPkm->blood;

    ui->progressBar_myBlood->setRange(0, myCurrentBlood);   //设置血条
    ui->progressBar_opBlood->setRange(0, opCurrentBlood);
    ui->progressBar_myBlood->setValue(myCurrentBlood);
    ui->progressBar_opBlood->setValue(opCurrentBlood);

    ui->label_myPkmAttr->setText("My Blood: " + QString::number(myCurrentBlood) + " / " + QString::number(myPkm->blood));
    ui->label_opPkmAttr->setText("Opponent Blood: " + QString::number(opCurrentBlood) + " / " + QString::number(opPkm->blood));

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rand_num(seed);	 // 大随机数

    int Is_over = 0, User_win=0;    //是否比赛结束，哪方获胜

    while(!Is_over){
        int mySpeed = myPkm->speed;
        int opSpeed = myPkm->speed;

        int my_attack_times=1, op_attack_times=1;
        if(mySpeed >= opSpeed)  //允许speed快的，多次攻击
            my_attack_times = mySpeed / opSpeed;
        else
            op_attack_times = opSpeed / mySpeed;

        unsigned int p = rand_num() % 10 + 1; //p的范围为1~10

        while(my_attack_times){ //我方攻击次数
            my_attack_times--;

            ui->label_mySkill->clear();

            delay(2);   //模拟攻击间隔
            p = rand_num() % 10 + 1;
            int damage = user->attackOpponent(userPkmIndex);
            if(damage == -1){   //使出技能
                ui->label_mySkill->setText(ATTACKKIND[myPkm->skill] + "!!!");   //展示使出的技能
                if(myPkm->kind != opPkm->kind)
                    if(myPkm->skill != defense_attack)
                        damage = myPkm->attack * 1.3;   //对不同类型的pokemon使出技能伤害高
                    else
                        myCurrentBlood += myPkm->blood * 0.2;   //defense attack加自己血量
                else
                    damage = myPkm->attack * 0.8;   //对同类型的pokemon使出伤害低
            }
            else ui->label_mySkill->setText("NORMAL ATTACK");

            if(p <= 2){  //0.2的几率暴击
                damage = damage * 1.2;
                ui->label_mySkill->setText("CRIT ATTACK!!!");
            }
            if(p == 8){ //0.1的几率对方闪避
                damage = 0;
                ui->label_mySkill->setText("ATTACK MISS!!!");
            }

            int recDamage = damage - opPkm->defense;  //实际受到的伤害
            if(recDamage >= 0)
                opCurrentBlood -= recDamage;

            if(opCurrentBlood <= 0){    //判断输赢
                User_win = 1;
                Is_over = 1;
                my_attack_times = op_attack_times = 0;  //停止比赛
            }
            ui->progressBar_opBlood->setValue(opCurrentBlood);  //更新血条
            ui->label_myPkmAttr->setText("My Blood: " + QString::number(myCurrentBlood) + " / " + QString::number(myPkm->blood));
            ui->label_opPkmAttr->setText("Opponent Blood: " + QString::number(opCurrentBlood) + " / " + QString::number(opPkm->blood));
        }

       while(op_attack_times){  //对方攻击次数
            op_attack_times--;

            ui->label_opSkill->clear();
            delay(2);   //模拟攻击间隔

            p = rand_num() % 10 + 1; //p->1~10

            int damage = opponent->attackOpponent(opPkmIndex);
            if(damage == -1){   //使出技能
                 ui->label_opSkill->setText(ATTACKKIND[opPkm->skill] + "!!!");  //展示使出的技能
                if(myPkm->kind != opPkm->kind){
                    if(opPkm->skill != defense_attack)
                        damage = opPkm->attack * 1.3;   //对不同类型的pokemon使出技能伤害高
                    else
                        opCurrentBlood += opPkm->blood * 0.2;   //defense attack加自己血量
                }
                else
                    damage = opPkm->attack * 0.8;
            }
            else ui->label_opSkill->setText("NORMAL ATTACK");

            if(p <= 2){  //0.2的几率暴击
                damage = damage * 1.2;
                ui->label_opSkill->setText("CRIT ATTACK!!!");
            }
            if(p == 8) {//0.1的几率对方闪避
                damage = 0;
                ui->label_opSkill->setText("ATTACK MISS!!!");
            }

            int recDamage = damage - myPkm->defense;    //实际受到的伤害
            if(recDamage >= 0)
                myCurrentBlood -= recDamage;

            if(myCurrentBlood <= 0){    //判断输赢
                User_win = 0;
                Is_over = 1;
                my_attack_times = op_attack_times = 0;  //停止比赛
            }
            ui->progressBar_myBlood->setValue(myCurrentBlood);  //更新血条
            ui->label_myPkmAttr->setText("My Blood: " + QString::number(myCurrentBlood) + " / " + QString::number(myPkm->blood));
            ui->label_opPkmAttr->setText("Opponent Blood: " + QString::number(opCurrentBlood) + " / " + QString::number(opPkm->blood));
        }
    }

    if(User_win == 1){
        QMessageBox::information (this,"Game Over","You Win!!!","OK");
    }
    else
        QMessageBox::information (this,"Game Over","You Lose!!!","OK");

    return User_win;    //返回结果
}


void MainWindow::delay(int time)    //模拟真实攻击间隔
{
    QTime dieTime= QTime::currentTime().addSecs(time);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::giveOutPkm(User *user)     //送出一个pokemon
{
    int pkmNum = user->getPkmNum();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rand_num(seed);	 // 大随机数
    ui->comboBox_giveOut->clear();
    if(pkmNum >= 3){    //随机从用户中拿出3个pokemon
        this->selectedIndex = rand_num() % pkmNum;
        for(int i=0, p=selectedIndex;i<3;i++){
            ui->comboBox_giveOut->addItem(user->getPkmByIndex(p)->name);
            p = (p + 1) % pkmNum;
        }
    }
    else{   //用户没有3个pokemon，拿出所有pokemon
        for(int i=0;i<pkmNum;i++)
            ui->comboBox_giveOut->addItem(user->getPkmByIndex(i)->name);
        this->selectedIndex = 0;
    }

    ui->comboBox_giveOut->setCurrentIndex(0);
    ui->label_myPkmAttr->setText(this->getPkmAttr(selectedIndex));
    ui->label_myPic->setStyleSheet("#label_myPic{border-image:url(:/Pokemon_picture/"+
                                   this->user->getPkmByIndex(selectedIndex)->name+".png);}");
}


void MainWindow::on_pushButton_select_clicked()     //决定要送出的pokemon
{
    unsigned int pkm_index = ui->comboBox_giveOut->currentIndex();
    pkm_index = (selectedIndex + pkm_index) % user->getPkmNum();
    if(user->getPkmNum() > 1){
        user->popPkmByIndex(pkm_index); //送出pokemon
        QMessageBox::critical(this, "Pop pokemon", "pop pokemon complete", "OK");
    }
    else    //如果用户pokemon个数为1，不送出
        QMessageBox::critical(this, "Pop pokemon", "no pokemon, get new pokemon", "OK");

    updateUserPkm();        //在server端数据库中，更新user自己的pokemon信息
    setComboBoxValue(1);    //更新用户pokemon信息
    setComboBoxValue(0);
    hideGiveOut();      //隐藏决斗赛中，送出pokemon界面
    showGameType();     //返回主界面
}

void MainWindow::on_pushButton_clicked()    //快速升级
{
    user->addExperience(ui->comboBox_myPkm->currentIndex(), 5);
    setComboBoxValue(0);    //更新用户pokemon信息
    setComboBoxValue(1);
}

void MainWindow::on_comboBox_giveOut_currentIndexChanged(int index)    //展示所有可能送出的pokemon
{
    mode = 4;
    if(index < 0 || index >= user->getPkmNum()) return;
    index = (selectedIndex + index) % user->getPkmNum();
    ui->label_myPkmAttr->setText(this->getPkmAttr(index));
    ui->label_myPic->setStyleSheet("#label_myPic{border-image:url(:/Pokemon_picture/"+
                                   this->user->getPkmByIndex(index)->name+".png);}");
}
