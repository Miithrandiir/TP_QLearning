//
// Created by mithrandir on 21/12/2021.
//

#include "Ile.hpp"
#include <cassert>

void Ile::addItemToMap(std::pair<int, int> position, TypeItem typeItem) {
    assert(carte[position.first][position.second] == 0);
    carte[position.first][position.second] = typeItem;
}

std::pair<int, int> Ile::gen_alea_position(Carte &map) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> distributionX(0, tailleX - 1);
    std::uniform_int_distribution<int> distributionY(0, tailleY - 1);

    int posX = distributionX(gen);
    int posY = distributionY(gen);

    while (map[posY][posX] != 0) {
        posX = distributionX(gen);
        posY = distributionY(gen);
    }

    return std::make_pair(posY, posX);
}

std::map<CARDINAL, int> Ile::actions_possibles(const Position &position) {
    assert(position.second >= 0 && position.second < tailleX && position.first >= 0 && position.first < tailleY);
    std::map<CARDINAL, int> actions_possibles;

    //verif nord
    if (position.first - 1 >= 0) {
        actions_possibles[NORD] = carte[position.first - 1][position.second];
    }
    //verif est
    if (position.second + 1 >= 0 && position.second + 1 < tailleX) {
        actions_possibles[EST] = carte[position.first][position.second + 1];
    }
    //verif sud
    if (position.first + 1 >= 0 && position.first + 1 < tailleY) {
        actions_possibles[SUD] = carte[position.first + 1][position.second];
    }
    //verif ouest
    if (position.second - 1 >= 0) {
        actions_possibles[OUEST] = carte[position.first][position.second - 1];
    }
    return actions_possibles;
}
