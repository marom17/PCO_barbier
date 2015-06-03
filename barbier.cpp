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
        std::cout << "J'attends qu'un client me réveille..." << std::endl;

        barbier->wait(mutexBarbier);

        std::cout << "Je me fait réveiller par un client..." << std::endl;

        while(siegeUtilise != 0){
            std::cout << "Prochain Client!" << std::endl;
            salleAttente->wakeOne();
        }

        mutexBarbier->unlock();
    }
}
