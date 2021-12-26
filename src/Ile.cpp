//
// Created by mithrandir on 21/12/2021.
//

#include "Ile.hpp"
#include <cassert>

void Ile::addItemToMap(std::pair<int, int> position, TypeItem typeItem) {
    assert(carte[position.second][position.first] == 0);
    carte[position.second][position.first] = typeItem;
}

std::pair<int, int> Ile::gen_alea_position(Carte &map) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> distributionX(0, get_taille_x() - 1);
    std::uniform_int_distribution<int> distributionY(0, get_taille_y() - 1);

    int posX = distributionX(gen);
    int posY = distributionY(gen);

    while (map[posY][posX] != 0) {
        posX = distributionX(gen);
        posY = distributionY(gen);
    }

    return std::make_pair(posX, posY);
}

std::map<CARDINAL, int> Ile::actions_possibles(const Position &position) {
    assert(position.first >= 0 && position.first < tailleX && position.second >= 0 && position.second < tailleY);
    std::map<CARDINAL, int> actions_possibles;

    //verif nord
    if (position.second - 1 >= 0) {
        actions_possibles[NORD] = carte[position.second - 1][position.first];
    }
    //verif est
    if (position.first + 1 >= 0 && position.first + 1 < tailleX) {
        actions_possibles[EST] = carte[position.second][position.first + 1];
    }
    //verif sud
    if (position.second + 1 >= 0 && position.second + 1 < tailleY) {
        actions_possibles[SUD] = carte[position.second + 1][position.first];
    }
    //verif ouest
    if (position.first - 1 >= 0) {
        actions_possibles[OUEST] = carte[position.second][position.first - 1];
    }
    return actions_possibles;
}

std::vector<std::vector<int>> Ile::matrice_action_etat() {

    std::vector<std::vector<int>> matrice_action_etat;

    for(int y=0;y<get_taille_y();++y) {
        for(int x=0;x<get_taille_x();++x) {
            std::vector<int> tmp;
            Position tmp_pos = std::make_pair(x,y);
            std::map<CARDINAL, int> action_possible = actions_possibles(tmp_pos);

            //Ordre particulier N S E O
            if(action_possible.count(NORD)) {
                tmp.push_back(action_possible[NORD]);
            } else {
                tmp.push_back(-1);
            }

            if(action_possible.count(SUD)) {
                tmp.push_back(action_possible[SUD]);
            } else {
                tmp.push_back(-1);
            }

            if(action_possible.count(EST)) {
                tmp.push_back(action_possible[EST]);
            } else {
                tmp.push_back(-1);
            }

            if(action_possible.count(OUEST)) {
                tmp.push_back(action_possible[OUEST]);
            } else {
                tmp.push_back(-1);
            }

            matrice_action_etat.push_back(tmp);
        }
    }

    return matrice_action_etat;

}

std::vector<int> Ile::faire_action(Position etat, CARDINAL action) {

    Position position;
    switch (action) {
        case NORD:
            position = std::make_pair(etat.first, etat.second - 1);
            break;
        case EST:
            position = std::make_pair(etat.first+ 1, etat.second );
            break;
        case SUD:
            position = std::make_pair(etat.first , etat.second+ 1);
            break;
        case OUEST:
            position = std::make_pair(etat.first- 1, etat.second );
            break;
    }

    return matrice_action_etat()[position.second];
}

void Ile::passe(Position position) {

    carte[position.second][position.first] = 0;

}
