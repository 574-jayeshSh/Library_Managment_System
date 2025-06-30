#include <iostream>
#include<bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;

    void input() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
    }

    void display() const {
        cout << "Book ID: " << id << "\nTitle: " << title << "\nAuthor: " << author << "\n\n";
    }
};

// ========== USER SYSTEM ==========
bool loginUser() {
    string username, password, fileUser, filePass;
    cout << "\n==== Login ====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream fin("users.txt");
    string line;
    while (getline(fin, line)) {
        size_t sep = line.find('|');
        fileUser = line.substr(0, sep);
        filePass = line.substr(sep + 1);
        if (fileUser == username && filePass == password) {
            cout << "Login successful!\n";
            return true;
        }
    }
    cout << "Login failed. Invalid credentials.\n";
    return false;
}

void registerUser() {
    string username, password;
    cout << "\n==== Register New User ====\n";
    cout << "Choose username: ";
    cin >> username;
    cout << "Choose password: ";
    cin >> password;

    ofstream fout("users.txt", ios::app);
    fout << username << "|" << password << "\n";
    fout.close();
    cout << "User registered successfully!\n";
}

// ========== BOOK SYSTEM ==========
void addBook() {
    ofstream fout("books.txt", ios::app);
    Book b;
    b.input();
    fout << b.id << "|" << b.title << "|" << b.author << "\n";
    fout.close();
    cout << "Book added successfully!\n";
}

void displayBooks() {
    ifstream fin("books.txt");
    Book b;
    string line;
    bool empty = true;

    while (getline(fin, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        b.id = stoi(line.substr(0, pos1));
        b.title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        b.author = line.substr(pos2 + 1);

        b.display();
        empty = false;
    }

    if (empty) {
        cout << "No books found.\n";
    }

    fin.close();
}

void searchBook() {
    ifstream fin("books.txt");
    int searchId;
    cout << "Enter Book ID to search: ";
    cin >> searchId;
    Book b;
    string line;
    bool found = false;

    while (getline(fin, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        b.id = stoi(line.substr(0, pos1));
        b.title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        b.author = line.substr(pos2 + 1);

        if (b.id == searchId) {
            cout << "Book found:\n";
            b.display();
            found = true;
            break;
        }
    }
    if (!found) cout << "Book not found.\n";
    fin.close();
}

void deleteBook() {
    ifstream fin("books.txt");
    ofstream temp("temp.txt");
    int deleteId;
    cout << "Enter Book ID to delete: ";
    cin >> deleteId;
    Book b;
    string line;
    bool found = false;

    while (getline(fin, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        b.id = stoi(line.substr(0, pos1));
        b.title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        b.author = line.substr(pos2 + 1);

        if (b.id != deleteId) {
            temp << b.id << "|" << b.title << "|" << b.author << "\n";
        } else {
            found = true;
        }
    }

    fin.close();
    temp.close();
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found) cout << "Book deleted successfully!\n";
    else cout << "Book not found.\n";
}

void updateBook() {
    ifstream fin("books.txt");
    ofstream temp("temp.txt");
    int updateId;
    cout << "Enter Book ID to update: ";
    cin >> updateId;
    Book b;
    string line;
    bool found = false;

    while (getline(fin, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        b.id = stoi(line.substr(0, pos1));
        b.title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        b.author = line.substr(pos2 + 1);

        if (b.id == updateId) {
            cout << "Enter new details:\n";
            b.input();
            found = true;
        }

        temp << b.id << "|" << b.title << "|" << b.author << "\n";
    }

    fin.close();
    temp.close();
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found) cout << "Book updated successfully!\n";
    else cout << "Book not found.\n";
}

// ========== MAIN ==========
int main() {
    int loginChoice;
    cout << "====== Library Management Login ======\n";
    cout << "1. Login\n2. Register\nChoose an option: ";
    cin >> loginChoice;

    bool loggedIn = false;
    if (loginChoice == 1) {
        loggedIn = loginUser();
    } else if (loginChoice == 2) {
        registerUser();
        loggedIn = loginUser();
    }

    if (!loggedIn) return 0;

    int choice;
    do {
        cout << "\n===== Library Menu =====\n";
        cout << "1. Add Book\n2. Display All Books\n3. Search Book\n";
        cout << "4. Delete Book\n5. Update Book\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: updateBook(); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
