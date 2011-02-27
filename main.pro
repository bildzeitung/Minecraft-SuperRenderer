QT       += core gui

TEMPLATE = app

HEADERS += callbacks.h  named_tag.h      tag_double.h tag_print.h  \
           chunks.h     player.h         tag_float.h  tag_short.h  \
           common.h     tag_byte.h       tag_int.h    tag_string.h \
           list.h       tag_byte_array.h tag_list.h                \
           main.h       tag_compound.h   tag_long.h \
    mainwindow.h \
    processor.h

SOURCES += callbacks.c  named_tag.c      tag_double.c tag_long.c   \
           chunks.c     tag_byte.c       tag_float.c  tag_print.c  \
           list.c       tag_byte_array.c tag_int.c    tag_short.c  \
                 tag_compound.c   tag_list.c   tag_string.c \
    mainwindow.cpp \
    main.cpp \
    processor.c

INCLUDEPATH = uthash-1.9.3/src

LIBS += -lz

FORMS += \
    mainwindow.ui
