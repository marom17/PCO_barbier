#include "clientcheveux.h"

ClientCheveux::ClientCheveux(QMutex *mutexClient,
                             QWaitCondition *salleAttente,
                             QWaitCondition *barbier,
                             QMutex *debug,
                             int *siegeUtilise)
{
    this->salleAttente = salleAttente;
    this->mutexClient = mutexClient;
    this->barbier = barbier;
    this->siegeUtilise = siegeUtilise;
    this->debug = debug;
    attentePousseCheveux = 5 + (qrand() % 6);
}

ClientCheveux::~ClientCheveux(){
    delete this->mutexClient;
    delete this->salleAttente;
    delete this->barbier;
    delete this->siegeUtilise;

}

void ClientCheveux::run(){
    while(true){
        //Attend que ces cheveux pousse
        debug->lock();
        qDebug() << "J'attends que mes cheveux poussent \n";
        debug->unlock();

        sleep(attentePousseCheveux);

        //Si la salle d'attente est pleine
        mutexClient->lock();

        debug->lock();
        qDebug() << "Je veux aller chez le barbier. \n";
        debug->unlock();

        while(*siegeUtilise >= NB_SIEGE){
            debug->lock();
            qDebug() << "Plus de place... Je passerai plus tard \n";
            debug->unlock();

            mutexClient->unlock();
            sleep(attentePousseCheveux / 2);
            mutexClient->lock();
        }

        debug->lock();
        qDebug() << "Je réveille le barbier et m'installe dans la salle d'attente \n";
        debug->unlock();

        //Réveille le barbier si besoin
        barbier->wakeOne();

        //Entrée en salle d'attente
        ++(*siegeUtilise);
        salleAttente->wait(mutexClient);

        debug->lock();
        qDebug() << "Le barbier m'a réveillé, je peux me faire couper les tifs FDP LOL \n";
        qDebug() << "Travail terminé!\n";
        debug->unlock();

        --(*siegeUtilise);
        mutexClient->unlock();
    }
}

