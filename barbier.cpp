#include "barbier.h"

Barbier::~Barbier()
{
    delete this->salleAttente;
    delete this->mutexBarbier;
    delete this->mutexBarbier;
    delete this->siegeUtilise;
    delete this->siegeCheveux;
    delete this->siegeTatoo;
}

Barbier::Barbier(QMutex *mutexBarbier,
                 QWaitCondition *barbier,
                 QWaitCondition *salleAttente,
                 QMutex *debug,
                 QMutex *mutexSiege,
                 int *siegeUtilise,
                 int *siegeCheveux,
                 int *siegeTatoo)
{
    this->mutexBarbier = mutexBarbier;
    this->barbier = barbier;
    this->salleAttente = salleAttente;
    this->siegeUtilise = siegeUtilise;
    this->debug = debug;
    this->mutexSiege = mutexSiege;
    this->siegeCheveux = siegeCheveux;
    this->siegeTatoo = siegeTatoo;
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

        mutexSiege->lock();
        while(*siegeUtilise != 0){
            mutexSiege->unlock();

            debug->lock();
            qDebug() << "Couper des cheveux, c'est ma passion!' \n";
            debug->unlock();

            sleep(1);

            debug->lock();
            qDebug() << "Prochain Client! \n";
            debug->unlock();
            salleAttente->wakeOne();

            (*siegeUtilise)--;
            mutexSiege->lock();
        }
        mutexSiege->unlock();

        mutexBarbier->unlock();
    }
}
