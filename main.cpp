#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Book {
private:
    int id;
    string title;
    string author;

public:
    void input() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
    }

    void saveToFile() {
        ofstream outFile("books.txt", ios::app);
        if (outFile.is_open()) {
            outFile << id << "," << title << "," << author << "\n";
            outFile.close();
            cout << "Book saved successfully.\n";
        } else {
            cout << "Error opening file.\n";
        }
    }

    static void showAllBooks() {
        ifstream inFile("books.txt");
        string line;

        cout << "\n------ All Books ------\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }
};

int main() {
    int choice;

    do {
        cout << "\n==== Library Menu ====\n";
        cout << "1. Add Book\n";
        cout << "2. Show All Books\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Book b;
                b.input();
                b.saveToFile();
                break;
            }
            case 2:
                Book::showAllBooks();
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
