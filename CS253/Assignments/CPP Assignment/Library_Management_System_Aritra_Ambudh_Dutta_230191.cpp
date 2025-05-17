#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <map>
#include <limits>
#include <iomanip>

using namespace std;

int countLinesInFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return 0;
    }
    int lineCount = 0;
    string line;
    while (getline(file, line))
    {
        ++lineCount;
    }
    return lineCount;
}

class Book
{
private:
    string title;
    string author;
    string publisher;
    string year;
    string ISBN;
    string status; // "Available", "Borrowed", or "Reserved"
    string borrowedBy;
    time_t borrowDate;

public:
    // Public constructor to initialize Book object
    Book(const string &title, const string &author, const string &publisher, const string &year, const string &ISBN, const string &status, const string &borrowedBy, time_t borrowDate)
        : title(title), author(author), publisher(publisher), year(year), ISBN(ISBN), status(status), borrowedBy(borrowedBy), borrowDate(borrowDate) {}

    void changeStatus(const string &newStatus)
    {
        status = newStatus;
        if (newStatus == "Available")
        {
            borrowedBy = "None";
            borrowDate = 0;
        }
    }

    string getStatus() const
    {
        return status;
    }

    string getISBN() const
    {
        return ISBN;
    }

    string getBorrowedBy() const
    {
        return borrowedBy;
    }

    time_t getBorrowDate() const
    {
        return borrowDate;
    }

    void borrowBook(const string &userID)
    {
        status = "Borrowed";
        borrowedBy = userID;
        borrowDate = time(nullptr);
    }

    void returnBook()
    {
        status = "Available";
        borrowedBy = "None";
        borrowDate = 0;
    }

    void displayDetailsIfAvailable() const
    {
        if (status == "Available")
        {
            cout << "Title: " << title << "\n";
            cout << "Author: " << author << "\n";
            cout << "Publisher: " << publisher << "\n";
            cout << "Year: " << year << "\n";
            cout << "ISBN: " << ISBN << "\n";
            cout << "Status: " << status << "\n";
            cout << "-------------------------\n";
        }
    }

    void displayDetails() const
    {
        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "Publisher: " << publisher << "\n";
        cout << "Year: " << year << "\n";
        cout << "ISBN: " << ISBN << "\n";
        cout << "Status: " << status << "\n";
        if (status == "Borrowed")
        {
            cout << "Borrowed By: " << borrowedBy << "\n";
            cout << "Borrow Date: " << ctime(&borrowDate);
        }
        cout << "-------------------------\n";
    }

    static vector<Book> readBookData(const string &filename)
    {
        vector<Book> books;
        ifstream file(filename);
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string title, author, publisher, year, ISBN, status, borrowedBy;
            time_t borrowDate;

            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, publisher, ',');
            getline(ss, year, ',');
            getline(ss, ISBN, ',');
            getline(ss, status, ',');
            getline(ss, borrowedBy, ',');
            ss >> borrowDate;

            Book book(title, author, publisher, year, ISBN, status, borrowedBy, borrowDate);
            books.push_back(book);
        }

        file.close();
        return books;
    }

    static void writeBookData(const vector<Book> &books, const string &filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Unable to open file " << filename << " for writing" << endl;
            return;
        }

        cout << "Writing " << books.size() << " books to " << filename << endl;

        for (size_t i = 0; i < books.size(); ++i)
        {
            const auto &book = books[i];
            file << book.getTitle() << ","
                 << book.getAuthor() << ","
                 << book.getPublisher() << ","
                 << book.getYear() << ","
                 << book.getISBN() << ","
                 << book.getStatus() << ","
                 << book.getBorrowedBy() << ","
                 << book.getBorrowDate();

            if (i != books.size() - 1)
            {
                file << "\n";
            }
        }
        file.close();
        cout << "Successfully wrote to " << filename << endl;
    }

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getPublisher() const { return publisher; }
    string getYear() const { return year; }
};

class User
{
protected:
    string username;
    string password;
    string ID;

public:
    User() {}
    User(const string &uname, const string &pwd, const string &id)
        : username(uname), password(pwd), ID(id) {}

    virtual ~User() {} // Make the class polymorphic by adding a virtual destructor

    string getUsername() const
    {
        return username;
    }

    string getPassword() const
    {
        return password;
    }

    string getID() const
    {
        return ID;
    }

    bool authenticate(const string &enteredPassword) const
    {
        return password == enteredPassword;
    }
};

class Student : public User
{
private:
    int fineDue;
    int booksBorrowed;

public:
    Student(const string &uname, const string &pwd, const string &id, int fine, int borrowed)
        : User(uname, pwd, id), fineDue(fine), booksBorrowed(borrowed) {}

    Student() {}

    int getFineDue() const
    {
        return fineDue;
    }

    int getBooksBorrowed() const
    {
        return booksBorrowed;
    }

    void borrowBook()
    {
        if (booksBorrowed < 3)
        {
            booksBorrowed++;
        }
        else
        {
            cout << "Cannot borrow more than 3 books.\n";
        }
    }

    void returnBook()
    {
        if (booksBorrowed > 0)
        {
            booksBorrowed--;
        }
    }

    void clearFine()
    {
        fineDue = 0;
    }

    void showBorrowedBooks() const
    {
        // This function should display the borrowed books
        // Implementation depends on how the borrowed books are tracked
    }

    static vector<Student> readStudentData(const string &filename)
    {
        vector<Student> students;
        ifstream file(filename);
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string uname, pwd, id;
            int fine, borrowed;

            getline(ss, uname, ',');
            getline(ss, pwd, ',');
            getline(ss, id, ',');
            ss >> fine >> borrowed;

            Student student(uname, pwd, id, fine, borrowed);
            students.push_back(student);
        }

        file.close();
        return students;
    }

    static void writeStudentData(const vector<Student> &students, const string &filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }

        for (size_t i = 0; i < students.size(); ++i)
        {
            const auto &student = students[i];
            file << student.getUsername() << ","
                 << student.getPassword() << ","
                 << student.getID() << ","
                 << student.getFineDue() << ","
                 << student.getBooksBorrowed();

            // Do not write a newline character if it's the last entry
            if (i != students.size() - 1)
            {
                file << "\n";
            }
        }
        file.close();
    }
};

class Faculty : public User
{
private:
    int booksBorrowed;

public:
    Faculty(const string &uname, const string &pwd, const string &id, int borrowed)
        : User(uname, pwd, id), booksBorrowed(borrowed) {}

