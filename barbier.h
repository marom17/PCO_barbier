/*
 * Authors: Stéphane Donnet; Romain Maillard
 * Date:  3 juin
 * Nom: barbier.h
 * But: définition du barbier
 *
*/

#ifndef BARBIER_H
#define BARBIER_H
#include <QThread>
#include <global.h>

class Barbier : public QThread
{
public:
    Barbier(QMutex *mutexBarbier,
            QWaitCondition *barbier,
            QWaitCondition *salleCheveux,
            QWaitCondition *salleTatoo,
            QMutex *debug,
            QMutex *mutexSiege,
            int *siegeUtilise,
            int *siegeCheveux,
            int *siegeTatoo);
    void run();
    ~Barbier();
private:
    QMutex *mutexBarbier;
    QWaitCondition *salleCheveux;
    QWaitCondition *salleTatoo;
    QWaitCondition *barbier;
    QMutex *debug;
    QMutex *mutexSiege;
    int *siegeUtilise;
    int *siegeCheveux;
    int *siegeTatoo;
};

#endif // BARBIER_H
