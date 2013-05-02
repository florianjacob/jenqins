/*
 * Copyright (C) 2008-2013 The Communi Project
 *
 * This example is free, and not covered by the LGPL license. There is no
 * restriction applied to their modification, redistribution, using and so on.
 * You can study them, modify them, use them in your own program - either
 * completely or partially.
 */

#include "botsession.h"
#include "modules/greetmodule.h"
#include "modules/echomodule.h"
#include "modules/messagemodule.h"
#include "modules/topicmodule.h"
#include <Communi/IrcCommand>
#include <Communi/IrcMessage>
#include <QtCore/QTimer>


BotSession::BotSession(QObject* parent) : IrcSession(parent), out(stdout)
{
    connect(this, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(this, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

	connect(this, SIGNAL(messageReceived(IrcMessage*)), this, SLOT(onMessageReceived(IrcMessage*)));

}

void BotSession::loadModule(const QString& module) {
	BotModule* m = BotModule::createAndRegisterModule(module, this);
	modules.append(m);
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
	out << "Verbunden." << endl;
	if (!m_nickservPassword.isEmpty()) {
		sendCommand(IrcCommand::createMessage(QString("NickServ"), QString("identify ") + m_nickservPassword));
		out << "tried to auth with nickserv." << endl;
	} else {
		foreach (QString channel, m_channels)
		{
			sendCommand(IrcCommand::createJoin(channel));
			out << "Betrete " << channel << "." << endl;
		}
	}

}

void BotSession::onDisconnected()
{
	out << "Disconnected. Reconnecting in 4 seconds." << endl;
	close();
	QTimer::singleShot(4000, this, "open");
}


void BotSession::onMessageReceived(IrcMessage* message)
{
	if (message->type() == IrcMessage::Private) {
		IrcPrivateMessage* msg = static_cast<IrcPrivateMessage*>(message);
		out << "[PM] <" << msg->sender().name() << " > " << msg->message() << endl;
	} else if (message->type() == IrcMessage::Notice) {
		IrcNoticeMessage* msg = static_cast<IrcNoticeMessage*>(message);
		out << "[Notice] " << msg->message() << endl;
		if (msg->message().startsWith("You are now identified for ")) {
			foreach (QString channel, m_channels)
			{
				sendCommand(IrcCommand::createJoin(channel));
				out << "Betrete " << channel << "." << endl;
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