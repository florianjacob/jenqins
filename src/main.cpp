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
#include "botconnection.h"
#include <iostream>
#include <QTime>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

#include "modules/echomodule.h"

#include <csignal>

struct CleanExit{
	CleanExit() {
		signal(SIGINT, &CleanExit::exitQt);
		signal(SIGTERM, &CleanExit::exitQt);
	}

	static void exitQt(int sig) {
		std::cout << std::endl << "shutting down..." << std::endl;
		QCoreApplication::exit(0);
	}
};

int main(int argc, char* argv[])
{
	CleanExit cleanExit;
    QCoreApplication app(argc, argv);

	QFileInfo localConfig(QDir::currentPath() + "/jenqins.ini");
	QString configPath;
	QString dataPath;
	if (localConfig.exists()) {
		qDebug() << localConfig.path() << "exists, using local folder.";
		configPath = localConfig.path();
		dataPath = localConfig.path();
	} else {
		configPath = QDir::homePath() + "/.config/jenqins.ini";
		dataPath = QDir::homePath() + "/.local/share";
		qDebug() << "using" << configPath << "and" << dataPath;
	}

	BotConnection connection(nullptr, dataPath);
	QTextStream qout(stdout);

    QSettings settings(configPath, QSettings::IniFormat);
    connection.setHost(settings.value("host", "irc.freenode.net").toString());
    connection.setPort(settings.value("port", 7070).toInt());
	if (settings.value("ssl", "true").toBool()) {
		connection.setSocket(new QSslSocket());
	}

	qsrand(QTime::currentTime().msec());
    connection.setNickName(settings.value("nickname", QString("jenqins%1").arg(qrand() % 99999)).toString());

    connection.setUserName(settings.value("username", connection.nickName()).toString());
    connection.setRealName(settings.value("realname", connection.userName()).toString());
    connection.setNickservPassword(settings.value("nickservpassword", "").toString());
	QString concatenatedChannels = settings.value("channels", "#ceylon").toString();
	QStringList channels = concatenatedChannels.split(" ", QString::SkipEmptyParts);
    connection.setChannels(channels);

	QString concatenatedModules = settings.value("modules", "topic memo help").toString();
	QStringList modules = concatenatedModules.split(" ", QString::SkipEmptyParts);
	foreach (const QString& module, modules)
	{
		connection.loadModule(module);
	}


    connection.open();
    qout << "Connecting " << (settings.value("ssl", "true").toBool() ? "securely " : "") <<  "as: " << connection.nickName() << "@" << connection.host() << ":" << connection.port() << "..." << endl;
    return app.exec();
}
