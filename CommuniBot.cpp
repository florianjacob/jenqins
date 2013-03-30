#include "CommuniBot.h"

#include <QTimer>
#include <iostream>

CommuniBot::CommuniBot()
{
    QTimer* timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), SLOT(output()) );
    timer->start( 1000 );
}

CommuniBot::~CommuniBot()
{}

void CommuniBot::output()
{
    std::cout << "Hello World!" << std::endl;
}

#include "CommuniBot.moc"
