/*
 *    <one line to give the program's name and a brief idea of what it does.>
 *    Copyright (C) 2013  Florian Jacob <fjacob@lavabit.com>
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "echomodule.h"

EchoModule::EchoModule(BotSession* session) : BotModule(session)
{
	connect(session, SIGNAL(messageReceived(IrcMessage*)), this, SLOT(onMessageReceived(IrcMessage*)));
}

EchoModule::~EchoModule()
{

}

void EchoModule::onMessageReceived(IrcMessage* message)
{
	if (message->type() == IrcMessage::Private) {
		IrcPrivateMessage* msg = static_cast<IrcPrivateMessage*>(message);
		if (!msg->target().compare(session->nickName(), Qt::CaseInsensitive)) {
			// echo private message
			session->sendMessage(msg->sender().name(), msg->message());
		} else if (msg->message().startsWith(session->nickName(), Qt::CaseInsensitive)) {
			// echo prefixed channel message
			QString reply = msg->message().mid(msg->message().indexOf(" "));
			session->sendMessage(msg->target(), msg->sender().name() + ":" + reply);
		}
	}

}
