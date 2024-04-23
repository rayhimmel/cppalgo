#include <iostream>
#include <string>

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

class StackLinkedList {
private:
    Node* top;

public:
    StackLinkedList() : top(nullptr) {}

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(const Character& value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    const Character& getLastElement() const {
        if (!isEmpty()) {
            return top->data;
        }
        else {
            throw std::runtime_error("stack emty goodby");
        }
    }

    void pop() {
        if (!isEmpty()) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
        else {
            throw std::runtime_error("stack emty goodby");
        }
    }

    ~StackLinkedList() {
        while (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

int main() {
    Character characters[] = {
        {"Rick", 69, Gender::Male},
        {"Paul", 4, Gender::Other},
        {"Astley", 20, Gender::Female}
    };

    StackLinkedList stack;

    for (const auto& character : characters) {
        stack.push(character);
    }

    while (!stack.isEmpty()) {
        const Character& character = stack.getLastElement();
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
        stack.pop();
    }

    return 0;
}
