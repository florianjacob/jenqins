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

GreetModule::GreetModule(BotConnection* connection) : BotModule(connection)
{
	connect(connection, SIGNAL(messageReceived(IrcMessage*)), this, SLOT(onMessageReceived(IrcMessage*)));
	qDebug() << "GreetModule connected.";

}

GreetModule::~GreetModule()
{

}

void GreetModule::onMessageReceived(IrcMessage* message) {
	if (message->type() == IrcMessage::Join) {
			IrcJoinMessage* msg = static_cast<IrcJoinMessage*>(message);

			if (msg->nick() != connection->nickName()) {
				QString greet = QString("Hi %1! Welcome in %2.").arg(msg->nick()).arg(msg->channel());
				connection->sendMessage(msg->channel(), greet);
				qDebug() << "Greeted" << msg->nick() << ".";
			} else {
				QString enter = QString("enters %1 and fades to the background, immediatly available when somebody needs his services.").arg(msg->channel());
				connection->sendMessage(msg->channel(), enter);
				qDebug() << "Commented join in " << msg->channel() << ".";
			}
	} else if (message->type() == IrcMessage::Part) {
			IrcPartMessage* msg = static_cast<IrcPartMessage*>(message);

			QString bye = QString(" is shocked that %1 left %2 in favour of another channel.")
			.arg(msg->nick()).arg(msg->channel());
			connection->sendAction(msg->channel(), bye);
			qDebug() << "Said good-bye to" << msg->nick() << ".";
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