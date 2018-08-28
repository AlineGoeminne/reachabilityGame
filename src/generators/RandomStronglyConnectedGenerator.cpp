#include "generators/RandomStronglyConnectedGenerator.hpp"

#include <random>
#include <chrono>

#include "generators/RandomGenerator.hpp"
#include "algorithms/Tarjan.hpp"
#include "generators/GenerateWeights.hpp"

using namespace algorithms;

namespace generators {
    ReachabilityGame randomStronglyConnectedGenerator(std::size_t size, std::size_t lowOutgoing, std::size_t upOutgoing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers, const std::vector<double>& probaTargets, const std::vector<types::Long>& maximumTargets) {
        // On commence par générer un jeu
        const ReachabilityGame game = randomGenerator(size, lowOutgoing, upOutgoing, maxWeight, minWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets, maximumTargets);

        // Et on va modifier le graphe
        Graph graph = game.getGraph();
        std::vector<Vertex::Ptr>& vertices = graph.getVertices();
        
        stronglyConnectedComponents components = tarjan(graph);

        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
        auto weightDistribution = constructWeightDistribution(minWeight, maxWeight);

        // Tant que tout le graphe n'est pas qu'une seule composante, on va fusionner deux composantes (aléatoirement choisies) en une seule
        while (components.size() > 1) {
            // On tire les deux composantes
            std::uniform_int_distribution<std::size_t> componentSelection(0, components.size() - 1);
            std::size_t i = 0, j = 0;
            while (i == j) {
                i = componentSelection(generator);
                j = componentSelection(generator);
            }
            
            stronglyConnectedComponent a, b;
            std::size_t k = 0;
            for (const stronglyConnectedComponent &compo : components) {
                if (k == i) {
                    a = compo;
                }
                if (k == j) {
                    b = compo;
                }
                k++;
            }

            // On tire deux sommets dans a et deux sommets dans b
            std::uniform_int_distribution<std::size_t> vertexASelection(0, a.size() - 1);
            std::uniform_int_distribution<std::size_t> vertexBSelection(0, b.size() - 1);

            // Les indices dans les ensembles A et B
            std::size_t vA = vertexASelection(generator);
            std::size_t uA = vertexASelection(generator);
            std::size_t vB = vertexBSelection(generator);
            std::size_t uB = vertexBSelection(generator);

            // On récupère les ID des sommets correspondants
            unsigned int vAID = 0, uAID = 0, vBID = 0, uBID = 0;
            k = 0;
            for (unsigned int v : a) {
                if (k == vA) {
                    vAID = v;
                }
                if (k == uA) {
                    uAID = v;
                }
                k++;
            }
            k = 0;
            for (unsigned int v : b) {
                if (k == vB) {
                    vBID = v;
                }
                if (k == uB) {
                    uBID = v;
                }
                k++;
            }

            // On crée un lien vA->vB et uB->uA
            // Comme a et b sont des composantes fortement connexes, on obtient une plus grosse composante fortement connexe
            if (!vertices[vAID]->hasSuccessor(vBID)) {
                vertices[vAID]->addSuccessor(vertices[vBID], generateWeights(nPlayers, generator, weightDistribution, multipleWeights));
            }
            if (!vertices[uBID]->hasSuccessor(uAID)) {
                vertices[uBID]->addSuccessor(vertices[uAID], generateWeights(nPlayers, generator, weightDistribution, multipleWeights));
            }

            components = algorithms::tarjan(graph);
        }

        // On a créé de nouveaux arcs. On doit mettre à jour les poids maximaux
        graph.updateMaxWeights();

        // On crée les nouveaux joueurs (ils ont les mêmes sommets et cibles que ceux du jeu de base)
        std::vector<Player> players;
        players.reserve(game.getPlayers().size());

        for (std::size_t i = 0 ; i < game.getPlayers().size() ; i++) {
            const Player& p = game.getPlayers()[i];
            Player newP(i);
            for (const Vertex::Ptr v : p.getVertices()) {
                newP.addVertex(vertices[v->getID()]);
            }
            for (const Vertex::Ptr v : p.getGoals()) {
                newP.addGoal(vertices[v->getID()]);
            }
            players.push_back(newP);
        }

        return ReachabilityGame(graph, vertices[game.getInit()->getID()], players);
    }
}