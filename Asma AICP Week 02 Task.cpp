#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <numeric>

using namespace std;

class MountainRailway {
//private:
    /*const int num_coaches = 6;
    const int num_trains = 4;
    const int ticket_price = 25;
    const int group_discount_threshold = 10;

    vector<time_t> departure_times;
    vector<time_t> return_times;

    vector<int> passengers_up;
    vector<int> passengers_down;
    vector<int> money_up;
    vector<int> money_down;
    vector<int> available_seats_up;
    vector<int> available_seats_down;*/

public:
	const int num_coaches = 6;
    const int num_trains = 4;
    const int ticket_price = 25;
    const int group_discount_threshold = 10;

    vector<time_t> departure_times;
    vector<time_t> return_times;

    vector<int> passengers_up;
    vector<int> passengers_down;
    vector<int> money_up;
    vector<int> money_down;
    vector<int> available_seats_up;
    vector<int> available_seats_down;
    MountainRailway() {
        // Train schedule
        int i;
        for (i = 0; i < num_trains; ++i) {
            departure_times.push_back((i + 9) * 3600); // 9:00 AM and onwards
            return_times.push_back(departure_times[i] + 3600); // 1 hour later
        }

        // Initialize data structures
        passengers_up.assign(num_trains, 0);
        passengers_down.assign(num_trains, 0);
        money_up.assign(num_trains, 0);
        money_down.assign(num_trains, 0);
        available_seats_up.assign(num_trains, num_coaches * 80);
        available_seats_down.assign(num_trains, num_coaches * 80 + (num_trains - 1 == i ? 2 : 0));
    }

    void display_screen() {
        // Display the current state of each train journey
        for (int i = 0; i < num_trains; ++i) {
            tm* departure_tm = localtime(&departure_times[i]);
            tm* return_tm = localtime(&return_times[i]);

            cout << "Train " << i + 1 << " (Up) - Departure Time: " << put_time(departure_tm, "%H:%M")
                 << ", Coaches: " << num_coaches << ", Seats available: " << getAvailableSeatsUp(i + 1) << endl;

            cout << "Train " << i + 1 << " (Down) - Return Time: " << put_time(return_tm, "%H:%M")
                 << ", Coaches: " << num_coaches << ", Seats available: " << available_seats_down[i] << endl;

            if (getAvailableSeatsUp(i + 1) > 0)
                cout << "Train " << i + 1 << " (Up): " << getAvailableSeatsUp(i + 1) << " seats available" << endl;
            else
                cout << "Train " << i + 1 << " (Up): Closed" << endl;

            if (available_seats_down[i] > 0)
                cout << "Train " << i + 1 << " (Down): " << available_seats_down[i] << " seats available" << endl;
            else
                cout << "Train " << i + 1 << " (Down): Closed" << endl;
        }
    }

    int getAvailableSeatsUp(int train_num) const {
        if (train_num >= 1 && train_num <= num_trains) {
            return available_seats_up[train_num - 1];
        } else {
            // Handle invalid train number
            return -1; // or throw an exception, print an error, etc.
        }
    }

    void purchase_tickets(int train_num, int num_tickets) {
        // Check if there are enough available seats for the selected train journey
        if (train_num < 1 || train_num > num_trains) {
            cout << "Error: Invalid train number." << endl;
            return;
        }

        if (num_tickets <= 0) {
            cout << "Error: Number of tickets must be greater than zero." << endl;
            return;
        }

        // Check if there are enough available seats for both upward and downward journeys
        int available_seats_up_local, available_seats_down_local;
        if (train_num == num_trains) {  // Last train has extra coaches
            available_seats_up_local = getAvailableSeatsUp(train_num);
            available_seats_down_local = available_seats_down[train_num - 1];
        } else {
            available_seats_up_local = getAvailableSeatsUp(train_num);
            available_seats_down_local = available_seats_down[train_num - 1];
        }

        if (num_tickets <= min(available_seats_up_local, available_seats_down_local)) {
            // Calculate total price
            int total_price = num_tickets * ticket_price;
            int group_discount = (num_tickets / group_discount_threshold) * ticket_price;
            total_price -= group_discount;

            // Update data structures
            passengers_up[train_num - 1] += num_tickets;
            passengers_down[train_num - 1] += num_tickets;
            money_up[train_num - 1] += total_price;
            money_down[train_num - 1] += total_price;

            // Update available seats
            available_seats_up[train_num - 1] -= num_tickets;
            available_seats_down[train_num - 1] -= num_tickets;

            cout << "Tickets purchased successfully for Train " << train_num << ". Total cost: $" << total_price << endl;
        } else {
            cout << "Error: Not enough seats available on Train " << train_num << "." << endl;
        }
    }

    void display_summary() {
        // Display the number of passengers and money for each train journey
        for (int i = 0; i < num_trains; ++i) {
            cout << "Train " << i + 1 << " (Up) - Passengers: " << passengers_up[i] << ", Money: $" << money_up[i] << endl;
            cout << "Train " << i + 1 << " (Down) - Passengers: " << passengers_down[i] << ", Money: $" << money_down[i] << endl;
        }

        // Calculate and display the total number of passengers and money for the day
        int total_passengers = accumulate(passengers_up.begin(), passengers_up.end(), 0);
        int total_money = accumulate(money_up.begin(), money_up.end(), 0);

        cout << "Total passengers for the day: " << total_passengers << endl;
        cout << "Total money for the day: $" << total_money << endl;

        // Find and display the train journey with the most passengers
        auto max_passengers_train = max_element(passengers_up.begin(), passengers_up.end()) - passengers_up.begin() + 1;
        cout << "Train " << max_passengers_train << " had the most passengers today." << endl;
    }
};

int main() {
    MountainRailway railway;

    // Task 1 - Start of the day
    railway.display_screen();

    // Main loop for ticket sales
    while (any_of(railway.available_seats_up.begin(), railway.available_seats_up.end(), [](int seats) { return seats > 0; })) {
        int train_num;  // Declare train_num here

        // Task 2 - Purchasing tickets interactively
        try {
            cout << "Enter the train number (1-4) or 0 to stop ticket sales: ";
            cin >> train_num;

            if (train_num == 0)
                break;  // Exit the loop if the operator chooses to stop ticket sales
            else if (train_num < 1 || train_num > 4) {
                cout << "Invalid train number. Please enter a number between 1 and 4." << endl;
                continue;
            }
        } catch (...) {
            cout << "Invalid input. Please enter a valid number." << endl;
            continue;
        }

        while (true) {
            try {
                int num_tickets;
                cout << "Enter the number of tickets or 0 to stop for this train: ";
                cin >> num_tickets;

                if (num_tickets == 0)
                    break;  // Move on to the next train if the operator chooses to stop for this train
                else if (num_tickets < 0) {
                    cout << "Invalid number of tickets. Please enter a number greater than 0." << endl;
                    continue;
                }

                // Task 2 - Purchasing tickets
                railway.purchase_tickets(train_num, num_tickets);

                // Display updated screen
                railway.display_screen();
            } catch (...) {
                cout << "Invalid input. Please enter a valid number." << endl;
            }
        }
    }

    // Task 3 - End of the day
    railway.display_summary();

    return 0;
}