    Faculty() {}

    int getBooksBorrowed() const
    {
        return booksBorrowed;
    }

    void borrowBook()
    {
        if (booksBorrowed < 5)
        {
            booksBorrowed++;
        }
        else
        {
            cout << "Cannot borrow more than 5 books.\n";
        }
    }

    void returnBook()
    {
        if (booksBorrowed > 0)
        {
            booksBorrowed--;
        }
    }

    void showBorrowedBooks() const
    {
        // This function should display the borrowed books
        // Implementation depends on how the borrowed books are tracked
    }

    static vector<Faculty> readFacultyData(const string &filename)
    {
        vector<Faculty> faculties;
        ifstream file(filename);
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string uname, pwd, id;
            int borrowed;

            getline(ss, uname, ',');
            getline(ss, pwd, ',');
            getline(ss, id, ',');
            ss >> borrowed;

            Faculty faculty(uname, pwd, id, borrowed);
            faculties.push_back(faculty);
        }

        file.close();
        return faculties;
    }

    static void writeFacultyData(const vector<Faculty> &faculties, const string &filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }

        for (size_t i = 0; i < faculties.size(); ++i)
        {
            const auto &faculty = faculties[i];
            file << faculty.getUsername() << ","
                 << faculty.getPassword() << ","
                 << faculty.getID() << ","
                 << faculty.getBooksBorrowed();

            // Do not write a newline character if it's the last entry
            if (i != faculties.size() - 1)
            {
                file << "\n";
            }
        }
        file.close();
    }
};

class Librarian : public User
{
public:
    Librarian(const string &uname, const string &pwd, const string &id)
        : User(uname, pwd, id) {}

    Librarian() {}

    void addBook(const string &filename, const string &title, const string &author, const string &publisher, const string &year, const string &ISBN)
    {
        ofstream file(filename, ios::app); // Open the file in append mode
        if (!file.is_open())
        {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }

        file << title << "," << author << "," << publisher << "," << year << "," << ISBN << ",Available,None,0\n";
        file.close();
    }

    void removeBook(const string &filename, const string &ISBN)
    {
        ifstream inFile(filename);
        ofstream tempFile("temp.txt");

        if (!inFile || !tempFile)
        {
            cerr << "Error opening files." << endl;
            return;
        }

        string line;
        bool updated = false;

        // Read each line from the original file
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string title, author, publisher, year, isbn, status, borrowedBy;
            time_t borrowDate;

            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, publisher, ',');
            getline(ss, year, ',');
            getline(ss, isbn, ',');
            getline(ss, status, ',');
            getline(ss, borrowedBy, ',');
            ss >> borrowDate;

            if (isbn == ISBN)
            {
                updated = true;
                continue;
            }
            else
            {
                tempFile << line << "\n";
            }
        }

        inFile.close();
        tempFile.close();

        // If the line was updated, replace the original file with the temporary file
        if (updated)
        {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
        }
        else
        {
            remove("temp.txt"); // Delete the temporary file if no update was made
        }
    }

    void addUser(const string &filename, const string &uname, const string &pwd, const string &id, const string &role)
    {
        ofstream file(filename, ios::app); // Open the file in append mode
        if (!file.is_open())
        {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }

        file << uname << "," << pwd << "," << id << "," << role << "\n";
        file.close();
    }

    void removeUser(const string &filename, const string &uname)
    {
        ifstream inFile(filename);
        ofstream tempFile("temp.txt");

        if (!inFile || !tempFile)
        {
            cerr << "Error opening files." << endl;
            return;
        }

        string line;
        bool updated = false;

        // Read each line from the original file
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string username, password, id, role;

            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, id, ',');
            getline(ss, role, ',');

            if (username == uname)
            {
                updated = true;
                continue;
            }
            else
            {
                tempFile << line << "\n";
            }
        }

        inFile.close();
        tempFile.close();

        // If the line was updated, replace the original file with the temporary file
        if (updated)
        {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
        }
        else
        {
            remove("temp.txt"); // Delete the temporary file if no update was made
        }
    }

    void searchUser(const string &filename, const string &uname)
    {
        ifstream inFile(filename);

        if (!inFile)
        {
            cerr << "Error opening file." << endl;
            return;
        }

        string line;
        bool found = false;

        // Read each line from the original file
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string username, password, id, role;

            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, id, ',');
            getline(ss, role, ',');

            if (username == uname)
            {
                cout << "Username: " << username << "\n";
                cout << "ID: " << id << "\n";
                cout << "Role: " << role << "\n";
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "User not found.\n";
        }

        inFile.close();
    }

    // NEW: read from librarians_data.txt
    static vector<Librarian> readLibrarianData(const string &filename)
    {
        vector<Librarian> librarians;
        ifstream file(filename);
        if (!file.is_open())
        {
            // If file doesn't exist or can't be opened, return empty vector
            return librarians;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string uname, pwd, id;
            getline(ss, uname, ',');
            getline(ss, pwd, ',');
            getline(ss, id, ',');

            Librarian librarian(uname, pwd, id);
            librarians.push_back(librarian);
        }

        file.close();
        return librarians;
    }

    // NEW: write out to librarians_data.txt
    static void writeLibrarianData(const vector<Librarian> &librarians, const string &filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }

        for (size_t i = 0; i < librarians.size(); ++i)
        {
            const auto &lib = librarians[i];
            file << lib.getUsername() << ","
                 << lib.getPassword() << ","
                 << lib.getID();

            if (i != librarians.size() - 1)
            {
                file << "\n";
            }
        }
        file.close();
    }
};

class BorrowRecord
{
private:
    string userID;
    string bookISBN;
    string bookTitle;
    time_t borrowDate;
    time_t returnDate; // 0 if still borrowed
    int daysKept;      // calculated on return
    int finePaid;      // amount paid on return

public:
    BorrowRecord(const string &userID, const string &bookISBN, const string &bookTitle,
                 time_t borrowDate, time_t returnDate = 0, int daysKept = 0, int finePaid = 0)
        : userID(userID), bookISBN(bookISBN), bookTitle(bookTitle),
          borrowDate(borrowDate), returnDate(returnDate), daysKept(daysKept), finePaid(finePaid) {}

