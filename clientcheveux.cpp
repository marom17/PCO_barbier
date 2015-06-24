/*
 * Authors: Stéphane Donnet; Romain Maillard
 * Date:  3 juin
 * Nom: clientcheveux.cpp
 * But: implémentation des clients voulant se faire couper les cheveux
 *
*/


#include "clientcheveux.h"

ClientCheveux::ClientCheveux(QMutex *mutexClient,
                             QWaitCondition *salleCheveux,
                             QWaitCondition *barbier,
                             QMutex *debug,
                             QMutex *mutexSiege,
                             int *siegeUtilise,
                             int *siegeCheveux)
{
    this->salleCheveux = salleCheveux;
    this->mutexClient = mutexClient;
    this->barbier = barbier;
    this->siegeUtilise = siegeUtilise;
    this->debug = debug;
    this->mutexSiege = mutexSiege;
    this->siegeCheveux = siegeCheveux;
    attentePousseCheveux = 5 + (qrand() % 6);
}

ClientCheveux::~ClientCheveux(){
    delete this->mutexClient;
    delete this->salleCheveux;
    delete this->barbier;
    delete this->siegeUtilise;
    delete this->siegeCheveux;

}

void ClientCheveux::run(){
    int cpt = 0;
    while(true){
        //Attend que ces cheveux pousse
        debug->lock();
        qDebug() << "Cheveux: J'attends que mes cheveux poussent \n";
        debug->unlock();

        sleep(attentePousseCheveux);

        mutexClient->lock();

        debug->lock();
        qDebug() << "Cheveux: Je veux aller chez le barbier. \n";
        debug->unlock();

        cpt = 0;

        //Si la salle d'attente est pleine
        mutexSiege->lock();
        while(*siegeUtilise >= NB_SIEGE){
            debug->lock();
            qDebug() << cpt++ << "Cheveux: Essai. Plus de place... Je passerai plus tard \n";
            debug->unlock();

            mutexClient->unlock();
            mutexSiege->unlock();
            sleep(attentePousseCheveux / 2);
            mutexClient->lock();
            mutexSiege->lock();
        }
        mutexSiege->unlock();

        debug->lock();
        qDebug() << "Cheveux: Je reveille le barbier et m'installe dans la salle d'attente \n";
        debug->unlock();

        //Réveille le barbier si besoin
        barbier->wakeOne();

        //Entrée en salle d'attente
        mutexSiege->lock();
        (*siegeUtilise)++;
        (*siegeCheveux)++;
        mutexSiege->unlock();

        salleCheveux->wait(mutexClient);

        debug->lock();
        qDebug() << "Cheveux: Le barbier m'a reveille, travail termine! \n";
        debug->unlock();

        mutexClient->unlock();
    }
}

