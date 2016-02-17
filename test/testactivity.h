/*
 *    This software is in the public domain, furnished "as is", without technical
 *       support, and with no warranty, express or implied, as to its usefulness for
 *          any purpose.
 *          */

#ifndef MIRALL_TESTACTIVITY_H
#define MIRALL_TESTACTIVITY_H

#include <QtTest>

#include "activity.h"

using namespace OCC;

class TestActivity : public QObject
{
    Q_OBJECT

private:

public slots:

private slots:
    void init() {
        qDebug() << Q_FUNC_INFO;
    }

    void cleanup() {
    }

    void testMarkupParser1() {

        ActivityFetcherV2 f;

        QString markup = "<file id=\"12\" link=\"http://link/to/file\">a_file</file> was born";
        QVERIFY( QLatin1String("a_file was born") ==  f.removeMarkup(markup));
        
        markup = "User <user id=\"12\" displayname=\"Goofy\">goofy</user> was here!";
        QVERIFY( QLatin1String("User goofy was here!") == f.removeMarkup(markup));
        
        markup = "File <file id=\"32\">foo</file> and <file id=\"33\">bar</file>";
        QString noMarkup = f.removeMarkup(markup);
        qDebug() << "XXXX" << noMarkup;
        QVERIFY(  noMarkup == QLatin1String("File foo and bar"));
        
        markup = "These files <collection><file>foo.txt</file> <file>bar.txt</file></collection>!";
        noMarkup = f.removeMarkup(markup);
        qDebug() << "XXXX" << noMarkup;
        QVERIFY(  noMarkup == QLatin1String("These files foo.txt bar.txt!"));

    }
};

#endif
