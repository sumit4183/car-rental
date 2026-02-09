# Car Rental System (Backend)

A C++ console-based application for managing a car rental system. This project provides a backend implementation using SQLite for data persistence, allowing for user management, car inventory control, booking handling, and payment processing.

## Features

- **User Management**
  - Register new users
  - Login existing users
  - Update user details
  - Delete users
  - Password security using SHA-256 hashing

- **Car Management**
  - Add new cars to the fleet
  - Edit existing car details
  - List all cars
  - Filter cars by type and rental price

- **Booking System**
  - Book a car
  - Cancel bookings
  - List all bookings
  - View bookings by specific user
  - Automated availability checks

- **Payment System**
  - Process payments for bookings
  - List all payments
  - View payments by specific user

## Prerequisites

To build and run this project, you need the following installed on your system:

- **C++ Compiler**: GCC (g++) supporting C++11 or later.
- **SQLite3**: Library for database management.
- **OpenSSL**: Library for cryptographic functions (SHA-256).

### macOS Installation (using Homebrew)

```bash
brew install sqlite3 openssl@1.1
```

## Build and Run

A helper script `build.sh` is provided in the `backend` directory to compile and run the application.

1. Navigate to the `backend` directory:
   ```bash
   cd backend
   ```

2. Make sure the script is executable:
   ```bash
   chmod +x build.sh
   ```

3. Run the build script:
   ```bash
   ./build.sh
   ```

This script will:
- Create a `bin` directory if it doesn't exist.
- Compile the source code using `g++`, linking against `sqlite3` and `openssl`.
- Execute the resulting binary.

## Usage

Upon running the application, you will be presented with a menu-driven interface:

```text
1.  Register new user
2.  Login existing user
...
11. Add car
...
21. Book a car
...
31. Process payment
...
999. Exit
```

Enter the number corresponding to the action you wish to perform and follow the on-screen prompts.

## Project Structure

- `src/`: Source files (`.cpp`)
  - `main.cpp`: Entry point and menu logic.
  - `database.cpp`: Database connection and initialization.
  - `user.cpp`, `car.cpp`, `booking.cpp`, `payment.cpp`: Core business logic.
  - `helper.cpp`: Utility functions (hashing, validation).
  - `inputs.cpp`: Input handling functions.
- `include/`: Header files (`.h`)
- `bin/`: Compiled executable (created after build).
- `car_rental.db`: SQLite database file (created after first run).

---

## 👤 Author

**Sumit Patel**
*   [LinkedIn](https://linkedin.com/in/sumit4183)
*   [GitHub](https://github.com/sumit4183)
*   [Portfolio](https://sumitp.netlify.app)