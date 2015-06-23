#ifndef BARBIER_H
#define BARBIER_H
#include <QThread>
#include <global.h>

class Barbier : public QThread
{
public:
    Barbier(QMutex *mutexBarbier,
            QWaitCondition *barbier,
            QWaitCondition *salleAttente,
            QMutex *debug,
            QMutex *mutexSiege,
            int *siegeUtilise,
            int *siegeCheveux,
            int *siegeTatoo);
    void run();
    ~Barbier();
private:
    QMutex *mutexBarbier;
    QWaitCondition *salleAttente;
    QWaitCondition *barbier;
    QMutex *debug;
    QMutex *mutexSiege;
    int *siegeUtilise;
    int *siegeCheveux;
    int *siegeTatoo;
};

#endif // BARBIER_H
