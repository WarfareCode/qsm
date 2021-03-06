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

#include "imageloaderthread.h"

#include "imageloader.h"

ImageLoaderThread::ImageLoaderThread(ImageLoader *loader, QObject *parent) :
    QThread(parent), m_loader(loader)
{
    Q_ASSERT(loader);
}

ImageLoaderThread::~ImageLoaderThread()
 {
    if (m_loader->autoDelete())
        delete m_loader;
}

void ImageLoaderThread::run()
{
    m_loader->run();
}
