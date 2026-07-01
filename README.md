# 🏦 Bank Management System & Digital Wallet

An interactive, console-based C++ banking application that simulates real-world financial operations. The system features a dual-role interface supporting both secure **User Operations** (wallets, deposits, withdrawals) and comprehensive **Administrative Control** (account monitoring and data persistence).

---

## **🔑 Admin Access Credentials**

To log in and evaluate the administrative functions, use the following pre-configured credentials:
* **Admin ID:** `10`
* **Admin Password:** `Admin!123`

---

## **Key Features**

* **Secure Authentication:** Features custom hidden password input logic masking credentials with (`*`) and includes robust password strength validation criteria.
* **Encryption Mechanism:** Custom type-casting rotation encryption logic to securely mask account passwords prior to file serialization.
* **Persistent Storage Architecture:** Saves and loads all user profile modifications dynamically to a persistent flat-file dataset (`account.txt`).
* **Optimized Search Engine:** Implements a binary search algorithm mapping unique 5-digit account numbers efficiently against sorted memory datasets.
* **Fraud Protection:** Automatically locks out any user account via automated status deactivation after **3 consecutive failed password attempts**.

---

## **How to Use the Program**

1. **Sign Up:** Create a new profile by providing a unique name, strong password, and an initialization balance. The system automatically provisions a unique 5-digit ID.
2. **User Login:** Access the secure operations menu using your unique ID and password.
3. **Wallet Navigation:** Execute operations such as checking balances, depositing funds, withdrawing cash safely, changing passwords, or deactivating accounts.
4. **Admin Dashboard:** Access structural overviews to check total system balances, lookup specific profiles, or toggle global account activation flags.

---
---

## **🛠️ Development Tools**

This project was built and managed using the following industry-standard tools:
* **VS Code:** The primary text editor used for writing, formatting, and debugging the C++ code.
* **Git:** Used for local version control to track changes and manage code history.
* **GitHub:** Used for hosting the repository online, managing backup history, and deploying the live site via GitHub Pages.

---


## **Technical Breakdown**

### **Object-Oriented Architecture**
The application relies on structural inheritance modeling where the base financial property blueprints are controlled in a parental `Bank` context, while specialized operations are extended within user or structural boundaries.

### **Data Structures**
Uses dynamic dynamic sequencing schemas (`std::vector<user>`) paired with modern custom comparison lambdas to guarantee continuous data alignment for stable underlying memory search calls.

---

## **Credits**

Conceptualized, structured, and developed by **Zyad**.

---

## **License & Copyright**

### 🔒 **Proprietary / Closed Source**

Copyright © 2026 Zyad. All rights reserved.

This project is **strictly closed-source**. All source code, architectural structure, dynamic business logic, and custom documentation are the private intellectual property of the author (**Zyad**). 

* **No Redistribution:** You may not copy, distribute, modify, sub-license, or publicly replicate this source code or any of its algorithms without explicit prior written permission from the owner.
* **Personal Use Only:** Accessing the repository is limited solely to reviewing and evaluating the implementation layout.
