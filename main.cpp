#include <iostream>
#include "src/Ile.hpp"
#include "src/Pirate.hpp"
#include "src/Agent.hpp"


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

    int nb_exemples = 50;
    int nb_gagnant = 0;

    for(int i = 0; i<nb_exemples;++i) {
        Ile ile(5,5,10);
        Agent agent(0.4,ile);
        Pirate pirate(ile);
//        agent.effectuer_episodes(100);
//        while (pirate.executer_agent(agent));
//        if(pirate.a_trouver_tresor())
//            nb_gagnant++;
        if(agent.random_step(ile, ile.gen_alea_position(), 100) > 0) {
            nb_gagnant++;
        }

    }

    std::cout << '\n';
    std::cout << "-- STATISTIQUES --" << std::endl;
    std::cout << "Gagné : " << nb_gagnant << '\n' << "Perdant : " << (nb_exemples - nb_gagnant) << '\n' << "Moyenne : " << ((double)nb_gagnant/(double)nb_exemples)*100 << " %" << std::endl;

    return 0;
}
