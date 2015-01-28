/* ********************************************************************
   itom measurement system
   URL: http://www.uni-stuttgart.de/ito
   Copyright (C) 2015, Institut f�r Technische Optik (ITO), 
   Universit�t Stuttgart, Germany 
 
   This file is part of the designer widget 'vtk3dVisualizer' for itom.

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

#ifndef ITEMPOINTCLOUDNORMAL_H
#define ITEMPOINTCLOUDNORMAL_H

#include "itemPointCloud.h"



class ItemPointCloudNormal : public ItemPointCloud
{
    Q_OBJECT

    //Q_PROPERTY(bool selected READ selected WRITE setSelected DESIGNABLE true USER true);
    /*Q_PROPERTY(int PointSize READ pointSize WRITE setPointSize DESIGNABLE true USER true);
    Q_PROPERTY(int LineWidth READ lineWidth WRITE setLineWidth DESIGNABLE true USER true);
    Q_PROPERTY(QColor Color READ color WRITE setColor DESIGNABLE true USER true);*/
    Q_PROPERTY(int Level READ level WRITE setLevel DESIGNABLE true USER true);
    Q_PROPERTY(float Scale READ scale WRITE setScale DESIGNABLE true USER true);

public:
    ItemPointCloudNormal(boost::shared_ptr<pcl::visualization::PCLVisualizer> visualizer, const QString &name, QTreeWidgetItem *treeItem);
    virtual ~ItemPointCloudNormal();

    ito::RetVal addPointCloud(const ito::PCLPointCloud &cloud);

    //properties
    //virtual void setVisible(bool value);

    ////bool selected() const { return m_selected; }
    ////void setSelected(bool value);

    //int pointSize() const { return m_pointSize; }
    //void setPointSize(int value);

    //int lineWidth() const { return m_lineWidth; }
    //void setLineWidth(int value);

    //QColor color() const { return m_color; }
    //void setColor(QColor value);



    int level() const { return m_level; }
    void setLevel(int value);

    float scale() const { return m_scale; }
    void setScale(float value);

protected:

    void updatePointCloudNormal();

    int m_level;
    float m_scale;

};





#endif //ITEMPOINTCLOUDNORMAL_H