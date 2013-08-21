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


#ifndef BOTMODULE_H
#define BOTMODULE_H
#include <QObject>
#include <QMetaObject>
#include <Communi/IrcCore/IrcMessage>
#include <Communi/IrcCore/IrcCommand>
#include <QDebug>
#include "../botconnection.h"

class BotModule : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString helpText READ helpText)
	Q_DISABLE_COPY(BotModule)

public:
    explicit BotModule(BotConnection* session);
    virtual ~BotModule();
	static const QMetaObject* metaObjectFor(const QString& moduleName);

	virtual QString helpText() const = 0 ;

protected:
	BotConnection* connection;
	QTextStream out;

};

#endif // BOTMODULE_H
