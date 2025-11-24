# Policy Announcement Management System

This project is a simple **C-based CRUD (Create, Read, Update, Delete)** system that manages policy announcements using file handling. All data is stored in a binary file (`policies.dat`) so policies remain saved even after the program is closed.

---

##  Features

* Add new policies
* List all saved policies
* Search policies by title
* Update existing policies
* Delete policies
* Auto-save all changes into `policies.dat`
* Loads saved data automatically on startup

---

##  Files Used

### **1. policies.dat**

A binary file that stores:

* Total policy count
* All policy structs (ID, Title, Description)

This file gets created automatically when adding the first policy.

---

##  How to Compile

Use GCC to compile the program:

```sh
gcc policy.c -o policy
```

Run the program:

```sh
./policy
```

On Windows (MinGW):

```sh
gcc policy.c -o policy.exe
policy.exe
```

---

##  Program Overview

### **Struct Used:**

```c
struct Policy {
    int id;
    char title[50];
    char description[200];
};
```

### **File Handling:**

* `saveToFile()` saves all data to `policies.dat`
* `loadFromFile()` loads existing data at program start

### **Main Menu Includes:**

1. Add Policy
2. List Policies
3. Search Policy by Title
4. Update Policy
5. Delete Policy
6. Exit

---

##  How to Use

1. Run the program.
2. Choose an option from the menu.
3. Follow the prompts to manage policies.
4. All changes are saved automatically.

---

 ## output photos

 ###**Main Menu**

 <img width="274" height="162" alt="Screenshot 2025-11-22 112513" src="https://github.com/user-attachments/assets/581eaf63-f80e-4a1f-92c5-e4fd3b92af51" />

 ###**Add Policy**

<img width="588" height="112" alt="Screenshot 2025-11-22 115556" src="https://github.com/user-attachments/assets/a4a8b53a-b494-4993-9568-75c3a49805a3" />

###**List policy** 

<img width="594" height="307" alt="Screenshot 2025-11-22 120048" src="https://github.com/user-attachments/assets/0babb1f1-c168-4588-b8c6-14a130d041f5" />

###**Search Policy by Title**

<img width="597" height="140" alt="Screenshot 2025-11-22 120218" src="https://github.com/user-attachments/assets/5c80e1db-b864-4ad3-a1ce-7a9caafc9f57" />

###**Update Policy**

Before Update

<img width="594" height="307" alt="Screenshot 2025-11-22 120048" src="https://github.com/user-attachments/assets/0babb1f1-c168-4588-b8c6-14a130d041f5" />

After Update

<img width="796" height="116" alt="Screenshot 2025-11-22 120436" src="https://github.com/user-attachments/assets/dcbe9150-664a-4d47-a28e-efb0985fbb07" />





