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

#include "widgetCurveProperties.h"

#include <qdebug.h>
#include "qmetaobject.h"


#include "Plot1DWidget.h"

#include "cmath"

#include "limits"

//-----------------------------------------------------------------------------------------------
WidgetCurveProperties::WidgetCurveProperties(Plot1DWidget* content, QWidget *parent /*= NULL*/) :
    m_pContent(content),
    QWidget(parent),
	m_visible(false)
{
    ui.setupUi(this);
	Qt::PenStyle;
	

}
void WidgetCurveProperties::updateProperties()
{
	if (m_visible)
	{
		ui.listWidget->clear();
		QList<QwtPlotCurve*> curves = m_pContent->getplotCurveItems();
		QwtPlotCurve*  curve;

		foreach(curve, curves)
		{
ui.listWidget->addItem(curve->title().text());

		}
		const QMetaObject *mo = qt_getEnumMetaObject(Qt::PenStyle::DashLine);//penStyle
		QMetaEnum me = mo->enumerator(mo->indexOfEnumerator("PenStyle"));

		int i;
		for (i = 0; i < me.keyCount(); ++i)
		{
			ui.comboBoxLineStyle->addItem(me.key(i), QVariant()); //add penStyles
		}
		const QMetaObject *moLineColor = qt_getEnumMetaObject(Qt::GlobalColor::black);//color
		QMetaEnum meLineColor = moLineColor->enumerator(moLineColor->indexOfEnumerator("GlobalColor"));
		for (i = 0; i < meLineColor.keyCount(); ++i)
		{
			ui.comboBoxLineColor->addItem(meLineColor.key(i), QVariant());
		}
		


		const QMetaObject *moBrushStyle = qt_getEnumMetaObject(Qt::BrushStyle::NoBrush);
		QMetaEnum meBrushStyle = moBrushStyle->enumerator(moBrushStyle->indexOfEnumerator("BrushStyle"));
		for (i = 0; i < meBrushStyle.keyCount(); ++i)
		{
			ui.comboBoxBrushStyle->addItem(meBrushStyle.key(i), QVariant());//addBrushStyles
		}

	}

}

