#include "barbier.h"

Barbier::~Barbier()
{
    delete this->salleAttente;
    delete this->mutexBarbier;
    delete this->mutexBarbier;
    delete this->siegeUtilise;
}

Barbier::Barbier(QMutex *mutexBarbier,
                 QWaitCondition *barbier,
                 QWaitCondition *salleAttente,
                 QMutex *debug,
                 int *siegeUtilise)
{
    this->mutexBarbier = mutexBarbier;
    this->barbier = barbier;
    this->salleAttente = salleAttente;
    this->siegeUtilise = siegeUtilise;
    this->debug = debug;
}

void Barbier::run(){
    while(true) {
        mutexBarbier->lock();

        debug->lock();
        qDebug() << "J'attends qu'un client me réveille... \n";
        debug->unlock();

        barbier->wait(mutexBarbier);

        debug->lock();
        qDebug() << "Je me fait réveiller par un client... \n";
        debug->unlock();

        while(*siegeUtilise != 0){
            debug->lock();
            qDebug() << "Prochain Client! \n";
            debug->unlock();
            salleAttente->wakeOne();
        }

        mutexBarbier->unlock();
    }
}
