#include <iostream>
#include "src/Ile.hpp"
#include "src/Pirate.hpp"


int main() {

    Ile ile(5,5,2);

    std::cout << ile;

    std::vector<std::vector<int>> matrice_action_etat = ile.matrice_action_etat();

    Pirate pirate(ile,0.9);

    std::cout << "Le pirate se situe X: " << pirate.get_position().first << " Y: " << pirate.get_position().second << std::endl;

    for(int i=0;i<10000;i++) {
        pirate.deplacement();
    }

    return 0;
}
