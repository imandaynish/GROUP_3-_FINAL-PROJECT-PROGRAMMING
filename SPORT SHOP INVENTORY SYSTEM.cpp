#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

// DATA STRUCTURE
struct Item {
    int id;
    string name;
    string category;
    int quantity;
    double price;
};

const int MAX = 100;

// FUNCTION PROTOTYPES
void addItem(Item items[], int& count);
void displayItems(const Item items[], int count);
void updateItem(Item items[], int count);
void deleteItem(Item items[], int& count);
void saveToFile(const Item items[], int count);
void loadFromFile(Item items[], int& count);
void clearScreen();

// MAIN PROGRAM
int main() {
    Item items[MAX];
    int itemCount = 0;
    int choice;

    loadFromFile(items, itemCount);

    do {
        clearScreen();
        cout << "\n=====================================\n";
        cout << "   SPORT SHOP INVENTORY SYSTEM\n";
        cout << "=====================================\n";
        cout << "1. Add New Item\n";
        cout << "2. Display All Items\n";
        cout << "3. Update Item\n";
        cout << "4. Delete Item\n";
        cout << "5. Save Data to File\n";
        cout << "6. Load Data from File\n";
        cout << "7. Exit\n";
        cout << "=====================================\n";
        cout << "Enter your choice (1-7): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            addItem(items, itemCount);
            break;
        case 2:
            displayItems(items, itemCount);
            break;
        case 3:
            updateItem(items, itemCount);
            break;
        case 4:
            deleteItem(items, itemCount);
            break;
        case 5:
            saveToFile(items, itemCount);
            break;
        case 6:
            loadFromFile(items, itemCount);
            break;
        case 7:
            cout << "Thank you. Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }

        if (choice != 7) {
            cout << "\nPress Enter to continue...";
            cin.ignore();  // Clear any leftover newline
            cin.get();     // Wait for Enter key
        }

    } while (choice != 7);

    // Auto-save on exit
    saveToFile(items, itemCount);
    return 0;
}

// CLEAR SCREEN
void clearScreen() {
    system("cls");  // Windows command to clear screen
}

// ADD ITEM
void addItem(Item items[], int& count) {
    if (count >= MAX) {
        cout << "Inventory is full!\n";
        return;
    }

    cout << "\nEnter Item ID: ";
    cin >> items[count].id;
    cin.ignore();

    cout << "Enter Item Name: ";
    getline(cin, items[count].name);

    cout << "Enter Category: ";
    getline(cin, items[count].category);

    cout << "Enter Quantity: ";
    cin >> items[count].quantity;

    cout << "Enter Price (RM): ";
    cin >> items[count].price;

    count++;
    cout << "Item added successfully!\n";
}

// DISPLAY ITEMS
void displayItems(const Item items[], int count) {
    if (count == 0) {
        cout << "No items in inventory.\n";
        return;
    }

    cout << "\n-----------------------------------------------------------------\n";
    cout << left << setw(8) << "ID"
        << setw(20) << "Name"
        << setw(15) << "Category"
        << setw(10) << "Qty"
        << setw(10) << "Price (RM)\n";
    cout << "-----------------------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(8) << items[i].id
            << setw(20) << items[i].name
            << setw(15) << items[i].category
            << setw(10) << items[i].quantity
            << fixed << setprecision(2) << items[i].price << endl;
    }
    cout << "-----------------------------------------------------------------\n";
    cout << "Total items: " << count << endl;  // Added item count
}

