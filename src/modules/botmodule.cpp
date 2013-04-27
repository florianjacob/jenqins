/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  Florian Jacob <fjacob@lavabit.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "botmodule.h"
#include "echomodule.h"
#include "greetmodule.h"
#include "messagemodule.h"
#include "topicmodule.h"

BotModule::BotModule(BotSession* session) : QObject(session), out(stdout)
{
	this->session = session;
}

BotModule::~BotModule()
{

}

BotModule* BotModule::createAndRegisterModule(QString module, BotSession* parent)
{
	if (module == "EchoModule") {
		return new EchoModule(parent);
	} else if (module == "GreetModule") {
		return new GreetModule(parent);
	} else if (module == "MessageModule") {
		return new MessageModule(parent);
	} else if (module == "TopicModule") {
		return new TopicModule(parent);
	} else {
		return 0;
	}
}


#include "botmodule.moc"
