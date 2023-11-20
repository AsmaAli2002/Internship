#include <iostream>
using namespace std;

int electricity_matrix[3][3] = {
    {55, 65, 75},
    {120, 150, 170},
    {210, 230, 240}
	};

// Function to calculate and display cost for slab 1
void costSlab1() {
    cout << "Slab 1 Bill Details:" << endl;
    cout << "Total Cost: ";
    for (int i = 0; i < 3; ++i) {
        int cost = electricity_matrix[0][i] * 10;
        cout << cost << "   ";
    }
    cout << endl;
}

// Function to calculate and display cost for slab 2
void costSlab2() {
    cout << "Slab 2 Bill Details:" << endl;
    cout << "Total Cost: ";
    for (int i = 0; i < 3; ++i) {
        int cost = electricity_matrix[1][i] * 15;
        cout << cost << "   ";
    }
    cout << endl;
	}

// Function to calculate and display cost for slab 3
void costSlab3() {
    cout << "Slab 3 Bill Details:" << endl;
    cout << "Total Cost: ";
    for (int i = 0; i < 3; ++i) {
        int cost = electricity_matrix[2][i] * 20;
        cout << cost << "   ";
    }
    cout << endl;
}

int main() {
    // Displaying student ID at the top of the menu
    cout << "Student ID: YourStudentID" << endl;

    // Loop
    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Display the bill of slab 1 and slab 2" << endl;
        cout << "2. Display the bill of slab 3" << endl;
        cout << "3. Exit" << endl;

        cout << "Enter your choice (1, 2, or 3): ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                costSlab1();
                costSlab2();
                break;
            case 2:
                costSlab3();
                break;
            case 3:
                cout << "Program closed!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
        }
    }

    return 0;
}