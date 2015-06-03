#ifndef CLIENTCHEVEUX_H
#define CLIENTCHEVEUX_H
#include <QThread>
#include <global.h>

class ClientCheveux : public QThread
{
public:
    ClientCheveux(QMutex *mutexClient,
                                 QWaitCondition *salleAttente,
                                 QWaitCondition *barbier,
                  int *siegeUtilise);
    void run();
    ~ClientCheveux();

private:
    int attentePousseCheveux;
    int *siegeUtilise;
    QMutex *mutexClient;
    QWaitCondition *salleAttente;
    QWaitCondition *barbier;
};

#endif // CLIENTCHEVEUX_H
