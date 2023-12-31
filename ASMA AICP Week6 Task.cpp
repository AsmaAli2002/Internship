#include <iostream>
#include <algorithm> // Add this include for std::min

using namespace std;

// Constants for weight limits
const double MIN_WEIGHT_CEMENT = 24.9;
const double MAX_WEIGHT_CEMENT = 25.1;
const double MIN_WEIGHT_SAND_GRAVEL = 49.9;
const double MAX_WEIGHT_SAND_GRAVEL = 50.1;

// Prices
const double PRICE_CEMENT = 3;
const double PRICE_SAND = 2;
const double PRICE_GRAVEL = 2;
const double PRICE_SPECIAL_PACK = 10;

bool validateSack(char contents, double weight) {
    if (contents != 'C' && contents != 'G' && contents != 'S') {
        cout << "Invalid contents. Must be C (cement), G (gravel), or S (sand)." << endl;
        return false;
    }

    if (contents == 'C' && !(MIN_WEIGHT_CEMENT < weight && weight < MAX_WEIGHT_CEMENT)) {
        cout << "Invalid weight for cement sack." << endl;
        return false;
    }

    if ((contents == 'G' || contents == 'S') && !(MIN_WEIGHT_SAND_GRAVEL < weight && weight < MAX_WEIGHT_SAND_GRAVEL)) {
        cout << "Invalid weight for sand or gravel sack." << endl;
        return false;
    }

    return true;
}

void processSingleSack() {
    char contents;
    double weight;

    cout << "Enter contents (C for cement, G for gravel, S for sand): ";
    cin >> contents;

    cout << "Enter weight of the sack in kilograms: ";
    cin >> weight;

    if (validateSack(contents, weight)) {
        cout << "Sack accepted. Contents: " << contents << ", Weight: " << weight << " kg." << endl;
    } else {
        cout << "Sack rejected." << endl;
    }
}

void processCustomerOrder(int &numCement, int &numGravel, int &numSand) {
    double totalWeight = 0;
    int sacksRejected = 0;

    cout << "Enter the number of cement sacks required: ";
    cin >> numCement;

    cout << "Enter the number of gravel sacks required: ";
    cin >> numGravel;

    cout << "Enter the number of sand sacks required: ";
    cin >> numSand;

    for (int i = 0; i < numCement; ++i) {
        char contents = 'C';
        double weight;

        cout << "Enter weight of the cement sack in kilograms: ";
        cin >> weight;

        if (validateSack(contents, weight)) {
            totalWeight += weight;
        } else {
            sacksRejected++;
            cout << "Sack rejected." << endl;
        }
    }

    for (int i = 0; i < numGravel; ++i) {
        char contents = 'G';
        double weight;

        cout << "Enter weight of the gravel sack in kilograms: ";
        cin >> weight;

        if (validateSack(contents, weight)) {
            totalWeight += weight;
        } else {
            sacksRejected++;
            cout << "Sack rejected." << endl;
        }
    }

    for (int i = 0; i < numSand; ++i) {
        char contents = 'S';
        double weight;

        cout << "Enter weight of the sand sack in kilograms: ";
        cin >> weight;

        if (validateSack(contents, weight)) {
            totalWeight += weight;
        } else {
            sacksRejected++;
            cout << "Sack rejected." << endl;
        }
    }

    cout << "\nTotal weight of the order: " << totalWeight << " kg" << endl;
    cout << "Number of sacks rejected: " << sacksRejected << endl;
}

double calculateRegularPrice(int numCement, int numGravel, int numSand) {
    double regularPrice = numCement * PRICE_CEMENT + numGravel * PRICE_GRAVEL + numSand * PRICE_SAND;
    cout << "Regular price for the order: $" << regularPrice << endl;
    return regularPrice;
}

double calculateDiscountPrice(int numCement, int numGravel, int numSand) {
    int numSpecialPacks = std::min({static_cast<int>(numCement), numGravel / 2, numSand / 2});
    double discountPrice = numSpecialPacks * PRICE_SPECIAL_PACK;

    if (numSpecialPacks > 0) {
        cout << "Discount price for special packs: $" << discountPrice << endl;
    }

    return discountPrice;
}

int main() {
    cout << "=== Process a customer order ===" << endl;
    int numCement, numGravel, numSand;
    processCustomerOrder(numCement, numGravel, numSand);

    cout << "\n=== Calculate order price ===" << endl;
    double regularPrice = calculateRegularPrice(numCement, numGravel, numSand);
    double discountPrice = calculateDiscountPrice(numCement, numGravel, numSand);

    double newPrice = (discountPrice > 0) ? (regularPrice - discountPrice) : regularPrice;
    double amountSaved = (discountPrice > 0) ? (regularPrice - newPrice) : 0;

    cout << "\nNew price for the order: $" << newPrice << endl;
    cout << "Amount saved: $" << amountSaved << endl;

    return 0;
}