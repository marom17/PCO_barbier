/*
 * Authors: Stéphane Donnet; Romain Maillard
 * Date:  3 juin
 * Nom: clientcheveux.h
 * But: définition des clients voulant se faire couper les cheveux
 *
*/

#ifndef CLIENTCHEVEUX_H
#define CLIENTCHEVEUX_H
#include <QThread>
#include <global.h>

class ClientCheveux : public QThread
{
public:
    ClientCheveux(QMutex *mutexClient,
                  QWaitCondition *salleCheveux,
                  QWaitCondition *barbier,
                  QMutex *debug,
                  QMutex *mutexSiege,
                  int *siegeUtilise,
                  int *siegeCheveux);
    void run();
    ~ClientCheveux();

private:
    int attentePousseCheveux;
    int *siegeUtilise;
    int *siegeCheveux;
    QMutex *mutexClient;
    QWaitCondition *salleCheveux;
    QWaitCondition *barbier;
    QMutex *mutexSiege;
    QMutex *debug;
};

#endif // CLIENTCHEVEUX_H
