/*
 * Authors: Stéphane Donnet; Romain Maillard
 * Date:  3 juin
 * Nom: global.h
 * But: définition de quelques variables global
 *
*/

#ifndef GLOBAL
#define GLOBAL
#include <QMutex>
#include <QWaitCondition>
#include "iostream"
#include <QtDebug>

extern QMutex *mutexClient;
extern QMutex *mutexBarbier;
extern QWaitCondition *salleCheveux;
extern QWaitCondition *salleTatoo;
extern QWaitCondition *barbier;

//TODO: Only for test. Ask NB_SIEGE to user!
const int NB_SIEGE = 10;
extern int siegeUtilise;
extern int siegeTatoo;
extern int siegeCheveux;

#endif // GLOBAL

