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

#ifndef ACTIVITY_H
#define ACTIVITY_H

namespace OCC {

class AccountState;
class Account;
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
    QString   _user;
    QString   _icon;

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
    virtual void startToFetch(AccountState* s);

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
    QString removeMarkup( const QString& str );

public slots:
    virtual void startToFetch(AccountState* s);

private slots:
    virtual void slotActivitiesReceived(const QVariantMap& json, int statusCode);

private:
    bool parseActionString( Activity *activity, const QString& subject, const QVariantList& params);

    ActivityList fetchFromDb(const QString &accountId );
    int lastSeenId();

};

}
#endif // ACTIVITY_H
