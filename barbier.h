#ifndef BARBIER_H
#define BARBIER_H
#include <QThread>
#include <global.h>

class Barbier : public QThread
{
public:
    Barbier();
    void run();
    ~Barbier();
};

#endif // BARBIER_H
