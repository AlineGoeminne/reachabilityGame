set terminal pngcairo size 1920,1080
set output "maxWeight.png"

set title "Temps d'exécution moyen et médian et nombre de timeouts en fonction du poids maximal (1000 générations)"

set xtics nomirror
set logscale y

set y2tics
unset logscale y2

set xlabel "poids maximal"
set ylabel "temps en ms"
set y2label "nombre de timeouts"

set style data linespoints

plot 'naiveMaxWeight.data' using 2:xtic(1) title "Moyennes des temps d'exécution - C++ - générateur naïf" axes x1y1,\
    "" using 3:xtic(1) title "Médiannes des temps d'exécution - C++ - générateur naïf" axes x1y1,\
    "" using 4:xtic(1) title "Nombre de timeouts - C++ - générateur naïf" axes x1y2 with points pointsize 2,\
    "treeMaxWeight.data" using 2:xtic(1) title "Moyenne des temps d'exécution - C++ - générateur arbre" axes x1y1,\
    "" using 3:xtic(1) title "Médiannes des temps d'exécution - C++ - générateur arbre" axes x1y1,\
    "" using 4:xtic(1) title "Nombre de timeouts - C++ - générateur arbre" axes x1y2 with points pointsize 2