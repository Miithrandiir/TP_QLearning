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

int Agent::random_step(Ile _ile, Position pos, int nb_steps_max) {

    int step = 0;

    Position position = pos;

    while(_ile.get_carte()[position.second][position.first] != TRESOR && step < nb_steps_max) {
        _ile.passe(position);
        position = _ile.nouvelle_position(position, _ile.gen_alea_action(position));
        step++;
    }

    return nb_steps_max - step;

}

int Agent::monte_carlo(Position pos, Ile _ile, int nb_steps_max) {
    int step = 0;

    Position position = pos;

    while(_ile.get_carte()[position.second][position.first] != TRESOR && step < nb_steps_max) {
        _ile.passe(position);

        auto actions = _ile.actions_possibles(position);
        int max = std::numeric_limits<int>::min();
        CARDINAL max_action;
        for(auto _a : actions) {

            int res = random_step(_ile, _ile.nouvelle_position(position, _a.first), nb_steps_max);
            if(res > max) {
                max_action = _a.first;
                max = res;
            }
        }

        position = _ile.nouvelle_position(position, max_action);
        step++;
    }
    return nb_steps_max - step;
}
