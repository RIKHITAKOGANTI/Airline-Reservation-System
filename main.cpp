#include <bits/stdc++.h>
using namespace std;

// Total number of seats in the flight
const int TOTAL_SEATS = 100;

// Array to track seat booking status: -1 for booked, 0 for available
int seatStatus[TOTAL_SEATS] = {0};    

// Indicates whether a seat is already taken
bool isSeatTaken = false;

// Counter for total seats reserved
int totalReservedSeats = 1000;

// Counter for total tickets cancelled
int totalCancelledTickets = 0;

class FlightReservation {
public:
    FlightReservation() {
        headPassenger = nullptr;
    }
    void bookTicket();
    void cancelTicket();
    void changeReservation();
    void showPassengerDetails();
    void showAllBookings();

private:
    // Structure to store passenger details
    struct Passenger {
        string firstName;
        string lastName;
        string id;
        string phoneNumber;
        string mealPreference;
        int seatNumber;
        int reservationNumber;
        Passenger* next;
    };
    
    // Pointer to the start of the linked list of passengers
    Passenger* headPassenger;

    // Temporary pointers for linked list traversal
    Passenger* tempPassenger;
    Passenger* prevPassenger;
};

void checkAvailableSeats(int seatNumber) {
    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seatStatus[i] == -1) {
            isSeatTaken = true;
            cout << "The seat is already booked. Please choose another seat from the available options:" << endl;
            int j = 1;
            while (j <= TOTAL_SEATS) {
                if (seatStatus[j - 1] == -1)
                    j++;
                else {
                    cout << "|" << j << "|";
                    if (j % 10 == 0)
                        cout << endl;
                    j++;
                }
            }
        }
    }
}

void FlightReservation::bookTicket() {
    // Allocate memory for a new passenger
    tempPassenger = new Passenger;
    
    // Collect passenger details
    cout << "Enter your first name: ";
    cin >> tempPassenger->firstName;
    cout << "Enter your last name: ";
    cin >> tempPassenger->lastName;
    cout << "Enter your ID: ";
    cin >> tempPassenger->id;
    cout << "Enter your phone number: ";
    cin >> tempPassenger->phoneNumber;

    int seatNumber;
    do {
        cout << "Enter the seat number: ";
        cin >> seatNumber;
        while (seatNumber > TOTAL_SEATS) {
            cout << "Invalid seat number. Please enter again: ";
            cin >> seatNumber;
        }
        if (seatStatus[seatNumber - 1] > -1) {
            isSeatTaken = false;
        } else {
            checkAvailableSeats(seatNumber);
        }

        seatStatus[seatNumber - 1] = -1;
        tempPassenger->seatNumber = seatNumber;
    } while (isSeatTaken == true);

    // Collect meal preference
    cout << "Enter your food preference: ";
    cout << "1. Vegetarian" << endl;
    cout << "2. Non-Vegetarian" << endl;
    cout << "3. No Food" << endl;
    int choice;
    cout << "Your choice: ";
    cin >> choice;
    while (choice < 1 || choice > 3) {
        cout << "Invalid choice. Please enter again: ";
        cin >> choice;
    }

    if (choice == 1) {
        tempPassenger->mealPreference = "Vegetarian";
    } else if (choice == 2) {
        tempPassenger->mealPreference = "Non-Vegetarian";
    } else {
        tempPassenger->mealPreference = "No Food";
    }
    tempPassenger->next = nullptr;

    // Assign reservation number
    totalReservedSeats++;
    tempPassenger->reservationNumber = totalReservedSeats;
    cout << "Your reservation number is: " << totalReservedSeats << endl;

    // Add passenger to linked list
    if (headPassenger == nullptr) {
        headPassenger = tempPassenger;
    } else {
        Passenger* current = headPassenger;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = tempPassenger;
    }
}

void FlightReservation::cancelTicket() {
    int reservationNumber;
    cout << "Enter your reservation number: ";
    cin >> reservationNumber;
    tempPassenger = headPassenger;
    prevPassenger = headPassenger;
    while (tempPassenger != nullptr) {
        if (tempPassenger->reservationNumber == reservationNumber) {
            if (tempPassenger == headPassenger) {
                headPassenger = headPassenger->next;
                seatStatus[tempPassenger->seatNumber - 1] = 0;
                totalCancelledTickets++;
                delete tempPassenger;
                break;
            } else {
                prevPassenger->next = tempPassenger->next;
                seatStatus[tempPassenger->seatNumber - 1] = 0;
                delete tempPassenger;
                totalCancelledTickets++;
                break;
            }
        } else {
            prevPassenger = tempPassenger;
            tempPassenger = tempPassenger->next;
        }
    }
}

