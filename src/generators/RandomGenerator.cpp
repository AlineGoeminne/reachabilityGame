#include "generators/RandomGenerator.hpp"

#include <random>
#include <chrono>

#include "generators/GenerateWeights.hpp"

using namespace types;

namespace generators {
    ReachabilityGame randomGenerator(std::size_t size, std::size_t lowOutgoing, std::size_t upOutgoing, std::size_t nPlayers, bool sharedTargets) {
        return randomGenerator(size, lowOutgoing, upOutgoing, 1, 1, false, nPlayers, sharedTargets);
    }

    ReachabilityGame randomGenerator(std::size_t size, std::size_t lowOutgoing, std::size_t upOutgoing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets) {
        std::vector<double> probaPlayers(nPlayers, 1./nPlayers);
        return randomGenerator(size, lowOutgoing, upOutgoing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers);
    }

    ReachabilityGame randomGenerator(std::size_t size, std::size_t lowOutgoing, std::size_t upOutgoing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers) {
        std::vector<double> probaTargets(nPlayers, 0.1);
        return randomGenerator(size, lowOutgoing, upOutgoing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets);
    }

    ReachabilityGame randomGenerator(std::size_t size, std::size_t lowOutgoing, std::size_t upOutgoing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers, const std::vector<double>& probaTargets) {
        std::vector<Long> maximumTargets(nPlayers, Long::infinity);
        return randomGenerator(size, lowOutgoing, upOutgoing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets, maximumTargets);
    }

    ReachabilityGame randomGenerator(std::size_t size, std::size_t lowOutgoing, std::size_t upOutgoing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers, const std::vector<double>& probaTargets, const std::vector<types::Long>& maximumTargets) {
        if (probaPlayers.size() != nPlayers || probaTargets.size() != nPlayers || maximumTargets.size() != nPlayers) {
            throw std::runtime_error("randomGenerator: les tableaux de probabilité doivent arriver une taille identique au nombre de joueurs");
        }
        if (lowOutgoing == 0 || upOutgoing == 0) {
            throw std::runtime_error("randomGenerator: les bornes sur le nombre de noeuds sortants doivent être > 0");
        }
        if (lowOutgoing > upOutgoing) {
            throw std::runtime_error("randomGenerator: la borne inférieure sur le nombre de noeuds sortants ne peut pas être supérieur à la borne supérieure");
        }
        if (lowOutgoing > size || upOutgoing > size) {
            throw std::runtime_error("randomGenerator: les bornes sur le nombre de noeuds sortants ne peuvent pas dépasser le nombre de noeuds");
        }

        // On crée les générateurs aléatoires qui seront utilisés
        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
        std::discrete_distribution<std::size_t> playersDistribution(probaPlayers.begin(), probaPlayers.end()); // Sommet appartient au joueur i; i est tiré aléatoirement selon probaPlayers
        std::vector<std::bernoulli_distribution> targetsDistributions; // Pour chaque joueur, probabilité qu'un sommet soit une cible
        std::uniform_int_distribution<std::size_t> numberOfNeighborsDistribution(lowOutgoing, upOutgoing); // Distribution pour le nombre d'arcs sortants
        std::uniform_int_distribution<std::size_t> neighborDistribution(0, size-1); // Distribution pour les sommets des arcs
        auto weightDistribution = constructWeightDistribution(minWeight, maxWeight);

        // On crée les joueurs
        std::vector<Player> players;
        for (std::size_t i = 0 ; i < nPlayers ; i++) {
            players.emplace_back(i); // On construit le joueur en lui donnant uniquement son ID
            targetsDistributions.emplace_back(probaTargets[i]); // On construit le générateur aléatoire (booléen) pour décider si un sommet est une cible pour le joueur i
        }
        
        // On crée tous les sommets
        std::vector<Vertex::Ptr> vertices(size, nullptr);
        for (std::size_t i = 0 ; i < size ; i++) {
            // On tire aléatoirement le joueur qui possède ce noeud
            std::size_t player = playersDistribution(generator);

            vertices[i] = std::make_shared<Vertex>(i, player, nPlayers);

            players[player].addVertex(vertices[i]);

            // On décide aléatoirement pour chaque joueur si le sommet est une cible
            for (std::size_t j = 0 ; j < nPlayers ; j++) {
                // On vérifie aussi que le joueur peut encore avoir une nouvelle cible
                if (maximumTargets[j] > players[j].getGoals().size() && targetsDistributions[j](generator)) {
                    players[j].addGoal(vertices[i]);
                    vertices[i]->addTargetFor(j);

                    if (!sharedTargets) {
                        // On ne peut partager les cibles. Donc, on arrête
                        break;
                    }
                }
            }
        }

        // On va vérifier que chaque joueur a bien au moins une cible. Si non, on va lui en donner une de force en négligeant sharedTargets
        for (Player &p : players) {
            if (p.getGoals().size() == 0) {
                p.addGoal(vertices[neighborDistribution(generator)]);
            }
        }

        // On crée les arcs
        for (std::size_t i = 0 ; i < size ; i++) {
            Vertex::Ptr v = vertices[i];

            // On tire le nombre d'arcs sortants
            std::size_t e = numberOfNeighborsDistribution(generator);

            while (e-- > 0) {
                // On détermine le voisin
                Vertex::Ptr u = vertices[neighborDistribution(generator)];
                // On ne veut pas avoir deux arcs v->u
                while (v->hasSuccessor(u->getID())) {
                    u = vertices[neighborDistribution(generator)];
                }

                v->addSuccessor(u, generateWeights(nPlayers, generator, weightDistribution, multipleWeights));
            }
        }

        Graph graph(vertices, 2);

        ReachabilityGame game(graph, vertices[0], players);

        return game;
    }
}