#ifndef CLIENTTATOO_H
#define CLIENTTATOO_H
#include <QThread>
#include <global.h>

class ClientTatoo : public QThread
{
public:
    ClientTatoo(QMutex *mutexClient,
                  QWaitCondition *salleTatoo,
                  QWaitCondition *barbier,
                  QMutex *debug,
                  QMutex *mutexSiege,
                  int *siegeUtilise,
                  int *siegeTatoo);
    void run();
    ~ClientTatoo();

private:
    int attenteTatoo;
    int *siegeUtilise;
    int *siegeTatoo;
    QMutex *mutexClient;
    QWaitCondition *salleTatoo;
    QWaitCondition *barbier;
    QMutex *mutexSiege;
    QMutex *debug;
};

#endif // CLIENTTATOO_H