    // Getters
    string getUserID() const { return userID; }
    string getBookISBN() const { return bookISBN; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }
    time_t getReturnDate() const { return returnDate; }
    int getDaysKept() const { return daysKept; }
    int getFinePaid() const { return finePaid; }

    // Return a book and update the record
    void returnBook(time_t returnTime, int daysKept, int finePaid)
    {
        this->returnDate = returnTime;
        this->daysKept = daysKept;
        this->finePaid = finePaid;
    }

    // Check if this record is for a specific user and book
    bool matches(const string &userID, const string &bookISBN) const
    {
        return this->userID == userID && this->bookISBN == bookISBN;
    }

    // Check if book is still borrowed (not returned yet)
    bool isActive() const
    {
        return returnDate == 0;
    }

    // Format record as a string
    string toString() const
    {
        stringstream ss;
        ss << userID << ","
           << bookISBN << ","
           << bookTitle << ","
           << borrowDate << ","
           << returnDate << ","
           << daysKept << ","
           << finePaid;
        return ss.str();
    }

    // Parse record from string
    static BorrowRecord fromString(const string &str)
    {
        stringstream ss(str);
        string userID, bookISBN, bookTitle;
        time_t borrowDate, returnDate;
        int daysKept, finePaid;

        getline(ss, userID, ',');
        getline(ss, bookISBN, ',');
        getline(ss, bookTitle, ',');
        ss >> borrowDate;
        ss.ignore(1); // Skip comma
        ss >> returnDate;
        ss.ignore(1); // Skip comma
        ss >> daysKept;
        ss.ignore(1); // Skip comma
        ss >> finePaid;

        return BorrowRecord(userID, bookISBN, bookTitle, borrowDate, returnDate, daysKept, finePaid);
    }
};

class Account
{
private:
    vector<string> borrowedBooks;
    map<string, time_t> borrowDates;
    int fine;

public:
    Account() : fine(0) {}

    void addBook(const string &bookISBN)
    {
        borrowedBooks.push_back(bookISBN);
        borrowDates[bookISBN] = time(nullptr);
    }

    void returnBook(const string &bookISBN)
    {
        borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), bookISBN), borrowedBooks.end());
        borrowDates.erase(bookISBN);
    }

    void calculateFine(bool isStudent)
    {
        time_t now = time(nullptr);
        fine = 0; // Reset fine
        for (const auto &entry : borrowDates)
        {
            int daysBorrowed = (now - entry.second) / (1);
            if (isStudent && daysBorrowed > 15)
            {
                fine += (daysBorrowed - 15) * 10;
            }
        }
    }

    int getFine() const
    {
        return fine;
    }

    void clearFine()
    {
        fine = 0;
    }

    const vector<string> &getBorrowedBooks() const
    {
        return borrowedBooks;
    }

    void showBorrowedBooks() const
    {
        if (borrowedBooks.empty())
        {
            cout << "No books borrowed as of now.\n";
            return;
        }
        time_t now = time(nullptr);
        for (const auto &bookISBN : borrowedBooks)
        {
            int daysBorrowed = (now - borrowDates.at(bookISBN)) / (1);
            cout << "Book ISBN: " << bookISBN << ", Days Borrowed: " << daysBorrowed << "\n";
        }
    }
};

class Library
{
private:
    vector<Book> books;
    vector<Student> students;
    vector<Faculty> faculties;
    vector<Librarian> librarians;
    vector<BorrowRecord> borrowHistory;
    const string historyFilename = "borrow_history.txt";

public:
    Library()
    {
        // Do not load or save in the constructor
        // We'll do it in initializeData() and loadData() separately
    }

    void addBook(const Book &book)
    {
        books.push_back(book);
    }

    void removeBook(const string &ISBN)
    {
        // Remember the old size
        auto oldSize = books.size();

        // Erase all matching books
        books.erase(remove_if(books.begin(), books.end(), [&](const Book &book)
                              { return book.getISBN() == ISBN; }),
                    books.end());

        // If the size actually shrank, a book was removed
        if (books.size() < oldSize)
        {
            cout << "Book removed successfully!\n";
        }
        else
        {
            cout << "No book found with ISBN " << ISBN << "\n";
        }
    }

    void displayBooks() const
    {
        for (const auto &book : books)
        {
            book.displayDetails();
        }
    }

    Book *findBook(const string &ISBN)
    {
        for (auto &book : books)
        {
            if (book.getISBN() == ISBN)
            {
                return &book;
            }
        }
        return nullptr;
    }

    User *findUser(const string &username)
    {
        for (auto &student : students)
        {
            if (student.getUsername() == username)
            {
                return &student;
            }
        }
        for (auto &faculty : faculties)
        {
            if (faculty.getUsername() == username)
            {
                return &faculty;
            }
        }
        for (auto &librarian : librarians)
        {
            if (librarian.getUsername() == username)
            {
                return &librarian;
            }
        }
        return nullptr;
    }

    Librarian *findLibrarian(const string &username)
    {
        for (auto &librarian : librarians)
        {
            if (librarian.getUsername() == username)
            {
                return &librarian;
            }
        }
        return nullptr;
    }

    void addUser(const User &user)
    {
        if (dynamic_cast<const Student *>(&user))
        {
            students.push_back(*dynamic_cast<const Student *>(&user));
        }
        else if (dynamic_cast<const Faculty *>(&user))
        {
            faculties.push_back(*dynamic_cast<const Faculty *>(&user));
        }
    }

    void removeUser(const string &ID)
    {
        // Track old sizes
        auto oldStudSize = students.size();
        auto oldFacSize = faculties.size();

        // Remove student with matching ID
        students.erase(remove_if(students.begin(), students.end(), [&](const Student &student)
                                 { return student.getID() == ID; }),
                       students.end());

        // Remove faculty with matching ID
        faculties.erase(remove_if(faculties.begin(), faculties.end(), [&](const Faculty &faculty)
                                  { return faculty.getID() == ID; }),
                        faculties.end());

        // If either vector shrank, a user was actually removed
        bool removedAnyone = (students.size() < oldStudSize) || (faculties.size() < oldFacSize);
        if (removedAnyone)
        {
            cout << "User removed successfully!\n";
        }
        else
        {
            cout << "No user found with ID " << ID << "\n";
        }
    }

    void saveData()
    {
        Book::writeBookData(books, "books_data.txt");
        Student::writeStudentData(students, "students_data.txt");
        Faculty::writeFacultyData(faculties, "faculties_data.txt");
        Librarian::writeLibrarianData(librarians, "librarians_data.txt");

        cout << "Data saved successfully." << endl;
    }

