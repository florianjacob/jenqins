#ifndef CommuniBot_H
#define CommuniBot_H

#include <QtCore/QObject>

class CommuniBot : public QObject
{
Q_OBJECT
public:
    CommuniBot();
    virtual ~CommuniBot();
private slots:
    void output();
};

#endif // CommuniBot_H
