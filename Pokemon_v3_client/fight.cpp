#include "fight.h"
#include "ui_fight.h"

Fight::Fight(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fight)
{
    ui->setupUi(this);
    ui->label_giveOut->hide();
    ui->comboBox_giveOut->hide();
    ui->pushButton_select->hide();
    connect(this,SIGNAL(setResult()),this->parentWidget(),SLOT(recResult()));

}

void Fight::fightBegin(unsigned int game_type, User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex)
{
    ui->setupUi(this);
    this->show();
//    connect(ui->pushButton_select, SIGNAL(pressed()), this, SLOT(on_pushButton_select_clicked()));
    ui->label_giveOut->hide();
    ui->comboBox_giveOut->hide();
    ui->pushButton_select->hide();
    this->user = user;
    this->opponent = opponent;

    unsigned int tmp_level = user->getAllPkmAttr(userPkmIndex)->level;
    qDebug() << "Game Start";
//    Pkm* myPkm = user->getPkmByIndex(userPkmIndex);
//    Pkm* opPkm = opponent->getPkmByIndex(opPkmIndex);

    ui->label_myPkmAttr->setText(user->getPkmAttrByIndex(userPkmIndex));
    ui->label_opPkmAttr->setText(opponent->getPkmAttrByIndex(opPkmIndex));
    ui->label_myPkmPic->setStyleSheet("#label_myPkmPic{border-image:url(:/Pokemon_picture/"+
                                   user->getAllPkmAttr(userPkmIndex)->name+".png);}");
    ui->label_opPkmPic->setStyleSheet("#label_opPkmPic{border-image:url(:/Pokemon_picture/"+
                                   opponent->getAllPkmAttr(opPkmIndex)->name+".png);}");
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
        this->~Fight();
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
        }
        else{
//            QMessageBox::information (this,"Pokemon Loss", "choose one pokemon to give out","OK");
            giveOutPkm(user);
        }
    }
//    delay(5);
    this->~Fight();
}


Fight::~Fight()
{
    delete ui;
}

bool Fight::fightProgress(User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex)
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

        while(my_attack_times){
            my_attack_times--;
            qDebug() << "my attack";

            ui->label_mySkill->clear();
            qsrand (QTime::currentTime ().msec () * (myPkm->experience+214));

            delay(2);
            unsigned int p = (qrand()+5) % 10 + 1; //p->1~10
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
            if(p == 7){ //0.1闪避
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

            qsrand (QTime::currentTime ().msec () * (opPkm->experience+214));

            ui->label_opSkill->clear();
            delay(2);

            unsigned int p = (qrand() + 5) % 10 + 1; //p->1~10
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
            if(p == 7) {//0.1闪避
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

void Fight::giveOutPkm(User *user)
{
    ui->label_giveOut->show();
    ui->pushButton_select->show();
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
    ui->comboBox_giveOut->show();
    ui->comboBox_giveOut->setCurrentIndex(0);
}



void Fight::on_pushButton_select_clicked()
{
    unsigned int pkm_index = ui->comboBox_giveOut->currentIndex();
    user->popPkmByIndex(pkm_index);
    QMessageBox::critical(this, "Pop pokemon", "pop pokemon complete", "OK");
    emit setResult();
//    this->~Fight();

}

void Fight::delay(int time)
{
    QTime dieTime= QTime::currentTime().addSecs(time);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
