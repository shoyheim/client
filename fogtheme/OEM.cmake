set( APPLICATION_NAME       "Intern Skylagring" )
set( APPLICATION_SHORTNAME  "InternSky" )
set( APPLICATION_EXECUTABLE "InternSky" )
set( APPLICATION_DOMAIN     "fog.fjordane-it.no" )
set( APPLICATION_VENDOR     "Serit Fjordane IT AS" )
set( APPLICATION_UPDATE_URL "https://deploy.fjit.no/skylagring/client/" CACHE STRING "URL for updater" )
set( APPLICATION_CLSID      "{2414F7C5-560F-4658-A176-2C8CC61B34CE}" )
set( APPLICATION_ICON_NAME  "InternSky" )
set( APPLICATION_VIRTUALFILE_SUFFIX "InternSky" CACHE STRING "Virtual file suffix (not including the .)")

set( THEME_CLASS            "MyTheme" )
set( APPLICATION_REV_DOMAIN "no.fjordane-it.fog.desktopclient" )
set( WIN_SETUP_BITMAP_PATH  "${OEM_THEME_DIR}/resources" )

set( CPACK_PACKAGE_ICON  "${OEM_THEME_DIR}/resources/skylagring.ico" )

set( MAC_INSTALLER_BACKGROUND_FILE "${CMAKE_SOURCE_DIR}/admin/osx/installer-background.png" CACHE STRING "The MacOSX installer background image")

set( THEME_INCLUDE          "${OEM_THEME_DIR}/mytheme.h" )
# set( APPLICATION_LICENSE    "${OEM_THEME_DIR}/license.txt )

option( WITH_CRASHREPORTER "Build crashreporter" OFF )
set( CRASHREPORTER_SUBMIT_URL "https://crash-reports.owncloud.com/submit" CACHE STRING "URL for crash reporter" )


