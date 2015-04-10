/*
 * Copyright (C) 2008-2013 The Communi Project
 *
 * This example is free, and not covered by the LGPL license. There is no
 * restriction applied to their modification, redistribution, using and so on.
 * You can study them, modify them, use them in your own program - either
 * completely or partially.
 */

#ifndef BOTCONNECTION_H
#define BOTCONNECTION_H

#include <IrcConnection>
#include <IrcMessage>
#include <QTextStream>
#include <QStringList>
#include <QAbstractSocket>

class BotModule;

class BotConnection : public IrcConnection
{
	Q_OBJECT
	Q_PROPERTY(QStringList channels READ channels WRITE setChannels)
	Q_PROPERTY(QString nickservPassword READ nickservPassword WRITE setNickservPassword)
	Q_PROPERTY(QList<BotModule*> modules READ modules)
	Q_PROPERTY(QString dataPath READ dataPath)
	Q_DISABLE_COPY(BotConnection)

public:
	explicit BotConnection(QObject* parent = 0, const QString& dataPath = "");

	QStringList channels() const;
	void setChannels(const QStringList& channel);

	QString nickservPassword() const;
	void setNickservPassword(const QString& password);
	void loadModule(const QString& module);
	QList<BotModule*> modules() const;

	void sendMessage(const QString& target, const QString& message);
	void sendAction(const QString& target, const QString& message);

	QString dataPath() const;

private slots:
	void onConnected();
	void onDisconnected();
	void onSocketError(QAbstractSocket::SocketError error);
	void onSocketStateChanged(QAbstractSocket::SocketState socketState);
	void onMessageReceived(IrcMessage* message);

private:
	QStringList m_channels;
	QString m_nickservPassword;
	QTextStream out;
	QList<BotModule*> m_modules;
	QString m_dataPath;

};

#endif // IRCBOT_H
