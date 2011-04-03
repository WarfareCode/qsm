#ifndef SLIDESHOWLISTMODEL_H
#define SLIDESHOWLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "slideshow.h"

class SlideshowListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SlideshowListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Slideshow* slideshow(const QModelIndex &index) const;
    bool removeSlideshow(const QModelIndex &index);

public slots:
    void addSlideshow(const Slideshow &slideshow);
    void clear();

private:
    QList<Slideshow> m_slideshowList;
};

#endif // SLIDESHOWLISTMODEL_H
