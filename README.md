<h1 align="center">🚌 Bus Ticket Reservation & Information System</h1>

<p align="center">
<b>Find your bus, pick your seat, book your ticket.</b><br>
A menu-driven C console app for managing buses, searching routes, reserving seats, and keeping passenger records.
</p>

---

## ✨ Features

- 🚍 **Bus management**: add, view, and update bus information
- 🔍 **Search**: look up buses by route and other details
- 💺 **Seat management**: view seat layouts and check availability
- 🎫 **Reservations**: book tickets with passenger details and a unique reservation ID (e.g. `R1001`)
- ❌ **Cancellation**: cancel a reservation and release the seat automatically
- ✅ **Input validation**: invalid or duplicate bookings are rejected
- 💾 **File handling**: buses, seats, and reservations are saved to `.dat` files and reloaded on startup

## 📁 Project Structure

```
├── docs/          Project proposal
└── src/
    ├── main.c            Menu and program flow
    ├── bus.c / bus.h               Bus management
    ├── search.c / search.h         Searching buses
    ├── seat.c / seat.h             Seat management
    ├── reservation.c / reservation.h   Passengers and reservations
    └── data.h            Shared structures and file functions
```

## 🚀 How to Run

```bash
git clone https://github.com/<Aarij-Khurram>/<Bus-management-and-reservation-system>.git
cd <Bus-management-and-reservation-system>
gcc src/*.c -o bus_system
./bus_system
```

On Windows: `bus_system.exe`

## 👥 Team

| Member | GitHub | Module |
|--------|--------|--------|
| Member 1 | [@Aarij-Khurram](https://github.com/Aarij-Khurram) | Bus management and `main.c` integration |
| Member 2 | [@guybilz](https://github.com/guybilz) | Search and seat management |
| Member 3 | [@Okashakhan2190](https://github.com/Okashakhan2190) | Reservations, passengers, `reservations.dat` |

## 🎓 About

Built for the Programming Fundamentals course (CS1002) as a semester project, using only C, modular `.c`/`.h` files, and file handling. No GUI, database, or web components.

## 📄 License

MIT