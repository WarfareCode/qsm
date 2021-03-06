/****************************************************************************
**
** Copyright (C) 2011 Alexander Vos <alexander.vos@stud.fh-swf.de>,
**                    Till Althaus <till.althaus@stud.fh-swf.de>
**
** This file is part of Qt Slideshow Manager (QSM).
**
** QSM is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QSM is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QSM.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "slideshowlistmodel.h"

#include <QBrush>

SlideshowListModel::SlideshowListModel(QObject *parent) :
    QAbstractListModel(parent), m_currentSlideshow(NULL)
{
}

Qt::ItemFlags SlideshowListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

QVariant SlideshowListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_slideshowList.count())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    {
        const Slideshow &slideshow = m_slideshowList.at(index.row());
        return QString("%1 (%2 images)").arg(slideshow.name()).arg(slideshow.imageCount());
    }
    case Qt::ToolTipRole:
        return m_slideshowList.at(index.row()).comment();
    case Qt::EditRole:
        return m_slideshowList.at(index.row()).name();
    }

    return QVariant();
}

bool SlideshowListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= m_slideshowList.count())
        return false;

    if (role == Qt::EditRole) {
        Slideshow *slideshow = &m_slideshowList[index.row()];
        QString oldName = slideshow->name();
        QString newName = value.toString();
        if (newName != oldName) {
            slideshow->setName(newName);
            emit slideshowRenamed(oldName, newName);
            return true;
        }
    }
    return false;
}

Slideshow* SlideshowListModel::slideshow(const QModelIndex &index) const
{
    if (!index.isValid() || index.row() >= m_slideshowList.count())
        return NULL;

    return const_cast<Slideshow*>(&m_slideshowList[index.row()]);
}

Slideshow* SlideshowListModel::slideshow(const QString &name) const
{
    foreach (const Slideshow &slideshow, m_slideshowList)
        if (slideshow.name() == name)
            return const_cast<Slideshow*>(&slideshow);
    return NULL;
}

QModelIndex SlideshowListModel::addSlideshow(const Slideshow &slideshow)
{
    beginInsertRows(QModelIndex(), m_slideshowList.count(), m_slideshowList.count());
    m_slideshowList.append(slideshow);
    endInsertRows();
    return index(m_slideshowList.count() - 1);
}

bool SlideshowListModel::removeSlideshow(const QModelIndex &index)
{
    if (!index.isValid() || index.row() >= m_slideshowList.count())
        return false;

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    m_slideshowList.removeAt(index.row());
    if (index == m_currentSlideshowIndex) {
        m_currentSlideshow = NULL;
        m_currentSlideshowIndex = QModelIndex();
    }
    endRemoveRows();

    return true;
}

void SlideshowListModel::clear()
{
    beginResetModel();
    m_slideshowList.clear();
    m_currentSlideshow = NULL;
    m_currentSlideshowIndex = QModelIndex();
    endResetModel();
}

int SlideshowListModel::addImage(const SlideshowImage &image)
{
    if (!m_currentSlideshow)
        return -1;

    int index = m_currentSlideshow->addImage(image);
    emit dataChanged(m_currentSlideshowIndex, m_currentSlideshowIndex);
    return index;
}

void SlideshowListModel::removeImage(const QModelIndex &index)
{
    if (!m_currentSlideshow)
        return;

    m_currentSlideshow->removeImage(index.row());
    emit dataChanged(m_currentSlideshowIndex, m_currentSlideshowIndex);
}

bool SlideshowListModel::setCurrentSlideshow(const QModelIndex &index)
{
    if (!index.isValid() || index.row() >= m_slideshowList.count())
        return false;

    m_currentSlideshow = &m_slideshowList[index.row()];
    m_currentSlideshowIndex = index;
    return true;
}
