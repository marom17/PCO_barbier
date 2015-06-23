#include <QCoreApplication>
#include <global.h>
#include <barbier.h>
#include <clientcheveux.h>

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

    Barbier *b = new Barbier(mutexBarbier, barbier, salleAttente, debug, mutexSiege, &siegeUtilise);

    b->start();

    ClientCheveux *c[20];
    for(int i = 0; i < 20; i++){
         c[i]= new ClientCheveux(mutexClient, salleAttente, barbier, debug, mutexSiege, &siegeUtilise);
         c[i]->start();
    }



    return a.exec();
}
