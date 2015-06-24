/*
 * Authors: Stéphane Donnet; Romain Maillard
 * Date:  3 juin
 * Nom: barbier.cpp
 * But: implémentation du barbier
 *
*/


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
        qDebug() << "Barbier: J'attends qu'un client me reveille... \n";
        debug->unlock();

        barbier->wait(mutexBarbier);

        debug->lock();
        qDebug() << "Barbier: Je me fait reveiller par un client... \n";
        debug->unlock();

        mutexSiege->lock();
        while(*siegeUtilise != 0){
            mutexSiege->unlock();

            debug->lock();
            qDebug() << "Barbier: Couper des cheveux, c'est ma passion!' \n";
            debug->unlock();

            sleep(1 + (qrand() % 2));

            debug->lock();
            qDebug() << "Barbier: Prochain Client! \n";
            debug->unlock();

            //Vérifie si il y a des gens voulants des tatoo pour le faire passer en premier
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
