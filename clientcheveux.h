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
                  QMutex *debug,
                  QMutex *mutexSiege,
                  int *siegeUtilise,
                  int *siegeCheveux);
    void run();
    ~ClientCheveux();

private:
    int attentePousseCheveux;
    int *siegeUtilise;
    int *siegeCheveux;
    QMutex *mutexClient;
    QWaitCondition *salleAttente;
    QWaitCondition *barbier;
    QMutex *mutexSiege;
    QMutex *debug;
};

#endif // CLIENTCHEVEUX_H
