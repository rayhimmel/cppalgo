#include <iostream>
#include <fstream>
#include <string>
#include <cctype> 

enum class Gender { Male, Female, Other };

bool isValidGender(char genderChar) {
    genderChar = std::toupper(genderChar);
    return genderChar == 'M' || genderChar == 'F' || genderChar == 'O';
}

bool isValidAge(int age) {
    return age >= 0 && age <= 122;
}

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
    if (!isValidGender(genderChar)) { 
        std::cerr << "idc u enby now" << std::endl;
        character.gender = Gender::Other; 
    }
    else {
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
    }
    if (!isValidAge(character.age)) {
        std::cerr << "idc u 0 y.o. now" << std::endl;
        character.age = 0;
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
        std::cerr << "cant write bye" << std::endl;
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
