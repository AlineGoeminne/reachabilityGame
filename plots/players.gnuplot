set terminal pngcairo size 1920,1080
set output "players.png"

set title "Temps d'exécution moyen et médian et pourcentage de timeouts en fonction du nombre de joueurs (1000 générations)"

set xtics nomirror
set xtics 1
set logscale y

set y2tics
unset logscale y2

set xlabel "nombre de joueurs\n"
set ylabel "temps en ms"
set y2label "pourcentage de timeouts"

set style data linespoints

set key bmargin horizontal center

plot 'naivePlayers.data' using 1:2 title "Moyennes des temps d'exécution - C++ - générateur naïf" axes x1y1,\
    "" using 1:3 title "Médiannes des temps d'exécution - C++ - générateur naïf" axes x1y1,\
    "" using 1:($4/10) title "Pourcentage de timeouts - C++ - générateur naïf" axes x1y2 with points pointsize 2,\
    "treePlayers.data" using 1:2 title "Moyenne des temps d'exécution - C++ - générateur arbre" axes x1y1,\
    "" using 1:3 title "Médiannes des temps d'exécution - C++ - générateur arbre" axes x1y1,\
    "" using 1:($4/10) title "Pourcentage de timeouts - C++ - générateur arbre" axes x1y2 with points pointsize 2