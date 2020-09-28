TEMPLATE = app
CONFIG += console
#CONFIG -= app_bundle

#since we want to use qDebug, we
#will not subtract qt.
#CONFIG -= qt
CONFIG += c++11



#WINDOWS
# put SFML file in the same location as project
LIBS += -L"..\..\SFML-2.5.1\lib" #change this
LIBS += -L"..\..\SFML-2.5.1\bin" #change this

#MAC
#LIBS += -L"/usr/local/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

#WINDOWS
INCLUDEPATH += "..\..\SFML-2.5.1\include" #change this
DEPENDPATH  += "..\..\SFML-2.5.1\include" #change this

#MAC
#INCLUDEPATH += "/usr/local/include"
#DEPENDPATH += "/usr/local/include"

SOURCES += \
    input.cpp \
        main.cpp \
    menu.cpp \
    shuntingyard.cpp \
    sidebar.cpp \
    user.cpp

HEADERS += \
    TrigFunction.h \
    constants.h \
    input.h \
    menu.h \
    sidebar.h \
    token.h \
    integer.h \
    operator.h \
    queue.h \
    stack.h \
    user.h \
    var.h \
    list.h \
    shuntingyard.h \
    listfunctions.h \
    z_workreport.h
