/* ********************************************************************
   itom measurement system
   URL: http://www.uni-stuttgart.de/ito
   Copyright (C) 2012, Institut f�r Technische Optik (ITO), 
   Universit�t Stuttgart, Germany 
 
   This file is part of itom.

   itom is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   itom is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with itom. If not, see <http://www.gnu.org/licenses/>.
*********************************************************************** */

#ifndef ITOMPLOTPLUGIN_H
#define ITOMPLOTPLUGIN_H

#include "plot/AbstractItomDesignerPlugin.h"

class Itom1DQwtPlotPlugin : public ito::AbstractItomDesignerPlugin
{
    Q_OBJECT

public:
    Itom1DQwtPlotPlugin(QObject *parent = 0);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    QWidget *createWidgetWithMode(ito::AbstractFigure::WindowMode winMode, QWidget * parent);
    void initialize(QDesignerFormEditorInterface *core);

private:
    bool initialized;
};

#endif // ITOMPLOTPLUGIN_H