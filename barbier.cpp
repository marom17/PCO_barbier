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
                 int *siegeUtilise)
{
    this->mutexBarbier=mutexBarbier;
    this->barbier=barbier;
    this->salleAttente=salleAttente;
    this->siegeUtilise=siegeUtilise;
}

void Barbier::run(){
    while(true) {
        mutexBarbier->lock();
        qDebug() << "J'attends qu'un client me réveille... \n";

        barbier->wait(mutexBarbier);

        qDebug() << "Je me fait réveiller par un client... \n";

        while(*siegeUtilise != 0){
            qDebug() << "Prochain Client! \n";
            salleAttente->wakeOne();
        }

        mutexBarbier->unlock();
    }
}
