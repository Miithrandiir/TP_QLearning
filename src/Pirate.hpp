//
// Created by mithrandir on 21/12/2021.
//

#ifndef QLEARNING_PIRATE_HPP
#define QLEARNING_PIRATE_HPP


#include "Ile.hpp"

#define MAX_MOUVEMENT 20

class Pirate {
private:
    Ile ile;
    int nb_deplacement;
    int butin;
    Position position;
    double epsilon;

public:

    Pirate(Ile &ile, double epsilon = 0.9) : ile(ile), epsilon(epsilon) {
        nb_deplacement = 0;
        butin = 0;
        position = gen_alea_position();
    }

    const Position get_position() const { return position; }


    Position gen_alea_position();

    double gen_alea_epsilon_greedy();

    void deplacement();

    void faireMouvementActions(const std::map<CARDINAL, int> &actions);

    void faireMouvementAleatoire(const std::map<CARDINAL, int> &);

    void faireMouvement(CARDINAL cardinal);



};


#endif //QLEARNING_PIRATE_HPP
