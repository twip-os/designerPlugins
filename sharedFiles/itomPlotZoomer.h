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

#ifndef ITOMPLOTZOOMER_H
#define ITOMPLOTZOOMER_H

#include <qwt_plot_zoomer.h>
#include <qpoint.h>

class QEvent;

class ItomPlotZoomer : public QwtPlotZoomer
{
    Q_OBJECT

    Q_PROPERTY( bool isEnabled READ isEnabled WRITE setEnabled )

public:
    explicit ItomPlotZoomer( QWidget *parent, bool doReplot = true );
    explicit ItomPlotZoomer( int xAxis, int yAxis,
                            QWidget *parent, bool doReplot = true );

    virtual ~ItomPlotZoomer();

    void setFixedAspectRatio(bool fixed);
    bool fixedAspectRatio() const { return m_fixedAspectRatio; }

    virtual void rescale(bool resizeEvent);

public Q_SLOTS:
    void setEnabled(bool enabled);

protected:
    bool eventFilter( QObject *object, QEvent *event );

    virtual void rescale() { rescale(false); };
    
    virtual bool accept( QPolygon & ) const;

private:
    bool m_fixedAspectRatio;
    bool m_aspectRatioChanged;
    int m_invertedAxes; //this member remembers the inversion of the xBottom and yLeft axis
};

#endif //ITOMPLOTZOOMER_H