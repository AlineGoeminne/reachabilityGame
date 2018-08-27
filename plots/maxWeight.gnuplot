set terminal pngcairo size 1920,1080
set output "maxWeight.png"

set title "Temps d'exécution moyen et médian et nombre de timeouts en fonction du poids maximal (1000 générations)"

set xtics 2 nomirror
set logscale y

set y2tics
unset logscale y2

set xlabel "poids maximal"
set ylabel "temps en ms"
set y2label "nombre de timeouts"

set style data linespoints

plot 'naiveMaxWeight.data' using 1:2 title "Moyennes des temps d'exécution - C++ - générateur naïf" axes x1y1,\
    "" using 1:3 title "Médiannes des temps d'exécution - C++ - générateur naïf" axes x1y1,\
    "" using 1:4 title "Nombre de timeouts - C++ - générateur naïf" axes x1y2 with points pointsize 2,\
    "treeMaxWeight.data" using 1:2 title "Moyenne des temps d'exécution - C++ - générateur arbre" axes x1y1,\
    "" using 1:3 title "Médiannes des temps d'exécution - C++ - générateur arbre" axes x1y1,\
    "" using 1:4 title "Nombre de timeouts - C++ - générateur arbre" axes x1y2 with points pointsize 2