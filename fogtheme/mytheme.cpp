/*
 * Copyright (C) by Klaas Freitag <freitag@owncloud.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#include "mytheme.h"

#include <QString>
#include <QVariant>
#ifndef TOKEN_AUTH_ONLY
#include <QPixmap>
#include <QIcon>
#include <QStyle>
#include <QApplication>
#endif
#include <QCoreApplication>
#include <QDebug>

#include "version.h"
#include "config.h"

namespace OCC {

myTheme::myTheme() :
    Theme()
{
    // qDebug() << " ** running fjit theme!";
}

QString myTheme::configFileName() const
{
    return QLatin1String("skylagring.cfg");
}

QString myTheme::about() const
{
    QString vendor = QStringLiteral(APPLICATION_VENDOR);
    // Ideally, the vendor should be "ownCloud GmbH", but it cannot be changed without
    // changing the location of the settings and other registery keys.
    if (vendor == QLatin1String("ownCloud")) {
        vendor = QStringLiteral("ownCloud GmbH");
    }
    return tr("<p>Version %1. For more information visit <a href=\"%2\">https://%3</a></p>"
              "<p>For known issues and help, please visit: <a href=\"https://central.owncloud.org/c/desktop-client\">https://central.owncloud.org</a></p>"
              "<p><small>By Klaas Freitag, Daniel Molkentin, Olivier Goffart, Markus Götz, "
              " Jan-Christoph Borchardt, Thomas Müller, Dominik Schmidt, Michael Stingl, Hannah von Reth, and others.</small></p>"
              "<p>Copyright ownCloud GmbH</p>"
              "<p>Distributed by %4 and licensed under the GNU General Public License (GPL) Version 2.0.<br/>"
              "%5 and the %5 logo are registered trademarks of %4 in the "
              "United States, other countries, or both.</p>"
              "<p><small>%6</small></p>")
        .arg(Utility::escape(version()),
            Utility::escape(QStringLiteral("https://" MIRALL_STRINGIFY(APPLICATION_DOMAIN))),
            Utility::escape(QStringLiteral(MIRALL_STRINGIFY(APPLICATION_DOMAIN))),
            Utility::escape(vendor),
            Utility::escape(appNameGUI()),
            aboutVersions(Theme::VersionFormat::RichText));

}

#ifndef TOKEN_AUTH_ONLY
QIcon myTheme::trayFolderIcon( const QString& ) const
{
    QPixmap fallback = qApp->style()->standardPixmap(QStyle::SP_FileDialogNewFolder);
    return QIcon::fromTheme("folder", fallback);
}

QIcon myTheme::applicationIcon( ) const
{
    return themeIcon( QLatin1String("skylagring-icon") );
}


QVariant myTheme::customMedia(Theme::CustomMediaType type)
{
    if (type == Theme::oCSetupTop) {
        // return QCoreApplication::translate("ownCloudTheme",
        //                                   "If you don't have an ownCloud server yet, "
        //                                   "see <a href=\"https://owncloud.com\">owncloud.com</a> for more info.",
        //                                   "Top text in setup wizard. Keep short!");
        return QVariant();
    } else {
        return QVariant();
    }
}

#endif

QString myTheme::helpUrl() const
{
    return QString::fromLatin1("https://doc.owncloud.org/desktop/%1.%2/").arg(MIRALL_VERSION_MAJOR).arg(MIRALL_VERSION_MINOR);
}

#ifndef TOKEN_AUTH_ONLY
QColor myTheme::wizardHeaderBackgroundColor() const
{
    return QColor("#D36D2F");
}

QColor myTheme::wizardHeaderTitleColor() const
{
    return QColor("#000000");
}

QPixmap myTheme::wizardHeaderLogo() const
{
    return QPixmap(hidpiFileName(":/client/theme/colored/wizard_logo.png"));
}
#endif

QString myTheme::appName() const
{
    return QLatin1String("InternSky");
}

QString myTheme::appNameGUI() const
{
    return QLatin1String("Serit Fjordane IT Skylagring");
}


}

