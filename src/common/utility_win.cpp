/*
 * Copyright (C) by Daniel Molkentin <danimo@owncloud.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#define WINVER 0x0600
#include <shlobj.h>
#include <winbase.h>
#include <windows.h>
#include <winerror.h>
#include <shlguid.h>
#include <string>
#include <QLibrary>

static const char runPathC[] = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
static const char panePathC[] = "Software\\Classes\\CLSID\\{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}\\Instance\\InitPropertyBag";
static const char panePath2C[] = "Software\\Classes\\Wow6432Node\\CLSID\\{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}\\Instance\\InitPropertyBag";

namespace OCC {

static void setupFavLink_private(const QString &folder)
{
    // First create a Desktop.ini so that the folder and favorite link show our application's icon.
    QFile desktopIni(folder + QLatin1String("/Desktop.ini"));
    if (desktopIni.exists()) {
        qCWarning(lcUtility) << desktopIni.fileName() << "already exists, not overwriting it to set the folder icon.";
    } else {
        qCInfo(lcUtility) << "Creating" << desktopIni.fileName() << "to set a folder icon in Explorer.";
        desktopIni.open(QFile::WriteOnly);
        desktopIni.write("[.ShellClassInfo]\r\nIconResource=");
        desktopIni.write(QDir::toNativeSeparators(qApp->applicationFilePath()).toUtf8());
        desktopIni.write(",0\r\n");
        desktopIni.close();

        // Set the folder as system and Desktop.ini as hidden+system for explorer to pick it.
        // https://msdn.microsoft.com/en-us/library/windows/desktop/cc144102
        DWORD folderAttrs = GetFileAttributesW((wchar_t *)folder.utf16());
        SetFileAttributesW((wchar_t *)folder.utf16(), folderAttrs | FILE_ATTRIBUTE_SYSTEM);
        SetFileAttributesW((wchar_t *)desktopIni.fileName().utf16(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
    }

    // Windows Explorer: Place under "Favorites" (Links)
    QString linkName;
    QDir folderDir(QDir::fromNativeSeparators(folder));

    /* Use new WINAPI functions */
    PWSTR path;

    if (SHGetKnownFolderPath(FOLDERID_Links, 0, NULL, &path) == S_OK) {
        QString links = QDir::fromNativeSeparators(QString::fromWCharArray(path));
        linkName = QDir(links).filePath(folderDir.dirName() + QLatin1String(".lnk"));
        CoTaskMemFree(path);
    }
    qCInfo(lcUtility) << "Creating favorite link from" << folder << "to" << linkName;
    if (!QFile::link(folder, linkName))
        qCWarning(lcUtility) << "linking" << folder << "to" << linkName << "failed!";
}

static void updateNavPanel_private(const QString &folder)
{
	// Set folder to navigation pane
	QString panePath = QLatin1String(panePathC);
	panePath.replace("{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}", QLatin1String(APPLICATION_CLSID));
	wchar_t* newPanePath = new wchar_t[panePath.length() + 1]();
	panePath.toWCharArray(newPanePath);
	QString panePath2 = QLatin1String(panePath2C);
	panePath2.replace("{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}", QLatin1String(APPLICATION_CLSID));
	wchar_t* newPanePath2 = new wchar_t[panePath2.length() + 1]();
	panePath2.toWCharArray(newPanePath2);
	QString f = folder;
	f.replace('/', '\\');
	wchar_t* path = new wchar_t[f.length() + 1]();
	f.toWCharArray(path);
	wchar_t* valuename = new wchar_t[17]();
	wcsncpy(valuename, L"TargetFolderPath", 16);

	CreateRegistryKeyValue(HKEY_CURRENT_USER, newPanePath, valuename, (PBYTE)path, sizeof(wchar_t) * f.length());
	CreateRegistryKeyValue(HKEY_CURRENT_USER, newPanePath2, valuename, (PBYTE)path, sizeof(wchar_t) * f.length());

	// memory cleanup
	delete newPanePath;
	delete path;
}


bool hasLaunchOnStartup_private(const QString &appName)
{
    QString runPath = QLatin1String(runPathC);
    QSettings settings(runPath, QSettings::NativeFormat);
    return settings.contains(appName);
}

void setLaunchOnStartup_private(const QString &appName, const QString &guiName, bool enable)
{
    Q_UNUSED(guiName);
    QString runPath = QLatin1String(runPathC);
    QSettings settings(runPath, QSettings::NativeFormat);
    if (enable) {
        settings.setValue(appName, QCoreApplication::applicationFilePath().replace('/', '\\'));
    } else {
        settings.remove(appName);
    }
}

static inline bool hasDarkSystray_private()
{
    return true;
}

} // namespace OCC
