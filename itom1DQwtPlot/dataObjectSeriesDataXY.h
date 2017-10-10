/* ********************************************************************
   itom measurement system
   URL: http://www.uni-stuttgart.de/ito
   Copyright (C) 2012, Institut fuer Technische Optik (ITO), 
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

#ifndef DATAOBJECTRASTERDATAXY_H
#define DATAOBJECTRASTERDATAXY_H

#include "common/sharedStructures.h"
#include "plot/AbstractFigure.h"
#include "DataObject/dataobj.h"
#include "../sharedFiles/itomQwtPlotEnums.h"
#include "dataObjectSeriesData.h"

#include <qwt_series_data.h>
#include <qlist.h>
#include <qrect.h>
#include <qsharedpointer.h>
#include <qwt_scale_map.h>

using namespace ito;

//----------------------------------------------------------------------------------------------------------------------------------
class DataObjectSeriesDataXY : public DataObjectSeriesData
{
public:
        explicit DataObjectSeriesDataXY(const int fastmode);
        ~DataObjectSeriesDataXY();
        RetVal updateDataObject(const ito::DataObject* dataObj,const ito::DataObject* xVec ,QVector<QPointF> bounds, QVector<QPointF> boundsX);
        //size_t size() const;
        QRectF boundingRect() const;
        LineData m_dX;
        QPointF sample(size_t n) const;


private:

    void calcHash();

    const ito::DataObject* m_pXVec;               /*!< borrowed reference, do not delete here */
    //template<typename _T> RetVal sortValues(const DataObject* obj, const int& x1, const int& y1);


    ColorType m_colorState;
    bool inSamplingMode;
    int m_fast;
    QByteArray m_hash;

    QString m_dObjValueDescription;
    QString m_dObjValueUnit;
    QString m_dObjAxisDescription;
    QString m_dObjAxisUnit;
    bool m_autoScaleY;
    double m_minY;
    double m_maxY;
    bool m_autoScaleX;
    double m_minX;
    double m_maxX;
    ItomQwtPlotEnums::ComplexType m_cmplxState;
};

//----------------------------------------------------------------------------------------------------------------------------------

#endif