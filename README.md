# TP Q Learning
## Simon HEBAN

## Epsilon Greedy

Lien vers le code [src/Pirate.cpp](https://github.com/Miithrandiir/TP_QLearning/blob/main/src/Pirate.cpp#L55)

L'algorithme Epsilon greedy permet de choisir si on fait un mouvement aléatoire ou un très bon mouvement grâce à nombre généré aléatoirement.
Si ce nombre est en dessous d'epsilon on effectue la meilleure action si ce nombre est au-dessus d'epsilon on effectue une action aléatoire.

## Q Learning

Lien vers le code [src/Agent.cpp](https://github.com/Miithrandiir/TP_QLearning/blob/main/src/Agent.cpp#L35)

L'algorithme Q Learning va apprendre de son environnement, de ses choix. Un coefficient important ici sera le coefficient gamma qui va permettre de choisir entre le gain instantané
et le gain qui s'étale sur le temps. Plus le gamma sera élevé plus on choisira le gain potentiel que l'on aura plus tard.

Je peux donner l'exemple de soi avoir (100 € maintenant puis 1 € après) ou (1 € et d'avoir 1 million après). Dans le cas d'un gamma faible on choisirait les 100 € tandis qu'avec un gamma plus élevé on ferait le choix des 1 euro puis 1 million.

## Monte Carlo

Lien vers le code [src/Agent.cpp](https://github.com/Miithrandiir/TP_QLearning/blob/main/src/Agent.cpp#L97)

Pour l'algorithme Monte-Carlo on va tester toutes les actions possibles, ce qui va en résulter, c'est le nombre de pas que l'on doit faire pour arriver au gain (le trésor ici). On va choisir ici le nombre de pas le plus petit qui permettra de rejoindre le trésor.