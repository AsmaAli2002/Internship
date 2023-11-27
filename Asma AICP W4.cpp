#include <iostream>
#include <cmath>
using namespace std;

double calcHexagonArea(double sideLength) {
    return 1.5 * 1.732 * pow(sideLength, 2);
}

double calcHexagonPerimeter(double sideLength) {
    return 6 * sideLength;
}

double calcHexagonAngleSum() {
    return 6 * 120;
}

void displayHexagon(double sideLength) {
    cout << "Hexagon Area: " << calcHexagonArea(sideLength) << endl;
    cout << "Hexagon Perimeter: " << calcHexagonPerimeter(sideLength) << endl;
    cout << "Sum of angles of Hexagon: " << calcHexagonAngleSum() << endl;
}

double calcSquareArea(double sideLength) {
    return pow(sideLength, 2);
}

double calcSquarePerimeter(double sideLength) {
    return 4 * sideLength;
}

void displaySquare(double sideLength) {
    cout << "Area of Square: " << calcSquareArea(sideLength) << endl;
    cout << "Perimeter of Square: " << calcSquarePerimeter(sideLength) << endl;
}

int main() {
    string cnic = "1710173440604";
    int lastDigit = cnic.back() - '0';

    double hexagonSide = lastDigit;
    double squareSide = lastDigit + 1;

    while (true) {
        cout << "Enter 1 to calculate area, perimeter, and sum of angles of Hexagon: " << endl;
        cout << "Enter 2 to calculate area and perimeter of Square: " << endl;
        cout << "Press any other key to exit... " << endl;

        char choice;
        cin >> choice;

        if (choice == '1') {
            displayHexagon(hexagonSide);
        } else if (choice == '2') {
            displaySquare(squareSide);
        } else {
            cout << "Exiting!" << endl;
            break;
        }
    }

    return 0;
}