QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATMSystemExtended2
TEMPLATE = app

SOURCES += \
    main.cpp \
    Account.cpp \
    Debit.cpp \
    Credit.cpp \
    CompCard.cpp \
    ATM.cpp \
    MainWindow.cpp \
    DepositDialog.cpp \
    WithdrawDialog.cpp \
    TransferDialog.cpp

HEADERS += \
    Account.h \
    Debit.h \
    Credit.h \
    CompCard.h \
    ATM.h \
    MainWindow.h \
    DepositDialog.h \
    WithdrawDialog.h \
    TransferDialog.h

FORMS += \
    MainWindow.ui \
    DepositDialog.ui \
    WithdrawDialog.ui \
    TransferDialog.ui

CONFIG += c++11

HEADERS += AdminWindow.h
FORMS += AdminWindow.ui
SOURCES += AdminWindow.cpp
