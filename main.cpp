#include <QCoreApplication>
#include <global.h>
#include <barbier.h>
#include <clientcheveux.h>
#include <clienttatoo.h>

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    QMutex *mutexClient = new QMutex();
    QMutex *mutexBarbier = new QMutex();
    QWaitCondition *salleAttente = new QWaitCondition();
    QWaitCondition *barbier = new QWaitCondition();
    QMutex *debug = new QMutex();
    QMutex *mutexSiege = new QMutex();

    int siegeUtilise = 0;
    int siegeTatoo = 0;
    int siegeCheveux = 0;

    Barbier *b = new Barbier(mutexBarbier, barbier, salleAttente, debug, mutexSiege, &siegeUtilise, &siegeTatoo, &siegeCheveux);

    b->start();

    ClientCheveux *c[20];
    for(int i = 0; i < 20; i++){
         c[i]= new ClientCheveux(mutexClient, salleAttente, barbier, debug, mutexSiege, &siegeUtilise, &siegeCheveux);
         c[i]->start();
    }

    ClientTatoo *d[20];
    for(int i = 0; i < 20; i++){
         d[i]= new ClientTatoo(mutexClient, salleAttente, barbier, debug, mutexSiege, &siegeUtilise, &siegeTatoo);
         d[i]->start();
    }



    return a.exec();
}
