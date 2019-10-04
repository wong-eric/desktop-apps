/*
 * (c) Copyright Ascensio System SIA 2010-2019
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at 20A-12 Ernesta Birznieka-Upisha
 * street, Riga, Latvia, EU, LV-1050.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
*/

#include "csvgpushbutton.h"

#include <QtSvg>
#include <QSvgRenderer>
#include <QPainter>
#include <QDebug>

CSVGPushButton::CSVGPushButton(QWidget * parent)
    : QPushButton(parent)
{

}

void CSVGPushButton::setIcon(const QByteArray& svgstr)
{
    m_svglayout = svgstr;
    updateIcon();
}

void CSVGPushButton::setIconSize(const QSize& size)
{
    QPushButton::setIconSize(size);
    updateIcon();
}

void CSVGPushButton::setDisabled(bool status)
{
    QPushButton::setDisabled(status);
    updateIcon();
}

void CSVGPushButton::updateIcon()
{
    if ( !m_svglayout.isEmpty() ) {
        QSize size = iconSize();
        QImage img(size, QImage::Format_ARGB32);
        img.fill(Qt::transparent);
        QPixmap pixmap = QPixmap::fromImage(img, Qt::NoFormatConversion);
qDebug() << "update icon: " << size;
        QPainter painter(&pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        QSvgRenderer r(m_svglayout);
        r.render(&painter, QRect(QPoint(0,0),size));

        if ( !isEnabled() ) {
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            painter.fillRect(pixmap.rect(), QColor(255,255,255,150));
            painter.end();
        }

        QPushButton::setIcon(QIcon(pixmap));
    }
}
