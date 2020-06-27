QT       += core gui sql network testlib  #udp+sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    high_attack.cpp \
    high_blood.cpp \
    high_defense.cpp \
    high_speed.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    pokemon.cpp \
    user.cpp

HEADERS += \
    high_attack.h \
    high_blood.h \
    high_defense.h \
    high_speed.h \
    login.h \
    mainwindow.h \
    pokemon.h \
    user.h

FORMS += \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qss.qrc

DISTFILES += \
    Pokemon_picture/Blastoise.png \
    Pokemon_picture/Charizard.png \
    Pokemon_picture/Charmander.png \
    Pokemon_picture/Diglett.png \
    Pokemon_picture/Dodrio.png \
    Pokemon_picture/Doduo.png \
    Pokemon_picture/Dugtrio.png \
    Pokemon_picture/Pikachu.png \
    Pokemon_picture/Snorlax.png \
    Pokemon_picture/Squirtle.png \
    Pokemon_picture/Wartortle.png \
    Pokemon_picture/charmelon.png \
    pokemon.db
