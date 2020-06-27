#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAutoFillBackground(true);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pokemon;
}



void MainWindow::on_pushButton_create_clicked()
{
    qsrand(QTime(0,0,0,0).msecsTo((QTime::currentTime()))); //生成随机种子
    unsigned int kind = qrand() % 4;
    SKILL skill =   SKILL(kind);
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
    ui->label_all->setText(pokemon->getAllValue());
}

void MainWindow::on_pushButton_levelUp_clicked()
{
    pokemon->experienceUp(100 * pokemon->getLevel() * pokemon->getLevel() - pokemon->getExperience());  //升级
    ui->label_all->setText(pokemon->getAllValue());
    if(pokemon->getLevel() == MAX_LEVEL){
        ui->label_all->setText("LEVEL MAX!!\n" + pokemon->getAllValue());
    }
}