    void loadData()
    {
        cout << "Attempting to load data from files..." << endl;

        books = Book::readBookData("books_data.txt");
        students = Student::readStudentData("students_data.txt");
        faculties = Faculty::readFacultyData("faculties_data.txt");
        librarians = Librarian::readLibrarianData("librarians_data.txt");

        cout << "Loaded " << books.size() << " books from books_data.txt\n";
        cout << "Loaded " << students.size() << " students from students_data.txt\n";
        cout << "Loaded " << faculties.size() << " faculty members from faculties_data.txt\n";
        cout << "Loaded " << librarians.size() << " librarians from librarians_data.txt\n";

        // Also load borrow history
        loadBorrowHistory();

        // Sync the data
        syncBookAndUserData();
    }

    void initializeData()
    {
        // If data files are empty or missing, populate with default data
        // and save once.
        int bookLines = countLinesInFile("books_data.txt");
        int studLines = countLinesInFile("students_data.txt");
        int facLines = countLinesInFile("faculties_data.txt");
        int libLines = countLinesInFile("librarians_data.txt");

        if (bookLines <= 0 || studLines <= 0 || facLines <= 0 || libLines <= 0)
        {
            // Insert default data
            books = {
                Book("Book1", "Author1", "Publisher1", "2001", "ISBN1", "Available", "None", 0),
                Book("Book2", "Author2", "Publisher2", "2002", "ISBN2", "Available", "None", 0),
                Book("Book3", "Author3", "Publisher3", "2003", "ISBN3", "Available", "None", 0),
                Book("Book4", "Author4", "Publisher4", "2004", "ISBN4", "Available", "None", 0),
                Book("Book5", "Author5", "Publisher5", "2005", "ISBN5", "Available", "None", 0),
                Book("Book6", "Author6", "Publisher6", "2006", "ISBN6", "Available", "None", 0),
                Book("Book7", "Author7", "Publisher7", "2007", "ISBN7", "Available", "None", 0),
                Book("Book8", "Author8", "Publisher8", "2008", "ISBN8", "Available", "None", 0),
                Book("Book9", "Author9", "Publisher9", "2009", "ISBN9", "Available", "None", 0),
                Book("Book10", "Author10", "Publisher10", "2010", "ISBN10", "Available", "None", 0)
                // Add more if you want
            };

            students = {
                Student("Student1", "password1", "S1", 0, 0),
                Student("Student2", "password2", "S2", 0, 0),
                Student("Student3", "password3", "S3", 0, 0),
                Student("Student4", "password4", "S4", 0, 0),
                Student("Student5", "password5", "S5", 0, 0)
                // Add more if you want
            };

            faculties = {
                Faculty("Faculty1", "password1", "F1", 0),
                Faculty("Faculty2", "password2", "F2", 0),
                Faculty("Faculty3", "password3", "F3", 0)
                // Add more if you want
            };

            librarians = {
                Librarian("Librarian1", "password1", "L1"),
                Librarian("Librarian2", "password2", "L2"),
                Librarian("Librarian3", "password3", "L3")
                // Add more if you want
            };

            // Save once to create and populate the files
            saveData();
        }
    }

    // New helper function to display books borrowed by a certain user
    void showUserBorrowedBooks(const string &userID) const
    {
        bool foundAny = false;
        for (const auto &book : books)
        {
            // Check if this book is borrowed by the userID and is actually “Borrowed”
            if (book.getBorrowedBy() == userID && book.getStatus() == "Borrowed")
            {
                cout << "Borrowed Book: " << book.getTitle()
                     << " (ISBN: " << book.getISBN() << ")\n";
                foundAny = true;
            }
        }
        if (!foundAny)
        {
            cout << "No borrowed books found for user with ID = " << userID << "\n";
        }
    }

    vector<Librarian> &getLibrarians()
    {
        return librarians;
    }

    vector<Book> &getBooks()
    {
        return books;
    }

    // New function to calculate fine for a student based on actual borrowed books
    int calculateStudentFine(const string &studentID) const
    {
        int totalFine = 0;
        time_t now = time(nullptr);
        for (const auto &book : books)
        {
            if (book.getBorrowedBy() == studentID && book.getStatus() == "Borrowed")
            {
                int daysBorrowed = (now - book.getBorrowDate()) / (1);
                if (daysBorrowed > 15)
                {
                    totalFine += (daysBorrowed - 15) * 10;
                }
            }
        }
        return totalFine;
    }

    void displayAllUsers() const
    {
        cout << "\n=== STUDENTS ===\n";
        for (const auto &student : students)
        {
            cout << "ID: " << student.getID()
                 << ", Username: " << student.getUsername()
                 << ", Books Borrowed: " << student.getBooksBorrowed() << "\n";
        }

        cout << "\n=== FACULTY ===\n";
        for (const auto &faculty : faculties)
        {
            cout << "ID: " << faculty.getID()
                 << ", Username: " << faculty.getUsername()
                 << ", Books Borrowed: " << faculty.getBooksBorrowed() << "\n";
        }

        cout << "\n=== LIBRARIANS ===\n";
        for (const auto &librarian : librarians)
        {
            cout << "ID: " << librarian.getID()
                 << ", Username: " << librarian.getUsername() << "\n";
        }
    }

    void displayAllBooksStatus() const
    {
        time_t now = time(nullptr);
        for (const auto &book : books)
        {
            cout << "Title: " << book.getTitle()
                 << ", ISBN: " << book.getISBN()
                 << ", Status: " << book.getStatus();

            if (book.getStatus() == "Borrowed")
            {
                string borrower = book.getBorrowedBy();
                time_t borrowDate = book.getBorrowDate();
                int daysBorrowed = (now - borrowDate) / 1; // Using test divisor

                cout << "\n  Borrowed by: " << borrower
                     << ", Date: " << ctime(&borrowDate)
                     << "  Days kept: " << daysBorrowed;

                // Check if overdue based on borrower type
                bool isStudent = borrower[0] == 'S'; // Student IDs start with 'S'
                int allowedDays = isStudent ? 15 : 60;

                if (daysBorrowed > allowedDays)
                {
                    cout << " (OVERDUE by " << (daysBorrowed - allowedDays) << " days)";
                    if (isStudent)
                    {
                        int fine = (daysBorrowed - allowedDays) * 10;
                        cout << ", Fine: " << fine << " rupees";
                    }
                }
            }
            cout << "\n-------------------------\n";
        }
    }

