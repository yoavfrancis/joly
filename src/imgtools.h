/***************************************
 * Joly. Connect your web and your computer in the one place.
 * Copyright (C) 2012-2013 Ivan Akulov <gxoptg@gmail.com>
 *
 * This file is the part of Joly.
 *
 * Joly is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Joly is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Joly. If not, see <http://www.gnu.org/licenses/>.
 **************************************/

#ifndef IMGTOOLS_H
#define IMGTOOLS_H

#include <QPixmap>

namespace ImgTools
{
    // scaling the image to the size where the smaller side of it equals "side"
    inline void scaleToSize(QPixmap *pixmap, int side) {
        if (pixmap->width() > pixmap->height()) {
            *pixmap = pixmap->scaledToHeight(side);
        } else {
//            qDebug() <<
            *pixmap = pixmap->scaledToWidth(side);
        }
    }

    // cropping center square with side == "squareSide"
    inline void cropCenterSquare(QPixmap *pixmap, int squareSide) {
        double heightCenter = pixmap->height()/2;
        double widthCenter = pixmap->width()/2;

        *pixmap = pixmap->copy(widthCenter - squareSide/2, heightCenter - squareSide/2, squareSide, squareSide);
    }
}

#endif // IMGTOOLS_H
