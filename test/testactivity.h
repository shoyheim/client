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
        const QString markup1 = "<file id=\"12\" link=\"http://link/to/file\">a_file</file> was born";

        ActivityFetcherV2 f;

        QVERIFY( QLatin1String("a_file was born") ==  f.removeMarkup(markup1));

    }
};

#endif
