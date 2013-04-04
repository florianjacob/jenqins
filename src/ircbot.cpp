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
#include <Communi/IrcCommand>
#include <Communi/IrcMessage>


IrcBot::IrcBot(QObject* parent) : IrcSession(parent), out(stdout)
{
    connect(this, SIGNAL(connected()), this, SLOT(onConnected()));

	GreetModule* greeter = new GreetModule(this);
	connect(this, SIGNAL(messageReceived(IrcMessage*)), greeter, SLOT(onMessageReceived(IrcMessage*)));

	MessageModule* messenger = new MessageModule(this);
	connect(this, SIGNAL(messageReceived(IrcMessage*)), messenger, SLOT(onMessageReceived(IrcMessage*)));

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
		sendCommand(IrcCommand::createMessage(QString("nickserv"), QString("identify ") + m_nickservPassword));
	}
    sendCommand(IrcCommand::createJoin(m_channel));
    out << "Verbunden. Betrete " << m_channel << "." << endl;

}

#include "ircbot.moc"