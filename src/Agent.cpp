//
// Created by mithrandir on 26/12/2021.
//

#include "Agent.hpp"

Position Agent::calculerQ(Position etat, CARDINAL action, Ile& ile1) {

    Position nouvelle_position = ile1.nouvelle_position(etat,action);
    ile1.passe(etat);

    double max = get_max_of_Q(nouvelle_position);

    double Q = ile1.matrice_action_etat().at(etat).at(action) + gamma * max;

    q[etat][action] = Q;

    return nouvelle_position;
}

double Agent::get_max_of_Q(Position &_position) {

    double max = std::numeric_limits<int>::min();
    auto actionsPossibles = ile.actions_possibles(_position);
    for(std::pair<CARDINAL, double>item : actionsPossibles) {
        if(max < q[_position][item.first]) {
            max = q[_position][item.first];
        }
    }

    return max;

}

int Agent::cardinal_to_int(CARDINAL & cardinal) {
    switch (cardinal) {

        case NORD:
            return 0;
            break;
        case EST:
            return 2;
            break;
        case SUD:
            return 1;
            break;
        case OUEST:
            return 3;
            break;
    }

    return 0;
}

void Agent::effectuer_episode() {

    Ile tmp_ile = Ile(this->ile);
    Position position = tmp_ile.gen_alea_position();
    //std::cout << "Premiere position " << "X: " << position.first << " Y:" << position.second << "\n";
    //std::cout << "Premiere action " << EnumCardinalStrings[action] << "\n";
    while(tmp_ile.get_carte()[position.second][position.first] != TRESOR) {
        position = calculerQ(position,tmp_ile.gen_alea_action(position),tmp_ile);
    }

}

void Agent::effectuer_episodes(int nb) {

    for(int i=0;i<nb;i++) {
        effectuer_episode();
    }

}

void Agent::afficher_q() {

    std::cout << " Matrice Q" << std::endl;

    std::cout << "N\tS\tE\tO" << std::endl;

    for(auto& item : q) {
        std::cout << item.second[NORD] << '\t' << item.second[SUD] << '\t' << item.second[EST] << '\t' << item.second[OUEST] << std::endl;
    }

}

CARDINAL Agent::meilleur_action(Position etat) {
    CARDINAL action;
    double max = std::numeric_limits<int>::min();
    for(auto& item : q[etat])
    {
        if(max < item.second) {
            max = item.second;
            action = item.first;
        }
    }

    return action;
}

int Agent::random_step(Ile &_ile, Position pos, int nb_steps_max) {

    int step = 0;

    Position position = pos;

    while(_ile.get_carte()[position.second][position.first] != TRESOR && step < nb_steps_max) {
        _ile.passe(position);
        position = _ile.nouvelle_position(position, _ile.gen_alea_action(position));
        step++;
    }

    return nb_steps_max - step;

}
