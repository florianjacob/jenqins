/*
 * Copyright (C) 2008-2013 The Communi Project
 *
 * This example is free, and not covered by the LGPL license. There is no
 * restriction applied to their modification, redistribution, using and so on.
 * You can study them, modify them, use them in your own program - either
 * completely or partially.
 */

#ifndef IRCBOT_H
#define IRCBOT_H

#include <Communi/IrcSession>
#include <QTextStream>

class IrcBot : public IrcSession
{
    Q_OBJECT
    Q_PROPERTY(QString channel READ channel WRITE setChannel)

public:
    IrcBot(QObject* parent = 0);

    QString channel() const;
    void setChannel(const QString& channel);

private slots:
    void onConnected();

private:
    QString m_channel;
    QTextStream out;
};

#endif // IRCBOT_H
