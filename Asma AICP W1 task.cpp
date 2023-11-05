#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const string CASE = "Case";
const string RAM = "RAM";
const string MAIN_HDD = "Main Hard Disk Drive";
const string SSD = "Solid State Drive";
const string SECOND_HDD = "Second Hard Disk Drive";
const string OPTICAL_DRIVE = "Optical Drive";
const string OS = "Operating System";

struct Item {
    string category;
    string code;
    string description;
    double price;
    Item(const string& cat, const string& c, const string& desc, double p)
        : category(cat), code(c), description(desc), price(p) {}
};

vector<Item> items = {
    {CASE, "A1", "compact", 75.00},
    {CASE, "A2", "tower", 150.00},
    {RAM, "B1", "8gb", 79.99},
    {RAM, "B2", "16gb", 149.99},
    {RAM, "B3", "32gb", 299.99},
    {MAIN_HDD, "C1", "1TB HDD", 49.99},
    {MAIN_HDD, "C2", "2TB HDD", 89.99},
    {MAIN_HDD, "C3", "4TB HDD", 129.99},
    {SSD, "D1", "240Gb SSD", 59.99},
    {SSD, "D2", "480Gb SSD", 119.99},
    {SECOND_HDD, "E1", "1TB HDD", 49.99},
    {SECOND_HDD, "E2", "2TB HDD", 89.99},
    {SECOND_HDD, "E3", "4TB HDD", 129.99},
    {OPTICAL_DRIVE, "F1", "DVD/Blu-Ray Player", 50.00},
    {OPTICAL_DRIVE, "F2", "DVD/Blu-Ray Re-writer", 100.00},
    {OS, "G1", "Standard Version", 100.00},
    {OS, "G2", "Professional Version", 175.00}
};

vector<Item> selectedComponents = {Item(CASE, "", "", 0.0), Item(RAM, "", "", 0.0), Item(MAIN_HDD, "", "", 0.0)};
const double basicComponentsCost = 200.00;
double totalPrice = basicComponentsCost;
vector<Item> additionalItems;

void displayItems(const string& category) {
    cout << "Available " << category << " options:" << endl;
    for (const Item& item : items) {
        if (item.category == category) {
            cout << "Item code " << item.code << " - " << item.description << ", Price: $" << fixed << setprecision(2) << item.price << endl;
        }
    }
}

Item selectItem(const string& category) {
    displayItems(category);
    while (true) {
        string itemCode;
        cout << "Enter the item code for " << category << ": ";
        cin >> itemCode;
        for (const Item& item : items) {
            if (item.category == category && item.code == itemCode) {
                selectedComponents[category == CASE ? 0 : (category == RAM ? 1 : 2)] = item;
                return item;
            }
        }
        cout << "Invalid item code. Please try again." << endl;
    }
}

void addAdditionalItems() {
    while (true) {
        string choice;
        cout << "Do you want to purchase additional items? (yes/no): ";
        cin >> choice;
        if (choice == "no") {
            break;
        } else if (choice == "yes") {
            cout << "Additional item codes:" << endl;
            for (const Item& item : items) {
                if (item.category != CASE && item.category != RAM && item.category != MAIN_HDD) {
                    cout << "Item code " << item.code << " - " << item.description << ", Price: $" << fixed << setprecision(2) << item.price << endl;
                }
            }
            string itemCode;
            cout << "Enter the item code for the additional item: ";
            cin >> itemCode;
            for (const Item& item : items) {
                if (item.code == itemCode) {
                    additionalItems.push_back(item);
                    totalPrice += item.price;
                    cout << "Added " << item.description << " to the computer. New total price: $" << fixed << setprecision(2) << totalPrice << endl;
                    break;
                }
            }
        } else {
            cout << "Invalid choice. Please enter 'yes' or 'no'." << endl;
        }
    }
}

int main() {
    selectItem(CASE);
    selectItem(RAM);
    selectItem(MAIN_HDD);

    for (const Item& component : selectedComponents) {
        totalPrice += component.price;
    }

    addAdditionalItems();

    cout << "Selected components:" << endl;
    for (const Item& component : selectedComponents) {
        cout << component.category << ": " << component.description << " - $" << fixed << setprecision(2) << component.price << endl;
    }

    totalPrice += basicComponentsCost;

    int numAdditionalItems = additionalItems.size();

    double discount = 0.0;

    if (numAdditionalItems == 1) {
        discount = totalPrice * 0.05;
    }
    else if (numAdditionalItems >= 2) {
        discount = totalPrice * 0.10;
    }

    if (numAdditionalItems > 0) {
        cout << "Total price before discount: $" << fixed << setprecision(2) << totalPrice - basicComponentsCost << endl;
        cout << "Discount: $" << fixed << setprecision(2) << discount << endl;
        totalPrice -= discount;
        cout << "Total price after discount: $" << fixed << setprecision(2) << totalPrice - basicComponentsCost << endl;
    }
    else {
        cout << "Total price: $" << fixed << setprecision(2) << totalPrice - basicComponentsCost << endl;
    }

    return 0;
}