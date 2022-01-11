#include <iostream>
#include "src/Ile.hpp"
#include "src/Pirate.hpp"
#include "src/Agent.hpp"
#include "chrono"

void comparer_algorithme(int width, int height, int nb_bottles, int nb_exemples);

int main() {

//    std::vector<std::vector<int>> matrice_action_etat = ile.matrice_action_etat();
//
//    Pirate pirate(ile,0.9);
//
//    std::cout << "Le pirate se situe X: " << pirate.get_position().first << " Y: " << pirate.get_position().second << std::endl;
//
//    for(int i=0;i<10000;i++) {
//        pirate.deplacement();
//    }

//    int nb_exemples = 50;
//    int nb_gagnant = 0;
//
//    for (int i = 0; i < nb_exemples; ++i) {
//        Ile ile(5, 5, 10);
//        Agent agent(0.4, ile);
//        Pirate pirate(ile);
//        agent.effectuer_episodes(100);
//        while (pirate.executer_agent(agent));
//        if(pirate.a_trouver_tresor())
//            nb_gagnant++;
//        if (agent.monte_carlo(ile.gen_alea_position(), ile, 10) > 0) {
//            nb_gagnant++;
//        }
//
//    }
//
//    std::cout << '\n';
//    std::cout << "-- STATISTIQUES --" << std::endl;
//    std::cout << "Gagné : " << nb_gagnant << '\n' << "Perdant : " << (nb_exemples - nb_gagnant) << '\n' << "Moyenne : "
//              << ((double) nb_gagnant / (double) nb_exemples) * 100 << " %" << std::endl;

    comparer_algorithme(3,5,10,10);
    comparer_algorithme(5,7,10,10);

    return 0;
}

std::pair<int, double> faire_epsilon_greedy(Pirate &pirate) {
    Pirate cpy_pirate(pirate);
    int nbStep = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while(cpy_pirate.deplacement()) nbStep++;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start);
    return std::make_pair(nbStep, duration.count());
}

std::pair<int, double> faire_q_learning(Pirate &pirate, Agent &agent) {
    Pirate cpy_pirate(pirate);
    Agent cpy_agent(agent);
    cpy_agent.effectuer_episodes(MAX_MOUVEMENT);
    int nb_step = 0;
    auto start = std::chrono::high_resolution_clock::now();

    while (cpy_pirate.executer_agent(cpy_agent)) {nb_step++;};

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start);

    return std::make_pair(nb_step, duration.count());
}

std::pair<int, double> faire_monte_carlo(Pirate &pirate, Ile& ile, Agent& agent, int nb_max_step) {
    Pirate cpy_pirate(pirate);
    Agent cpy_agent(agent);
    auto start = std::chrono::high_resolution_clock::now();
    int nb_step = nb_max_step - cpy_agent.monte_carlo(cpy_pirate.get_position(),ile, nb_max_step);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start);
    return std::make_pair(nb_step, duration.count());
}


void comparer_algorithme(int width, int height, int nb_bottles, int nb_exemples) {

    std::pair<int,double> stat_greedy(0,0);
    std::pair<int,double> stat_q_learning(0,0);
    std::pair<int,double> stat_monte_carlo(0,0);

    for (int i = 0; i < nb_exemples; ++i) {
        Ile ile(width, height, nb_bottles);
        Pirate pirate(ile, 0.9);
        Agent agent(0.75, ile);
        auto res_q_learning = faire_q_learning(pirate, agent);
        auto res_monte_carlo = faire_monte_carlo(pirate, ile, agent, 100);
        auto res_greedy = faire_epsilon_greedy(pirate);

        stat_greedy.first += res_greedy.first;
        stat_greedy.second += res_greedy.second / 1000000;

        stat_q_learning.first += res_q_learning.first;
        stat_q_learning.second += res_q_learning.second / 1000000;

        stat_monte_carlo.first += res_monte_carlo.first;
        stat_monte_carlo.second += res_monte_carlo.second / 1000000;
    }

    std::cout << nb_exemples << " xps, " << "environment size " << width << "x" << height << ", " << TRESOR << " local optima" << std::endl;
    std::cout << "\t" << "Q Learning: " << stat_q_learning.first/nb_exemples << " steps (" << stat_q_learning.second/nb_exemples << "s per run)" << std::endl;
    std::cout << "\t" << "E Greedy: " << stat_greedy.first/nb_exemples << " steps (" << stat_greedy.second/nb_exemples << "s per run)" << std::endl;
    std::cout << "\t" << "MonteCarlo: " << stat_monte_carlo.first/nb_exemples << " steps (" << stat_monte_carlo.second/nb_exemples << "s per run)" << std::endl;
}