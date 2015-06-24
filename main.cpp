/*
 * Authors: Stéphane Donnet; Romain Maillard
 * Date:  3 juin
 * Nom: main.cpp
 * But: permet d'initialiser les clients et le barbier et les variables
 *
*/

#include <QCoreApplication>
#include <global.h>
#include <barbier.h>
#include <clientcheveux.h>
#include <clienttatoo.h>
#include <QVector>

using namespace std;

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    QMutex *mutexClient = new QMutex();
    QMutex *mutexBarbier = new QMutex();
    QWaitCondition *salleCheveux = new QWaitCondition();
    QWaitCondition *salleTatoo = new QWaitCondition();
    QWaitCondition *barbier = new QWaitCondition();
    QMutex *debug = new QMutex();
    QMutex *mutexSiege = new QMutex();

    int siegeUtilise = 0;
    int siegeTatoo = 0;
    int siegeCheveux = 0;
    int nbCheveux = 0;
    int nbTatoo = 0;

    cout << "Bienvenue dans le sallon de coiffure et tatouage PCO"<< endl;
    do{
        cout << "Combien voulez-vous de client voulant se faire couper les cheveux ?";
        cin >> nbCheveux;
    }while(nbCheveux<0);
    do{
        cout << "Combien voulez-vous de client voulant se faire tatouer ?";
        cin >> nbTatoo;
    }while(nbTatoo<0);

    Barbier *b = new Barbier(mutexBarbier, barbier, salleCheveux, salleTatoo, debug, mutexSiege, &siegeUtilise, &siegeTatoo, &siegeCheveux);

    b->start();



    QVector<ClientCheveux*> c;
    for(int i = 0; i < nbCheveux; i++){
        c.push_front(new ClientCheveux(mutexClient, salleCheveux, barbier, debug, mutexSiege, &siegeUtilise, &siegeCheveux));
        c.front()->start();
    }

    QVector<ClientTatoo*> d;
    for(int i = 0; i < nbTatoo; i++){
        d.push_front(new ClientTatoo(mutexClient, salleTatoo, barbier, debug, mutexSiege, &siegeUtilise, &siegeTatoo));
        d.front()->start();
    }



    return a.exec();
}
