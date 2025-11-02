#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

// =================== STRUCT: ELEMENT (Periodic Table) ===================
struct Element {
    string name;
    string symbol;
    int atomicNumber;
    double atomicWeight;
    double meltingPoint;   // in °C
    double boilingPoint;   // in °C
    int group;
    int period;
};

// Display element details
void displayElement(const Element &e) {
    cout << "\n----------------------------------------\n";
    cout << "Name: " << e.name << endl;
    cout << "Symbol: " << e.symbol << endl;
    cout << "Atomic Number: " << e.atomicNumber << endl;
    cout << "Atomic Weight: " << e.atomicWeight << endl;
    cout << "Melting Point: " << e.meltingPoint << " °C" << endl;
    cout << "Boiling Point: " << e.boilingPoint << " °C" << endl;
    cout << "Group: " << e.group << ", Period: " << e.period << endl;
    cout << "----------------------------------------\n";
}

// Search element by name or symbol
void searchElement(const vector<Element> &elements, const string &query) {
    for (const auto &e : elements) {
        if (e.name == query || e.symbol == query) {
            displayElement(e);
            return;
        }
    }
    cout << "\nElement not found in the database.\n";
}

// =================== COMPOUND MANAGEMENT (OOP + FILE HANDLING) ===================

// Base class
class Compound {
protected:
    string name;
    float molecularWeight = 0;

public:
    virtual void inputData() = 0;
    virtual void displayData() const = 0;
    virtual void saveToFile(ofstream &file) const = 0;
    virtual ~Compound() {}
};

// Derived class for Organic Compounds
class OrganicCompound : public Compound {
private:
    int carbonAtoms = 0, hydrogenAtoms = 0, oxygenAtoms = 0;

public:
    void inputData() override {
        cout << "\nEnter Organic Compound Name: ";
        cin >> name;
        cout << "Enter number of Carbon atoms: ";
        cin >> carbonAtoms;
        cout << "Enter number of Hydrogen atoms: ";
        cin >> hydrogenAtoms;
        cout << "Enter number of Oxygen atoms: ";
        cin >> oxygenAtoms;

        molecularWeight = (carbonAtoms * 12.01) + (hydrogenAtoms * 1.008) + (oxygenAtoms * 16.00);
    }

    void displayData() const override {
        cout << "\n[Organic Compound]";
        cout << "\nName: " << name;
        cout << "\nC: " << carbonAtoms << ", H: " << hydrogenAtoms << ", O: " << oxygenAtoms;
        cout << "\nMolecular Weight: " << fixed << setprecision(2) << molecularWeight << endl;
    }

    void saveToFile(ofstream &file) const override {
        file << "Organic," << name << "," << molecularWeight << endl;
    }
};

// Derived class for Inorganic Compounds
class InorganicCompound : public Compound {
private:
    int totalAtoms = 0;
    float atomicWeight = 0;

public:
    void inputData() override {
        cout << "\nEnter Inorganic Compound Name: ";
        cin >> name;
        cout << "Enter number of atoms: ";
        cin >> totalAtoms;
        cout << "Enter average atomic weight: ";
        cin >> atomicWeight;

        molecularWeight = totalAtoms * atomicWeight;
    }

    void displayData() const override {
        cout << "\n[Inorganic Compound]";
        cout << "\nName: " << name;
        cout << "\nTotal Atoms: " << totalAtoms;
        cout << "\nMolecular Weight: " << fixed << setprecision(2) << molecularWeight << endl;
    }

    void saveToFile(ofstream &file) const override {
        file << "Inorganic," << name << "," << molecularWeight << endl;
    }
};

// View compounds from file
void viewFileData() {
    ifstream file("chemistry.txt");
    if (!file) {
        cout << "\nNo data found yet!\n";
        return;
    }

    cout << "\n--- Stored Compounds ---\n";
    string type, name;
    float mw;

    while (getline(file, type, ',')) {
        getline(file, name, ',');
        if (!(file >> mw)) break;
        file.ignore(); // Ignore newline
        if (!type.empty())
            cout << type << " | " << name << " | " << mw << endl;
    }

    file.close();
}

// =================== MAIN PROGRAM ===================
int main() {
    vector<Element> table = {
        {"Hydrogen", "H", 1, 1.008, -259.1, -252.9, 1, 1},
        {"Helium", "He", 2, 4.0026, -272.2, -268.9, 18, 1},
        {"Lithium", "Li", 3, 6.94, 180.5, 1342, 1, 2},
        {"Beryllium", "Be", 4, 9.0122, 1278, 2970, 2, 2},
        {"Boron", "B", 5, 10.81, 2076, 3927, 13, 2},
        {"Carbon", "C", 6, 12.011, 3550, 4827, 14, 2},
        {"Nitrogen", "N", 7, 14.007, -210, -196, 15, 2},
        {"Oxygen", "O", 8, 15.999, -218, -183, 16, 2},
        {"Fluorine", "F", 9, 18.998, -220, -188, 17, 2},
        {"Neon", "Ne", 10, 20.180, -249, -246, 18, 2},
        {"Sodium", "Na", 11, 22.990, 97.8, 883, 1, 3},
        {"Magnesium", "Mg", 12, 24.305, 650, 1090, 2, 3},
        {"Aluminum", "Al", 13, 26.982, 660.3, 2470, 13, 3},
        {"Silicon", "Si", 14, 28.085, 1414, 3265, 14, 3},
        {"Phosphorus", "P", 15, 30.974, 44.2, 280, 15, 3},
        {"Sulfur", "S", 16, 32.06, 115, 445, 16, 3},
        {"Chlorine", "Cl", 17, 35.45, -101, -34.6, 17, 3},
        {"Argon", "Ar", 18, 39.948, -189, -186, 18, 3},
        {"Potassium", "K", 19, 39.098, 63.5, 759, 1, 4},
        {"Calcium", "Ca", 20, 40.078, 842, 1484, 2, 4},
        {"Iron", "Fe", 26, 55.845, 1538, 2862, 8, 4},
        {"Copper", "Cu", 29, 63.546, 1084.6, 2562, 11, 4},
        {"Zinc", "Zn", 30, 65.38, 419.5, 907, 12, 4},
        {"Silver", "Ag", 47, 107.868, 961.8, 2162, 11, 5},
        {"Gold", "Au", 79, 196.967, 1064, 2856, 11, 6}
    };

    Compound *compound = nullptr;
    ofstream file;
    int choice;
    string query;

    do {
        cout << "\n\n========== CHEMISTRY INFORMATION SYSTEM ==========";
        cout << "\n1. Search Element (Periodic Table)";
        cout << "\n2. Add Organic Compound";
        cout << "\n3. Add Inorganic Compound";
        cout << "\n4. View Stored Compounds";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nEnter element name or symbol: ";
            cin >> query;
            searchElement(table, query);
            break;

        case 2:
            compound = new OrganicCompound();
            compound->inputData();
            compound->displayData();
            file.open("chemistry.txt", ios::app);
            compound->saveToFile(file);
            file.close();
            delete compound;
            compound = nullptr;
            break;

        case 3:
            compound = new InorganicCompound();
            compound->inputData();
            compound->displayData();
            file.open("chemistry.txt", ios::app);
            compound->saveToFile(file);
            file.close();
            delete compound;
            compound = nullptr;
            break;
        case 4:
            viewFileData();
            break;
        case 5:
            cout << "\nExiting program... Goodbye!\n";
            break;
        default:
            cout << "\nInvalid choice! Try again.\n";
        }
    } while (choice != 5);
return 0;
}