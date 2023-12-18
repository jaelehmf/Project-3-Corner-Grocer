/*
Project 3
CS 210

Author: Jeri Mabuti
*/


#include <iostream>
#include <fstream>    
#include <string>
#include <vector>
#include "GroceryItem.h"

using namespace std;

//Function to read inventory file and return vector of GroceryItem objects
vector<GroceryItem> readInventoryFile(const string& filename) {
    ifstream inFS(filename);        //filename will be replaced with Inventory.txt in the main()
    vector<GroceryItem> items;

    if (inFS.is_open()) {
        string itemName;

        //Loop to read each line from input file until there are no more lines to read
        while (getline(inFS, itemName)) {   
            bool found = false;                     //To keep track of items with the same names are found
            for (auto& item : items) {  
                if (item.getName() == itemName) {   //Checks if the name matches itemName from input file
                    item.addItem(1);                //If item with same name found, then +1 
                    found = true;
                    break;
                }
            }
            //If item with same name not found then creates a newItem w/ quantity of 1
            if (!found) {           
                GroceryItem newItem(itemName, 1); 
                items.push_back(newItem);       //Adds new item to list
            }
        }
        inFS.close();   //Close input file
    }
    else {
        //cerr instead of cout for imemdiate error message if file doesn't open
        cerr << "Unable to open file " << filename << endl; 
    }

    return items;   //Saves item vector containing GroceryItem objects
}

//Function to print frequency of all items
void printFrequency(const vector<GroceryItem>& items) {
    for (const auto& item : items) {
        cout << item.getName() << " " << item.getQuantity() << endl;
    }
}

//Function to print the frequency of all items into a histogram
void printHistogram(const vector<GroceryItem>& items) {
    for (const auto& item : items) {
        cout << item.getName() << " ";
        for (int i = 0; i < item.getQuantity(); ++i) {
            cout << "*";
        }
        cout << endl;
    }
}

//Function to write data to a backup file
void backupData(const vector<GroceryItem>& items) {
    ofstream outFS("frequency.dat");    //Opening output file stream
    if (outFS.is_open()) {
        for (const auto& item : items) {
            outFS << item.getName() << " " << item.getQuantity() << endl;
        }
        outFS.close();                  //Close output file steam
    }
    else {
        //Display error message upon debug if unable to create file
        cerr << "Unable to create backup file." << endl; 
    }
}

int main() {
    //Calling function to read the data from the Inventory.txt file 
    vector<GroceryItem> inventory = readInventoryFile("Inventory.txt");
    
    int choice;        //Variable for the switch function
    
    //Main menu loop
    do {
        cout << "Menu:\n";
        cout << "1. Search for an item\n";
        cout << "2. Display all frequency\n";
        cout << "3. Print histogram\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string searchItem;          //Variable for user input when searching for item
            cout << "Enter the item you wish to look for: ";
            cin.ignore();               //Clear newline from the input buffer
            getline(cin, searchItem);       

            //Convert user input to lowercase for case-insensitive comparison
            for (char& c : searchItem) {
                c = tolower(static_cast<unsigned char>(c));
            }

            int frequency = 0;
            string foundItemName;
            for (const auto& item : inventory) {
                string itemName = item.getName();
                string itemNameLower = itemName;    //Variable for if user input is lowercase

                //Convert user input to lowercase for case-insensitive comparison
                for (char& c : itemNameLower) {
                    c = tolower(static_cast<unsigned char>(c));
                }

                //If user input is lowercase, program can still match to existing data
                if (itemNameLower == searchItem) {
                    frequency = item.getQuantity();
                    foundItemName = item.getName();
                    break;
                }
            }

            if (frequency > 0) {
                //Display the found item name exactly as stored in inventory, not lowercase
                cout << foundItemName << " " << frequency << endl;
            }
            else {
                cout << "Item not found in inventory." << endl;
            }
            break;
        }
        case 2:
            //Display a list of item name with quanitity of that item
            cout << "\nFrequency of all items:" << endl;
            for (const auto& item : inventory) {
                cout << item.getName() << " " << item.getQuantity() << endl;
            }
            break;
        case 3:
            //Displays a histogram with same info as case 2 and converts quantity to a number of asterisks 
            cout << "\nHistogram:" << endl;
            for (const auto& item : inventory) {
                cout << item.getName() << "*";
                for (int i = 0; i < item.getQuantity(); ++i) {
                    cout << "*";
                }
                cout << endl;
            }
            break;
        case 4:
            backupData(inventory);              //Backing up the data before exiting program
            cout << "\nExiting program...\n";
            break;
        default:
            cout << "\nInvalid choice. Please enter a valid option.\n";
        }
    } 
    
    //Main menu loop repeats until user input is 4
    while (choice != 4); 

    return 0;
}