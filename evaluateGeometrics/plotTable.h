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

#ifndef PLOTTABLE_H
#define PLOTTABLE_H

#include "common/sharedStructures.h"
#include "common/sharedStructuresPrimitives.h"
#include "DataObject/dataobj.h"

#include <qtabwidget.h>
#include <qtablewidget.h>
#include <qwidget.h>
#include <qstring.h>
#include <qevent.h>
#include <qpoint.h>
#include <qtimer.h>
#include <qmenu.h>
#include <qvector.h>
#include <qstringlist.h>

class EvaluateGeomatricsFigure;

static char const* primitivNames[] = {"not defined", "point", "line", "elipse", "retangle", "square", "err", "err", "err", "polygon"};

struct InternalInfo
{
    bool m_autoTitle;
    QString m_title;
    bool m_autoAxisLabel;
    QString m_axisLabel;
    bool m_autoValueLabel;
    QString m_valueLabel;

    QString titleLabel;
};

struct relationsShip
{
    ito::uint32 type;
    ito::float32 firstElementIdx;
    ito::float32 secondElementIdx;
    ito::uint32 firstElementRow;
    ito::uint32 secondElementRow;
    ito::float32 extValue;
};

class PlotTable : public QTabWidget
{
    Q_OBJECT

        friend class EvaluateGeometricsFigure;

    public:
        enum State { stateIdle, statePanner, stateZoomer, statePicker };

        PlotTable(QMenu *contextMenu, InternalInfo *data, QWidget * parent = 0);
        ~PlotTable();

        ito::RetVal init();

        enum tMeasurementType
        {
            tNoType       =   0,
            tRadius       =   1,
            tAngle        =   2,
            tDistance     =   3,
            tIntersection =   4,
            tArea         =   5,
            tProtected    =   0x4000,
            tExtern       =   0x8000
        }; 

        bool m_showContextMenu;
        void refreshPlot(const ito::DataObject* dataObj);

        ito::RetVal setInterval(const Qt::Axis axis, const bool autoCalcLimits, const double minValue, const double maxValue);

        void setZoomerEnable(const bool checked);
        void setPickerEnable(const bool checked);
        void setPannerEnable(const bool checked);

    protected:
        /*
        void keyPressEvent ( QKeyEvent * event );
        void mousePressEvent ( QMouseEvent * event );
        void mouseMoveEvent ( QMouseEvent * event );
        void mouseReleaseEvent ( QMouseEvent * event );
        void contextMenuEvent(QContextMenuEvent * event);

        void setLabels(const QString &title, const QString &valueLabel, const QString &axisLabel);
        */
        void updateScaleValues(bool recalculateBoundaries = false);

        void updateLabels();

    private:

        void updateRelationShips(const bool fastUpdate);
        inline void setPrimitivElement(const int row, const bool update, const int cols, ito::float32 *val);

        inline bool calculateAngle(ito::float32 *first, ito::float32 *second, ito::float32 &angle);
        inline bool calculateDistance(ito::float32 *first, ito::float32 *second, ito::float32 &distance);
        inline bool calculateRadius(ito::float32 *first, ito::float32 &radius);
        inline bool calculateIntersections(ito::float32 *first, ito::float32 *second, cv::Vec3f &point);

        ito::RetVal m_lastRetVal;

        QMenu *m_contextMenu;

        bool m_xDirect;
        bool m_yDirect;

        QWidget *m_pParent;

        QTableWidget * m_geometrics;
        QTableWidget * m_relations;

        QWidget* m_firstTab;
        QWidget* m_secondTab;

        State m_state;

        InternalInfo *m_data;

        QVector<geometricPrimitives> m_rowHash;
        QVector<relationsShip> m_relationsList;

        QStringList m_relationNames;

    signals:
        void spawnNewChild(QVector<QPointF>);
        void updateChildren(QVector<QPointF>);

    public slots:
        //void replot();

};


#endif // PLOTTABLE_H
