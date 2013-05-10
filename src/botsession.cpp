/*
 * Copyright (C) 2008-2013 The Communi Project
 *
 * This example is free, and not covered by the LGPL license. There is no
 * restriction applied to their modification, redistribution, using and so on.
 * You can study them, modify them, use them in your own program - either
 * completely or partially.
 */

#include "botsession.h"
#include <Communi/IrcCommand>
#include <Communi/IrcMessage>
#include <QtCore/QTimer>
#include <QDebug>
#include "modules/botmodule.h"


BotSession::BotSession(QObject* parent) : IrcSession(parent), out(stdout)
{
    connect(this, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(this, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

	connect(this, SIGNAL(messageReceived(IrcMessage*)), this, SLOT(onMessageReceived(IrcMessage*)));

}

void BotSession::loadModule(const QString& moduleName) {
	const QMetaObject* metaObject = BotModule::metaObjectFor(moduleName);
	if (metaObject) {
		BotModule* module = qobject_cast<BotModule*>(metaObject->newInstance(Q_ARG(BotSession*, this)));
		m_modules.append(module);
	} else {
		out << moduleName << " is not a known module. Ignoring it." << endl;
	}
}

QList< BotModule* > BotSession::modules() const
{
	return m_modules;
}


QStringList BotSession::channels() const
{
	return m_channels;
}

void BotSession::setChannels(const QStringList& channels)
{
	m_channels = channels;

}

QString BotSession::nickservPassword() const
{
	return m_nickservPassword;
}

void BotSession::setNickservPassword(const QString& password)
{
	m_nickservPassword = password;
}


void BotSession::onConnected()
{
	out << "Connected." << endl;
	if (!m_nickservPassword.isEmpty()) {
		sendCommand(IrcCommand::createMessage(QString("NickServ"), QString("identify ") + m_nickservPassword));
		out << "Trying to auth with nickserv..." << endl;
	} else {
		foreach (QString channel, m_channels)
		{
			sendCommand(IrcCommand::createJoin(channel));
			out << "Entering " << channel << "." << endl;
		}
	}

}

void BotSession::onDisconnected()
{
	out << "Disconnected. Reconnecting in 4 seconds..." << endl;
	close();
	QTimer::singleShot(4000, this, "open");
}


void BotSession::onMessageReceived(IrcMessage* message)
{
	if (message->type() == IrcMessage::Private) {
		IrcPrivateMessage* msg = static_cast<IrcPrivateMessage*>(message);
		qDebug() << "[PM] <" << msg->sender().name() << ">" << msg->message();
	} else if (message->type() == IrcMessage::Notice) {
		IrcNoticeMessage* msg = static_cast<IrcNoticeMessage*>(message);
		qDebug() << "[Notice]" << msg->message();
		if (msg->message().startsWith("You are now identified for ")) {
			foreach (QString channel, m_channels)
			{
				sendCommand(IrcCommand::createJoin(channel));
				out << "Entering " << channel << "." << endl;
			}
		}
	} else if (message->type() == IrcMessage::Error) {
		IrcErrorMessage* msg = static_cast<IrcErrorMessage*>(message);
		out << "[Error] " << msg->error() << endl;
	}
}

void BotSession::sendMessage(const QString& target, const QString& message)
{
	sendCommand(IrcCommand::createMessage(target, message));
}


void BotSession::sendAction(const QString& target, const QString& message)
{
	sendCommand(IrcCommand::createCtcpAction(target, message));
}


#include "botsession.moc"