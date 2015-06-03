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
        std::cout << "J'attends que mes cheveux poussent" <<  std::endl;
        sleep(attentePousseCheveux);

        //Si la salle d'attente est pleine
        mutexClient->lock();
        std::cout << "Je veux aller chez le barbier." << std::endl;
        while(*siegeUtilise >= NB_SIEGE){
            std::cout << "Plus de place... Je passerai plus tard" << std::endl;
            mutexClient->unlock();
            sleep(attentePousseCheveux / 2);
            mutexClient->lock();
        }

        std::cout << "Je réveille le barbier et m'installe dans la salle d'attente" << std::endl;

        //Réveille le barbier si besoin
        barbier->wakeOne();

        //Entrée en salle d'attente
        ++(*siegeUtilise);
        salleAttente->wait(mutexClient);

        std::cout << "Le barbier m'a réveillé, je peux me faire couper les tifs FDP LOL" << std::endl;
        std::cout << "Travail terminé!" << std::endl;
        --(*siegeUtilise);
        mutexClient->unlock();
    }
}