// UPDATE ITEM
void updateItem(Item items[], int count) {
    if (count == 0) {
        cout << "No items in inventory to update.\n";
        return;
    }

    int searchID;
    bool found = false;

    cout << "Enter Item ID to update: ";
    cin >> searchID;
    cin.ignore();  

    for (int i = 0; i < count; i++) {
        if (items[i].id == searchID) {
            found = true;

            cout << "\n=== CURRENT ITEM DETAILS ===\n";
            cout << "ID: " << items[i].id << endl;
            cout << "Name: " << items[i].name << endl;
            cout << "Category: " << items[i].category << endl;
            cout << "Quantity: " << items[i].quantity << endl;
            cout << "Price: RM" << fixed << setprecision(2) << items[i].price << endl;

            cout << "\n=== ENTER NEW VALUES ===\n";
            cout << "Leave field blank and press Enter to keep current value\n";

            // Update name
            cout << "New Name [" << items[i].name << "]: ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                items[i].name = newName;
            }

            // Update category
            cout << "New Category [" << items[i].category << "]: ";
            string newCategory;
            getline(cin, newCategory);
            if (!newCategory.empty()) {
                items[i].category = newCategory;
            }

            // Update quantity
            int newQuantity;
            cout << "New Quantity [" << items[i].quantity << "] (enter -1 to keep current): ";
            cin >> newQuantity;
            if (newQuantity >= 0) {
                items[i].quantity = newQuantity;
            }
            cin.ignore();

            // Update price
            double newPrice;
            cout << "New Price (RM) [" << fixed << setprecision(2) << items[i].price << "] (enter -1 to keep current): ";
            cin >> newPrice;
            if (newPrice >= 0) {
                items[i].price = newPrice;
            }
            cin.ignore();

            cout << "\nItem updated successfully!\n";
            break;
        }
    }

    if (!found) {
        cout << "Item not found!\n";
    }
}

// DELETE ITEM
void deleteItem(Item items[], int& count) {
    if (count == 0) {
        cout << "No items in inventory to delete.\n";
        return;
    }

    int searchID;
    bool found = false;

    cout << "Enter Item ID to delete: ";
    cin >> searchID;
    cin.ignore();  

    for (int i = 0; i < count; i++) {
        if (items[i].id == searchID) {
            found = true;

            cout << "\n=== ITEM TO DELETE ===\n";
            cout << "ID: " << items[i].id << endl;
            cout << "Name: " << items[i].name << endl;
            cout << "Category: " << items[i].category << endl;
            cout << "Quantity: " << items[i].quantity << endl;
            cout << "Price: RM" << fixed << setprecision(2) << items[i].price << endl;

            // Ask for confirmation
            cout << "\nAre you sure you want to delete this item? (yes/no): ";
            string confirm;
            getline(cin, confirm);

            if (confirm == "yes" || confirm == "YES" || confirm == "y" || confirm == "Y") {
                
                for (int j = i; j < count - 1; j++) {
                    items[j] = items[j + 1];
                }
                count--;  
                cout << "Item deleted successfully!\n";
            }
            else {
                cout << "Deletion cancelled.\n";
            }
            break;
        }
    }

    if (!found) {
        cout << "Item not found!\n";
    }
}

// SAVE TO FILE 
void saveToFile(const Item items[], int count) {
    if (count == 0) {
        cout << "No items to save.\n";
        return;
    }
    ofstream outFile("SPORT_SHOP_INVENTORY.txt");

    if (!outFile) {
        cout << "Error opening file!\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        outFile << "Item ID     : " << items[i].id << endl;
        outFile << "Item Name   : " << items[i].name << endl;
        outFile << "Category    : " << items[i].category << endl;
        outFile << "Quantity    : " << items[i].quantity << endl;
        outFile << "Price (RM)  : " << fixed << setprecision(2) << items[i].price << endl;
        outFile << "----------------------------\n";
    }

    outFile.close();
    cout << "Data saved successfully!\n";
}

// LOAD FROM FILE 
void loadFromFile(Item items[], int& count) {
    ifstream inFile("SPORT_SHOP_INVENTORY.txt");

    if (!inFile) {
        cout << "File not found!\n";
        return;
    }

    count = 0;
    string line;

    while (getline(inFile, line)) {
        if (line.find("Item ID") != string::npos) {
            items[count].id = stoi(line.substr(line.find(":") + 1));

            getline(inFile, line);
            items[count].name = line.substr(line.find(":") + 1);

            getline(inFile, line);
            items[count].category = line.substr(line.find(":") + 1);

            getline(inFile, line);
            items[count].quantity = stoi(line.substr(line.find(":") + 1));

            getline(inFile, line);
            items[count].price = stod(line.substr(line.find(":") + 1));

            getline(inFile, line); // skip dashed line
            count++;
        }
    }

    inFile.close();
    cout << "Data loaded successfully!\n";
}
