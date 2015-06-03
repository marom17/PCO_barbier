#include "clientcheveux.h"

ClientCheveux::ClientCheveux(QMutex *mutexClient,
                             QWaitCondition *salleAttente,
                             QWaitCondition *barbier,
                             int *siegeUtilise)
{
    this->salleAttente=salleAttente;
    this->mutexClient=mutexClient;
    this->barbier=barbier;
    this->siegeUtilise=siegeUtilise;
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
        qDebug() << "J'attends que mes cheveux poussent \n";
        sleep(attentePousseCheveux);

        //Si la salle d'attente est pleine
        mutexClient->lock();
        qDebug() << "Je veux aller chez le barbier. \n";
        while(*siegeUtilise >= NB_SIEGE){
            qDebug() << "Plus de place... Je passerai plus tard \n";
            mutexClient->unlock();
            sleep(attentePousseCheveux / 2);
            mutexClient->lock();
        }

        qDebug() << "Je réveille le barbier et m'installe dans la salle d'attente \n";

        //Réveille le barbier si besoin
        barbier->wakeOne();

        //Entrée en salle d'attente
        ++(*siegeUtilise);
        salleAttente->wait(mutexClient);

        qDebug() << "Le barbier m'a réveillé, je peux me faire couper les tifs FDP LOL \n";
        qDebug() << "Travail terminé!\n";
        --(*siegeUtilise);
        mutexClient->unlock();
    }
}

