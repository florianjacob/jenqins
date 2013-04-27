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
#include <Communi/IrcMessage>
#include <QTextStream>
#include <QStringList>

class BotModule;

class BotSession : public IrcSession
{
    Q_OBJECT
    Q_PROPERTY(QStringList channels READ channels WRITE setChannels)
    Q_PROPERTY(QString nickservPassword READ nickservPassword WRITE setNickservPassword)

public:
    BotSession(QObject* parent = 0);

    QStringList channels() const;
    void setChannels(const QStringList& channel);

	QString nickservPassword() const;
	void setNickservPassword(const QString& password);
	void loadModule(const QString& module);

	void sendMessage(const QString& target, const QString& message);
	void sendAction(const QString& target, const QString& message);

private slots:
    void onConnected();
	void onMessageReceived(IrcMessage* message);

private:
    QStringList m_channels;
    QString m_nickservPassword;
    QTextStream out;
	QList<BotModule*> modules;
};

#endif // IRCBOT_H
