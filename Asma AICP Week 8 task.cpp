#include <iostream>
#include <limits>
#include <map>
#include <vector>

using namespace std;

// Constants
const int COST_PER_HOUR = 20;
const int COST_PER_HALF_HOUR = 12;
const int OPENING_TIME = 10;
const int CLOSING_TIME = 17;

// Function to calculate cost based on time
int calculateCost(int hours) {
    if (hours >= 1) {
        return COST_PER_HOUR * hours;
    } else {
        return COST_PER_HALF_HOUR * (hours * 2);
    }
}

// Function to find the next available boat
int findNextAvailableBoat(map<int, map<string, int>> &boatSchedule, int currentTime) {
    int nextAvailableBoat = 0;
    int minEndTime = numeric_limits<int>::max();

    for (auto &entry : boatSchedule) {
        int boatNumber = entry.first;
        int endTime = entry.second["end_time"];

        if (endTime <= currentTime && endTime < minEndTime) {
            minEndTime = endTime;
            nextAvailableBoat = boatNumber;
        }
    }

    return nextAvailableBoat;
}

int main() {
    // Variables
    int moneyTaken = 0;
    int totalHoursHired = 0;
    map<int, map<string, int>> boatSchedule;
    vector<int> boatsNotUsed;

    // Initialize boat schedule
    for (int boatNumber = 1; boatNumber <= 10; ++boatNumber) {
        boatSchedule[boatNumber]["end_time"] = OPENING_TIME;
        boatSchedule[boatNumber]["hours_hired"] = 0;
        boatsNotUsed.push_back(boatNumber);
    }

    // Input for each boat
    for (int boatNumber = 1; boatNumber <= 10; ++boatNumber) {
        cout << "\nBoat " << boatNumber << ":\n";

        // Input start time
        int startTime;
        cout << "Enter start time (between 10 and 17): ";
        cin >> startTime;

        // Validate start time
        if (startTime < OPENING_TIME || startTime >= CLOSING_TIME) {
            cout << "Error: Boat can't be hired before 10:00 or after 17:00.\n";
            continue;
        }

        // Find the next available boat
        int nextAvailableBoat = findNextAvailableBoat(boatSchedule, startTime);

        // If no boats are available, show the earliest time
        if (nextAvailableBoat == 0) {
            int earliestAvailableTime = numeric_limits<int>::max();
            for (const auto &entry : boatSchedule) {
                earliestAvailableTime = min(earliestAvailableTime, entry.second["end_time"]);
            }

            cout << "No boats available. The earliest available time is: " << earliestAvailableTime << "\n";
            break;
        }

        // Input end time
        int endTime;
        cout << "Enter end time (between start time and 17): ";
        cin >> endTime;

        // Validate end time
        if (endTime <= startTime || endTime > CLOSING_TIME) {
            cout << "Error: Invalid end time.\n";
            continue;
        }

        // Calculate hours hired
        int hoursHired = endTime - startTime;

        // Calculate cost
        int boatCost = calculateCost(hoursHired);

        // Update total hours and money taken
        totalHoursHired += hoursHired;
        moneyTaken += boatCost;

        // Update boat schedule
        boatSchedule[boatNumber]["end_time"] = endTime;
        boatSchedule[boatNumber]["hours_hired"] += hoursHired;

        // Remove boat from boatsNotUsed vector
        boatsNotUsed.erase(remove(boatsNotUsed.begin(), boatsNotUsed.end(), boatNumber), boatsNotUsed.end());

        // Output boat details
        cout << "Boat " << boatNumber << " hired for " << hoursHired << " hours. Cost: $" << boatCost << "\n";
    }

    // Output total money taken and hours hired
    cout << "\nTotal money taken for the day: $" << moneyTaken << "\n";
    cout << "Total hours hired for the day: " << totalHoursHired << "\n";

    // Output boats not used
    cout << "\nBoats not used today: ";
    for (int boatNumber : boatsNotUsed) {
        cout << boatNumber << " ";
    }
    cout << "\n";

    // Calculate boat used the most
    int boatUsedTheMost = 0;
    int maxHoursHired = 0;

    for (const auto &entry : boatSchedule) {
        int boatNumber = entry.first;
        int hoursHired = entry.second["hours_hired"];

        if (hoursHired > maxHoursHired) {
            maxHoursHired = hoursHired;
            boatUsedTheMost = boatNumber;
        }
    }

    // Output report
    cout << "Boat used the most today: " << boatUsedTheMost << " (" << maxHoursHired << " hours)\n";

    return 0;
}