QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    src/main.cpp \
    src/network/network.cpp \
    src/network/post.cpp \
    src/network/user.cpp \
    src/pages/makepostpage.cpp \
    src/pages/loginpage.cpp \
    src/pages/profilepage.cpp \
    src/pages/feedpage.cpp \
    src/socialnetworkwindow.cpp

HEADERS += \
    src/network/network.h \
    src/network/post.h \
    src/network/user.h \
    src/pages/makepostpage.h \
    src/pages/loginpage.h \
    src/pages/profilepage.h \
    src/widgets/post.hpp \
    src/pages/feedpage.h \
    src/socialnetworkwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
