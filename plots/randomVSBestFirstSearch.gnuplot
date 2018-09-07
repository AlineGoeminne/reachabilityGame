set terminal pngcairo size 1920,1080
set output "randomVSBestFirstSearch.png"

set title "Comparaison de A* et de la méthode naïve"

set xtics 1 nomirror

set xlabel "nombre de sommets"

set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set boxwidth 0.9

plot 'randomVSBestFirstSearch.data' using 2:xtic(1) title 'Nombre de fois que la méthode naïve est meilleure',\
    '' using 5:xtic(1) title "Nombre de fois que la méthode naïve n'a pas créé d'équilibre de Nash",\
    '' using 3:xtic(1) title 'Nombre de fois que la méthode A* est meilleure',\
    '' using 4:xtic(1) title "Nombre de fois que la méthode A* a atteint la limite de temps"