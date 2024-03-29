//
//  main.cpp
//  hw2
//
//  Created by Kaelan Nguyen on 9/20/23.
//

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

bool readInventory(string fileName, int numRecords, string *&plu, string *&name, bool *&salesType, double *&price, int *&currentInv);

int main() {
    
    int numRecords = 0;
    string fileName;
    // cout << setprecision(3) << showpoint;
    
    // get file name
    cout << "Enter file name: ";
    cin >> fileName;
    
    //initialize filler variables to read file
    string num1, num2;
    bool num3;
    double num4;
    int num5;
    
    // read file
    ifstream inFile(fileName);
    if (!inFile)
    {
        cout << "File could not be opened\n" << "Exiting\n";
        return 0;
    } // end of if
    else
    {
        // read file + count # of records
        while (inFile >> num1 >> num2 >> num3 >> num4 >> num5)
        {
            numRecords++;
        } // end of while to read file
        
        // close and reopen to read from the beginning
        inFile.close();
        
    } // end of else
    
    cout << "There are " << numRecords << " records in the file" << endl << endl;
    
    // initialize pointers to arrays
    string *plu = nullptr;
    string *name = nullptr;
    bool *salesType = nullptr;
    double *price = nullptr;
    int *currentInv = nullptr;
    
    // dynamically allocate new arrays using newly acquired numRecords
    plu = new string[numRecords];
    name = new string[numRecords];
    salesType = new bool[numRecords];
    price = new double[numRecords];
    currentInv = new int[numRecords];

    readInventory(fileName, numRecords, plu, name, salesType, price, currentInv);
    
    // print inventory
    cout << "Inventory read from file: \n" << "------------------------\n";
    for (int i = 0; i < numRecords; i++)
    {
        cout
        << setw(5) << "PLU: "
        << setw(5) << plu[i] << ", "
        << setw(20) << left << name[i] << ", "
        << setw(5) << "type: "
        << setw(2) << salesType[i] << ", "
        << setw(10) << "unit price: "
        << setw(5) << price[i] << ", "
        << setw(10) << "inventory: "
        << setw(5) << currentInv[i]  << endl;
    }
    
    return 0;
} // end of main

bool readInventory(string fileName, int numRecords, string *&plu, string *&name, bool *&salesType, double *&price, int *&currentInv)
{
    ifstream inFile;
    inFile.open(fileName);
    
    // populate dynamically allocated arrays w/ file
    if (inFile)
    {
        for (int i = 0; i < numRecords; i++)
        {
            inFile >> plu[i] >> name[i] >> salesType[i] >> price[i] >> currentInv[i];
        } // end of for loop to read new arrays
        inFile.close();
        return true;
    } // end of if
    else
    {
        cout << "Read failed";
        return false;
    }
} // end of readInventory