    void updateBook(const string &ISBN)
    {
        Book *book = findBook(ISBN);
        if (!book)
        {
            cout << "Book with ISBN " << ISBN << " not found.\n";
            return;
        }

        int choice;
        cout << "What would you like to update?\n"
             << "1. Title\n2. Author\n3. Publisher\n4. Year\n"
             << "Enter choice: ";
        cin >> choice;

        string newValue;
        cout << "Enter new value: ";
        cin >> newValue;

        // Create a temporary book with the updated values
        Book updatedBook(
            choice == 1 ? newValue : book->getTitle(),
            choice == 2 ? newValue : book->getAuthor(),
            choice == 3 ? newValue : book->getPublisher(),
            choice == 4 ? newValue : book->getYear(),
            book->getISBN(),
            book->getStatus(),
            book->getBorrowedBy(),
            book->getBorrowDate());

        // Remove old book and add updated one
        books.erase(remove_if(books.begin(), books.end(),
                              [&](const Book &b)
                              { return b.getISBN() == ISBN; }),
                    books.end());
        books.push_back(updatedBook);

        cout << "Book updated successfully!\n";
    }

    void updateUser(const string &userID)
    {
        // Find which type of user it is
        bool isStudent = false;
        bool isFaculty = false;
        bool isLibrarian = false;

        for (auto &student : students)
        {
            if (student.getID() == userID)
            {
                isStudent = true;
                break;
            }
        }

        if (!isStudent)
        {
            for (auto &faculty : faculties)
            {
                if (faculty.getID() == userID)
                {
                    isFaculty = true;
                    break;
                }
            }
        }

        if (!isStudent && !isFaculty)
        {
            for (auto &librarian : librarians)
            {
                if (librarian.getID() == userID)
                {
                    isLibrarian = true;
                    break;
                }
            }
        }

        if (!isStudent && !isFaculty && !isLibrarian)
        {
            cout << "User with ID " << userID << " not found.\n";
            return;
        }

        // Update username/password
        int choice;
        cout << "What would you like to update?\n"
             << "1. Username\n2. Password\n"
             << "Enter choice: ";
        cin >> choice;

        string newValue;
        cout << "Enter new value: ";
        cin >> newValue;

        if (isStudent)
        {
            for (auto &student : students)
            {
                if (student.getID() == userID)
                {
                    if (choice == 1)
                    {
                        Student updatedStudent(newValue, student.getPassword(),
                                               student.getID(), student.getFineDue(),
                                               student.getBooksBorrowed());

                        students.erase(remove_if(students.begin(), students.end(),
                                                 [&](const Student &s)
                                                 { return s.getID() == userID; }),
                                       students.end());
                        students.push_back(updatedStudent);
                    }
                    else if (choice == 2)
                    {
                        Student updatedStudent(student.getUsername(), newValue,
                                               student.getID(), student.getFineDue(),
                                               student.getBooksBorrowed());

                        students.erase(remove_if(students.begin(), students.end(),
                                                 [&](const Student &s)
                                                 { return s.getID() == userID; }),
                                       students.end());
                        students.push_back(updatedStudent);
                    }
                    break;
                }
            }
        }
        else if (isFaculty)
        {
            // Similar logic for faculty
            for (auto &faculty : faculties)
            {
                if (faculty.getID() == userID)
                {
                    if (choice == 1)
                    {
                        Faculty updatedFaculty(newValue, faculty.getPassword(),
                                               faculty.getID(), faculty.getBooksBorrowed());

                        faculties.erase(remove_if(faculties.begin(), faculties.end(),
                                                  [&](const Faculty &f)
                                                  { return f.getID() == userID; }),
                                        faculties.end());
                        faculties.push_back(updatedFaculty);
                    }
                    else if (choice == 2)
                    {
                        Faculty updatedFaculty(faculty.getUsername(), newValue,
                                               faculty.getID(), faculty.getBooksBorrowed());

                        faculties.erase(remove_if(faculties.begin(), faculties.end(),
                                                  [&](const Faculty &f)
                                                  { return f.getID() == userID; }),
                                        faculties.end());
                        faculties.push_back(updatedFaculty);
                    }
                    break;
                }
            }
        }
        else if (isLibrarian)
        {
            // Similar logic for librarian
            for (auto &librarian : librarians)
            {
                if (librarian.getID() == userID)
                {
                    if (choice == 1)
                    {
                        Librarian updatedLibrarian(newValue, librarian.getPassword(), librarian.getID());

                        librarians.erase(remove_if(librarians.begin(), librarians.end(),
                                                   [&](const Librarian &l)
                                                   { return l.getID() == userID; }),
                                         librarians.end());
                        librarians.push_back(updatedLibrarian);
                    }
                    else if (choice == 2)
                    {
                        Librarian updatedLibrarian(librarian.getUsername(), newValue, librarian.getID());

                        librarians.erase(remove_if(librarians.begin(), librarians.end(),
                                                   [&](const Librarian &l)
                                                   { return l.getID() == userID; }),
                                         librarians.end());
                        librarians.push_back(updatedLibrarian);
                    }
                    break;
                }
            }
        }

        cout << "User updated successfully!\n";
    }

    void syncBookAndUserData()
    {
        // Reset all borrowing counts first
        for (auto &student : students)
        {
            student = Student(student.getUsername(), student.getPassword(),
                              student.getID(), student.getFineDue(), 0);
        }

        for (auto &faculty : faculties)
        {
            faculty = Faculty(faculty.getUsername(), faculty.getPassword(),
                              faculty.getID(), 0);
        }

        // Then count actual borrowed books from the books data
        for (const auto &book : books)
        {
            if (book.getStatus() == "Borrowed")
            {
                string borrower = book.getBorrowedBy();

                // Update the correct user's borrowed count
                if (borrower[0] == 'S')
                { // Student ID format
                    for (auto &student : students)
                    {
                        if (student.getID() == borrower)
                        {
                            student = Student(student.getUsername(), student.getPassword(),
                                              student.getID(), student.getFineDue(),
                                              student.getBooksBorrowed() + 1);
                            break;
                        }
                    }
                }
                else if (borrower[0] == 'F')
                { // Faculty ID format
                    for (auto &faculty : faculties)
                    {
                        if (faculty.getID() == borrower)
                        {
                            faculty = Faculty(faculty.getUsername(), faculty.getPassword(),
                                              faculty.getID(), faculty.getBooksBorrowed() + 1);
                            break;
                        }
                    }
                }
            }
        }

        // Save the corrected data
        Student::writeStudentData(students, "students_data.txt");
        Faculty::writeFacultyData(faculties, "faculties_data.txt");
    }

