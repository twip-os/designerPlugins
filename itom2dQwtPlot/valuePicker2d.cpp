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

#include "valuePicker2d.h"

#include <qpainter.h>
#include <qbrush.h>
#include <qwt_plot_canvas.h>

ValuePicker2D::ValuePicker2D(int xAxis, int yAxis, QWidget* parent, const QwtRasterData* valueData) : 
    QwtPlotPicker(xAxis, yAxis, parent),
    m_valueData(valueData)
{
}

ValuePicker2D::~ValuePicker2D()
{
}

QwtText ValuePicker2D::trackerTextF( const QPointF &pos ) const
{
    QString text;
    if (m_valueData)
    {
        double value = m_valueData->value(pos.x(), pos.y());
        text.sprintf("[%.2f, %.2f]\n%.4f", pos.x(), pos.y(), value);
    }
    else
    {
        text.sprintf("[%.2f, %.2f]", pos.x(), pos.y());
    }

    return text;
}

void ValuePicker2D::drawTracker( QPainter *painter ) const
{
    const QRect textRect = trackerRect( painter->font() );
    if ( !textRect.isEmpty() )
    {
        const QwtText label = trackerText( trackerPosition() );
        if ( !label.isEmpty() )
        {
            painter->fillRect(textRect, m_rectFillBrush);
            label.draw( painter, textRect );
        }
    }
}

void ValuePicker2D::setBackgroundFillBrush( const QBrush &brush )
{
    if(brush != this->m_rectFillBrush)
    {
        m_rectFillBrush = brush;
        updateDisplay();
    }
}