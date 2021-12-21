//
// Created by mithrandir on 21/12/2021.
//

#include "Pirate.hpp"

/**
 * @important   position.first = Y
 *              position.second = X
 * @param cardinal
 */
void Pirate::faireMouvement(CARDINAL cardinal) {

    switch (cardinal) {
        case NORD:
            position = std::make_pair(position.first - 1, position.second);
            break;
        case EST:
            position = std::make_pair(position.first, position.second + 1);
            break;
        case SUD:
            position = std::make_pair(position.first + 1, position.second);
            break;
        case OUEST:
            position = std::make_pair(position.first, position.second - 1);
            break;
    }

    butin += ile.get_carte()[position.first][position.second];

    if(ile.get_carte()[position.first][position.second] == TRESOR) {

        std::cout << "Le pirate a trouvé le trésor !!" << '\n' << "Il part avec un butin de " << butin << std::endl;
        exit(0);

    }

}

void Pirate::faireMouvementAleatoire(const std::map<CARDINAL, int> &actions) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> distribution(0, actions.size()-1);

    /**
     * On procède ainsi pour éviter de donner un cardinal impossible (e.g donné le nord alors que l'on est à la position la plus au nord possible)
     */
    CARDINAL cardinal;
    int alea = distribution(gen);
    int i=0;
    for(auto item : actions) {
        if(i==alea) {
            cardinal = item.first;
            break;
        }
        i++;
    }

    faireMouvement(cardinal);
}

void Pirate::faireMouvementActions(const std::map<CARDINAL, int> &actions) {

    std::pair<CARDINAL, int> meilleur_actions = std::make_pair(NORD, std::numeric_limits<int>::min());

    for (auto &item: actions) {
        if (item.second > meilleur_actions.second) {
            meilleur_actions = item;
        }
    }

    faireMouvement(meilleur_actions.first);
}

void Pirate::deplacement() {
    if(nb_deplacement > MAX_MOUVEMENT) {
        std::cout << "Le pirate n'a pas trouvé de trésor en moins de 20 déplacements" << '\n' << "Il part avec un butin de " << butin;
        exit(0);
    }
    double rand = gen_alea_epsilon_greedy();
    nb_deplacement++;
    auto actions = ile.actions_possibles(get_position());
    if (rand > epsilon) {
        faireMouvementAleatoire(actions);
    } else {
        faireMouvementActions(actions);
    }

}

Position Pirate::gen_alea_position() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> distributionX(0, ile.get_taille_x() - 1);
    std::uniform_int_distribution<int> distributionY(0, ile.get_taille_y() - 1);

    int posX = distributionX(gen);
    int posY = distributionY(gen);

    return std::make_pair(posY, posX);
}

double Pirate::gen_alea_epsilon_greedy() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> distribution(0, 1);

    return distribution(gen);
}
