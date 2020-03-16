#ifndef UPGRADE_H
#define UPGRADE_H

class Upgrade {
public:
    Upgrade* getResource(unsigned) const;
    unsigned getPrice(unsigned) const;

private:
    unsigned idUpgrade;
    unsigned price;

};

#endif

