/*
 * Copyright (C) 2008-2013 The Communi Project
 *
 * This example is free, and not covered by the LGPL license. There is no
 * restriction applied to their modification, redistribution, using and so on.
 * You can study them, modify them, use them in your own program - either
 * completely or partially.
 */

#include <QCoreApplication>
#include <QSettings>
#include <QTextStream>
#include <QSslSocket>
#include "botsession.h"
#include <iostream>
#include <QTime>

#include "modules/echomodule.h"

#include <csignal>

struct CleanExit{
	CleanExit() {
		signal(SIGINT, &CleanExit::exitQt);
		signal(SIGTERM, &CleanExit::exitQt);
	}

	static void exitQt(int sig) {
		std::cout << "exiting.." << std::endl;
		QCoreApplication::exit(0);
	}
};

int main(int argc, char* argv[])
{
	CleanExit cleanExit;
    QCoreApplication app(argc, argv);
	BotSession session;
	QTextStream qout(stdout);


    QSettings settings("settings.ini", QSettings::IniFormat);
    session.setHost(settings.value("host", "irc.freenode.net").toString());
    session.setPort(settings.value("port", 7070).toInt());
	if (settings.value("ssl", "true").toBool()) {
		session.setSocket(new QSslSocket());
	}

	qsrand(QTime::currentTime().msec());
    session.setNickName(settings.value("nickname", QString("jenqins%1").arg(qrand() % 99999)).toString());

    session.setUserName(settings.value("username", session.nickName()).toString());
    session.setRealName(settings.value("realname", session.userName()).toString());
    session.setNickservPassword(settings.value("nickservpassword", "").toString());
	QString concatenatedChannels = settings.value("channels", "#ceylon").toString();
	QStringList channels = concatenatedChannels.split(" ", QString::SkipEmptyParts);
    session.setChannels(channels);

	QString concatenatedModules = settings.value("modules", "topic memo help").toString();
	QStringList modules = concatenatedModules.split(" ", QString::SkipEmptyParts);
	foreach (const QString& module, modules)
	{
		session.loadModule(module);
	}


    session.open();
    qout << "Verbinde als: " << session.nickName() << "@" << session.host() << ":" << session.port() << "..." << endl;
    return app.exec();
}
