#include "generators/RandomTreeLikeGenerator.hpp"

#include <random>
#include <chrono>
#include <iostream>

using namespace types;

class TreeVertex : public Vertex {
public:
    typedef std::shared_ptr<TreeVertex> Ptr;

    explicit TreeVertex(unsigned int id, unsigned int player, std::size_t nPlayers) : Vertex(id, player, nPlayers) {}

    std::size_t m_depth;
};

std::vector<Long> generateWeights(std::size_t nPlayers, std::default_random_engine &generator, std::uniform_int_distribution<long> &weightDistribution, bool multipleWeights) {
    std::vector<Long> weights;
    if (multipleWeights) {
        for (std::size_t i = 0 ; i < nPlayers ; i++) {
            weights.push_back(weightDistribution(generator));
        }
    }
    else {
        weights = std::vector<Long>(nPlayers, weightDistribution(generator));
    }
    return weights;
}

std::size_t generate(TreeVertex::Ptr root, std::size_t firstChildID, std::vector<TreeVertex::Ptr> &vertices, const std::vector<Player> &players, bool multipleWeights, std::default_random_engine& generator, std::uniform_int_distribution<std::size_t>& branchingFactorDistribution, std::uniform_int_distribution<long> &weightDistribution, std::bernoulli_distribution &sameDepthDistribution, std::bernoulli_distribution& skippingDistribution, std::bernoulli_distribution& climbingDistribution) {
    std::size_t size = vertices.size();

    std::size_t e = branchingFactorDistribution(generator);

    std::unordered_set<TreeVertex::Ptr> childs;

    //std::cout << *root << " a " << e << " enfants\n";

    // On définit d'abord tous les enfants
    for (std::size_t i = 0 ; i < e ; i++) {
        if (firstChildID + i >= size) {
            // On a atteint la limite sur le nombre de sommets
            break;
        }

        TreeVertex::Ptr vertex = vertices[firstChildID + i];

        childs.insert(vertex);

        std::vector<Long> weights = generateWeights(players.size(), generator, weightDistribution, multipleWeights);

        root->addSuccessor(vertex, weights);

        vertex->m_depth = root->m_depth + 1;
    }

    // On demande ensuite aux enfants de générer leurs enfants
    std::size_t firstNextID = firstChildID + e;
    for (TreeVertex::Ptr v : childs) {
        firstNextID = generate(v, firstNextID, vertices, players, multipleWeights, generator, branchingFactorDistribution, weightDistribution, sameDepthDistribution, skippingDistribution, climbingDistribution);
    }

    // On va maintenant prendre tous les noeuds et regarder si on peut créer des arcs
    for (std::size_t i = 0 ; i < size ; i++) {
        TreeVertex::Ptr vertex = vertices[i];

        if (root->hasSuccessor(vertex->getID())) {
            // On a déjà un lien => on passe au suivant
            continue;
        }

        if (vertex->m_depth < root->m_depth) {
            // On veut remonter dans l'arbre
            if (climbingDistribution(generator)) {
                root->addSuccessor(vertex, generateWeights(players.size(), generator, weightDistribution, multipleWeights));
            }
        }
        else if (vertex->m_depth == root->m_depth) {
            // Même profondeur (frères/cousins)
            if (sameDepthDistribution(generator)) {
                root->addSuccessor(vertex, generateWeights(players.size(), generator, weightDistribution, multipleWeights));
            }
        }
        else {
            // On veut descendre
            if (childs.find(vertex) == childs.end() && skippingDistribution(generator)) {
                // vertex n'est pas un enfant de root
                root->addSuccessor(vertex, generateWeights(players.size(), generator, weightDistribution, multipleWeights));
            }
        }
    }

    // Si root n'a pas d'arc sortant, on fait une boucle sur lui-même
    if (root->getNumberSuccessors() == 0) {
        root->addSuccessor(root, generateWeights(players.size(), generator, weightDistribution, multipleWeights));
    }

    // On retourne l'ID du dernier fils utilisé pour s'assurer que les noeuds ne sont pas réutilisés
    return firstChildID + e;
}

namespace generators {
    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSameDepth, double probaSkipping, double probaClimbing, bool multipleWeights, std::size_t nPlayers, bool sharedTargets) {
        return randomTreeLikeGenerator(size, lowBranchingFactor, upBranchingFactor, probaSameDepth, probaSkipping, probaClimbing, 1, 1, multipleWeights, nPlayers, sharedTargets);
    }

    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSameDepth, double probaSkipping, double probaClimbing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets) {
        std::vector<double> probaPlayers(nPlayers, 1./nPlayers);
        return randomTreeLikeGenerator(size, lowBranchingFactor, upBranchingFactor, probaSameDepth, probaSkipping, probaClimbing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers);
    }

    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSameDepth, double probaSkipping, double probaClimbing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers) {
        std::vector<double> probaTargets(nPlayers, 0.1);
        return randomTreeLikeGenerator(size, lowBranchingFactor, upBranchingFactor, probaSameDepth, probaSkipping, probaClimbing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets);
    }

    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSameDepth, double probaSkipping, double probaClimbing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers, const std::vector<double> &probaTargets) {
        std::vector<Long> maximumTargets(nPlayers, Long::infinity);
        return randomTreeLikeGenerator(size, lowBranchingFactor, upBranchingFactor, probaSameDepth, probaSkipping, probaClimbing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets, maximumTargets);
    }

    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSameDepth, double probaSkipping, double probaClimbing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers, const std::vector<double> &probaTargets, const std::vector<types::Long>& maximumTargets) {
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
        std::uniform_int_distribution<long> weightDistribution(minWeight, maxWeight); // Distribution pour les poids des arcs
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

        // On crée récursivement les arcs
        vertices[0]->m_depth = 0;
        generate(vertices[0], 1, vertices, players, multipleWeights, generator, branchingFactorDistribution, weightDistribution, sameDepthDistribution, skippingDistribution, climbingDistribution);

        std::vector<Vertex::Ptr> baseVertices(vertices.begin(), vertices.end());
        Graph graph(baseVertices, nPlayers);

        ReachabilityGame game(graph, baseVertices[0], players);

        return game;
    }
}