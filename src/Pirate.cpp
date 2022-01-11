//
// Created by mithrandir on 21/12/2021.
//

#include "Pirate.hpp"
#include <algorithm>
/**
 * @important   position.first = Y
 *              position.second = X
 * @param cardinal
 */
void Pirate::faireMouvement(CARDINAL cardinal) {

    switch (cardinal) {
        case NORD:
            position = std::make_pair(position.first, position.second - 1);
            break;
        case EST:
            position = std::make_pair(position.first+ 1, position.second );
            break;
        case SUD:
            position = std::make_pair(position.first , position.second+ 1);
            break;
        case OUEST:
            position = std::make_pair(position.first- 1, position.second );
            break;
    }
    butin += ile.get_carte()[position.second][position.first];
    if(ile.get_carte()[position.second][position.first] == TRESOR) {
        this->trouver_tresor = true;

    }
    ile.passe(position);
}

void Pirate::faireMouvementAleatoire(const std::map<CARDINAL, int> &actions) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> distribution(0, actions.size()-1);

    /**
     * On procède ainsi pour éviter de donner un cardinal impossible (e.g donner le nord alors que l'on est à la position la plus au nord possible)
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

bool Pirate::deplacement() {
    if(nb_deplacement > MAX_MOUVEMENT || a_trouver_tresor()) {
        return false;
    }

    while(nb_deplacement < MAX_MOUVEMENT && !a_trouver_tresor()) {
        double rand = gen_alea_epsilon_greedy();
        nb_deplacement++;
        auto actions = ile.actions_possibles(get_position());
        if (rand > epsilon) {
            faireMouvementAleatoire(actions);
        } else {
            faireMouvementActions(actions);
        }
    }

    return true;
}

Position Pirate::gen_alea_position() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> distributionX(0, ile.get_taille_x() - 1);
    std::uniform_int_distribution<int> distributionY(0, ile.get_taille_y() - 1);

    int posX = distributionX(gen);
    int posY = distributionY(gen);

    return std::make_pair(posX, posY);
}

double Pirate::gen_alea_epsilon_greedy() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> distribution(0, 1);

    return distribution(gen);
}

bool Pirate::executer_agent(Agent& agent) {
    if(nb_deplacement > MAX_MOUVEMENT || a_trouver_tresor())
        return false;
    nb_deplacement++;

    auto action_disponible = ile.actions_possibles(position);
    std::vector<CARDINAL> tmp;
    for(auto item : action_disponible)
        tmp.push_back(item.first);


    CARDINAL meilleur_action = agent.meilleur_action(position);
    //regarde si l'action est possible
    if(std::find(tmp.begin(), tmp.end(), meilleur_action) == tmp.end())
        return false;

    Position res = ile.faire_action(position, meilleur_action);
    position = res;
    int _butin = ile.passe(position);
    if(_butin == TRESOR)
        trouver_tresor = true;
    butin += _butin;

    return true;
}