//-----------------------------------------------------------------------------------------------
void WidgetCurveProperties::on_listWidget_itemSelectionChanged()
{

	QList<QListWidgetItem*> selection = ui.listWidget->selectedItems();
	QListWidgetItem* item;
	int row = -1;
	QPen pen;


	bool constWidth = true;// if the current selection does not have the same linewidth at all, than constWidth will be set to false 
	bool constLineStyle = true;// if the current selection does not have the same linestyle at all, than constWidth will be set to false 
	bool constVisible = true;// if the current selection does not have the same visibility at all, than constWidth will be set to false
	bool constBrushStyle = true;// if the current selection does not have the same baseline at all, than constWidth will be set to false
	bool constLineColor = true;// if the current selection does not have the same lineColor at all, than constWidth will be set to false

	bool first = true; //marks the first line witch is checked 
	float width;
	Qt::PenStyle lineStyle;
	Qt::BrushStyle brushStyle;
	QColor lineColor;
	bool visible;
	foreach(item, selection)
	{
		row = ui.listWidget->row(item);
		pen = m_pContent->getplotCurveItems().at(row)->pen();


		if (!first)
		{

			if (!(std::abs(pen.widthF() - width) <= FLT_EPSILON))
			{
				constWidth = false;
			}
			if (lineStyle != pen.style())
			{
				constLineStyle = false;
			}
			if (m_pContent->getplotCurveItems().at(row)->isVisible() != visible)
			{
				constVisible = false;
			}
			if ( brushStyle != m_pContent->getplotCurveItems().at(row)->brush().style())
			{
				constBrushStyle = false;
			}
			if (lineColor.operator==(pen.color()))
			{
				constLineColor = false;
			}
			

		}

		width = pen.widthF();
		lineStyle = pen.style();
		visible = m_pContent->getplotCurveItems().at(row)->isVisible();
		brushStyle = m_pContent->getplotCurveItems().at(row)->brush().style();
		first = false; //set to false after first for iteration
	}
	if (row != -1)//true if a curve is selected
	{
		if (constWidth)//all lines have the same width
		{
			ui.doubleSpinBoxLineWidth->setValue((float)pen.widthF());
		}
		else
		{
			ui.doubleSpinBoxLineWidth->setValue(0.000f);
		}
		if (constLineStyle)
		{
			ui.comboBoxLineStyle->setCurrentIndex((int)pen.style());
		}
		else
		{
			ui.comboBoxLineStyle->setCurrentIndex(-1);
		}
		if (constVisible)
		{
			ui.checkBoxVisible->setCheckState(Qt::Checked);
		}
		else
		{
			ui.checkBoxVisible->setCheckState(Qt::Unchecked);
		}
		if (constBrushStyle)
		{
			ui.comboBoxBrushStyle->setCurrentIndex((int)m_pContent->getplotCurveItems().at(row)->brush().style());
		}
		else
		{
			ui.comboBoxBrushStyle->setCurrentIndex(-1);
		}
		if (constLineColor)//is the Color the same for all lines_________________________________________________________________________________________
		{
			const QMetaObject *moLineColor = qt_getEnumMetaObject(Qt::GlobalColor::black);//color
			QMetaEnum meLineColor = moLineColor->enumerator(moLineColor->indexOfEnumerator("GlobalColor"));
			bool colorFound = false;
			for (int i = 0; i < meLineColor.keyCount(); ++i)
			{
				if (pen.color().operator==(QColor((Qt::GlobalColor)i)))//check if the LineColor is defined in Qt::GlobalColor enum
				{
					ui.comboBoxLineColor->setCurrentIndex(i);
					colorFound = true;
					break;
				}
			}
			if (!colorFound)
			{
				ui.comboBoxLineColor->setCurrentIndex(-1);//if the color is not defined in Qt::GlobalColor the index of the comboBox will be set to -1
			}
		}
		else
		{
			ui.comboBoxLineColor->setCurrentIndex(-1);
		}

	}

}
//-----------------------------------------------------------------------------------------------
void WidgetCurveProperties::on_comboBoxLineColor_currentIndexChanged(int val)
{
	QList<QListWidgetItem*> selection = ui.listWidget->selectedItems();
	QListWidgetItem* item;
	int row;
	QPen pen;
	foreach(item, selection)
	{
		row = ui.listWidget->row(item);
		pen = m_pContent->getplotCurveItems().at(row)->pen();
		pen.setColor((Qt::GlobalColor)val);
		m_pContent->getplotCurveItems().at(row)->setPen(pen);

	}
	m_pContent->replot();
}
//-----------------------------------------------------------------------------------------------
void WidgetCurveProperties::on_comboBoxBrushStyle_currentIndexChanged(int val)
{
	QList<QListWidgetItem*> selection = ui.listWidget->selectedItems();
	QListWidgetItem* item;
	int row;
	QBrush brush;
	foreach(item, selection)
	{

		row = ui.listWidget->row(item);
		brush = m_pContent->getplotCurveItems().at(row)->brush();
		brush.setStyle((Qt::BrushStyle)val);
		brush.setColor(QColor(Qt::black));
		m_pContent->getplotCurveItems().at(row)->setBrush(brush);

		


	}
	m_pContent->replot();
}
//-----------------------------------------------------------------------------------------------
void WidgetCurveProperties::on_checkBoxVisible_stateChanged(int state)
{
	QList<QListWidgetItem*> selection = ui.listWidget->selectedItems();
	QListWidgetItem* item;
	int row;

	foreach(item, selection)
	{
		row = ui.listWidget->row(item);
		m_pContent->getplotCurveItems().at(row)->setVisible((bool)state);

	}
	m_pContent->replot();

}
//-----------------------------------------------------------------------------------------------
void WidgetCurveProperties::on_comboBoxLineStyle_currentIndexChanged(int val)
{
	QList<QListWidgetItem*> selection = ui.listWidget->selectedItems();
	QListWidgetItem* item;
	QPen pen;
	int row;

	foreach(item, selection)
	{
		row = ui.listWidget->row(item);
		pen = m_pContent->getplotCurveItems().at(row)->pen();
		pen.setStyle((Qt::PenStyle)val);
		m_pContent->getplotCurveItems().at(row)->setPen(pen);
	}
	m_pContent->replot();
}
//-----------------------------------------------------------------------------------------------
void WidgetCurveProperties::on_doubleSpinBoxLineWidth_valueChanged(double i)
{
	QList<QListWidgetItem*> selection = ui.listWidget->selectedItems();
	QListWidgetItem* item;
	QPen pen;
	int row;
	foreach(item, selection)
	{
		row = ui.listWidget->row(item);
		pen=m_pContent->getplotCurveItems().at(row)->pen();
		pen.setWidthF((qreal)i);
		m_pContent->getplotCurveItems().at(row)->setPen(pen);
		
		
	}
	m_pContent->replot();
}
//-----------------------------------------------------------------------------------------------
void WidgetCurveProperties::visibilityChanged(bool visible)
{
	m_visible = visible;
	if (visible)
	{
		updateProperties();
	}
}