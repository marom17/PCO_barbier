#ifndef CLIENTCHEVEUX_H
#define CLIENTCHEVEUX_H
#include <QThread>
#include <global.h>

class ClientCheveux : public QThread
{
public:
    ClientCheveux();
    void run();
    ~ClientCheveux();

private:
    int attentePousseCheveux;
};

#endif // CLIENTCHEVEUX_H
