QT       += core gui
QT	 += multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/bll/bot.cpp \
    src/bll/commandprocessor.cpp \
    src/dal/audio.cpp \
    src/dal/customaudio.cpp \
    src/dal/filemanager.cpp \
    src/dal/jsonparser.cpp \
    src/dal/listener.cpp \
    src/dal/writer.cpp \
    src/entities/commentdata.cpp \
    src/entities/networkdata.cpp \
    src/entities/userdata.cpp \
    src/pl/commentbox.cpp \
    src/pl/mainwindow.cpp \
    src/pl/preferences.cpp

HEADERS += \
    include/bll/bot.h \
    include/bll/commandprocessor.h \
    include/dal/audio.h \
    include/dal/customaudio.h \
    include/dal/filemanager.h \
    include/dal/jsonparser.h \
    include/dal/listener.h \
    include/dal/writer.h \
    include/entities/commentdata.h \
    include/entities/networkdata.h \
    include/entities/userdata.h \
    include/pl/commentbox.h \
    include/pl/mainwindow.h \
    include/pl/preferences.h

FORMS += \
    src/pl/commentbox.ui \
    src/pl/mainwindow.ui \
    src/pl/preferences.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_ICONS = img/logo.ico

DISTFILES += \
    src/css/style.qss
