/*
 * Copyright (C) 2008-2013 The Communi Project
 *
 * This example is free, and not covered by the LGPL license. There is no
 * restriction applied to their modification, redistribution, using and so on.
 * You can study them, modify them, use them in your own program - either
 * completely or partially.
 */

#include "ircbot.h"
#include "modules/greetmodule.h"
#include "modules/echomodule.h"
#include "modules/messagemodule.h"
#include "modules/topicmodule.h"
#include <Communi/IrcCommand>
#include <Communi/IrcMessage>


IrcBot::IrcBot(QObject* parent) : IrcSession(parent), out(stdout)
{
    connect(this, SIGNAL(connected()), this, SLOT(onConnected()));

	/*
	GreetModule* greeter = new GreetModule(this);
	connect(this, SIGNAL(messageReceived(IrcMessage*)), greeter, SLOT(onMessageReceived(IrcMessage*)));
	*/

	connect(this, SIGNAL(messageReceived(IrcMessage*)), this, SLOT(onMessageReceived(IrcMessage*)));

	MessageModule* messenger = new MessageModule(this);
	connect(this, SIGNAL(messageReceived(IrcMessage*)), messenger, SLOT(onMessageReceived(IrcMessage*)));

	TopicModule* topic = new TopicModule(this);
	connect(this, SIGNAL(messageReceived(IrcMessage*)), topic, SLOT(onMessageReceived(IrcMessage*)));

	/*
	EchoModule* echoer = new EchoModule(this);
	connect(this, SIGNAL(messageReceived(IrcMessage*)), echoer, SLOT(onMessageReceived(IrcMessage*)));
	*/
}

QString IrcBot::channel() const
{
	return m_channel;
}

void IrcBot::setChannel(const QString& channel)
{
	m_channel = channel;

}

QString IrcBot::nickservPassword() const
{
	return m_nickservPassword;
}

void IrcBot::setNickservPassword(const QString& password)
{
	m_nickservPassword = password;
}


void IrcBot::onConnected()
{
	if (!m_nickservPassword.isEmpty()) {
		sendCommand(IrcCommand::createMessage(QString("NickServ"), QString("identify ") + m_nickservPassword));
		out << "tried to auth with nickserv." << endl;
	} else {
		sendCommand(IrcCommand::createJoin(m_channel));
		out << "Verbunden. Betrete " << m_channel << "." << endl;
	}

}

void IrcBot::onMessageReceived(IrcMessage* message)
{
	if (message->type() == IrcMessage::Notice) {
		IrcNoticeMessage* msg = static_cast<IrcNoticeMessage*>(message);
		out << "[Notice] " << msg->message() << endl;
		if (msg->message().startsWith("You are now identified for ")) {
			sendCommand(IrcCommand::createJoin(m_channel));
			out << "Authentifiziert. Betrete " << m_channel << "." << endl;
		}
	} else if (message->type() == IrcMessage::Private) {
		IrcPrivateMessage* msg = static_cast<IrcPrivateMessage*>(message);
		out << "[PM] <" << msg->sender().name() << " > " << msg->message() << endl;
	} else if (message->type() == IrcMessage::Error) {
		IrcErrorMessage* msg = static_cast<IrcErrorMessage*>(message);
		out << "[Error] " << msg->error() << endl;

	}
}


#include "ircbot.moc"