set terminal pngcairo size 1920,1080
set output "size.png"

set title "Temps d'exécution moyen et médian et pourcentage de timeouts en fonction du nombre de nœuds (1000 générations)"

set xtics 1 nomirror
set logscale y

set y2tics
unset logscale y2

set xlabel "taille"
set ylabel "temps en ms"
set y2label "pourcentage de timeouts"

set style data linespoints

f(x) = x

plot 'naiveSize.data' using 1:2 title "Moyennes des temps d'exécution - C++ - générateur naïf" axes x1y1,\
    "" using 1:3 title "Médiannes des temps d'exécution - C++ - générateur naïf" axes x1y1,\
    "" using 1:($4/10) title "Pourcentage de timeouts - C++ - générateur naïf" axes x1y2 with points pointsize 2,\
    "treeSize.data" using 1:2 title "Moyenne des temps d'exécution - C++ - générateur arbre" axes x1y1,\
    "" using 1:3 title "Médiannes des temps d'exécution - C++ - générateur arbre" axes x1y1,\
    "" using 1:($4/10) title "Pourcentage de timeouts - C++ - générateur arbre" axes x1y2 with points pointsize 2,\
    "sizePython.data" using 1:($2*1000) title "Moyenne des temps d'exécution - Python" axes x1y1,\
    "" using 1:($3*1000) title "Médiannes des temps d'exécution - Python" axes x1y1,\
    f(x) title "Fonction linéaire",\
    log(x) title "Fonction log"