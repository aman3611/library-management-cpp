# 📚 Library Management System (C++)

This is a simple command-line based **Library Management System** built using C++.  
It allows you to manage books in a library including adding, searching, deleting, issuing, and returning books.

---

## 🚀 Features

- 📘 Add a new book (ID, Title, Author)
- 📚 View all books
- 🔍 Search books by title or author
- ❌ Delete a book by ID
- ✅ Issue a book to a student
- 🔁 Return a previously issued book
- 💾 File-based storage (no database needed)

---

## 🛠️ Technologies Used

- C++ (Core Language)
- File Handling (`fstream`)
- Command-line interface

---

## 📂 Files

- `main.cpp` - Main source code
- `books.txt` - Stores all books data
- `issued_books.txt` - Tracks issued books

---

## 💻 How to Run

### 1. Compile:

```bash
g++ main.cpp -o library


RUN:

./library     # Linux/Mac/WSL
library.exe   # Windows