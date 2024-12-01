#include "Transportation.h"
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

class Passanger_Transportation : protected Transportation {
protected:
    int Seats_Number;
    int Tickets_All;
    int Tickets_Sold;

public:
    Passanger_Transportation()
        : Seats_Number(0), Tickets_All(0), Tickets_Sold(0) {}

    ~Passanger_Transportation() = default;

    void Pass_Create() {
        try {
            std::cout << "Enter transportation details:" << std::endl;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Departure City: ";
            std::getline(std::cin, Departure);
            if (Departure.empty()) {
                throw std::invalid_argument("Departure city cannot be empty.");
            }

            std::cout << "Destination City: ";
            std::getline(std::cin, Destination);
            if (Destination.empty()) {
                throw std::invalid_argument("Destination city cannot be empty.");
            }

            std::cout << "Vehicle: ";
            std::getline(std::cin, Vehicle);
            if (Vehicle.empty()) {
                throw std::invalid_argument("Vehicle cannot be empty.");
            }

            std::cout << "Transportation ID: ";
            std::cin >> Transportation_ID;
            if (std::cin.fail() || Transportation_ID <= 0) {
                throw std::invalid_argument("Transportation ID must be a positive integer.");
            }

            std::cout << "Transportation Time (min): ";
            std::cin >> Transportation_Time;
            if (std::cin.fail() || Transportation_Time <= 0) {
                throw std::invalid_argument("Transportation time must be a positive integer.");
            }

            std::cout << "Break Time (min): ";
            std::cin >> Break_Time;
            if (std::cin.fail() || Break_Time < 0) {
                throw std::invalid_argument("Break time cannot be negative.");
            }

            std::cout << "Seats Number: ";
            std::cin >> Seats_Number;
            if (std::cin.fail() || Seats_Number <= 0) {
                throw std::invalid_argument("Seats number must be a positive integer.");
            }

            std::cout << "Total Tickets: ";
            std::cin >> Tickets_All;
            if (std::cin.fail() || Tickets_All <= 0) {
                throw std::invalid_argument("Total tickets must be a positive integer.");
            }

            std::cout << "Sold Tickets: ";
            std::cin >> Tickets_Sold;
            if (std::cin.fail() || Tickets_Sold < 0 || Tickets_Sold > Tickets_All) {
                throw std::invalid_argument("Sold tickets must be between 0 and total tickets.");
            }

            std::cout << "Transportation details successfully recorded!" << std::endl;

            SaveToFile("transportations.txt"); // Зберігаємо у файл після успішного вводу

        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid input: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Pass_Create();
        }
    }

    void SaveToFile(const std::string& filename) const {
        std::ofstream file(filename, std::ios::app);
        if (!file) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }
        file << Departure << "," << Destination << "," << Vehicle << "," << Transportation_ID << ","
             << Transportation_Time << "," << Break_Time << "," << Seats_Number << ","
             << Tickets_All << "," << Tickets_Sold << std::endl;
        file.close();
    }

    void LoadAllFromFile(const std::string& filename) const {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for reading!" << std::endl;
            return;
        }

        std::string line;
        int record_count = 0;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string departure, destination, vehicle;
            int id, time, break_time, seats, tickets_all, tickets_sold;

            std::getline(iss, departure, ',');
            std::getline(iss, destination, ',');
            std::getline(iss, vehicle, ',');
            iss >> id;
            iss.ignore();
            iss >> time;
            iss.ignore();
            iss >> break_time;
            iss.ignore();
            iss >> seats;
            iss.ignore();
            iss >> tickets_all;
            iss.ignore();
            iss >> tickets_sold;

            std::cout << "\n--- Transportation " << ++record_count << " ---\n"
                      << "Departure City: " << departure << "\n"
                      << "Destination City: " << destination << "\n"
                      << "Vehicle: " << vehicle << "\n"
                      << "Transportation ID: " << id << "\n"
                      << "Transportation Time: " << time << " min\n"
                      << "Break Time: " << break_time << " min\n"
                      << "Seats: " << seats << "\n"
                      << "Tickets Available: " << (tickets_all - tickets_sold) << "\n"
                      << "Tickets Sold: " << tickets_sold << "\n"
                      << "--------------------------\n";
        }

        if (record_count == 0) {
            std::cout << "No transportation records found in the file." << std::endl;
        }

        file.close();
    }
};
