/* ********************************************************************
   itom measurement system
   URL: http://www.uni-stuttgart.de/ito
   Copyright (C) 2016, Institut fuer Technische Optik (ITO), 
   Universitaet Stuttgart, Germany 
 
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

#ifndef WIDGETCURVEPROPERTIES
#define WIDGETCURVEPROPERTIES

#include <qwidget.h>

#include "ui_widgetCurveProperties.h"

class WidgetCurveProperties : public QWidget 
{
    Q_OBJECT
public:
    WidgetCurveProperties(QWidget *parent = NULL);
    ~WidgetCurveProperties() {};

private:
    Ui::WidgetCurveProperties ui;

private slots:
void on_listWidget_itemClicked(QListWidgetItem *item);
};

#endif