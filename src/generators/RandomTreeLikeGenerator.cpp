#include "generators/RandomTreeLikeGenerator.hpp"

#include <random>
#include <chrono>
#include <iostream>
#include <queue>

#include "generators/GenerateWeights.hpp"

using namespace types;

/**
 * \brief Spécialisation des sommets pour les arbres.
 * 
 * Contient la profondeur du sommet
 */
class TreeVertex : public Vertex {
public:
    typedef std::shared_ptr<TreeVertex> Ptr;

    explicit TreeVertex(unsigned int id, unsigned int player, std::size_t nPlayers) : Vertex(id, player, nPlayers) {}

    std::size_t m_depth;
};
namespace generators {
    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSelf, double probaSameDepth, double probaSkipping, double probaClimbing, bool multipleWeights, std::size_t nPlayers, bool sharedTargets) {
        return randomTreeLikeGenerator(size, lowBranchingFactor, upBranchingFactor, probaSelf, probaSameDepth, probaSkipping, probaClimbing, 1, 1, multipleWeights, nPlayers, sharedTargets);
    }

    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSelf, double probaSameDepth, double probaSkipping, double probaClimbing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets) {
        std::vector<double> probaPlayers(nPlayers, 1./nPlayers);
        return randomTreeLikeGenerator(size, lowBranchingFactor, upBranchingFactor, probaSelf, probaSameDepth, probaSkipping, probaClimbing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers);
    }

    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSelf, double probaSameDepth, double probaSkipping, double probaClimbing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers) {
        std::vector<double> probaTargets(nPlayers, 0.1);
        return randomTreeLikeGenerator(size, lowBranchingFactor, upBranchingFactor, probaSelf, probaSameDepth, probaSkipping, probaClimbing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets);
    }

    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSelf, double probaSameDepth, double probaSkipping, double probaClimbing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers, const std::vector<double> &probaTargets) {
        std::vector<Long> maximumTargets(nPlayers, Long::infinity);
        return randomTreeLikeGenerator(size, lowBranchingFactor, upBranchingFactor, probaSelf, probaSameDepth, probaSkipping, probaClimbing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets, maximumTargets);
    }

    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSelf, double probaSameDepth, double probaSkipping, double probaClimbing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers, const std::vector<double> &probaTargets, const std::vector<types::Long>& maximumTargets) {
        if (probaPlayers.size() != nPlayers || probaTargets.size() != nPlayers || maximumTargets.size() != nPlayers) {
            throw std::runtime_error("randomGenerator: les tableaux de probabilité doivent arriver une taille identique au nombre de joueurs");
        }
        if (lowBranchingFactor == 0 || lowBranchingFactor == 0) {
            throw std::runtime_error("randomTreeLikeGenerator: les bornes sur le facteur de branchement doivent être > 0");
        }
        if (lowBranchingFactor > upBranchingFactor) {
            throw std::runtime_error("randomGenerator: la borne inférieure sur le facteur de branchement ne peut pas être supérieur à la borne supérieure");
        }
        if (lowBranchingFactor > size || upBranchingFactor > size) {
            throw std::runtime_error("randomGenerator: les bornes sur le facteur de branchement ne peuvent pas dépasser le nombre de noeuds");
        }

        // On crée les générateurs aléatoires qui seront utilisés
        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
        std::discrete_distribution<std::size_t> playersDistribution(probaPlayers.begin(), probaPlayers.end()); // Sommet appartient au joueur i; i est tiré aléatoirement selon probaPlayers
        std::vector<std::bernoulli_distribution> targetsDistributions; // Pour chaque joueur, probabilité qu'un sommet soit une cible
        std::uniform_int_distribution<std::size_t> branchingFactorDistribution(lowBranchingFactor, upBranchingFactor); // Distribution pour le facteur de branchement
        auto weightDistribution = constructWeightDistribution(minWeight, maxWeight);
        std::bernoulli_distribution selfDistribution(probaSelf); // Distribution pour savoir si on peut générer un arc de v à v
        std::bernoulli_distribution sameDepthDistribution(probaSameDepth); // Distribution pour savoir si on peut générer un arc entre deux sommets à la même profondeur
        std::bernoulli_distribution skippingDistribution(probaSkipping); // Distribution pour savoir si on peut générer un arc entre un sommet et un autre plus profond qui n'est pas son enfant
        std::bernoulli_distribution climbingDistribution(probaClimbing); // Distribution pour savoir si on peut générer un arc qui monte dans l'arbre
        std::uniform_int_distribution<std::size_t> forceTargetDistribution(0, size-1); // Distribution pour décider quel sommet devient une cible quand il faut en forcer une pour un joueur

        // On crée les joueurs
        std::vector<Player> players;
        for (std::size_t i = 0 ; i < nPlayers ; i++) {
            players.emplace_back(i); // On construit le joueur en lui donnant uniquement son ID
            targetsDistributions.emplace_back(probaTargets[i]); // On construit le générateur aléatoire (booléen) pour décider si un sommet est une cible pour le joueur i
        }

        // On va créer les sommets
        std::vector<TreeVertex::Ptr> vertices(size, nullptr);
        for (std::size_t i = 0 ; i < size ; i++) {
            // On choisit le joueur
            std::size_t player = playersDistribution(generator);
            vertices[i] = std::make_shared<TreeVertex>(i, player, nPlayers);

            players[player].addVertex(vertices[i]);

            // On décide si le sommet est une cible 
            for (std::size_t j = 0 ; j < nPlayers ; j++) {
                if (players[player].getGoals().size() < maximumTargets[j] && targetsDistributions[j](generator)) {
                    players[j].addGoal(vertices[i]);
                    vertices[i]->addTargetFor(j);

                    if (!sharedTargets) {
                        // On s'arrête parce qu'on ne peut pas partager une cible
                        break;
                    }
                }
            }
        }

        // On vérifie que tous les joueurs ont une cible
        for (Player &p : players) {
            if (p.getGoals().size() == 0) {
                p.addGoal(vertices[forceTargetDistribution(generator)]);
            }
        }

        vertices[0]->m_depth = 0;
        std::queue<TreeVertex::Ptr> queue;
        queue.push(vertices[0]);
        std::size_t nextFreeID = 1;

        while (!queue.empty() && nextFreeID < size) {
            TreeVertex::Ptr root = queue.front();
            queue.pop();

            std::size_t e = branchingFactorDistribution(generator);
            
            for (std::size_t i = 0 ; i < e && nextFreeID < size ; i++) {
                TreeVertex::Ptr child = vertices[nextFreeID++];
                child->m_depth = root->m_depth + 1;
                root->addSuccessor(child, generateWeights(nPlayers, generator, weightDistribution, multipleWeights));

                queue.push(child);
            }
        }

        for (TreeVertex::Ptr v : vertices) {
            for (TreeVertex::Ptr u : vertices) {
                if (v->hasSuccessor(u->getID())) {
                    continue;
                }
                if (v->getID() == u->getID() && selfDistribution(generator)) {
                    // Même sommet
                    v->addSuccessor(u, generateWeights(nPlayers, generator, weightDistribution, multipleWeights));
                }
                else if (u->m_depth > v->m_depth && skippingDistribution(generator)) {
                    // On veut descendre dans l'arbre
                    v->addSuccessor(u, generateWeights(nPlayers, generator, weightDistribution, multipleWeights));
                }
                else if (u->m_depth == v->m_depth && sameDepthDistribution(generator)) {
                    // Frères/cousins
                    v->addSuccessor(u, generateWeights(nPlayers, generator, weightDistribution, multipleWeights));
                }
                else if (u->m_depth < v->m_depth && climbingDistribution(generator)) {
                    // On veut remonter dans l'arbre
                    v->addSuccessor(u, generateWeights(nPlayers, generator, weightDistribution, multipleWeights));
                }
            }

            // On vérifie qu'on n'est pas dans un cul-de-sac
            if (v->getNumberSuccessors() == 0) {
                // Sinon, on ajoute un arc de v à v
                v->addSuccessor(v, generateWeights(nPlayers, generator, weightDistribution, multipleWeights));
            }
        }

        std::vector<Vertex::Ptr> baseVertices(vertices.begin(), vertices.end());
        Graph graph(baseVertices, nPlayers);

        ReachabilityGame game(graph, baseVertices[0], players);

        return game;
    }
}