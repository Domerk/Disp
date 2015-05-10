# Qt 5.4

SOURCES += \
    main.cpp \
    mwgt.cpp \
    sim.cpp \
    wgt2.cpp

HEADERS += \
    mwgt.h \
    sim.h \
    wgt2.h

RESOURCES += \
    images.qrc

QT += \
    widgets
    core

QMAKE_CXXFLAGS += -std=gnu++0x
