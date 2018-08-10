#include <iostream>

#include "Vertex.hpp"

using namespace std;

int main() {
    Vertex::Ptr v0 = std::make_shared<Vertex>(0, 1);
    Vertex::Ptr v1 = std::make_shared<Vertex>(1, 20);
    v0->addSuccessor(v1, 5);
    v1->addSuccessor(v0, 10);

    auto t = v0->getPredecessor(1);
    if (t.first) {
        cout << t.second << '\n';
    }
    else {
        cout << "Empty\n";
    }
    return 0;
}