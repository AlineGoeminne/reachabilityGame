#include <iostream>

#include "Vertex.hpp"
#include "Graph.hpp"
#include "Player.hpp"

using namespace std;

int main() {
    Vertex::Ptr v0 = std::make_shared<Vertex>(0, 1, 2);
    Vertex::Ptr v1 = std::make_shared<Vertex>(1, 20, 2);
    v0->addSuccessor(v1, 5);
    v1->addSuccessor(v0, 10);

    std::vector<Vertex::Ptr> vertices(2);
    vertices[0] = v0;
    vertices[1] = v1;

    Graph g(vertices, 2);

    std::cout << sizeof(char) << '\n';
    std::cout << sizeof(Player*) << '\n';
    std::cout << sizeof(std::unique_ptr<Player>) << '\n';
    return 0;
}