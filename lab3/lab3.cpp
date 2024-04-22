#include <iostream>
#include <string>
#include <cassert>

enum class Gender { Male, Female, Other };

struct Character {
    std::string name;
    int age;
    Gender gender;
};

struct Node {
    Character data;
    Node* next;
};

struct LinkedList {
    Node* head;
    Node* tail;
    size_t size;

    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    Node* insertAfter(Node* node, const Character& value) {
        Node* newNode = new Node{ value, nullptr };
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else if (node == nullptr) {
            newNode->next = head;
            head = newNode;
        }
        else {
            newNode->next = node->next;
            node->next = newNode;
            if (node == tail)
                tail = newNode;
        }
        size++;
        return newNode;
    }

    struct FindNodeResult {
        Node* previous;
        Node* current;
    };

    FindNodeResult findByAge(int age) {
        FindNodeResult result{ nullptr, head };
        while (result.current && result.current->data.age != age) {
            result.previous = result.current;
            result.current = result.current->next;
        }
        return result;
    }

    void removeAfter(Node* node) {
        if (!head || (node && !node->next))
            return;

        Node* toRemove;
        if (!node) {
            toRemove = head;
            head = toRemove->next;
            if (tail == toRemove)
                tail = nullptr;
        }
        else {
            toRemove = node->next;
            node->next = toRemove->next;
            if (tail == toRemove)
                tail = node;
        }

        delete toRemove;
        size--;
    }

    void assertNoCycles() {
        size_t gotSize = 0;
        Node* current = head;
        while (current) {
            gotSize++;
            current = current->next;
            assert(gotSize <= size);
        }
        if (gotSize == size) {
            std::cout << "zers no cycles & siz is: " << gotSize << std::endl;
        }
    }

    void display() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << "Name: " << current->data.name << ", Age: " << current->data.age << ", Gender: ";
            switch (current->data.gender) {
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
            current = current->next;
        }
    }
};

int main() {
    LinkedList list;
    Character characters[] = {
        {"Rick", 69, Gender::Male},
        {"Paul", 4, Gender::Other},
        {"Astley", 20, Gender::Female}
    };

    list.insertAfter(nullptr, characters[0]);
    list.insertAfter(nullptr, characters[1]);
    list.insertAfter(nullptr, characters[2]);

    list.display();

    LinkedList::FindNodeResult result = list.findByAge(4);
    if (result.current)
        std::cout << "n o d e:  " << result.current->data.name << std::endl;

    list.removeAfter(nullptr);

    std::cout << "\nu got zis: " << std::endl;
    list.display();

    list.assertNoCycles();

    return 0;
}
