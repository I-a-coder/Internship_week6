#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Constants for ticket costs
const double ADULT_ONE_DAY = 20.00;
const double ADULT_TWO_DAYS = 30.00;
const double CHILD_ONE_DAY = 12.00;
const double CHILD_TWO_DAYS = 18.00;
const double SENIOR_ONE_DAY = 16.00;
const double SENIOR_TWO_DAYS = 24.00;
const double FAMILY_ONE_DAY = 60.00;
const double FAMILY_TWO_DAYS = 90.00;
const double GROUP_ONE_DAY_PER_PERSON = 15.00;
const double GROUP_TWO_DAYS_PER_PERSON = 22.50;
const double LION_FEEDING_COST = 2.50;
const double PENGUIN_FEEDING_COST = 2.00;
const double BBQ_COST = 5.00;

// Function to display ticket options and extra attractions
void displayOptions() {
    cout << "Welcome to the Wildlife Park!\n";
    cout << "Ticket Options:\n";
    cout << "1. One-Day Tickets:\n";
    cout << "   - Adult: $20.00\n";
    cout << "   - Child (up to 2 per adult): $12.00\n";
    cout << "   - Senior: $16.00\n";
    cout << "   - Family (up to 2 adults/seniors and 3 children): $60.00\n";
    cout << "   - Group (6 or more people): $15.00 per person\n";
    cout << "2. Two-Day Tickets:\n";
    cout << "   - Adult: $30.00\n";
    cout << "   - Child (up to 2 per adult): $18.00\n";
    cout << "   - Senior: $24.00\n";
    cout << "   - Family (up to 2 adults/seniors and 3 children): $90.00\n";
    cout << "   - Group (6 or more people): $22.50 per person\n";
    cout << "\nExtra Attractions:\n";
    cout << "   - Lion Feeding: $2.50 per person\n";
    cout << "   - Penguin Feeding: $2.00 per person\n";
    cout << "   - Evening BBQ (Two-Day Tickets only): $5.00 per person\n";
}

// Function to validate input and get integer input
int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0) {
            break;
        }
        else {
            cout << "Invalid input. Please enter a positive integer.\n";
            cin.clear();
        }
    }
    return value;
}

// Function to validate input and get yes/no input
bool getYesNoInput(const string& prompt) {
    char response;
    while (true) {
        cout << prompt;
        cin >> response;
        if (response == 'y' || response == 'Y') {
            return true;
        }
        else if (response == 'n' || response == 'N') {
            return false;
        }
        else {
            cout << "Invalid input. Please enter 'y' for yes or 'n' for no.\n";
            cin.clear();
        }
    }
}

// Function to calculate total cost based on ticket options and extra attractions
double calculateTotalCost(int numAdults, int numChildren, int numSeniors, int numDays, bool hasBBQ, bool hasPenguinFeeding, bool hasLionFeeding) {
    double totalCost = 0.0;

    if (numDays == 1) {
        totalCost += numAdults * ADULT_ONE_DAY;
        totalCost += numChildren * CHILD_ONE_DAY;
        totalCost += numSeniors * SENIOR_ONE_DAY;
        if (numAdults + numSeniors + numChildren <= 5) {
            totalCost += FAMILY_ONE_DAY;
        }
        else {
            totalCost += GROUP_ONE_DAY_PER_PERSON * (numAdults + numSeniors + numChildren);
        }
        if (hasPenguinFeeding) {
            totalCost += (numAdults + numChildren + numSeniors) * PENGUIN_FEEDING_COST;
        }
        if (hasLionFeeding) {
            totalCost += (numAdults + numChildren + numSeniors) * LION_FEEDING_COST;
        }
    }
    else if (numDays == 2) {
        totalCost += numAdults * ADULT_TWO_DAYS;
        totalCost += numChildren * CHILD_TWO_DAYS;
        totalCost += numSeniors * SENIOR_TWO_DAYS;
        if (numAdults + numSeniors + numChildren <= 5) {
            totalCost += FAMILY_TWO_DAYS;
        }
        else {
            totalCost += GROUP_TWO_DAYS_PER_PERSON * (numAdults + numSeniors + numChildren);
        }
        if (hasBBQ) {
            totalCost += (numAdults + numChildren + numSeniors) * BBQ_COST;
        }
        if (hasPenguinFeeding) {
            totalCost += (numAdults + numChildren + numSeniors) * PENGUIN_FEEDING_COST;
        }
        if (hasLionFeeding) {
            totalCost += (numAdults + numChildren + numSeniors) * LION_FEEDING_COST;
        }
    }

    return totalCost;
}

// Function to determine the best value option
string getBestOption(int numAdults, int numChildren, int numSeniors, int numDays, bool hasBBQ, bool includePenguinFeeding, bool includeLionFeeding) 
{
    double costForIndividuals = calculateTotalCost(numAdults, numChildren, numSeniors, numDays, hasBBQ, includePenguinFeeding, includeLionFeeding);
    double costForTwoFamilyTickets = 2 * (numDays == 1 ? FAMILY_ONE_DAY : FAMILY_TWO_DAYS);
    double costForGroupTicket = (numAdults + numChildren + numSeniors) * (numDays == 1 ? GROUP_ONE_DAY_PER_PERSON : GROUP_TWO_DAYS_PER_PERSON);

    double bestValueCost = min(costForIndividuals, min(costForTwoFamilyTickets, costForGroupTicket));

    if (bestValueCost == costForIndividuals) {
        return "Individual tickets for each person";
    }
    else if (bestValueCost == costForTwoFamilyTickets) {
        return "Two Family tickets";
    }
    else {
        return "Group ticket for all";
    }
}
int main() {
    static int bookingCounter = 1; // Initialize a counter for booking numbers
    displayOptions();

    int numAdults = getIntInput("\nEnter number of adults: ");
    int numChildren = getIntInput("Enter number of children: ");
    int numSeniors = getIntInput("Enter number of seniors: ");
    int numDays = getIntInput("Enter number of days (1 or 2): ");

    bool includeBBQ = (numDays == 2) && getYesNoInput("Include Evening BBQ? (y/n): ");
    bool includePenguinFeeding = getYesNoInput("Include Penguin Feeding? (y/n): ");
    bool includeLionFeeding = getYesNoInput("Include Lion Feeding? (y/n): ");
    string bestOption = getBestOption(numAdults, numChildren, numSeniors, numDays, includeBBQ, includePenguinFeeding, includeLionFeeding);

    double totalCost = calculateTotalCost(numAdults, numChildren, numSeniors, numDays, includeBBQ, includePenguinFeeding, includeLionFeeding);

    // Generate and display the booking number
    int bookingNumber = bookingCounter++;
    cout << "\nBooking Number: " << bookingNumber << endl;

    // Display booking details
    cout << "\nBooking Details:\n";
    cout << "Number of Adults: " << numAdults << endl;
    cout << "Number of Children: " << numChildren << endl;
    cout << "Number of Seniors: " << numSeniors << endl;
    cout << "Number of Days: " << numDays << endl;
    cout << "Evening BBQ Included: " << (includeBBQ ? "Yes" : "No") << endl;
    cout << "Penguin Feeding Included: " << (includePenguinFeeding ? "Yes" : "No") << endl;
    cout << "Lion Feeding Included: " << (includeLionFeeding ? "Yes" : "No") << endl;
   
    cout << "Best value option: " << bestOption << endl;
    cout << fixed << setprecision(2);
    cout << "Total Cost: $" << totalCost << endl;

    return 0;
  

   
}