void FlightReservation::changeReservation() {
    int currentSeatNumber, newSeatNumber;
    cout << "Enter your current seat number: ";
    cin >> currentSeatNumber;
    Passenger* currentPassenger = headPassenger;
    
    while (currentPassenger != nullptr) {
        if (currentPassenger->seatNumber == currentSeatNumber) {
            break;
        }
        currentPassenger = currentPassenger->next;
    }

    cout << "Choose a new seat number from the available options:" << endl;
    int i = 1;
    while (i <= TOTAL_SEATS) {
        if (seatStatus[i - 1] == -1) {
            i++;
        } else {
            cout << "|" << i << "|";
            if (i % 10 == 0)
                cout << endl;
            i++;
        }
    }

    cin >> newSeatNumber;
    seatStatus[currentPassenger->seatNumber - 1] = 0;
    currentPassenger->seatNumber = newSeatNumber;
    seatStatus[newSeatNumber - 1] = -1;
}

void FlightReservation::showPassengerDetails() {
    int reservationNumber;
    cout << "Enter your reservation number: ";
    cin >> reservationNumber;
    tempPassenger = headPassenger;
    while (tempPassenger != nullptr) {
        if (tempPassenger->reservationNumber == reservationNumber) {
            cout << "Reservation Number\tFirst Name\tLast Name\tID\tPhone Number\tSeat Number\tMeal Preference" << endl;
            cout << tempPassenger->reservationNumber << "\t\t\t" << tempPassenger->firstName << "\t\t" << tempPassenger->lastName << "\t\t" << tempPassenger->id << "\t\t" << tempPassenger->phoneNumber << "\t\t" << tempPassenger->seatNumber << "\t\t" << tempPassenger->mealPreference << endl;
            break;
        }
        tempPassenger = tempPassenger->next;
    }
}

void FlightReservation::showAllBookings() {
    tempPassenger = headPassenger;
    cout << "Reservation Number\tFirst Name\tLast Name\tID\tPhone Number\tSeat Number\tMeal Preference" << endl;
    while (tempPassenger != nullptr) {
        cout << tempPassenger->reservationNumber << "\t\t\t" << tempPassenger->firstName << "\t\t" << tempPassenger->lastName << "\t\t" << tempPassenger->id << "\t\t" << tempPassenger->phoneNumber << "\t\t" << tempPassenger->seatNumber << "\t\t" << tempPassenger->mealPreference << endl;
        tempPassenger = tempPassenger->next;
    }
}

void displayMenu() {
    cout << "\t\t|--------------------------------------------------------------|" << endl;
    cout << "\t\t|                                                            |" << endl;
    cout << "\t\t|  WELCOME TO YRNCOLLO AIRLINE FLIGHT RESERVATION SYSTEM     |" << endl;
    cout << "\t\t|                                                            |" << endl;
    cout << "\t\t|--------------------------------------------------------------|" << endl;
    cout << "\t\t|  Choose your option:                                      |" << endl;
    cout << "\t\t|--------------------------------------------------------------|" << endl;
    cout << "\t\t|                                                            |" << endl;
    cout << "\t\t|  1) BOOK TICKET                                           |" << endl;
    cout << "\t\t|                                                            |" << endl;
    cout << "\t\t|  2) CANCEL TICKET                                         |" << endl;
    cout << "\t\t|                                                            |" << endl;
    cout << "\t\t|  3) CHANGE RESERVATION                                    |" << endl;
    cout << "\t\t|                                                            |" << endl;
    cout << "\t\t|  4) VIEW PASSENGER DETAILS                                |" << endl;
    cout << "\t\t|                                                            |" << endl;
    cout << "\t\t|  5) VIEW ALL BOOKINGS                                     |" << endl;
    cout << "\t\t|                                                            |" << endl;
    cout << "\t\t|  6) EXIT                                                  |" << endl;
    cout << "\t\t|--------------------------------------------------------------|" << endl;

    int choice;
    do {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                system("CLS");
                flightReservation.bookTicket();
                break;
            case 2:
                system("CLS");
                flightReservation.cancelTicket();
                break;
            case 3
