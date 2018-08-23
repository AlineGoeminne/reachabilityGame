set terminal pngcairo size 1920,1080
set output "players.png"

set title "Temps d'exécution moyen et médian et nombre de timeouts en fonction du nombre de joueurs (1000 générations par taille)"

set xtics nomirror
set logscale y

set y2tics
unset logscale y2

set xlabel "taille"
set ylabel "temps en ms"
set y2label "nombre de joueurs"

set style data linespoints

plot 'naivePlayers.data' using 2:xtic(1) title "Moyennes des temps d'exécution - C++ - générateur naïf" axes x1y1,\
    "" using 3:xtic(1) title "Médiannes des temps d'exécution - C++ - générateur naïf" axes x1y1,\
    "" using 4:xtic(1) title "Nombre de timeouts - C++ - générateur naïf" axes x1y2 with points pointsize 2,\
    "treePlayers.data" using 2:xtic(1) title "Moyenne des temps d'exécution - C++ - générateur arbre" axes x1y1,\
    "" using 3:xtic(1) title "Médiannes des temps d'exécution - C++ - générateur arbre" axes x1y1,\
    "" using 4:xtic(1) title "Nombre de timeouts - C++ - générateur arbre" axes x1y2 with points pointsize 2