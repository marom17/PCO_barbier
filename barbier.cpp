#include "barbier.h"

Barbier::~Barbier()
{
    delete this->salleCheveux;
    delete this->salleTatoo;
    delete this->mutexBarbier;
    delete this->mutexBarbier;
    delete this->siegeUtilise;
    delete this->siegeCheveux;
    delete this->siegeTatoo;
}

Barbier::Barbier(QMutex *mutexBarbier,
                 QWaitCondition *barbier,
                 QWaitCondition *salleCheveux,
                 QWaitCondition *salleTatoo,
                 QMutex *debug,
                 QMutex *mutexSiege,
                 int *siegeUtilise,
                 int *siegeCheveux,
                 int *siegeTatoo)
{
    this->mutexBarbier = mutexBarbier;
    this->barbier = barbier;
    this->salleCheveux = salleCheveux;
    this->salleTatoo = salleTatoo;
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
            if(this->siegeTatoo>0){
                salleTatoo->wakeOne();
                (*siegeTatoo)--;
            }
            else{
                salleCheveux->wakeOne();
                (*siegeCheveux)--;
            }

            (*siegeUtilise)--;
            mutexSiege->lock();
        }
        mutexSiege->unlock();

        mutexBarbier->unlock();
    }
}
