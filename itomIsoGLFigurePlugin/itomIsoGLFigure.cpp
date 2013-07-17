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

#include "itomIsoGLFigure.h"

#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qimagewriter.h>

//#include <GV_plot_renderer.h>

//#include "dialog2DScale.h"

using namespace ito;


//----------------------------------------------------------------------------------------------------------------------------------
ItomIsoGLWidget::ItomIsoGLWidget(const QString &itomSettingsFile, AbstractFigure::WindowMode windowMode, QWidget *parent) :
    AbstractDObjFigure(itomSettingsFile, windowMode, parent),
    m_pContent(NULL),
    m_actScaleSetting(NULL),
   // m_actPan(NULL),
   // m_actZoomToRect(NULL),
   // m_actMarker(NULL),
   // m_actLineCut(NULL),
    m_actPalette(NULL),
    m_actToggleColorBar(NULL),
    m_actChangeBGColor(NULL),
    m_toggleIllumination(NULL),
    m_toggleIlluminationRotation(NULL),
   // m_actColorDisplay(NULL),
   // m_actGrayDisplay(NULL),
   // m_actAScan(NULL),
   // m_actForward(NULL),
   // m_actBack(NULL),
    m_actCmplxSwitch(NULL),
    m_mnuCmplxSwitch(NULL),
    m_actTringModeSwitch(NULL),
    m_mnuTringModeSwitch(NULL),
    m_toggleInfoText(NULL),
	m_lblCoordinates(NULL)
{
    m_pOutput.insert("bounds", new ito::Param("bounds", ito::ParamBase::DoubleArray, NULL, QObject::tr("Points for line plots from 2d objects").toAscii().data()));

    int id = qRegisterMetaType<QSharedPointer<ito::DataObject> >("QSharedPointer<ito::DataObject>");

    QMenu *contextMenu = new QMenu(QObject::tr("plot2D"), this);

    QGLFormat fmt;
    fmt.setDoubleBuffer(0);

    fmt.setOverlay(0);
    if (fmt.swapInterval() != -1)
        fmt.setSwapInterval(0);
    fmt.setProfile(QGLFormat::CoreProfile);

    int glVer = QGLFormat::openGLVersionFlags();

    if (glVer >= 32)
    {
        fmt.setVersion(2,0);
    }

    fmt.setDepth(0);

    m_pContent = new plotGLWidget(contextMenu, fmt, this, 0);
    m_pContent->setObjectName("canvasWidget");

    setCentralWidget(m_pContent);
    //m_pContent->setFocus();

    //m_actHome
    m_actHome = new QAction(QIcon(":/itom2DQwtFigurePlugin/icons/home.png"),tr("Home"), this);
    m_actHome->setObjectName("actHome");
    m_actHome->setToolTip("Reset original view");

	//m_actSave
    m_actSave = new QAction(QIcon(":/itom2DQwtFigurePlugin/icons/filesave.png"),tr("Save"), this);
    m_actSave->setObjectName("actSave");
    m_actSave->setToolTip("Export current view");

    //m_actScaleSetting
    m_actScaleSetting = new QAction(QIcon(":/plots/icons/itom_icons/autoscal.png"),tr("Scale Settings"), this);
    m_actScaleSetting->setObjectName("actScaleSetting");
    m_actScaleSetting->setToolTip("Set the ranges and offsets oif this view");

    //m_actPan
    /*
    m_actPan = new QAction(QIcon(":/matplotlibFigure/icons/move.png"), QObject::tr("move"), this);
    m_actPan->setObjectName("actionPan");
    m_actPan->setCheckable(true);
    m_actPan->setChecked(false);
    m_actPan->setEnabled(false);
    m_actPan->setToolTip("Pan axes with left mouse, zoom with right");
    */

    //m_actZoomToRect
    /*
    m_actZoomToRect = new QAction(QIcon(":/matplotlibFigure/icons/zoom_to_rect.png"), QObject::tr("zoom to rectangle"), this);
    m_actZoomToRect->setObjectName("actionZoomToRect");
    m_actZoomToRect->setCheckable(true);
    m_actZoomToRect->setChecked(false);
    m_actZoomToRect->setToolTip("Zoom to rectangle");
    */
    //m_actMarker
    /*
    m_actMarker = new QAction(QIcon(":/matplotlibFigure/icons/marker.png"), QObject::tr("marker"), this);
    m_actMarker->setObjectName("actionMarker");
    m_actMarker->setCheckable(true);
    m_actMarker->setChecked(false);
    */
    //m_actLineCut
    /*
    m_actLineCut = new QAction(QIcon(":/plots/icons/itom_icons/pntline.png"),tr("Linecut"),this);
    m_actLineCut->setCheckable(true);
    m_actLineCut->setObjectName("LineCut");
    m_actLineCut->setToolTip("Show a in plane line cut");
    */
    //m_actPalette
    m_actPalette = new QAction(QIcon(":/plots/icons/itom_icons/color.png"),tr("Palette"),this);
    m_actPalette->setObjectName("TogglePalette");
    m_actPalette->setToolTip("Switch between color palettes");

    //m_actToggleColorBar
    m_actToggleColorBar = new QAction(QIcon(":/plots/icons/itom_icons/colorbar.png"),tr("Show Colorbar"), this);
    m_actToggleColorBar->setObjectName("ShowColorBar");
    m_actToggleColorBar->setToolTip("Toggle visibility of the color bar on right canvas side");

    //m_actChangeBGColor
    m_actChangeBGColor = new QAction(QIcon(":/plots/icons/itom_icons/blkorwht.png"),tr("Change Background Color"), this);
    m_actChangeBGColor->setObjectName("Change Background Color");
    m_actChangeBGColor->setToolTip("Switch between the different background colors");

    //m_toggleIllumination
    m_toggleIllumination = new QAction(QIcon(":/itomIsoGLFigurePlugin/icons/LightOff.png"),tr("Enable Illumination"), this);
    m_toggleIllumination->setCheckable(true);
    m_toggleIllumination->setObjectName("Enable illumination rendering");
    m_toggleIllumination->setToolTip("Enable illumination rendering");

    //m_toggleIlluminationRotation
    m_toggleIlluminationRotation = new QAction(QIcon(":/itomIsoGLFigurePlugin/icons/LightDir.png"),tr("Change illumination direction"), this);
    m_toggleIlluminationRotation->setCheckable(true);
    m_toggleIlluminationRotation->setObjectName("Change illumination direction");
    m_toggleIlluminationRotation->setToolTip("Change illumination direction");


    //m_actAspectSwitch
    m_actTringModeSwitch = new QAction(tr("Triangles"), this);
    m_mnuTringModeSwitch = new QMenu("Mode Switch");
    m_mnuTringModeSwitch->addAction(tr("M++Mode"));
    m_mnuTringModeSwitch->addAction(tr("JoeMode"));
    m_actTringModeSwitch->setMenu(m_mnuTringModeSwitch);

    m_toggleInfoText = new QAction(QIcon(":/itomIsoGLFigurePlugin/icons/info.png"),tr("Show Infotext"), this);
    m_toggleInfoText->setCheckable(true);
    m_toggleInfoText->setObjectName("Show Infotext");
    m_toggleInfoText->setToolTip("Show Infotext");

    //m_actAScan
    /*
    m_actAScan = new QAction(QIcon(":/plots/icons/itom_icons/1dzdir.png"),tr("Slice in z-direction"),this);
    m_actAScan->setObjectName("a-Scan");
    m_actAScan->setToolTip("Show a slice through z-Stack");
    m_actAScan->setCheckable(true);
    m_actAScan->setVisible(false);
    */
    //m_actForward
    /*
    m_actForward = new QAction(QIcon(":/itom2DQwtFigurePlugin/icons/forward.png"), tr("forward"), this);
    m_actForward->setObjectName("actionForward");
    m_actForward->setVisible(false);
    m_actForward->setToolTip("Forward to next plane");
    */
    //m_actBack
    /*
    m_actBack = new QAction(QIcon(":/itom2DQwtFigurePlugin/icons/back.png"), tr("back"), this);
    m_actBack->setObjectName("actionBack");
    m_actBack->setVisible(false);
    m_actBack->setToolTip("Back to previous plane");
    */
    //m_actCmplxSwitch
    m_actCmplxSwitch = new QAction(QIcon(":/itomDesignerPlugins/complex/icons/ImRe.png"),tr("Switch Imag, Real, Abs, Pha"), this);
    m_mnuCmplxSwitch = new QMenu("Complex Switch");
    m_mnuCmplxSwitch->addAction(tr("Imag"));
    m_mnuCmplxSwitch->addAction(tr("Real"));
    m_mnuCmplxSwitch->addAction(tr("Abs"));
    m_mnuCmplxSwitch->addAction(tr("Pha"));
    m_actCmplxSwitch->setMenu(m_mnuCmplxSwitch);
    m_actCmplxSwitch->setVisible(false);

    bool test;
    test = connect(m_actSave, SIGNAL(triggered()), this, SLOT(mnuExport()));
    test = connect(m_actHome, SIGNAL(triggered()), this, SLOT(mnuHome()));

    //test = connect(m_actScaleSetting, SIGNAL(triggered()), this, SLOT(mnuScaleSetting()));
    //test = connect(m_actPan, SIGNAL(toggled(bool)), this, SLOT(mnuPanner(bool)));
    //test = connect(m_actZoomToRect, SIGNAL(toggled(bool)), this, SLOT(mnuZoomer(bool)));
    //test = connect(m_actMarker, SIGNAL(toggled(bool)), this, SLOT(mnuValuePicker(bool)));
    //test = connect(m_actLineCut, SIGNAL(toggled(bool)), this, SLOT(mnuLinePicker(bool)));

    test = connect(m_actPalette, SIGNAL(triggered()), this, SLOT(mnuPalette()));
    test = connect(m_actToggleColorBar, SIGNAL(triggered()), this, SLOT(mnuColorBar()));
    test = connect(m_actChangeBGColor, SIGNAL(triggered()), this, SLOT(mnuToggleBPColor()));
    test = connect(m_toggleIllumination, SIGNAL(toggled(bool)), this, SLOT(mnutoggleIllumination(bool)));
    test = connect(m_toggleIlluminationRotation, SIGNAL(toggled(bool)), this, SLOT(mnutoggleIlluminationRotation(bool)));

    test = connect(m_toggleInfoText, SIGNAL(toggled(bool)), m_pContent, SLOT(toogleObjectInfoText(bool)));

    //test = connect(m_actAScan, SIGNAL(toggled(bool)), this, SLOT(mnuAScanPicker(bool)));
    test = connect(m_mnuCmplxSwitch, SIGNAL(triggered(QAction*)), this, SLOT(mnuCmplxSwitch(QAction*)));
    test = connect(m_mnuTringModeSwitch, SIGNAL(triggered(QAction*)), this, SLOT(mnuTringModeSwitch(QAction*)));

	QToolBar *toolbar = new QToolBar(this);
	addToolBar(toolbar, "mainToolBar", Qt::TopToolBarArea, 1);

    contextMenu->addAction(m_actSave);
    contextMenu->addSeparator();
    contextMenu->addAction(m_actHome);
    contextMenu->addAction(m_actScaleSetting);
    contextMenu->addAction(m_toggleInfoText);
//    contextMenu->addSeparator();
//    contextMenu->addAction(m_actPan);
//    contextMenu->addAction(m_actZoomToRect);
//    contextMenu->addAction(m_actMarker);
    contextMenu->addSeparator();
    contextMenu->addAction(toolbar->toggleViewAction());

    // next block is colorbar
    toolbar->addSeparator();
    toolbar->addAction(m_actPalette);
    toolbar->addAction(m_actToggleColorBar);
    toolbar->addAction(m_actChangeBGColor);
    toolbar->addAction(m_actTringModeSwitch);

    toolbar->addSeparator();
    toolbar->addAction(m_toggleIllumination);
    toolbar->addAction(m_toggleIlluminationRotation);
//    m_toolbar->addAction(m_actAspectSwitch);

    toolbar->addSeparator();
    toolbar->addAction(m_toggleInfoText);

    // next block is for complex and stacks
    toolbar->addSeparator();
//    m_toolbar->addAction(m_actAScan);
//    m_toolbar->addAction(m_actBack);
//    m_toolbar->addAction(m_actForward);
    toolbar->addAction(m_actCmplxSwitch);

    m_pEventFilter = NULL;

    m_pEventFilter = new GL3DEFilter(this);
    installEventFilter( m_pEventFilter );
}

