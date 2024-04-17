#include <iostream>
#include <fstream>
#include <string>

enum class Gender { Male, Female, Other };

struct Character {
    std::string name;
    int age;
    Gender gender;
};

void writeToCSV(const Character& character, std::ofstream& file) {
    file << character.name << "," << character.age << ",";
    switch (character.gender) {
    case Gender::Male:
        file << "M";
        break;
    case Gender::Female:
        file << "F";
        break;
    case Gender::Other:
        file << "O";
        break;
    }
    file << "\n";
}

Character readFromCSV(std::ifstream& file) {
    Character character;
    std::getline(file, character.name, ',');
    file >> character.age;
    file.ignore();
    char genderChar;
    file >> genderChar;
    file.ignore();
    switch (genderChar) {
    case 'M':
        character.gender = Gender::Male;
        break;
    case 'F':
        character.gender = Gender::Female;
        break;
    default:
        character.gender = Gender::Other;
        break;
    }
    return character;
}

int main() {
    Character characters[] = {
        {"Rick", 69, Gender::Male},
        {"Paul", 4, Gender::Other},
        {"Astley", 20, Gender::Female}
    };

    std::ofstream writeFile("characters.csv");
    if (writeFile.is_open()) {
        for (const auto& character : characters) {
            writeToCSV(character, writeFile);
        }
        writeFile.close();
    }
    else {
        std::cerr << "cant write by" << std::endl;
        return 1;
    }

    std::ifstream readFile("characters.csv");
    if (readFile.is_open()) {
        Character character;
        while (!readFile.eof()) {
            character = readFromCSV(readFile);
            if (readFile.fail()) {
                break;
            }
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
        }
        readFile.close();
    }
    else {
        std::cerr << "cant read bye" << std::endl;
        return 1;
    }

    return 0;
}
