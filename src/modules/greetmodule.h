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


#ifndef GREETMODULE_H
#define GREETMODULE_H
#include "botmodule.h"


class GreetModule : public BotModule
{
	Q_OBJECT

public:
    Q_INVOKABLE explicit GreetModule(BotSession* session);
    virtual ~GreetModule();

	virtual QString helpText() const;

public slots:
	virtual void onMessageReceived(IrcMessage* message);
};

#endif // GREETMODULE_H
