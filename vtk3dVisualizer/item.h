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

#ifndef ITEM_H
#define ITEM_H

#include "PointCloud/pclStructures.h"
#include "pcl/visualization/pcl_visualizer.h"

#include <qobject.h>
#include <qlist.h>
#include <qstring.h>
#include <qsharedpointer.h>

class QTreeWidgetItem;



class Item : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool visible READ visible WRITE setVisible DESIGNABLE true USER true);

public:
    
    Item(const QString &name, QTreeWidgetItem *treeItem);
    virtual ~Item();

    inline QString name() const { return m_name; };
    inline QString type() const { return m_type; };
    void setTreeItem(QTreeWidgetItem *treeItem)
    {
        m_treeItem = treeItem;
    }

    inline QTreeWidgetItem* treeItem() const { return m_treeItem; }

    //properties
    bool visible() const { return m_visible; }
    virtual void setVisible(bool value);

    static int itemRole;

signals:
    void updateCanvasRequest();

protected:
    QString m_name;
    QString m_type;
    bool m_visible;

    QTreeWidgetItem* m_treeItem;
    
};

typedef QSharedPointer<Item> SharedItemPtr;


//class PointCloudItem : public Item
//{
//    Q_OBJECT
//    Q_ENUMS(Representation)
//
//    //Q_PROPERTY(bool selected READ selected WRITE setSelected DESIGNABLE true USER true);
//
//public:
//    PointCloudItem(boost::shared_ptr<pcl::visualization::PCLVisualizer> visualizer, ito::PCLPointCloud cloud, const QString &name);
//
//    enum Representation { Points , Wireframe, Surface }; //equals pcl::visualization::RenderingRepresentationProperties
//    //properties
//    virtual void setVisible(bool value);
//
//    //bool selected() const { return m_selected; }
//    //void setSelected(bool value);
//
//    Representation representation() const; 
//
//protected:
//    boost::shared_ptr<pcl::visualization::PCLVisualizer> m_visualizer;
//    ito::PCLPointCloud m_cloud;
//    //bool m_selected;
//
//};





#endif //ITEM_H