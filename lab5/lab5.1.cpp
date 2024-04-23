#include <iostream>
#include <string>
#include <stdexcept>

enum class Gender { Male, Female, Other };

struct Character {
    std::string name;
    int age;
    Gender gender;
};

class Node {
public:
    Character data;
    Node* next;

    Node(const Character& data) : data(data), next(nullptr) {}
};

class QueueLinkedList {
private:
    Node* frontPtr;
    Node* rearPtr;

public:
    QueueLinkedList() : frontPtr(nullptr), rearPtr(nullptr) {}

    bool isEmpty() const {
        return frontPtr == nullptr;
    }

    void enqueue(const Character& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontPtr = newNode;
        }
        else {
            rearPtr->next = newNode;
        }
        rearPtr = newNode;
    }

    const Character& front() const {
        if (!isEmpty()) {
            return frontPtr->data;
        }
        else {
            throw std::runtime_error("q emty goodby");
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            Node* temp = frontPtr;
            frontPtr = frontPtr->next;
            delete temp;
            if (frontPtr == nullptr) {
                rearPtr = nullptr;
            }
        }
        else {
            throw std::runtime_error("q emty goodby");
        }
    }

    ~QueueLinkedList() {
        while (frontPtr != nullptr) {
            Node* temp = frontPtr;
            frontPtr = frontPtr->next;
            delete temp;
        }
        rearPtr = nullptr;
    }
};

int main() {
    Character characters[] = {
        {"Rick", 69, Gender::Male},
        {"Paul", 4, Gender::Other},
        {"Astley", 20, Gender::Female}
    };

    QueueLinkedList queue;

    for (const auto& character : characters) {
        queue.enqueue(character);
    }

    while (!queue.isEmpty()) {
        const Character& character = queue.front();
        std::cout << "Name: " << character.name << ", Age: " << character.age << ", Gender: ";
        switch (character.gender) {
        case Gender::Male:
            std::cout << "Male";
            break;
        case Gender::Female:
            std::cout << "Female";
            break;
        case Gender::Other:
            std::cout << "Other";
            break;
        }
        std::cout << std::endl;
        queue.dequeue();
    }

    return 0;
}
