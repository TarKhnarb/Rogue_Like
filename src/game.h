#ifndef SRC_GAME_H
#define SRC_GAME_H
#include <vector>

class game {
public :

    void gameLoop();
    void playerLogic();
    void initMap();
    void displayMap();

    void initMonster();

    void shoot();
    void updateProjectile();

private :
    std::vector<Projectile> projectileArray;
    std::vector<Entity> monsterArray;

    unsigned map[27][27];
    unsigned donjon[21][21];
};


#endif //SRC_GAME_H
