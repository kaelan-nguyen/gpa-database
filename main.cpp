#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// Function Prototypes
int smallestGPA(double GPA[], int size, int j);
int smallestNetID(int netID[], int size, int j);

void swapGPA(double GPA[], int& j, int& indx);
void swapNetID(int netID[], int& j, int& indx);
void swapMajor(string major[], int& j, int& indx);

void printAll(int netID[], string major[], double GPA[], int size);
int linearSearchID(int arr[], int numElems, int value, int &nIter);
int binarySearchID(int arr[], int numElems, int value, int &nIter);

int main ()
{
    const int NUM_ELMTS = 18;
    cout << setprecision(3) << showpoint;

    // netID, major, and GPA are parallel arrays
    int netID[NUM_ELMTS]; // Original netID array
    string major[NUM_ELMTS]; // Original major array
    double GPA[NUM_ELMTS]; // Original GPA array

    // sortedGPAbyGPA is sorted by GPA, and sortedNetIDbyGPA and sortedMajorbyGPA are parallel arrays
    double sortedGPAbyGPA[NUM_ELMTS]; // GPA array, sorted by GPA
    int sortedNetIDbyGPA[NUM_ELMTS];
    string sortedMajorbyGPA[NUM_ELMTS];

    // sortedNetIDbyID is sorted by netID, and sortedMajorbyID and sortedGPAbyID are parallel arrays
    int sortedNetIDbyID[NUM_ELMTS]; // netID array, sorted by netID
    string sortedMajorbyID[NUM_ELMTS];
    double sortedGPAbyID[NUM_ELMTS];

    // My variables
    int userChoice = 0;
    string fileName;

    cout << "Enter file name: " << endl;
    cin >> fileName;

    ifstream infoInp;
    infoInp.open(fileName);
    int fileNUM_ELMTS = 0;
    // int fileCounter = 0;
    
    if (infoInp) // Validating file was opened
    {
        // success
        while (infoInp >> netID[fileNUM_ELMTS] >> major[fileNUM_ELMTS] >> GPA[fileNUM_ELMTS]) {
            // cout << netID[fileNUM_ELMTS] << major[fileNUM_ELMTS] << GPA[fileNUM_ELMTS] << endl;
            fileNUM_ELMTS++;
        }
        // fileNUM_ELMTS = fileCounter - 1
        infoInp.close();
    }
    else
    {
        cout << "Could not open file\n" << "Exiting";
        return 0;
    }

    // Copying over originals
    for (int i = 0; i < fileNUM_ELMTS; i++)
    {
        sortedGPAbyGPA[i] = GPA[i];
        sortedNetIDbyGPA[i] = netID[i];
        sortedMajorbyGPA[i] = major[i];

        sortedNetIDbyID[i] = netID[i];
        sortedMajorbyID[i] = major[i];
        sortedGPAbyID[i] = GPA[i];
    }
    
    
    // Sort by GPA
    for (int j = 0; j < fileNUM_ELMTS; j++)
    {
        // double small = sortedGPAbyGPA[j];
        int indx = j;
        indx = smallestGPA(sortedGPAbyGPA, fileNUM_ELMTS, j);
        swapGPA(sortedGPAbyGPA, j, indx);
        swapNetID(sortedNetIDbyGPA, j, indx);
        swapMajor(sortedMajorbyGPA, j, indx);
    }

    // Sort by netID
    for (int j = 0; j < fileNUM_ELMTS; j++)
    {
        // int small = sortedNetIDbyID[j];
        int indx2 = j;
        indx2 = smallestNetID(sortedNetIDbyID, fileNUM_ELMTS, j);
        swapNetID(sortedNetIDbyID, j, indx2);
        swapGPA(sortedGPAbyID, j, indx2);
        swapMajor(sortedMajorbyID, j, indx2);
    }
    
    
    // Print original arrays
    cout << "Original arrays:" << endl << "----------------" << endl;
    printAll(netID, major, GPA, fileNUM_ELMTS);
    
    // Print arrays sorted by GPA
    cout << "Arrays sorted by GPA:" << endl << "---------------------" << endl;
    printAll(sortedNetIDbyGPA, sortedMajorbyGPA, sortedGPAbyGPA, fileNUM_ELMTS);
    
    // Print arrays sorted by netID
    cout << "Arrays sorted by netID:" << endl << "-----------------------" << endl;
    printAll(sortedNetIDbyID, sortedMajorbyID, sortedGPAbyID, fileNUM_ELMTS);

    cout << endl;
    
    do {
        cout << endl << "***************" << endl << "Menu of choices" << endl << "***************" << endl;
        cout << "1 - List top n students" << endl;
        cout << "2 - Search on a netID" << endl;
        cout << "3 - Quit" << endl;
        cin >> userChoice;
        
        // List top n students
        int listN;
        if (userChoice == 1) {
            cout << "Enter n: ";
            cin >> listN;
            if (listN > fileNUM_ELMTS) {
                listN = fileNUM_ELMTS;
            }
            cout << "Top " << listN << " students are:\n" << endl;
            for (int i = listN; i > 0; i--)
            {
                cout << "netID: " << sortedNetIDbyGPA[i] << ", major: " << sortedMajorbyGPA[i] << ", GPA: " << sortedGPAbyGPA[i] << endl;
            }
        }
        
        // Linear search
        int netIDsearch, nIter;
        if (userChoice == 2) {
            cout << "Enter netID: ";
            cin >> netIDsearch;
            int linsearchResult = linearSearchID(netID, fileNUM_ELMTS, netIDsearch, nIter);
            int binsearchResult = binarySearchID(netID, fileNUM_ELMTS, netIDsearch, nIter);
            
            // Print result of linear search
            cout <<  endl << "Result of linear search:\n" << "------------------------\n";
            if (linsearchResult == -1) {
                cout << "Student not found\n" << "It took " << nIter << " iterations\n";
            }
            else {
                cout << "Student found at index " << linsearchResult << ", GPA is " << GPA[linsearchResult] << endl;
                cout << "It took " << nIter << " iterations\n";
            }
            
            // Print result of binary search
            cout << endl << "Result of binary serach:\n" << "------------------------\n";
            if (binsearchResult == -1) {
                cout << "Student not found\n" << "It took " << nIter << " iterations \n";
            }
            else {
                cout << "Student found at index " << binsearchResult << ", GPA is " << GPA[binsearchResult] << endl;
                cout << "It took " << nIter << " iterations\n";
            }
            
        }
    
        } while (userChoice != 3);
    
    if (userChoice == 3) {
        cout << "Exiting" << endl;
    }
    
    
    
    return 0;
}

