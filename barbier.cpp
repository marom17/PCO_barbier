#include "barbier.h"

Barbier::Barbier()
{

}

Barbier::~Barbier()
{

}

void Barbier::run(){
    while(true) {
        mutexBarbier->lock();
        qDebug() << "J'attends qu'un client me réveille... \n";

        barbier->wait(mutexBarbier);

        qDebug() << "Je me fait réveiller par un client... \n";

        while(siegeUtilise != 0){
            qDebug() << "Prochain Client! \n";
            salleAttente->wakeOne();
        }

        mutexBarbier->unlock();
    }
}
