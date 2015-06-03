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
            int *siegeUtilise);
    void run();
    ~Barbier();
private:
    QMutex *mutexBarbier;
    QWaitCondition *salleAttente;
    QWaitCondition *barbier;
    QMutex *debug;
    int *siegeUtilise;
};

#endif // BARBIER_H