//----------------------------------------------------------------------------------------------------------------------------------
ItomIsoGLWidget::~ItomIsoGLWidget()
{

}

//----------------------------------------------------------------------------------------------------------------------------------
ito::RetVal ItomIsoGLWidget::applyUpdate()
{
    m_pOutput["displayed"]->copyValueFrom(m_pInput["source"]);
    ((plotGLWidget*)m_pContent)->refreshPlot(m_pOutput["displayed"]); //push the displayed DataObj into the actual plot widget for displaying

    return ito::retOk;
}

//----------------------------------------------------------------------------------------------------------------------------------
QSharedPointer<ito::DataObject> ItomIsoGLWidget::getDisplayed(void)
{
    return QSharedPointer<ito::DataObject>(m_pOutput["displayed"]->getVal<ito::DataObject*>());
}

//----------------------------------------------------------------------------------------------------------------------------------
QSharedPointer<ito::DataObject> ItomIsoGLWidget::getSource(void)
{
    return QSharedPointer<ito::DataObject>(m_pInput["source"]->getVal<ito::DataObject*>());
}

//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::setShowContextMenu(bool show)
{
    if(m_pContent) ((plotGLWidget*)m_pContent)->m_showContextMenu = show;
}

//----------------------------------------------------------------------------------------------------------------------------------
bool ItomIsoGLWidget::showContextMenu() const
{
    if(m_pContent) return ((plotGLWidget*)m_pContent)->m_showContextMenu;
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------
ito::RetVal ItomIsoGLWidget::displayLineCut(QVector<QPointF> bounds, ito::uint32 &uniqueID)
{
    return ito::retError;
}
//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::mnuHome()
{
    if(m_pContent) ((plotGLWidget*)m_pContent)->homeView();
    return;
}

//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::mnuPalette()
{
    ((plotGLWidget*)m_pContent)->m_paletteNum++;
    ((plotGLWidget*)m_pContent)->setColorMap("");
}


//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::mnuExport()
{
#ifndef QT_NO_PRINTER
    QString fileName = "bode.pdf";
#else
    QString fileName = "bode.png";
#endif

#ifndef QT_NO_FILEDIALOG
    const QList<QByteArray> imageFormats =
        QImageWriter::supportedImageFormats();

    QStringList filter;
    filter += "PDF Documents (*.pdf)";
#ifndef GV_NO_SVG
#ifdef QT_SVG_LIB
    filter += "SVG Documents (*.svg)";
#endif
#endif
    filter += "Postscript Documents (*.ps)";

    if ( imageFormats.size() > 0 )
    {
        QString imageFilter("Images (");
        for ( int i = 0; i < imageFormats.size(); i++ )
        {
            if ( i > 0 )
                imageFilter += " ";
            imageFilter += "*.";
            imageFilter += imageFormats[i];
        }
        imageFilter += ")";

        filter += imageFilter;
    }

    fileName = QFileDialog::getSaveFileName(
        this, "Export File Name", fileName,
        filter.join(";;"), NULL, QFileDialog::DontConfirmOverwrite);
#endif

/*
    if ( !fileName.isEmpty() )
    {
        GVPlotRenderer renderer;

        // flags to make the document look like the widget
        renderer.setDiscardFlag(GVPlotRenderer::DiscardBackground, false);
        renderer.setLayoutFlag(GVPlotRenderer::KeepFrames, true);

        renderer.renderDocument(((plotGLWidget*)m_pContent), fileName, QSizeF(300, 200), 85);
    }
*/
}

//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::mnuScaleSetting()
{
/*
    DataObjectRasterData* rasterData = static_cast<DataObjectRasterData*>(((plotGLWidget*)m_pContent)->m_pContent->data());
    double minX = 0.0, maxX = 0.0, minY = 0.0, maxY = 0.0, minZ = 0.0, maxZ = 0.0;
    double minRangeX = 0.0, maxRangeX = 0.0, minRangeY = 0.0, maxRangeY = 0.0;
    int dims = 2, numPlanes = 1, curPlane = 0;
    bool autoCalcX, autoCalcY, autoCalcZ;
    GVInterval interval;

    if(rasterData)
    {
        interval = rasterData->interval(Qt::XAxis);
        minX = interval.minValue();
        maxX = interval.maxValue();
        interval = rasterData->interval(Qt::YAxis);
        minY = interval.minValue();
        maxY = interval.maxValue();
        interval = rasterData->interval(Qt::ZAxis);
        minZ = interval.minValue();
        maxZ = interval.maxValue();

        QSharedPointer<ito::DataObject> dataObj = rasterData->getDataObject();

        if(dataObj != NULL)
        {
            int dims = dataObj->getDims();
            bool test = false;
            minRangeX = dataObj->getPixToPhys(dims - 1, 0.0, test);
            maxRangeX = dataObj->getPixToPhys(dims - 1, dataObj->getSize(dims-1, true), test);
            minRangeY = dataObj->getPixToPhys(dims - 2, 0.0, test);
            maxRangeY = dataObj->getPixToPhys(dims - 2, dataObj->getSize(dims-2, true), test);

            dims = dataObj->getDims();
            if(dims > 2)
            {
                int* wholeSize = new int[dims];
                int* offsets = new int[dims];

                dataObj->locateROI(wholeSize, offsets);

                for(int cntPlane = 0; cntPlane < (dims-2); cntPlane++)
                {
                    numPlanes *= wholeSize[cntPlane];
                }
                curPlane = offsets[dims-3];
                if(dims > 4)
                {
                    for(int cntPlane = 0; cntPlane < (dims-3); cntPlane++)
                    {
                        curPlane += curPlane + offsets[cntPlane] * wholeSize[cntPlane - 1];
                    }
                }
                delete wholeSize;
                delete offsets;
            }

        }
        else
        {
            minRangeX = minX;
            maxRangeX = maxX;
            minRangeY = minY;
            maxRangeY = maxY;
        }
    }
    else
    {
        QMessageBox::warning(this, tr("no data available"), tr("no data object is currently being displayed in this widget."));
    }

    Dialog2DScale *dlg = new Dialog2DScale(minX, maxX, minRangeX, maxRangeX, minY, maxY, minRangeY, maxRangeY, minZ, maxZ, dims, curPlane, numPlanes);
    dlg->exec();
    if(dlg->result() == QDialog::Accepted)
    {
        dlg->getData(minX,maxX,minY,maxY,minZ,maxZ, curPlane, autoCalcX, autoCalcY, autoCalcZ);

        ((plotGLWidget*)m_pContent)->setInterval(Qt::XAxis, autoCalcX, minX, maxX);
        ((plotGLWidget*)m_pContent)->setInterval(Qt::YAxis, autoCalcY, minY, maxY);
        ((plotGLWidget*)m_pContent)->setInterval(Qt::ZAxis, autoCalcZ, minZ, maxZ);
        ((plotGLWidget*)m_pContent)->setColorMap();
    }

    delete dlg;
    dlg = NULL;
*/
}
//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::mnuColorBar()
{
    if(m_pContent)
        ((plotGLWidget*)m_pContent)->togglePaletteMode();
}
//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::mnutoggleIllumination(const bool checked)
{
    if(m_pContent) ((plotGLWidget*)m_pContent)->toggleIllumination(checked);
    m_toggleIlluminationRotation->setEnabled(checked);
    if(!checked)
    {
        m_toggleIllumination->setIcon(QIcon(":/itomIsoGLFigurePlugin/icons/LightOff.png"));
        m_toggleIlluminationRotation->setChecked(false);
    }
    else
    {
        m_toggleIllumination->setIcon(QIcon(":/itomIsoGLFigurePlugin/icons/LightOn.png"));
    }
}
//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::mnutoggleIlluminationRotation(const bool checked)
{
    if(m_pContent) ((plotGLWidget*)m_pContent)->toggleIlluminationRotation(checked);
}

//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::mnuCmplxSwitch(QAction *action)
{
    //GVScaleWidget *rightAxis = axisWidget(GVPlot::yRight);
    //enableAxis(GVPlot::yRight, checked);

    if (m_pContent)
    {


        if (action->text() == QString("Imag"))
        {
            ((plotGLWidget*)m_pContent)->setCmplxMode(0);
            m_actCmplxSwitch->setIcon(QIcon(":/itomDesignerPlugins/complex/icons/ImReImag.png"));
        }
        else if (action->text() == QString("Real"))
        {
            ((plotGLWidget*)m_pContent)->setCmplxMode(1);
            m_actCmplxSwitch->setIcon(QIcon(":/itomDesignerPlugins/complex/icons/ImReReal.png"));
        }
        else if (action->text() == QString("Pha"))
        {
            ((plotGLWidget*)m_pContent)->setCmplxMode(2);
            m_actCmplxSwitch->setIcon(QIcon(":/itomDesignerPlugins/complex/icons/ImRePhase.png"));
        }
        else
        {
            ((plotGLWidget*)m_pContent)->setCmplxMode(3);
            m_actCmplxSwitch->setIcon(QIcon(":/itomDesignerPlugins/complex/icons/ImReAbs.png"));
        }
        ((plotGLWidget*)m_pContent)->refreshPlot(NULL);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::mnuTringModeSwitch(QAction *action)
{
    //GVScaleWidget *rightAxis = axisWidget(GVPlot::yRight);
    //enableAxis(GVPlot::yRight, checked);

    if (m_pContent)
    {
        if (action->text() == QString("M++Mode"))
        {
            m_mnuTringModeSwitch->setTitle("Triangles");
            int vismode = ((plotGLWidget*)m_pContent)->getCurrentVisMode();
            if(vismode == plotGLWidget::PAINT_POINTS) ((plotGLWidget*)m_pContent)->setCurrentVisMode(plotGLWidget::PAINT_TRIANG);
        }
        if (action->text() == QString("JoeMode"))
        {
            m_mnuTringModeSwitch->setTitle("Points");
            int vismode = ((plotGLWidget*)m_pContent)->getCurrentVisMode();
            if(vismode == plotGLWidget::PAINT_TRIANG) ((plotGLWidget*)m_pContent)->setCurrentVisMode(plotGLWidget::PAINT_POINTS);
        }
    }

}


//----------------------------------------------------------------------------------------------------------------------------------
QPointF ItomIsoGLWidget::getZAxisInterval(void)
{
    //return ((plotGLWidget*)m_pContent)->m_startRangeZ;
    return QPointF(0.0, 1.0);
}

//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::setZAxisInterval(QPointF interval)
{
    ((plotGLWidget*)m_pContent)->setInterval(Qt::ZAxis, 0, interval.x(), interval.y());
    return;
}

//----------------------------------------------------------------------------------------------------------------------------------
QString ItomIsoGLWidget::getColorPalette(void)
{
    return QString();
}

//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::setColorPalette(QString palette)
{
    ((plotGLWidget*)m_pContent)->setColorMap(palette);
}
//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::enableIlluGUI(const bool checked)
{
    if(!checked) m_toggleIllumination->setChecked(false);
    if(!checked) m_toggleIlluminationRotation->setChecked(false);
    m_toggleIllumination->setEnabled(checked);
    m_toggleIlluminationRotation->setEnabled(checked);
}
//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::enableComplexGUI(const bool checked)
{
    m_actCmplxSwitch->setEnabled(checked);
    m_actCmplxSwitch->setVisible(checked);
}
//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::enableZStackGUI(const bool checked)
{

}
//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::setLinePlotCoordinates(const QVector<QPointF> pts)
{
    char buf[60] = {0};
    if(pts.size() > 1)
    {
        sprintf(buf, "[%.6g; %.6g]\n[%.6g; %.6g]", pts[0].x(), pts[0].y(), pts[1].x(), pts[1].y());
    }
    else if(pts.size() == 1)
    {
        sprintf(buf, "[%.6g; %.6g]\n[ - ; - ]", pts[0].x(), pts[0].y());
    }
    else
    {
        sprintf(buf, "[ - ; - ]\n[ - ; - ]");
    }
    m_lblCoordinates->setText(buf);
}

//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::triggerReplot()
{
    if(m_pContent != NULL)
    {
        ((plotGLWidget*)m_pContent)->m_forceReplot = true;
        ((plotGLWidget*)m_pContent)->refreshPlot(NULL);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
void ItomIsoGLWidget::mnuToggleBPColor()
{
    if(m_pContent != NULL)
    {
        int color = ((plotGLWidget*)m_pContent)->getBGColor();
        ((plotGLWidget*)m_pContent)->setBGColor(color + 1);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
bool GL3DEFilter::event(QEvent *e)
{
    if ( e->type() == QEvent::User )
    {
//        showCursor(true);
        return true;
    }
    return QObject::event(e);
}

//----------------------------------------------------------------------------------------------------------------------------------
bool GL3DEFilter::eventFilter(QObject *object, QEvent *e)
{

    if(e->type() == QEvent::Destroy)
        return false;

    if (!m_plotObj || m_plotObj == NULL|| ((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent) == NULL)
        return false;

    switch(e->type())
    {
        case QEvent::FocusIn:
//            showCursor(true);
        case QEvent::FocusOut:
//            showCursor(false);

        case QEvent::Resize:
        {
         //   m_plotObj->resizeGLWidget(true);
            break;
        }

        case QEvent::Wheel:
        {
            if(((const QWheelEvent *)e)->delta() > 0)
            {
                m_plotObj->riseZAmplifierer(0.95);
            }
            else
            {
                m_plotObj->reduceZAmplifierer(1.05);
            }
            break;
        }

        case QEvent::Paint:
        {
            QApplication::postEvent(this, new QEvent(QEvent::User));
            break;
        }

        case QEvent::MouseButtonPress:
        {
            rotating = true;

            startPos[0] = QCursor::pos().x();
            startPos[1] = QCursor::pos().y();

            return true;
        }
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
        {
            if(!rotating) return true;

            double deltaZ = (QCursor::pos().x() - startPos[0]) / 200.0;
            double deltaX = (QCursor::pos().y() - startPos[1]) / 200.0;
            double deltaY = 0;

            startPos[0] = QCursor::pos().x();
            startPos[1] = QCursor::pos().y();

            if(((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent)->lightArrowEnabled())
            {
                ((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent)->rotateLightArrow(deltaX, deltaY, deltaZ);
            }
            else
            {
                ((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent)->rotateView(deltaX, deltaY, deltaZ);
            }

            if(e->type() == QEvent::MouseButtonRelease)
            {
                rotating = true;
                moving = false;
            }
            ((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent)->paintEvent(NULL);
            return true;
        }

        case QEvent::KeyPress:
        {
            switch(((const QKeyEvent *)e)->key())
            {
                case Qt::Key_Up:
                {
                    ((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent)->rotateView(-0.05, 0.0, 0.0);
                }
                ((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent)->paintEvent(NULL);
                return true;

                case Qt::Key_Down:
                {
                    ((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent)->rotateView(0.05, 0.0, 0.0);

                }
                ((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent)->paintEvent(NULL);
                return true;

                case Qt::Key_Right:
                {
                    ((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent)->rotateView(0.0, 0.0, 0.05);

                }
                ((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent)->paintEvent(NULL);
                return true;

                case Qt::Key_Left:
                {
                    ((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent)->rotateView(0, 0, -0.05);

                }
                ((plotGLWidget*)((ItomIsoGLWidget*)m_plotObj)->m_pContent)->paintEvent(NULL);
                return true;

                // The following keys represent a direction, they are
                // organized on the keyboard.

                case Qt::Key_V:
                {

                }
                break;

                default:
                break;
            }
        }
        default:
            break;
    }

    return QObject::eventFilter(object, e);
}