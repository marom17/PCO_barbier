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

    int siegeUtilise = 0;

    Barbier *b = new Barbier(mutexBarbier, barbier, salleAttente, debug, &siegeUtilise);
    ClientCheveux *c = new ClientCheveux(mutexClient, salleAttente, barbier, debug, &siegeUtilise);

    b->start();
    c->start();

    return a.exec();
}
