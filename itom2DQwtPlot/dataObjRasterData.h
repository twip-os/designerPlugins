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

#ifndef DATAOBJRASTERDATA_H
#define DATAOBJRASTERDATA_H

#include "common/sharedStructures.h"
#include "DataObject/dataobj.h"
#include "plotCanvas.h"

#include <qwt_raster_data.h>
#include <qlist.h>
#include <qrect.h>
#include <qsharedpointer.h>
#include <qcryptographichash.h>

struct InternalData;

//----------------------------------------------------------------------------------------------------------------------------------
class DataObjRasterData : public QwtRasterData
{
    public:
        explicit DataObjRasterData(const InternalData *m_internalData);
        explicit DataObjRasterData(QSharedPointer<ito::DataObject> dataObj, QList<unsigned int>startPoint, unsigned int wDimIndex, unsigned int width, unsigned int hDimIndex, unsigned int height, bool replotPending);
        ~DataObjRasterData();

        double value2(int m, int n) const;
        double value2_yinv(int m, int n) const;
        double value(double x, double y) const;
        void initRaster( const QRectF& area, const QSize& raster );
        void discardRaster();

        inline QSize getSize() const { return QSize(m_D.m_xSize, m_D.m_ySize); }

        QByteArray calcHash(const ito::DataObject *dObj = NULL);

        bool updateDataObject(const ito::DataObject *dataObj, int planeIdx = -1);

        bool pointValid(const QPointF &point) const;
       
    protected:
        //Definition: Scale-Coordinate of dataObject =  ( px-Coordinate - Offset)* Scale
        inline double pxToScaleCoords(double px, double offset, double scaling) { return ((double)px - offset) * scaling; }
        inline double scaleToPxCoords(double coord, double offset, double scaling) { return (coord / scaling) + offset; }

    private:

        void deleteCache();

        QByteArray m_hash;
        bool m_validHash;

        ito::DataObject m_dataObj; //the source data object (unchanged)
        ito::DataObject *m_dataObjPlane; //pointer to the source data object (<=2D) or a shallow copy to the depicted plane (>=3D)

        bool m_validData;
        QByteArray m_dataHash;
        QCryptographicHash m_hashGenerator;
        QRectF m_lastRasteredArea;
        QSize m_lastRasteredRaster;

        QRectF m_xyBounds;
        QPointF m_zBounds;

        struct DataParam {
            int** m_dataPtr; //only for comparison
            size_t m_planeIdx;
            double m_yScaling;
            double m_xScaling;
            double m_yOffset;
            double m_xOffset;
            int m_ySize;
            int m_xSize;
            bool m_yaxisFlipped;
        };

        DataParam m_D;

        cv::Mat *m_plane;
        uchar **m_rasteredLinePtr;
        int m_rasteredLines;
        int *m_xIndizes;

        QElapsedTimer timer1, timer2;
        unsigned int nrOfRendering;

        const InternalData *m_pInternalData;
};

//----------------------------------------------------------------------------------------------------------------------------------

#endif
