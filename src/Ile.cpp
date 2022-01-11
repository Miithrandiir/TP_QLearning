//
// Created by mithrandir on 21/12/2021.
//

#include "Ile.hpp"
#include <cassert>

void Ile::addItemToMap(std::pair<int, int> position, TypeItem typeItem) {
    assert(carte[position.second][position.first] == 0);
    carte[position.second][position.first] = typeItem;
}

std::pair<int, int> Ile::gen_alea_position() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> distributionX(0, get_taille_x() - 1);
    std::uniform_int_distribution<int> distributionY(0, get_taille_y() - 1);

    int posX = distributionX(gen);
    int posY = distributionY(gen);

    while (carte[posY][posX] != 0) {
        posX = distributionX(gen);
        posY = distributionY(gen);
    }

    return std::make_pair(posX, posY);
}

std::map<CARDINAL, int> Ile::actions_possibles(const Position &_position) {
    assert(_position.first >= 0 && _position.first < tailleX && _position.second >= 0 && _position.second < tailleY);
    std::map<CARDINAL, int> actions_possibles;

    //verif nord
    if (_position.second != 0 && (_position.second - 1) >= 0) {
        Position newp = nouvelle_position(_position, NORD);
        assert(newp.first >= 0 && newp.first < tailleX && newp.second >= 0 && newp.second < tailleY);
        actions_possibles[NORD] = carte[_position.second - 1][_position.first];
    }
    //verif est
    if ((_position.first + 1) >= 0 && (_position.first + 1) < tailleX) {
        Position newp = nouvelle_position(_position, EST);
        assert(newp.first >= 0 && newp.first < tailleX && newp.second >= 0 && newp.second < tailleY);
        actions_possibles[EST] = carte[_position.second][_position.first + 1];
    }
    //verif sud
    if ((_position.second + 1) >= 0 && (_position.second + 1) < tailleY) {
        Position newp = nouvelle_position(_position, SUD);
        assert(newp.first >= 0 && newp.first < tailleX && newp.second >= 0 && newp.second < tailleY);
        actions_possibles[SUD] = carte[_position.second + 1][_position.first];
    }
    //verif ouest
    if (_position.first != 0 && (_position.first - 1) >= 0) {
        Position newp = nouvelle_position(_position, OUEST);
        assert(newp.first >= 0 && newp.first < tailleX && newp.second >= 0 && newp.second < tailleY);
        actions_possibles[OUEST] = carte[_position.second][_position.first - 1];
    }

    return actions_possibles;
}

MatriceActionEtat Ile::matrice_action_etat() {

    MatriceActionEtat matrice_action_etat;

    for (int y = 0; y < get_taille_y(); ++y) {
        for (int x = 0; x < get_taille_x(); ++x) {
            std::map<CARDINAL, int> tmp;
            for (int i = 0; i < 4; i++) {
                tmp.emplace((CARDINAL) i, -1);
            }
            auto action_possibles = actions_possibles(std::make_pair(x, y));
            for (auto&[key, value]: action_possibles) {
                tmp[key] = value;
            }

            matrice_action_etat.emplace(std::make_pair(x, y), tmp);
        }
    }

    return matrice_action_etat;

}


Position Ile::faire_action(Position etat, CARDINAL action) {

    Position pos = nouvelle_position(etat, action);
    assert(pos.first >= 0 && pos.second >= 0);
    return pos;
}

int Ile::passe(Position position) {
    int tmp = carte[position.second][position.first];
    carte[position.second][position.first] = 0;
    return tmp;
}

Position Ile::nouvelle_position(Position etat, CARDINAL cardinal) {
    Position _position;
    switch (cardinal) {
        case NORD:
            _position = std::make_pair(etat.first, etat.second - 1);
            break;
        case EST:
            _position = std::make_pair(etat.first + 1, etat.second);
            break;
        case SUD:
            _position = std::make_pair(etat.first, etat.second + 1);
            break;
        case OUEST:
            _position = std::make_pair(etat.first - 1, etat.second);
            break;
    }
    assert(_position.first >= 0 && _position.second >= 0);
    return _position;
}

CARDINAL Ile::gen_alea_action(Position _position) {
    assert(_position.first >= 0 && _position.first < tailleX && _position.second >= 0 && _position.second < tailleY);
    std::map<CARDINAL, int> action_possible = actions_possibles(_position);

    std::vector<CARDINAL> tmp;

    tmp.reserve(action_possible.size());
    for (auto &item: action_possible) {
        tmp.push_back(item.first);
    }

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> distribution(0, tmp.size() - 1);

    return tmp[distribution(gen)];

}
