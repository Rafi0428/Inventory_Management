# C Inventory Management System

A lightweight, console-based inventory management system written in C. This program uses standard file I/O operations to perform CRUD (Create, Read, Update, Delete) actions on a local binary file.

## Features
* **Add Products:** Save new item details (ID, Name, Quantity, Price, Supplier).
* **Display Inventory:** View all stored products in a formatted table.
* **Search:** Find specific products using their unique ID.
* **Update:** Modify the stock quantity or price of existing items.
* **Delete:** Remove a product from the database entirely.

## Prerequisites
* A C compiler (like GCC)

## How to Compile and Run

1. Clone this repository to your local machine.
2. Open your terminal or command prompt.
3. Compile the code using GCC:
   ```bash
   gcc inventory.c -o inventory