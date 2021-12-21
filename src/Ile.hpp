//
// Created by mithrandir on 21/12/2021.
//

#ifndef QLEARNING_ILE_HPP
#define QLEARNING_ILE_HPP


#include <vector>
#include <random>
#include <iostream>
#include <map>

enum TypeItem {
    NOTHING = 0,
    BOUTEILLE_RHUM = 2,
    TRESOR = 10
};

enum CARDINAL {
    NORD = 0,
    EST = 1,
    SUD = 2,
    OUEST = 3
};
static const char *EnumCardinalStrings[] = {"Nord", "Est", "Sud", "Ouest"};

typedef std::vector<std::vector<int>> Carte;
/**
 * @IMPORTANT POSITION => Y PUIS X
 */
typedef std::pair<int, int> Position;

class Ile {
private:

    int tailleX;
    int tailleY;
    int nb_bouteilles;
    Carte carte;


    void addItemToMap(std::pair<int, int> position, TypeItem typeItem);

    std::pair<int, int> gen_alea_position(Carte &);

public:
    Ile(int tailleX, int tailleY, int nb_bouteilles) : tailleX(tailleX), tailleY(tailleY),
                                                       nb_bouteilles(nb_bouteilles) {


        //initialisation de la carte
        for (int y = 0; y < tailleY; y++) {
            std::vector<int> tmp;
            tmp.reserve(tailleX);
            for (int x = 0; x < tailleX; x++) {
                tmp.push_back(0);
            }
            carte.push_back(tmp);
        }

        //Generation des emplacements des bouteilles de rhum
        for (int i = 0; i < nb_bouteilles; i++) {
            addItemToMap(gen_alea_position(carte), BOUTEILLE_RHUM);
        }

        addItemToMap(gen_alea_position(carte), TRESOR);
    }

    const Carte get_carte() const { return carte; }

    const int get_taille_x() const { return tailleX; }

    const int get_taille_y() const { return tailleY; }

    friend std::ostream &operator<<(std::ostream &os, const Ile &ile) {
        for (auto &vector: ile.get_carte()) {
            for (auto &item: vector) {
                os << item << '\t';
            }
            os << std::endl;
        }
        return os;
    }

    std::map<CARDINAL, int> actions_possibles(const Position &position);
};


#endif //QLEARNING_ILE_HPP