    // Load borrow history from file
    void loadBorrowHistory()
    {
        borrowHistory.clear();
        ifstream file(historyFilename);
        if (!file.is_open())
        {
            cout << "Borrow history file not found. Creating new file.\n";
            return;
        }

        string line;
        while (getline(file, line))
        {
            borrowHistory.push_back(BorrowRecord::fromString(line));
        }
        cout << "Loaded " << borrowHistory.size() << " history records.\n";
        file.close();
    }

    // Save borrow history to file
    void saveBorrowHistory()
    {
        ofstream file(historyFilename);
        if (!file.is_open())
        {
            cerr << "Error: Unable to open file " << historyFilename << " for writing" << endl;
            return;
        }

        for (size_t i = 0; i < borrowHistory.size(); ++i)
        {
            file << borrowHistory[i].toString();
            if (i != borrowHistory.size() - 1)
            {
                file << "\n";
            }
        }
        file.close();
    }

    // Add a new borrow record when a book is borrowed
    void addBorrowRecord(const string &userID, Book *book)
    {
        borrowHistory.push_back(BorrowRecord(userID, book->getISBN(), book->getTitle(), time(nullptr)));
        saveBorrowHistory();
    }

    // Update a record when a book is returned
    void updateBorrowRecord(const string &userID, Book *book, int finePaid)
    {
        time_t now = time(nullptr);
        string ISBN = book->getISBN();

        for (auto &record : borrowHistory)
        {
            if (record.matches(userID, ISBN) && record.isActive())
            {
                int daysKept = (now - record.getBorrowDate()) / 1; // Using test divisor
                record.returnBook(now, daysKept, finePaid);
                saveBorrowHistory();
                return;
            }
        }
    }

    // Display borrow history for a specific user
    void displayUserBorrowHistory(const string &userID) const
    {
        cout << "\n=== BORROWING HISTORY FOR USER: " << userID << " ===\n";

        bool foundAny = false;
        cout << "+----------------------+---------------+--------------------------+--------------------------+-----------+\n";
        cout << "| Book Title           | ISBN          | Borrowed On              | Returned On              | Days Kept |\n";
        cout << "+----------------------+---------------+--------------------------+--------------------------+-----------+\n";

        for (const auto &record : borrowHistory)
        {
            if (record.getUserID() == userID)
            {
                foundAny = true;
                string title = record.getBookTitle().substr(0, 20);
                string isbn = record.getBookISBN().substr(0, 10);

                time_t borrowDate = record.getBorrowDate();
                string borrowDateStr = ctime(&borrowDate);
                borrowDateStr = borrowDateStr.substr(0, borrowDateStr.length() - 1); // Remove newline

                string returnDateStr;
                if (record.isActive())
                {
                    returnDateStr = "Still borrowed";
                }
                else
                {
                    time_t returnDate = record.getReturnDate();
                    returnDateStr = ctime(&returnDate);
                    returnDateStr = returnDateStr.substr(0, returnDateStr.length() - 1); // Remove newline
                }

                // Format with simple ASCII characters - removed Fine Paid column
                cout << "| " << left << setw(20) << title
                     << " | " << setw(13) << isbn
                     << " | " << setw(19) << borrowDateStr
                     << " | " << setw(24) << returnDateStr
                     << " | " << setw(9) << (record.isActive() ? "Current" : to_string(record.getDaysKept()))
                     << " |\n";
            }
        }

        cout << "+----------------------+---------------+--------------------------+--------------------------+-----------+\n";

        if (!foundAny)
        {
            cout << "No borrowing history found for this user.\n";
        }
    }

    // Display currently borrowed books for a user (from history)
    void showUserCurrentBooks(const string &userID) const
    {
        cout << "\n=== CURRENTLY BORROWED BOOKS FOR USER: " << userID << " ===\n";

        bool foundAny = false;
        cout << "+----------------------+---------------+--------------------------+----------------+\n";
        cout << "| Book Title           | ISBN          | Borrowed On              | Days Borrowed  |\n";
        cout << "+----------------------+---------------+--------------------------+----------------+\n";

        time_t now = time(nullptr);

        for (const auto &record : borrowHistory)
        {
            if (record.getUserID() == userID && record.isActive())
            {
                foundAny = true;
                string title = record.getBookTitle().substr(0, 20);
                string isbn = record.getBookISBN().substr(0, 10);

                time_t borrowDate = record.getBorrowDate();
                string borrowDateStr = ctime(&borrowDate);
                borrowDateStr = borrowDateStr.substr(0, borrowDateStr.length() - 1); // Remove newline

                int daysBorrowed = (now - borrowDate) / 1; // Using test divisor

                // Format with simple ASCII characters
                cout << "| " << left << setw(20) << title
                     << " | " << setw(13) << isbn
                     << " | " << setw(19) << borrowDateStr
                     << " | " << setw(14) << daysBorrowed << " |\n";
            }
        }

        cout << "+----------------------+---------------+--------------------------+----------------+\n\n";

        if (!foundAny)
        {
            cout << "No books currently borrowed by this user.\n";
        }
    }
};

