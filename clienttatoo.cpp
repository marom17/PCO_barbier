/*
 * Authors: Stéphane Donnet; Romain Maillard
 * Date:  23 juin
 * Nom: clienttatoo.cpp
 * But: implémentation des clients voulant des tatoos
 *
*/

#include "clienttatoo.h"

ClientTatoo::ClientTatoo(QMutex *mutexClient,
                             QWaitCondition *salleTatoo,
                             QWaitCondition *barbier,
                             QMutex *debug,
                             QMutex *mutexSiege,
                             int *siegeUtilise,
                             int *siegeTatoo)
{
    this->salleTatoo = salleTatoo;
    this->mutexClient = mutexClient;
    this->barbier = barbier;
    this->siegeUtilise = siegeUtilise;
    this->debug = debug;
    this->mutexSiege = mutexSiege;
    this->siegeTatoo = siegeTatoo;
    attenteTatoo = 5 + (qrand() % 6);
}

ClientTatoo::~ClientTatoo(){
    delete this->mutexClient;
    delete this->salleTatoo;
    delete this->barbier;
    delete this->siegeUtilise;
    delete this->siegeTatoo;

}

void ClientTatoo::run(){
    int cpt = 0;
    while(true){
        //Attend l'envie d'un nouveau tatoo
        debug->lock();
        qDebug() << "Tatoo: J'attends d'avoir envie d'un nouveau Tatoo \n";
        debug->unlock();

        sleep(attenteTatoo);

        mutexClient->lock();

        debug->lock();
        qDebug() << "Tatoo: Je veux aller chez le barbier pour me faire tatouer. \n";
        debug->unlock();

        cpt = 0;

        //Si la salle d'attente est pleine
        mutexSiege->lock();
        while(*siegeUtilise >= NB_SIEGE){
            debug->lock();
            qDebug() << cpt++ << "Tatoo: Essai. Plus de place... Je passerai plus tard \n";
            debug->unlock();

            mutexClient->unlock();
            mutexSiege->unlock();
            sleep(attenteTatoo / 2);
            mutexClient->lock();
            mutexSiege->lock();
        }
        mutexSiege->unlock();

        debug->lock();
        qDebug() << "Tatoo: Je reveille le barbier et m'installe dans la salle d'attente \n";
        debug->unlock();

        //Réveille le barbier si besoin
        barbier->wakeOne();

        //Entrée en salle d'attente
        mutexSiege->lock();
        (*siegeUtilise)++;
        (*siegeTatoo)++;
        mutexSiege->unlock();

        salleTatoo->wait(mutexClient);

        debug->lock();
        qDebug() << "Tatoo: Le barbier m'a réveille, tatoo termine! \n";
        debug->unlock();

        mutexClient->unlock();
    }
}

