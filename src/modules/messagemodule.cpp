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


#include "messagemodule.h"
#include <QTime>

MessageModule::MessageModule(IrcBot* bot): BotModule(bot)
{

}

MessageModule::~MessageModule()
{

}


void MessageModule::onMessageReceived(IrcMessage* message)
{
	if (message->type() == IrcMessage::Private) {
		IrcPrivateMessage* msg = static_cast<IrcPrivateMessage*>(message);

		// is the message not a direct message => a message from a channel?
		if (msg->target().compare(bot->nickName(), Qt::CaseInsensitive) != 0) {
			if (messages.contains(msg->sender().name())) {
				out << "replaying messages for " << msg->sender().name() << ".." << endl;
				foreach (QString message, messages.values(msg->sender().name()))
				{
					bot->sendCommand(IrcCommand::createMessage(msg->target(), message));
				}
				messages.remove(msg->sender().name());
			}

			if (msg->message().startsWith(bot->nickName(), Qt::CaseInsensitive)) {
				QStringList parts = msg->message().split(" ", QString::SkipEmptyParts);
				if (parts.size() >= 4) {
					parts.removeFirst();

					if (parts.first() == "memo") {
						parts.removeFirst();
						QString receiver = parts.first();
						parts.removeFirst();
						if (receiver == bot->nickName()) {
							bot->sendCommand(IrcCommand::createMessage(msg->target(),
																	   QString("You can't leave memos for me..")));
						} else if (receiver == msg->sender().name()) {
							bot->sendCommand(IrcCommand::createMessage(msg->target(),
																	   QString("You can't leave memos for yourself.")));
						} else {
							messages.insertMulti(receiver,
												 QString("%1: [%2] <%3/%4> %5")
							.arg(receiver).arg(QTime::currentTime().toString("HH:mm"))
							.arg(msg->target()).arg(msg->sender().name()).arg(parts.join(" ")));
							bot->sendCommand(IrcCommand::createMessage(msg->target(),
																	   QString("%1: Memo for %2 recorded.").arg(msg->sender().name()).arg(receiver)));
						}
					}
				}
			}
		}

	} else if (message->type() == IrcMessage::Join || message->type() == IrcMessage::Nick) {
		if (messages.contains(message->sender().name())) {
			out << "Notifying " << message->sender().name() << " about his messages." << endl;
			bot->sendCommand(IrcCommand::createMessage(message->sender().name(), QString("You have memos. Speak publicly in a channel to retreive them.")));
		}
	}
}


#include "messagemodule.moc"