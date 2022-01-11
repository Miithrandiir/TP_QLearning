//
// Created by mithrandir on 26/12/2021.
//

#ifndef QLEARNING_AGENT_HPP
#define QLEARNING_AGENT_HPP

#include "vector"
#include "Ile.hpp"

class Agent {

private:

    double gamma;
    /**
     * [0] => représente les si
     *      [0] => NORD
     *      [1] => SUD
     *      [2] => EST
     *      [3] => OUEST
     */
    std::map<Position, std::map<CARDINAL, double>> q;
    Ile ile;
public:

    Agent(double _gamma, Ile &_ile) : gamma(_gamma), ile(_ile) {

        for (int y = 0; y < ile.get_taille_y(); ++y) {
            for (int x = 0; x < ile.get_taille_x(); ++x) {
                std::map<CARDINAL, double> tmp;
                //Init NORD SUD EST OUEST
                tmp.emplace(NORD,0);
                tmp.emplace(SUD,0);
                tmp.emplace(EST,0);
                tmp.emplace(OUEST,0);
                //Si
                q.insert(std::make_pair(std::make_pair(x,y),tmp));
            }
        }

    }

    Position calculerQ(Position etat, CARDINAL action, Ile& ile1);

    double get_max_of_Q(Position&);

    int cardinal_to_int(CARDINAL&);

    void effectuer_episode();

    void effectuer_episodes(int nb);

    CARDINAL meilleur_action(Position position1);

    void afficher_q();

    int random_step(Ile _ile, Position pos, int nb_steps_max);

    int monte_carlo(Position pos, Ile _ile, int nb_steps_max);

};


#endif //QLEARNING_AGENT_HPP
