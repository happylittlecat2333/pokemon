# db数据形式：
table users: username, password
table pokemon: user, name, level, experience, attack, blood, defense, speed, kind, skill

# 发送形式：
收SING_UP：SIGN_UP_SUCCESS, name, level, experience, attack, blood, defense, speed, kind, skill
                           name, level, expe$$rience, attack, blood, defense, speed, kind, skill
                             name, level, experience, attack, blood, defense, speed, kind, skill
        或 NAME_EXIST
收SIGN_IN：SIGN_IN_SUCCESS, name, level, experience, attack, blood, defense, speed, kind, skill
                             name, level, experience, attack, blood, defense, speed, kind, skill
                            name, level, experience, attack, blood, defense, speed, kind, skill
            USER_NONE
            PWD_ERROR
收ALL_USER: ALL_USER, username, name, level, experience, attack, blood, defense, speed, kind, skill
                                name, level, experience, attack, blood, defense, speed, kind, skill
                                 name,level, experience, attack, blood, defense, speed, kind, skill
                    username, name, level, experience, attack, blood, defense, speed, kind, skill
                                name, level, experience, attack, blood, defense, speed, kind, skill
                                 name,level, experience, attack, blood, defense, speed, kind, skill
                                .....   

收VIRTUAL_PKM: VIRTUAL_OKM, name, level, experience, attack, blood, defense, speed, kind, skill
                           name, level, expe$$rience, attack, blood, defense, speed, kind, skill
                             name, level, experience, attack, blood, defense, speed, kind, skill
                             .....

发PKM_DATA username port username, name, level, experience, attack, blood, defense, speed, kind, skill
                                name, level, experience, attack, blood, defense, speed, kind, skill
                                 name,level, experience, attack, blood, defense, speed, kind, skill


# Mode
mode == 0: my pkm
mode == 1: all user pkm
mode == 2: online pkm
mode == 3: oppoment combo box changed


# 发送形式
SIGN_IN, username, password, port
SIGN_UP, username, password, port
SIGN_OUT, port
ALL_USER, port


# 类格式
login:
    Pkm* attrAll[3]
    Pkm** getAllPkm(){return attrAll;$$}

MainWindows:
    Pkm** allPkmAttr;

User:
    Pkm** allPkmAttr;



Fight:

    void fighting(pkm, pkm);


MainWindow:  Server
    Qlist<Pkm*> virtual_pokemon;


Blood = 100 + 20 + 10
attack = 50 + 10 + 5
defense = 25 + 5 + 5
speed = 10 + 2 + 2
