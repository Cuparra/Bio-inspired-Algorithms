TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Crossover.c \
    GeneticAlgorithm.c \
    main.c \
    Mutation.c \
    Population.c \
    Selection.c \

HEADERS += \
    Crossover.h \
    GeneticAlgorithm.h \
    Mutation.h \
    Population.h \
    Selection.h \
