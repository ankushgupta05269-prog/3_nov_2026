
#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
    string number, type;
    int entry;

    Vehicle() {
        number = "";
        type = "";
        entry = 0;
    }
};

class ParkingLot {
    Vehicle v[10];
    bool occupied[10] = {};
    int served = 0, bikes = 0, cars = 0;
    int earnings = 0;

public:

    void park() {
        string n, t;
        int h;

        cout << "Vehicle Number: ";
        cin >> n;

        for (int i = 0; i < 10; i++) {
            if (occupied[i] && v[i].number == n) {
                cout << "Already Parked!\n";
                return;
            }
        }

        cout << "Type (Bike/Car): ";
        cin >> t;

        if (t != "Bike" && t != "bike" &&
            t != "Car" && t != "car") {
            cout << "Invalid Type!\n";
            return;
        }

        cout << "Entry Hour: ";
        if (!(cin >> h) || h < 0 || h > 23) {
            cout << "Invalid Hour!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        for (int i = 0; i < 10; i++) {
            if (!occupied[i]) {
                v[i].number = n;
                v[i].type = t;
                v[i].entry = h;
                occupied[i] = true;

                cout << "Parked at Slot: " << i + 1 << endl;
                return;
            }
        }

        cout << "Parking Full!\n";
    }

    void remove() {
        string n;
        int h;

        cout << "Vehicle Number: ";
        cin >> n;

        for (int i = 0; i < 10; i++) {
            if (occupied[i] && v[i].number == n) {

                cout << "Exit Hour: ";
                if (!(cin >> h) || h < 0 || h > 23) {
                    cout << "Invalid Hour!\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    return;
                }

                if (h < v[i].entry) {
                    cout << "Invalid Exit Hour!\n";
                    return;
                }

                int fee = (h - v[i].entry) *
                          ((v[i].type == "Bike" ||
                            v[i].type == "bike") ? 10 : 20);

                cout << "\n----- BILL -----\n";
                cout << "Vehicle: " << n << endl;
                cout << "Hours: " << h - v[i].entry << endl;
                cout << "Fee: Rs. " << fee << endl;

                served++;
                if (v[i].type == "Bike" || v[i].type == "bike")
                    bikes++;
                else
                    cars++;

                earnings += fee;
                occupied[i] = false;
                return;
            }
        }

        cout << "Not Found!\n";
    }

    void show() {
        for (int i = 0; i < 10; i++) {
            if (occupied[i]) {
                cout << "\nSlot: " << i + 1;
                cout << "\nNumber: " << v[i].number;
                cout << "\nType: " << v[i].type;
                cout << "\nEntry: " << v[i].entry << endl;
            }
        }
    }

    void freeSlots() {
        int count = 0;

        cout << "Free Slots: ";

        for (int i = 0; i < 10; i++) {
            if (!occupied[i]) {
                cout << i + 1 << " ";
                count++;
            }
        }

        cout << "\nTotal Free: " << count << endl;
    }

    void search() {
        string n;
        cout << "Vehicle Number: ";
        cin >> n;

        for (int i = 0; i < 10; i++) {
            if (occupied[i] && v[i].number == n) {
                cout << "Found at Slot: " << i + 1 << endl;
                return;
            }
        }

        cout << "Not Found!\n";
    }

    void summary() {
        cout << "\nTotal Vehicles: " << served;
        cout << "\nTotal Bikes: " << bikes;
        cout << "\nTotal Cars: " << cars;
        cout << "\nTotal Earnings: Rs. " << earnings << endl;
    }

    void menu() {
        int ch;

        do {
            cout << "\n\n1.Park\n2.Remove\n3.Show Parked";
            cout << "\n4.Free Slots\n5.Search\n6.Summary & Exit";
            cout << "\nEnter Choice: ";

            if (!(cin >> ch)) {
                cout << "Invalid Input!\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            switch (ch) {
                case 1: park(); break;
                case 2: remove(); break;
                case 3: show(); break;
                case 4: freeSlots(); break;
                case 5: search(); break;
                case 6: summary(); break;
                default: cout << "Wrong Choice!\n";
            }

        } while (ch != 6);
    }
};

int main() {
    ParkingLot p;
    p.menu();
    return 0;
}
