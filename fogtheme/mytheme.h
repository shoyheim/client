/*
 * Copyright (C) by Daniel Molkentin <danimo@owncloud.com>, ownCloud Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#ifndef MY_THEME_H
#define MY_THEME_H

#include "theme.h"

#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QIcon>
#include <QApplication>


namespace OCC {

class MyTheme : public Theme
{
public:
    MyTheme()
        : Theme() {};

    QIcon folderDisabledIcon() const Q_DECL_OVERRIDE { return themeIcon( QLatin1String("state-error" ) ); }
    QString configFileName() const Q_DECL_OVERRIDE  { return QLatin1String( "skylagring.cfg" ); }

    /*
     * If you changed file names in /replacements/mytheme/theme/colored
     * you will have to do that here also.
     */
    QIcon applicationIcon() const Q_DECL_OVERRIDE {
        return themeIcon( QLatin1String("InternSky-icon" ) );
    }

    /*
     * If you have your own help page change the URL below.
     * example: return QLatin1String( "http://www.yourwebsite.com/support" );
     */
    virtual QString helpUrl() const {
        return QString::fromLatin1("http://doc.owncloud.org/desktop/%1.%2/").arg(MIRALL_VERSION_MAJOR).arg(MIRALL_VERSION_MINOR);
    }

    /*
     * If you have your own URL for updates, change it below.
     * example: return QLatin1String( "http://www.yourwebsite.com/updates/" );
     */
    virtual QString updateCheckUrl() const {
        return QLatin1String( "https://deploy.fjit.no/skylagring/client/" );
    }

    /*
     * Enter the color of the header title in the setup wizard.
     * example: return QColor("#FFFFFF");
     */
	virtual QColor wizardHeaderTitleColor() const
	{              
	    return QColor( QLatin1String("#D36D2F"));
	}

    /*
     * Enter the background color of the header in the setup wizard.
     * example: return QColor("#10283F");
     */
	virtual QColor wizardHeaderBackgroundColor() const
	{
            return QColor( QLatin1String("#000000"));
	}

    /*
     * The logo you want to be seen in the header of the setup wizard..
     * example: return QPixmap(":/mirall/theme/colored/wizard_logo.png");
     */
    QIcon wizardHeaderLogo() const override
	{
            return QPixmap( QLatin1String(":/fogtheme/theme/colored/wizard_logo.png"));
    }

    virtual QString about() const
    {
        QString devString;
        devString = QLatin1String("<p>Version %2. For more information visit <a href=\"%3\">%4</a></p> <p><small>By Serit Fjordane IT AS</small></p> <p>Copyright Serit Fjordane IT</p> <p>Licensed under the GNU General Public License (GPL) Version 2.0<br/></p>").arg(MIRALL_VERSION_STRING).arg("https://" MIRALL_STRINGIFY(APPLICATION_DOMAIN)).arg(MIRALL_STRINGIFY(APPLICATION_DOMAIN));

        return devString;
    }

	QString overrideServerUrl() const
	{
	    return QLatin1String("");
	}


};

} // namespace OCC

#endif // MY_THEME_H
