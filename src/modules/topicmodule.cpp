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


#include "topicmodule.h"

TopicModule::TopicModule(BotSession* session) : BotModule(session)
{
	connect(session, SIGNAL(messageReceived(IrcMessage*)), this, SLOT(onMessageReceived(IrcMessage*)));
}

TopicModule::~TopicModule()
{

}

void TopicModule::onMessageReceived(IrcMessage* message)
{
	if (message->type() == IrcMessage::Private) {
		IrcPrivateMessage* msg = static_cast<IrcPrivateMessage*>(message);

		if (msg->target().compare(session->nickName(), Qt::CaseInsensitive) != 0) {
			// message is from channel
			if (msg->message().startsWith(session->nickName(), Qt::CaseInsensitive)) {
				// message is for bot
				QStringList parts = msg->message().split(" ", QString::SkipEmptyParts);
				if (parts.size() >= 3) {
					parts.removeFirst();

					if (parts.first() == "topic") {
						parts.removeFirst();
						out << "Setting topic for " << msg->target() << " to " << parts.join(" ") << endl;
						session->sendCommand(IrcCommand::createTopic(msg->target(), parts.join(" ")));
					}
				}
			}
		}
	}

}

QString TopicModule::helpText() const
{
	return QString("TopicModule: Set topic with '%1: topic <topic>'").arg(session->nickName());
}


#include "topicmodule.moc"