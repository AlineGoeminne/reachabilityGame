set terminal pngcairo size 1920,1080
set output "size.png"

set title "Temps d'exécution moyen et médian en fonction du nombre de nœuds (1000 générations par taille)"

set xtics nomirror
set logscale y

set xlabel "taille"
set ylabel "temps en ms"

set style data linespoints

plot 'naiveSize.data' using 2:xtic(1) title "Valeurs positives (moyennes) - C++ - générateur naïf",\
    "" using 3:xtic(1) title "Valeurs positives (médiannes) - C++ - générateur naïf",\
    "treeSize.data" using 2:xtic(1) title "Valeurs positives (moyennes) - C++ - générateur arbre",\
    "" using 3:xtic(1) title "Valeurs positives (médiannes) - C++ - générateur arbre",\
    "sizePython.data" using 2:xtic(1) title "Valeurs positives (moyennes) - Python",\
    "" using 3:xtic(1) title "Valeurs positives (médiannes) - Python"