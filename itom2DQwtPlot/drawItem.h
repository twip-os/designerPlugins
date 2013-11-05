/* ********************************************************************
 *   itom measurement system
 *   URL: http://www.uni-stuttgart.de/ito
 *   Copyright (C) 2012, Institut für Technische Optik (ITO), 
 *   Universität Stuttgart, Germany 
 * 
 *   This file is part of itom.
 * 
 *   itom is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 * 
 *   itom is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 * 
 *   You should have received a copy of the GNU General Public License
 *   along with itom. If not, see <http://www.gnu.org/licenses/>.
 *********************************************************************** */

#ifndef DRAWITEM_H
#define DRAWITEM_H

#include <qwt_plot_canvas.h>
#include <qwt_plot_shapeitem.h>
#include <qwt_plot_marker.h>

#include <qpoint.h>
#include <qpainterpath.h>

class DrawItem : public QwtPlotShapeItem
{
    public:
        explicit DrawItem(const QString &title = QString::null);
        virtual ~DrawItem();
        void setRect(const QRectF &);
        void setShape( const QPainterPath & );
        
    //    virtual QwtText trackerTextF( const QPointF &pos ) const;
    //    void drawTracker( QPainter *painter ) const;
    //    void setBackgroundFillBrush( const QBrush &brush );
        
        
    protected:
        
    private:
        QPen m_markerPen;
        QBrush m_markerBrush;
        QPen m_linePen;
        QVector<QwtPlotMarker> m_marker;
        
    signals:
        
    public slots:
        
    private slots:
    
};

#endif //DRAWITEM_H
