TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    Crossover.c \
    GeneticAlgorithm.c \
    Mutation.c \
    Population.c \
    Selection.c

HEADERS += \
    Crossover.h \
    GeneticAlgorithm.h \
    Mutation.h \
    Population.h \
    Selection.h