int main()
{
    Library library;

    // 1. Create or fill files if empty
    library.initializeData();

    // 2. Load existing data (or default data just saved)
    library.loadData();

    try
    {
        while (true)
        {
            cout << "Enter 1 for Student, 2 for Faculty, 3 for Librarian, and any other number to exit: ";
            int userType;
            if (!(cin >> userType))
            {
                cout << "Invalid input. Please enter an integer.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (userType != 1 && userType != 2 && userType != 3)
            {
                cout << "Saving data and exiting...\n";
                break;
            }

            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            User *user = library.findUser(username);
            if (!user || !user->authenticate(password))
            {
                cout << "Invalid username or password.\n";
                continue;
            }

            if (userType == 1)
            {
                Student *student = dynamic_cast<Student *>(user);
                if (!student)
                {
                    cout << "Invalid user type.\n";
                    continue;
                }

                while (true)
                {
                    cout << "1. Borrow Book\n2. Return Book\n3. Pay Fine\n"
                         << "4. Show Current Borrowed Books\n"
                         << "5. View Borrowing History\n" // New option
                         << "6. Exit\n";                  // Changed from 5 to 6
                    int choice;
                    if (!(cin >> choice))
                    {
                        cout << "Invalid input. Please enter an integer.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    if (choice == 6) // Changed from 5 to 6
                        break;

                    switch (choice)
                    {
                    case 1: // Borrow Book
                    {
                        string ISBN;
                        cout << "Enter ISBN of the book to borrow: ";
                        cin >> ISBN;
                        Book *book = library.findBook(ISBN);

                        // First check if the book exists and is available
                        if (!book || book->getStatus() != "Available")
                        {
                            cout << "Book is not available.\n";
                            break;
                        }

                        // NEW: Check for unpaid fines before allowing borrowing
                        int fine = library.calculateStudentFine(student->getID());
                        if (fine > 0)
                        {
                            cout << "You have unpaid fines of " << fine << " rupees.\n";
                            cout << "Please pay your fines before borrowing new books.\n";
                            break;
                        }

                        // Then check if under book limit
                        if (student->getBooksBorrowed() < 3)
                        {
                            // Student increments their borrowed count
                            student->borrowBook();

                            // Mark the book as borrowed
                            book->borrowBook(student->getID());

                            // Add borrow record
                            library.addBorrowRecord(student->getID(), book);

                            // Immediately save so the data file stays consistent
                            library.saveData();

                            cout << "Book borrowed successfully!\n";
                        }
                        else
                        {
                            // Do *not* borrow or save if already at limit
                            cout << "Cannot borrow more than 3 books.\n";
                        }
                        break;
                    }
                    case 2: // Return Book
                    {
                        string ISBN;
                        cout << "Enter ISBN of the book to return: ";
                        cin >> ISBN;

                        Book *book = library.findBook(ISBN);
                        if (!book || book->getBorrowedBy() != student->getID())
                        {
                            cout << "You have not borrowed this book.\n";
                            break;
                        }

                        // Check if this specific book has any fine associated with it
                        time_t now = time(nullptr);
                        int daysBorrowed = (now - book->getBorrowDate()) / 1; // Using your testing divisor

                        int finePaid = 0;
                        if (daysBorrowed > 15) // Book is overdue
                        {
                            int bookFine = (daysBorrowed - 15) * 10;
                            cout << "This book is overdue by " << (daysBorrowed - 15) << " days.\n";
                            cout << "You must pay a fine of " << bookFine << " rupees before returning.\n";
                            cout << "Would you like to pay the fine now? (1 for Yes, 0 for No): ";

                            int payNow;
                            cin >> payNow;

                            if (payNow == 1)
                            {
                                cout << "Enter amount to pay: ";
                                int amount;
                                cin >> amount;

                                if (amount >= bookFine)
                                {
                                    cout << "Fine paid successfully. You can now return the book.\n";
                                    // Reset this book's borrow date (effectively clearing its fine)
                                    book->borrowBook(student->getID());
                                    finePaid = amount; // Record how much was paid
                                }
                                else
                                {
                                    cout << "Insufficient amount. Book cannot be returned.\n";
                                    break;
                                }
                            }
                            else
                            {
                                cout << "Book cannot be returned without paying the fine.\n";
                                break;
                            }
                        }

                        // If we reach here, either there was no fine or the fine was paid
                        student->returnBook();
                        book->returnBook();

                        // Update borrow record
                        library.updateBorrowRecord(student->getID(), book, finePaid);

                        library.saveData();
                        cout << "Book returned successfully!\n";
                        break;
                    }
                    case 3:
                    {
                        // Calculate fine based on actual borrowed books
                        int fine = library.calculateStudentFine(student->getID());

                        cout << "Your fine is: " << fine << " rupees.\n";

                        if (fine == 0)
                        {
                            break;
                        }

                        cout << "Enter amount to pay: ";
                        int amount;
                        cin >> amount;

                        if (amount >= fine)
                        {
                            // 1. Update the student's fineDue
                            student->clearFine();

                            // 2. Reset timestamps ONLY for overdue books (those with fines)
                            time_t now = time(nullptr);
                            for (auto &book : library.getBooks())
                            {
                                if (book.getBorrowedBy() == student->getID() && book.getStatus() == "Borrowed")
                                {
                                    // Check if this specific book is overdue
                                    int daysBorrowed = (now - book.getBorrowDate()) / 1;
                                    if (daysBorrowed > 15) // This book had a fine
                                    {
                                        // Reset only THIS book's borrow date
                                        book.borrowBook(student->getID()); // Sets timestamp to now
                                    }
                                }
                            }

                            // 3. Save all changes
                            library.saveData();
                            cout << "Fine cleared. Borrow time reset for overdue books.\n";
                        }
                        else
                        {
                            cout << "Insufficient amount.\n";
                        }
                        break;
                    }
                    case 4: // Current borrowed books
                    {
                        // Use history-based approach instead of single book display
                        library.showUserCurrentBooks(student->getID());
                        break;
                    }
                    case 5: // View complete history
                    {
                        library.displayUserBorrowHistory(student->getID());
                        break;
                    }
                    default:
                        cout << "Invalid choice.\n";
                    }
                }
            }
            else if (userType == 2)
            {
                Faculty *faculty = dynamic_cast<Faculty *>(user);
                if (!faculty)
                {
                    cout << "Invalid user type.\n";
                    continue;
                }

                while (true)
                {
                    cout << "1. Borrow Book\n2. Return Book\n"
                         << "3. Show Current Borrowed Books\n"
                         << "4. View Borrowing History\n" // New option
                         << "5. Exit\n";                  // Changed from 4 to 5
                    int choice;
                    if (!(cin >> choice))
                    {
                        cout << "Invalid input. Please enter an integer.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    if (choice == 5) // Changed from 4 to 5
                        break;

                    switch (choice)
                    {
                    case 1: // Borrow Book
                    {
                        // 1) Check if the book exists and is "Available"
                        string ISBN;
                        cout << "Enter ISBN of the book to borrow: ";
                        cin >> ISBN;
                        Book *book = library.findBook(ISBN);
                        if (!book || book->getStatus() != "Available")
                        {
                            cout << "Book is not available.\n";
                            break;
                        }

                        // 2) Confirm faculty is under their 5-book limit
                        if (faculty->getBooksBorrowed() >= 5)
                        {
                            cout << "Cannot borrow more than 5 books.\n";
                            break;
                        }

                        // 3) Verify no borrowed book is overdue by more than 60 days
                        bool hasOverdue = false;
                        // Loop through all books in the library
                        for (auto &b : library.getBooks())
                        {
                            if (b.getBorrowedBy() == faculty->getID() && b.getStatus() == "Borrowed")
                            {
                                time_t now = time(nullptr);
                                double daysBorrowed = difftime(now, b.getBorrowDate()) / (1);
                                if (daysBorrowed > 60.0)
                                {
                                    hasOverdue = true;
                                    break;
                                }
                            }
                        }
                        if (hasOverdue)
                        {
                            cout << "Cannot borrow a new book while you have an overdue book (more than 60 days).\n";
                            break;
                        }

                        // 4) If we reach here, the faculty is allowed to borrow
                        faculty->borrowBook();              // increments faculty->booksBorrowed
                        book->borrowBook(faculty->getID()); // marks book as "Borrowed"

                        // Add borrow record
                        library.addBorrowRecord(faculty->getID(), book);

                        library.saveData(); // persist changes
                        cout << "Book borrowed successfully!\n";
                        break;
                    }
                    case 2:
                    {
                        // Return Book for Faculty
                        string ISBN;
                        cout << "Enter ISBN of the book to return: ";
                        cin >> ISBN;

                        Book *book = library.findBook(ISBN);
                        if (book && book->getBorrowedBy() == faculty->getID())
                        {
                            faculty->returnBook(); // decrements faculty->booksBorrowed
                            book->returnBook();    // sets book status to "Available"

                            // Update borrow record (faculty pay no fines)
                            library.updateBorrowRecord(faculty->getID(), book, 0);

                            library.saveData(); // persists updated data

                            cout << "Book returned successfully!\n";
                        }
                        else
                        {
                            cout << "You have not borrowed this book.\n";
                        }
                        break;
                    }
                    case 3: // Current borrowed books
                    {
                        library.showUserCurrentBooks(faculty->getID());
                        break;
                    }
                    case 4: // View complete history
                    {
                        library.displayUserBorrowHistory(faculty->getID());
                        break;
                    }
                    default:
                        cout << "Invalid choice.\n";
                    }
                }
            }
            else if (userType == 3)
            {
                Librarian *librarian = library.findLibrarian(username);
                if (!librarian || !librarian->authenticate(password))
                {
                    cout << "Invalid user type or password.\n";
                    continue;
                }

                while (true)
                {
                    cout << "1. Add Book\n"
                         << "2. Remove Book\n"
                         << "3. Add User\n"
                         << "4. Remove User\n"
                         << "5. View All Books\n"
                         << "6. View All Users\n"               // New option
                         << "7. View Book Status Details\n"     // New option
                         << "8. Update Book\n"                  // New option
                         << "9. Update User\n"                  // New option
                         << "10. View User Borrowing History\n" // New option
                         << "11. Exit\n";                       // Changed from 10 to 11
                    int choice;
                    if (!(cin >> choice))
                    {
                        cout << "Invalid input. Please enter an integer.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    if (choice == 11) // Changed from 10 to 11
                        break;

                    switch (choice)
                    {
                    case 1: // Add Book
                    {
                        string title, author, publisher, year, ISBN;
                        cout << "Enter title: ";
                        cin >> title;
                        cout << "Enter author: ";
                        cin >> author;
                        cout << "Enter publisher: ";
                        cin >> publisher;
                        cout << "Enter year: ";
                        cin >> year;
                        cout << "Enter ISBN: ";
                        cin >> ISBN;

                        Book book(title, author, publisher, year, ISBN, "Available", "None", 0);
                        library.addBook(book);
                        library.saveData();

                        cout << "Book added successfully!\n";
                        break;
                    }
                    case 2: // Remove Book
                    {
                        string ISBN;
                        cout << "Enter ISBN of the book to remove: ";
                        cin >> ISBN;
                        library.removeBook(ISBN);
                        library.saveData();
                        break;
                    }
                    case 3: // Add User
                    {
                        string uname, pwd, id, role;
                        cout << "Enter username: ";
                        cin >> uname;
                        cout << "Enter password: ";
                        cin >> pwd;
                        cout << "Enter ID: ";
                        cin >> id;
                        cout << "Enter role (Student/Faculty/Librarian): ";
                        cin >> role;

                        if (role == "Student")
                        {
                            Student newStudent(uname, pwd, id, 0, 0);
                            library.addUser(newStudent);
                        }
                        else if (role == "Faculty")
                        {
                            Faculty newFaculty(uname, pwd, id, 0);
                            library.addUser(newFaculty);
                        }
                        else if (role == "Librarian")
                        {
                            library.getLibrarians().push_back(Librarian(uname, pwd, id));
                        }

                        library.saveData();
                        cout << "User added successfully!\n";
                        break;
                    }
                    case 4: // Remove User
                    {
                        string userID;
                        cout << "Enter ID of the user to remove: ";
                        cin >> userID;
                        library.removeUser(userID);
                        library.saveData();
                        break;
                    }
                    case 5: // View All Books
                    {
                        library.displayBooks();
                        break;
                    }
                    case 6: // View All Users
                    {
                        library.displayAllUsers();
                        break;
                    }
                    case 7: // View Book Status Details
                    {
                        library.displayAllBooksStatus();
                        break;
                    }
                    case 8: // Update Book
                    {
                        string ISBN;
                        cout << "Enter ISBN of the book to update: ";
                        cin >> ISBN;

                        library.updateBook(ISBN);

                        // Immediately save to disk
                        library.saveData();
                        break;
                    }
                    case 9: // Update User
                    {
                        string userID;
                        cout << "Enter ID of the user to update: ";
                        cin >> userID;

                        library.updateUser(userID);

                        // Immediately save to disk
                        library.saveData();
                        break;
                    }
                    case 10: // View User Borrowing History
                    {
                        string userID;
                        cout << "Enter ID of the user to view history: ";
                        cin >> userID;

                        library.displayUserBorrowHistory(userID);
                        break;
                    }
                    default:
                        cout << "Invalid choice.\n";
                    }
                }
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "An error occurred: " << e.what() << endl;
    }

    // Make sure data is saved before exiting
    library.saveData();
    cout << "Program terminated successfully.Goodbye!!" << endl;
    return 0;
}