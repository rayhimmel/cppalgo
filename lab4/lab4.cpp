#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int value;
    std::vector<Node*> neighbors;

    Node(int val) : value(val) {}
};

int sumOfNeighbors(Node* node) {
    int sum = 0;
    for (Node* neighbor : node->neighbors) {
        sum += neighbor->value;
    }
    return sum;
}

void DFS(Node* node) {
    if (node == nullptr) return;

    std::cout << node->value << " ";

    for (Node* neighbor : node->neighbors) {
        DFS(neighbor);
    }
}

void BFS(Node* node) {
    if (node == nullptr) return;

    std::queue<Node*> q;
    q.push(node);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        std::cout << current->value << " ";

        for (Node* neighbor : current->neighbors) {
            q.push(neighbor);
        }
    }
}

int main() {
    Node* A = new Node(1);
    Node* B = new Node(2);
    Node* C = new Node(3);
    Node* D = new Node(4);

    A->neighbors.push_back(B);
    A->neighbors.push_back(C);
    B->neighbors.push_back(C);
    C->neighbors.push_back(D);
    D->neighbors.push_back(A);
    D->neighbors.push_back(C);

    std::cout << "sum of A neighbors: " << sumOfNeighbors(A) << std::endl;

    std::cout << "DFS: ";
    DFS(A);
    std::cout << std::endl;

    std::cout << "BFS: ";
    BFS(A);
    std::cout << std::endl;

    delete A;
    delete B;
    delete C;
    delete D;

    return 0;
}

/* направленные графы - каждый нод хранит инфу о своих соседях, но соседи необязательно должны хранить инфу об этом ноде, т.е. меньше памяти требуют
ненаправленные - все узлы хранят инфу обо всех своих соседях */