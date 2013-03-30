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
#include "ircbot.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    IrcBot bot;
    QTextStream qout(stdout);

    QSettings settings("settings.ini", QSettings::IniFormat);
    bot.setHost(settings.value("host", "irc.freenode.net").toString());
    bot.setPort(settings.value("port", 6667).toInt());
    bot.setUserName(settings.value("username", "CommuniBot").toString());
    bot.setNickName(settings.value("nickname", "CommuniBot").toString());
    bot.setRealName(settings.value("realname", "CommuniBot").toString());
    bot.setChannel(settings.value("channel", "#ceylon").toString());

    bot.open();
    qout << "Verbinde als: " << bot.nickName() << "@" << bot.host() << ":" << bot.port() << "..." << endl;
    return app.exec();
}
