set terminal pngcairo size 1920,1080

set title "Temps d'exécution moyen et médian et nombre de timeouts en fonction du nombre de joueurs et du nombre de sommets (1000 générations)"

set xtics 1 nomirror
set ytics 2

set xlabel "nombre de joueurs"
set ylabel "nombre de sommets"
set zlabel "temps en ms"

set style data lines

set hidden3d

set dgrid3d 20,26
set pm3d

set output "naivePlayersSizeMean.png"
splot 'naivePlayersSize.data' using 1:2:3 title "Moyennes des temps d'exécution - C++ - générateur naïf"

set output "naivePlayersSizeMedian.png"
splot 'naivePlayersSize.data' using 1:2:4 title "Médiannes des temps d'exécution - C++ - générateur naïf"

set output "treePlayersSizeMean.png"
splot 'treePlayersSize.data' using 1:2:3 title "Moyennes des temps d'exécution - C++ - générateur arbre"

set output "treePlayersSizeMedian.png"
splot 'treePlayersSize.data' using 1:2:4 title "Médiannes des temps d'exécution - C++ - générateur arbre"