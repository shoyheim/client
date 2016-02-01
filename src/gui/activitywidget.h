/*
 * Copyright (C) by Klaas Freitag <freitag@owncloud.com>
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

#ifndef ACTIVITYWIDGET_H
#define ACTIVITYWIDGET_H

#include <QDialog>
#include <QDateTime>
#include <QLocale>
#include <QAbstractListModel>
#include <QSortFilterProxyModel>

#include "progressdispatcher.h"
#include "owncloudgui.h"
#include "account.h"

#include "ui_activitywidget.h"

class QPushButton;
class QProgressIndicator;

namespace OCC {

class Account;
class AccountStatusPtr;
class ProtocolWidget;

namespace Ui {
  class ActivityWidget;
}
class Application;

/**
 * @brief ActivityFile Structure
 * @ingroup gui
 *
 * contains information about a file of an activity.
 */
class ActivityFile
{
public:
    enum FileType {Unknown, File, Directory};
    ActivityFile();
    ActivityFile( const QString& file );

    void setType( FileType type );
    QString relativePath() const;
    QString fullPath( const QString _accountName ) const;

private:
    QString _relFileName;
    FileType _type;
};

/**
 * @brief Activity Structure
 * @ingroup gui
 *
 * contains all the information describing a single activity.
 */

class Activity
{
public:
    void addFile( const QString& file );
    void addDirectory( const QString& dir );

    QVector<ActivityFile> files();

    qlonglong _id;
    QString   _subject;
    QString   _message;
    QUrl      _link;
    QDateTime _dateTime;
    QString   _accName;

private:
    QVector<ActivityFile> _files;

    /**
     * @brief Sort operator to sort the list youngest first.
     * @param val
     * @return
     */
    bool operator<( const Activity& val ) const {
        return _dateTime.toMSecsSinceEpoch() > val._dateTime.toMSecsSinceEpoch();
    }

};

/**
 * @brief The ActivityList
 * @ingroup gui
 *
 * A QList based list of Activities
 */
class ActivityList:public QList<Activity>
{
public:
    ActivityList();
    void setAccountName( const QString& name );
    QString accountName() const;
    int lastId() const;

private:
    QString _accountName;
    int _lastId;
};


class ActivityFetcher : public QObject
{
    Q_OBJECT
public:
    explicit ActivityFetcher();

public slots:
    virtual void slotFetch(AccountState* s);

private slots:
    virtual void slotActivitiesReceived(const QVariantMap& json, int statusCode);

signals:
    void newActivityList( ActivityList list );
    void accountWithoutActivityApp(AccountState*);

private:

};

class ActivityFetcherV2 : public ActivityFetcher
{
    Q_OBJECT
public:
    explicit ActivityFetcherV2();

public slots:
    virtual void slotFetch(AccountState* s);

private slots:
    virtual void slotActivitiesReceived(const QVariantMap& json, int statusCode);

private:
    bool parseActionString( Activity *activity, const QString& subject, const QVariantList& params);
    ActivityList fetchFromDb(const QString &accountId );
    int lastSeenId();

};

/**
 * @brief The ActivityListModel
 * @ingroup gui
 *
 * Simple list model to provide the list view with data.
 */
class ActivityListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ActivityListModel(QWidget *parent=0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

    bool canFetchMore(const QModelIndex& ) const Q_DECL_OVERRIDE;
    void fetchMore(const QModelIndex&) Q_DECL_OVERRIDE;

    ActivityList activityList();

public slots:
    void slotRefreshActivity(AccountState* ast);
    void slotRemoveAccount( AccountState *ast );

signals:
    void accountWithoutActivityApp(AccountState* ast);

private slots:
    void slotAddNewActivities(const ActivityList& list);

private:
    void startFetchJob(AccountState* s);
    Activity findItem(int indx) const;

    QList<ActivityList> _activityLists;
    QSet<AccountState*> _currentlyFetching;
};

class ActivitySortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    ActivitySortProxyModel(QObject *parent = 0);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;

};

/**
 * @brief The ActivityWidget class
 * @ingroup gui
 *
 * The list widget to display the activities, contained in the
 * subsequent ActivitySettings widget.
 */

class ActivityWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ActivityWidget(QWidget *parent = 0);
    ~ActivityWidget();
    QSize sizeHint() const Q_DECL_OVERRIDE { return ownCloudGui::settingsDialogSize(); }
    void storeActivityList(QTextStream &ts);

public slots:
    void slotOpenFile(QModelIndex indx);
    void slotRefresh(AccountState* ptr);
    void slotRemoveAccount( AccountState *ptr );
    void slotAccountWithoutActivityApp(AccountState *ast);

signals:
    void guiLog(const QString&, const QString&);
    void copyToClipboard();
    void rowsInserted();

private:
    void showLabels();
    QString timeString(QDateTime dt, QLocale::FormatType format) const;
    Ui::ActivityWidget *_ui;
    QPushButton *_copyBtn;

    QSet<QString> _accountsWithoutActivities;

    ActivitySortProxyModel *_model;
};


/**
 * @brief The ActivitySettings class
 * @ingroup gui
 *
 * Implements a tab for the settings dialog, displaying the three activity
 * lists.
 */
class ActivitySettings : public QWidget
{
    Q_OBJECT
public:
    explicit ActivitySettings(QWidget *parent = 0);
    ~ActivitySettings();
    QSize sizeHint() const Q_DECL_OVERRIDE { return ownCloudGui::settingsDialogSize(); }

public slots:
    void slotRefresh( AccountState* ptr );
    void slotRemoveAccount( AccountState *ptr );

    void slotCopyToClipboard();

signals:
    void guiLog(const QString&, const QString&);

private:
    bool event(QEvent* e) Q_DECL_OVERRIDE;

    QTabWidget *_tab;
    ActivityWidget *_activityWidget;
    ProtocolWidget *_protocolWidget;
    QProgressIndicator *_progressIndicator;

};

}
#endif // ActivityWIDGET_H
