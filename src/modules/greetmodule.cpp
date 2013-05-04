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


#include "greetmodule.h"
#include <QTextStream>

GreetModule::GreetModule(BotSession* session) : BotModule(session)
{
	connect(session, SIGNAL(messageReceived(IrcMessage*)), this, SLOT(onMessageReceived(IrcMessage*)));

}

GreetModule::~GreetModule()
{

}

void GreetModule::onMessageReceived(IrcMessage* message) {
	if (message->type() == IrcMessage::Join) {
			IrcJoinMessage* msg = static_cast<IrcJoinMessage*>(message);
			QString name = msg->sender().name();
			if (name != session->nickName()) {
				QString greet = QString("Hi %1! Welcome in %2.").arg(name).arg(msg->channel());
				session->sendMessage(msg->channel(), greet);
				out << "Greeted " << name << "." << endl;
			} else {
				QString enter = QString("enters %1 and fades to the background, immediatly available when somebody needs his services.").arg(msg->channel());
				session->sendMessage(msg->channel(), enter);
				out << "Joined " << msg->channel() << "." << endl;
			}
	} else if (message->type() == IrcMessage::Part) {
			IrcPartMessage* msg = static_cast<IrcPartMessage*>(message);
			QString name = msg->sender().name();
			QString bye = QString(" is shocked that %1 left %2 in favour of another channel.")
			.arg(name).arg(msg->channel());
			session->sendAction(msg->channel(), bye);
			out << "Said good-bye to " << name << "." << endl;
			/*
	} else if (message->type() == IrcMessage::Quit) {
			IrcQuitMessage* msg = static_cast<IrcQuitMessage*>(message);
			QString name = msg->sender().name();
			QString bye = QString(" is a little sad that %1 left.").arg(name);
			bot->sendCommand(IrcCommand::createCtcpAction(bot->channel(), bye));
			out << "Said good-bye to " << name << "." << endl;
			*/
	}
}

QString GreetModule::helpText() const
{
    return QString("GreetModule: Comments joins and parts.");
}


#include "greetmodule.moc"