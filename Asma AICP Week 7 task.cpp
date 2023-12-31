#include <iostream>
#include <algorithm>

using namespace std;

const int NUM_CHARITIES = 3;

// Initialize charity names and donation totals
string charities[NUM_CHARITIES] = {"Charity A", "Charity B", "Charity C"};
double donation_totals[NUM_CHARITIES] = {0};

// Function to display charities and totals
void display_totals() {
    cout << "\nCharity Totals So Far (Descending Order):\n";
    pair<string, double> sorted_charities[NUM_CHARITIES];

    for (int i = 0; i < NUM_CHARITIES; ++i) {
        sorted_charities[i] = make_pair(charities[i], donation_totals[i]);
    }

    sort(sorted_charities, sorted_charities + NUM_CHARITIES,
         [](const pair<string, double> &a, const pair<string, double> &b) {
             return a.second > b.second;
         });

    double grand_total = 0;

    for (const auto &charity : sorted_charities) {
        grand_total += charity.second;
        cout << charity.first << ": $" << charity.second << endl;
    }

    cout << "\nGRAND TOTAL DONATED TO CHARITY: $" << grand_total << endl;
}

// Function to get valid donation choice
int get_donation_choice() {
    while (true) {
        int choice;
        cout << "Enter the number of your chosen charity (1, 2, or 3), or -1 to show totals: ";
        cin >> choice;

        if (choice == -1 || (1 <= choice && choice <= NUM_CHARITIES)) {
            return choice;
        } else {
            cout << "Invalid choice. Please enter a number between 1 and " << NUM_CHARITIES << ", or -1 to show totals." << endl;
        }
    }
}

// Main program
int main() {
    int num_customers;
    cout << "Enter the number of customers: ";
    cin >> num_customers;

    // Set up charities
    for (int i = 0; i < NUM_CHARITIES; ++i) {
        cout << "Enter the name of Charity " << i + 1 << ": ";
        cin >> charities[i];
    }

    for (int customer = 1; customer <= num_customers; ++customer) {
        cout << "\nCustomer " << customer << ":\n";

        while (true) {
            // Display charities and totals
            cout << "Choose a charity:\n";
            for (int i = 0; i < NUM_CHARITIES; ++i) {
                cout << i + 1 << ". " << charities[i] << endl;
            }

            display_totals();

            // Get user input for donation choice
            int choice = get_donation_choice();

            if (choice == -1) {
                break;  // Show totals and exit donation loop
            } else {
                // Get user input for shopping bill
                double bill;
                cout << "Enter the customer's shopping bill amount: $";
                cin >> bill;

                // Calculate and display donation
                double donation = bill * 0.01;
                donation_totals[choice - 1] += donation;
                cout << "Donation of $" << donation << " to " << charities[choice - 1] << " recorded." << endl;
            }
        }
    }

    // Display final totals and grand total
    display_totals();

    return 0;
}