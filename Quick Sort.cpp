// Gideon Keith-Stanley
// OCCC Fall 2020
// CS-2363 C++ Online
// Quick Sort

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//Globals
long long comparisons = 0;
long long exchanges = 0;

//Constants
const int SMALL_LIST_SIZE = 10;

//Quick Sort Prototypes
void setMedianOfThree(int* arr, int first, int last);
void quicksort(int* arr, int first, int last);
void insertionSort(int* arr, int start, int stop);
int partition(int* arr, int start, int stop);

//Sort helper prototypes
bool inOrder(int a, int b);
void exchange(int& a, int& b);

//Array prototypes
void displayArray(const int* theArray, int start, int stop);
void displayArray(const int* theArray, int theSize);


int main(int argc, char * argv[])
{
    //declare variables
    int* arr;
    int size;
    string fileName = "";

    //Create objects
    ifstream fin;

    //Prompt the user for a filename, if one wasn't an argument
    if (argc == 2)
    {
        fileName = argv[1];
    }
    else
    {
        //Display a friendly greeting to the user
        cout << "Welcome to Quicksort!" << endl;

        //Prompt the user for a file name
        cout << "Enter the file name: ";

        //Accept that file name
        getline(cin, fileName);
        cout << endl;
    }

    //Attempt to open the file for input(see note below)
    fin.open(fileName);

    //On failure, display an appropriate error message and exit
    if (!fin)
    {
        cout << "ENOENT";
        exit(EXIT_FAILURE);
        cin.get();
    }

    //Read the data in the file and populate an array
    fin >> size;
    arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        fin >> arr[i];
    }

    quicksort(arr, 0, size-1);
    displayArray(arr, size);
    cout << "Comparisons: " << comparisons << endl;
    cout << "Exchanges: " << exchanges << endl;

    //output file sequence
    string outFile = fileName.substr(0, fileName.length() - 4) + "_sorted.txt";
    ofstream fout;
    fout.open(outFile);
    for (int i = 0; i < size; i++)
    {
        fout << arr[i] << " ";
    }
    cout << "Sorted array located in " << outFile << endl;
    cin.get();
}

//Set median of three
void setMedianOfThree(int* arr, int f, int l)
{
    int first = arr[f];
    int last = arr[l];
    int middle = arr[(f + l) / 2];
    int highest = first;
    int lowest = first;
    int median = f;

    if (middle > highest)
    {
        highest = middle;
    }
    
    if (last > highest)
    {
        highest = middle;
    }

    if (middle < lowest)
    {
        lowest = middle;
    }

    if (last < lowest)
    {
        lowest = last;
    }

    if (middle < highest && middle > lowest)
    {
        median = (f + l) / 2;
    }

    if (last < highest && last > lowest)
    {
        median = l;
    }

    if (median != f)
    {
        exchange(arr[f], arr[median]);
    }

 }

//quicksort
void quicksort(int* arr, int start, int stop)
{
    if ((stop - start) <= SMALL_LIST_SIZE)
    {
        insertionSort(arr, start, stop);
    }
    else
    {
        setMedianOfThree(arr, start, stop);
        int partitionElement = partition(arr, start, stop);
        quicksort(arr, start, partitionElement - 1);
        quicksort(arr, partitionElement + 1, stop);
    }

}

int partition(int* arr, int start, int stop)
{
    int left = start;
    int right = stop;
    
    while (left < right)
    {
        while (inOrder(arr[left], arr[right]))
        {
            right--;
        }
        if (!inOrder(arr[left], arr[right]))
        {
            exchange(arr[left], arr[right]);
        }
        while (inOrder(arr[left], arr[right]))
        {
            left++;
        }
        if (!inOrder(arr[left], arr[right]))
        {
            exchange(arr[left], arr[right]);
        }
    }

    if (left == right)
    {
        return left;
    }
}

//Insertion sort
void insertionSort(int* arr, int start, int stop)
{
    for (int i = start; i < stop - 1; i++)
    {
        int j = i + 1;
        while (j > 0 && !inOrder(arr[j - 1], arr[j]))
        {
            exchange(arr[j], arr[j - 1]);
            j--;
        }
    }
}

//Sort helpers
bool inOrder(int a, int b)
{
    comparisons++;
    return (b >= a);
}

void exchange(int& a, int& b)
{
    exchanges++;
    int swap = b;
    b = a;
    a = swap;
}


//Array helpers
void displayArray(const int* theArray, int theSize)
{
    if (theSize <= 200)
    {
        displayArray(theArray, 0, theSize);
    }
    else
    {
        displayArray(theArray, 0, 100);
        displayArray(theArray, theSize - 100, theSize);
    }
}

void displayArray(const int* theArray, int start, int stop)
{
    for (int i = start; i < stop; i++)
    {
        if (i % 10 == 0)
        {
            cout << endl;
        }
        cout << setw(10) << theArray[i];
    }
    cout << endl << endl;
}