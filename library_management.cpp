#include <bits/stdc++.h>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book(int i, string t, string a, bool is = false) {
        id = i;
        title = t;
        author = a;
        issued = is;
    }
};

vector<Book> library;


void loadBooks() {
    library.clear();
    ifstream file("library.txt");
    if (!file) return;

    int id;
    string title, author;
    bool issued;

    while (file >> id) {
        file.ignore();
        getline(file, title);
        getline(file, author);
        file >> issued;
        library.push_back(Book(id, title, author, issued));
    }
    file.close();
}


void saveBooks() {
    ofstream file("library.txt");
    for (auto &b : library) {
        file << b.id << endl;
        file << b.title << endl;
        file << b.author << endl;
        file << b.issued << endl;
    }
    file.close();
}


void addBook() {
    int id;
    string title, author;

    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Title: ";
    getline(cin, title);

    cout << "Enter Author: ";
    getline(cin, author);

    library.push_back(Book(id, title, author));
    saveBooks();
    cout << "Book added successfully!" << endl;
}


void viewBooks() {
    if (library.empty()) {
        cout << "No books available." << endl;
        return;
    }

    for (auto &b : library) {
        cout << "ID: " << b.id
             << " | Title: " << b.title
             << " | Author: " << b.author
             << " | Status: " << (b.issued ? "Issued" : "Available")
             << endl;
    }
}


void searchBook() {
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;

    for (auto &b : library) {
        if (b.id == id) {
            cout << "Book Found:" << endl;
            cout << "Title: " << b.title << endl;
            cout << "Author: " << b.author << endl;
            cout << "Status: " << (b.issued ? "Issued" : "Available") << endl;
            return;
        }
    }
    cout << "Book not found." << endl;
}


void issueBook() {
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;

    for (auto &b : library) {
        if (b.id == id) {
            if (b.issued) {
                cout << "Book already issued." << endl;
            } else {
                b.issued = true;
                saveBooks();
                cout << "Book issued successfully." << endl;
            }
            return;
        }
    }
    cout << "Book not found." << endl;
}


void returnBook() {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;

    for (auto &b : library) {
        if (b.id == id) {
            if (!b.issued) {
                cout << "Book was not issued." << endl;
            } else {
                b.issued = false;
                saveBooks();
                cout << "Book returned successfully." << endl;
            }
            return;
        }
    }
    cout << "Book not found." << endl;
}


int main() {
    loadBooks();
    int choice;

    do {
        cout << endl;
        cout << "--- Library Management System ---" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. View Books" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Issue Book" << endl;
        cout << "5. Return Book" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 0: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}


