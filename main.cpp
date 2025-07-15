#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>

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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    static void searchBooks() {
        ifstream inFile("books.txt");
        if (!inFile) {
            cout << "No books found. File missing.\n";
            return;
        }

        string line, query;
        cout << "Enter book title or author to search: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, query);

        transform(query.begin(), query.end(), query.begin(), ::tolower);

        bool found = false;
        while (getline(inFile, line)) {
            string lowerLine = line;
            transform(lowerLine.begin(), lowerLine.end(), lowerLine.begin(), ::tolower);
            if (lowerLine.find(query) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }
        inFile.close();

        if (!found) {
            cout << "No matching books found.\n";
        }
    }

    static void deleteBook() {
        ifstream inFile("books.txt");
        if (!inFile) {
            cout << "No books found.\n";
            return;
        }

        int delId;
        cout << "Enter Book ID to delete: ";
        cin >> delId;

        string line;
        bool found = false;
        ofstream tempFile("temp.txt");

        while (getline(inFile, line)) {
            int pos = line.find(',');
            if (pos != string::npos) {
                int currentId = stoi(line.substr(0, pos));
                if (currentId == delId) {
                    found = true;
                    continue;
                }
            }
            tempFile << line << "\n";
        }

        inFile.close();
        tempFile.close();

        if (found) {
            remove("books.txt");
            rename("temp.txt", "books.txt");
            cout << "Book deleted successfully.\n";
        } else {
            remove("temp.txt");
            cout << "Book with ID " << delId << " not found.\n";
        }
    }

    static bool isBookAvailable(int bookId) {
        ifstream file("issued_books.txt");
        string line;
        while (getline(file, line)) {
            int pos = line.find(',');
            if (pos != string::npos) {
                int id = stoi(line.substr(0, pos));
                if (id == bookId) {
                    return false; // Already issued
                }
            }
        }
        return true;
    }

    static void issueBook() {
        int bookId;
        string studentName;
        cout << "Enter Book ID to issue: ";
        cin >> bookId;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!isBookAvailable(bookId)) {
            cout << "Sorry, this book is already issued.\n";
            return;
        }

        cout << "Enter student name: ";
        getline(cin, studentName);

        ofstream file("issued_books.txt", ios::app);
        file << bookId << "," << studentName << "\n";
        file.close();
        cout << "Book issued successfully to " << studentName << ".\n";
    }

    static void returnBook() {
        int bookId;
        cout << "Enter Book ID to return: ";
        cin >> bookId;

        ifstream file("issued_books.txt");
        ofstream temp("temp_issued.txt");
        string line;
        bool found = false;

        while (getline(file, line)) {
            int pos = line.find(',');
            if (pos != string::npos) {
                int id = stoi(line.substr(0, pos));
                if (id == bookId) {
                    found = true;
                    continue;
                }
            }
            temp << line << "\n";
        }
        file.close();
        temp.close();

        remove("issued_books.txt");
        rename("temp_issued.txt", "issued_books.txt");

        if (found)
            cout << "Book returned successfully.\n";
        else
            cout << "Book ID not found in issued records.\n";
    }
};

int main() {
    int choice;

    do {
        cout << "\n==== Library Menu ====\n";
        cout << "1. Add Book\n";
        cout << "2. Show All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
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
                Book::searchBooks();
                break;
            case 4:
                Book::deleteBook();
                break;
            case 5:
                Book::issueBook();
                break;
            case 6:
                Book::returnBook();
                break;
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