int smallestGPA(double GPA[], int size, int j)
{
    double small = GPA[j];
    int indx;
    for (int i = j+1; i < size; i++)
    {
        if (small > GPA[i]) {
            small = GPA[i];
            indx = i;
        }
    }
    return indx;
}

int smallestNetID(int netID[], int size, int j)
{
    int small = netID[j];
    int indx;
    for (int i = j+1; i < size; i++)
    {
        if (small > netID[i]) {
            small = netID[i];
            indx = i;
        }
    }
    return indx;
}

void swapGPA(double GPA[], int& j, int& indx)
{
    double tmp = GPA[j];
    GPA[j] = GPA[indx];
    GPA[indx] = tmp;
}

void swapNetID(int netID[], int& j, int& indx)
{
    int tmp = netID[j];
    netID[j] = netID[indx];
    netID[indx] = tmp;
}

void swapMajor(string major[], int& j, int& indx)
{
    string tmp = major[j];
    major[j] = major[indx];
    major[indx] = tmp;
}

void printAll(int netID[], string major[], double GPA[], int size)
{
    cout
    << setw(7) << "index"
    << setw(7) << "netID"
    << setw(7) << "major"
    << setw(7) << "GPA"
    << setw(7) << "index"
    << setw(7) << "netID"
    << setw(7) << "major"
    << setw(7) << "GPA" << endl;
    for (int i = 0; i < size; i++)
    {
        cout
        << setw(7) << i
        << setw(7) << netID[i]
        << setw(7) << major[i]
        << setw(7) << GPA[i];
        // i++;
        cout
        << setw(7) << i
        << setw(7) << netID[i]
        << setw(7) << major[i]
        << setw(7) << GPA[i] << endl;
    }
    cout << endl;
}
/* This function implements linear search on an array. It takes the following arguments:
arr: the array, numElems: number of elements of array,
value: search value, and nIter. nIter is a reference variable used
to pass the number of iterations back to the calling function.
The function returns the index where the match is found, -1 if no
match is found
*/
int linearSearchID(int arr[], int numElems, int value, int &nIter)
{
    for (int i = 0; i < numElems; i++)
    {
        if (value == arr[i]) {
            nIter = i + 1;
            return i;
        }
    }
    return -1;
}

/* This function implements binary search on an array. It takes the following arguments:
arr: the array, numElems: number of elements of array,
value: search value, and nIter. nIter is a reference variable used
to pass the number of iterations back to the calling function.
The function returns the index where the match is found, -1 if no
match is found
*/
int binarySearchID(int arr[], int numElems, int value, int &nIter)
{
    int left = 0;
    int right = (numElems - 1);
    while (left <= right) {
        nIter++;
        int middle = (right/2);
        if (arr[middle] == value) {
            return middle;
        }
        else if (arr[middle] < value) {
            left = middle + 1;
        }
        else {
            right = middle - 1;
        }
    }
    return -1;
}
