################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
################################################################

include( qwtconfig.pri )

TEMPLATE = subdirs
CONFIG   += ordered

SUBDIRS = \
    src \
    textengines

contains(QWT_CONFIG, QwtDesigner ) {
    SUBDIRS += designer
}

contains(QWT_CONFIG, QwtExamples ) {
    SUBDIRS += examples
}

qwtspec.files  = qwtconfig.pri qwt.prf
qwtspec.path  = $${QWT_INSTALL_FEATURES}

INSTALLS += qwtspec

CONFIG(debug,debug|release) {
    QMAKE_LFLAGS += ./../../../debug/lib
}
CONFIG(release,debug|release) {
    QMAKE_LFLAGS += ./../../../release/lib
}

