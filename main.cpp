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

//Permet de chosir le nombre de client
#define NBCHEVEUX 20
#define NBTATOO 5

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

    Barbier *b = new Barbier(mutexBarbier, barbier, salleCheveux, salleTatoo, debug, mutexSiege, &siegeUtilise, &siegeTatoo, &siegeCheveux);

    b->start();


    ClientCheveux *c[NBCHEVEUX];
    for(int i = 0; i < NBCHEVEUX; i++){
         c[i]= new ClientCheveux(mutexClient, salleCheveux, barbier, debug, mutexSiege, &siegeUtilise, &siegeCheveux);
         c[i]->start();
    }

    ClientTatoo *d[NBTATOO];
    for(int i = 0; i < NBTATOO; i++){
         d[i]= new ClientTatoo(mutexClient, salleTatoo, barbier, debug, mutexSiege, &siegeUtilise, &siegeTatoo);
         d[i]->start();
    }



    return a.exec();
}
