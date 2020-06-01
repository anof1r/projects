// C++ program for Sorts visualization
#include <iostream>
#include "Bits/stdc++.h"
#include <chrono>
#include "graphics.h"
#include <algorithm>
#include <thread>
#include "windows.h"
using namespace std;

// Initialize the size
// with the total numbers to sorted
// and the gap to be maintained in graph
vector<int> numbers;
int size;
int gap = 4;



// Function for swapping the lines graphically
void swap(int i, int j, int x, int y)
{
    // Swapping the first line with the correct line
    // by making it black again and then draw the pixel
    // for white color.
    setcolor(GREEN);
    line(i, size, i, size - x);
    setcolor(BLACK);
    line(i, size, i, size - x);
    setcolor(WHITE);
    line(i, size, i, size - y);

    // Swapping the first line with the correct line
    // by making it black again and then draw the pixel
    // for white color.
    setcolor(BLACK);
    line(j, size, j, size - y);
    setcolor(GREEN);
    line(j, size, j, size - y);
    setcolor(WHITE);
    line(j, size, j, size - x);
}

// Bubble sort function
void bubbleSort()
{
    int temp, i, j;

    for (i = 1; i < size; i++) {
        for (j = 0; j < size - i; j++) {
            if (numbers[j] > numbers[j + 1]) {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;

                // As we swapped the last two numbers
                // just swap the lines with the values.
                // This is function call
                // for swapping the lines
                swap(gap * j + 1,
                     gap * (j + 1) + 1,
                     numbers[j + 1],
                     numbers[j]);
            }
        }
    }
}

void insertionSort()
{
    int n = size;
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = numbers[i];
        j = i - 1;

        while (j >= 0 && numbers[j] > key)
        {
            numbers[j + 1] = numbers[j];
            j = j - 1;
               swap(gap * j + 1,
                    gap * (j + 1) + 1,
                    numbers[j + 1],
                    numbers[j]);
        }
        numbers[j + 1] = key;
    }
}

void swap_quick(int* a, int* b)
{
int t = *a;
*a = *b;
*b = t;
}

int partition (int arr[], int low, int high)
{

    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap_quick(&arr[i], &arr[j]);
            swap(gap * j + 1,
                gap * (i) + 1,
                numbers[i],
                numbers[j]);
        }
    }
    swap_quick(&arr[i + 1], &arr[high]);
    swap(gap * high + 1,
        gap * (i + 1) + 1,
        numbers[i + 1],
        numbers[high]);
    return (i + 1);


}

void quickSort(int arr[] = &numbers[0], int low = 0, int high =numbers.size() - 1)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(&arr[0], low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high );
    }
}


void swap_colors_selsort(int i, int j, int x, int y)
{

    // y is the minimum element,
    // first make this number green
    // Now, swapping it by making black again
    // and then draw the pixels
    // for white color with x value.
    setcolor(GREEN);
    line(j, size, j, size - y);

    delay(100);

    setcolor(BLACK);
    line(j, size, j, size - y);

    setcolor(WHITE);
    line(j, size, j, size - x);

    // X is the element to be swapped,
    // first make this number black
    // Now, highlight y with green
    // representing the minimum element
    // and then draw the pixels
    // for white color with y value.
    setcolor(BLACK);
    line(i, size, i, size - x);

    setcolor(GREEN);
    line(i, size, i, size - y);

    delay(100);

    setcolor(WHITE);
    line(i, size, i, size - y);
}

// Function for swapping two numbers
void swap_sel(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Selection sort function
void selsort()
{
    for (int i = 0; i < size - 1; i++) {

        // Find the minimum element
        // in unsorted array
        int min_idx = i;

        for (int j = i + 1; j < size; j++) {
            if (numbers[j] < numbers[min_idx]) {
                min_idx = j;
            }
        }

        // Swap the found minimum element
        // with the first element
        // delay(500);
        swap_sel(&numbers[min_idx],
             &numbers[i]);

        // Function to show transition in swapping
               swap_colors_selsort(gap * i + 1,
                    gap * (min_idx) + 1,
                    numbers[min_idx],
                    numbers[i]);
    }
}
void CocktailSort(int n = numbers.size() , int a[] = &numbers[0])
{
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = false;

        // loop from left to right same as
        // the bubble sort
        for (int i = start; i < end; ++i) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
                swap(gap * i + 1,
                    gap * (i + 1) + 1,
                    numbers[i + 1],
                    numbers[i]);
            }
        }

        // if nothing moved, then array is sorted.
        if (!swapped)
            break;

        // otherwise, reset the swapped flag so that it
        // can be used in the next stage
        swapped = false;

        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;

        // from right to left, doing the
        // same comparison as in the previous stage
        for (int i = end - 1; i >= start; --i) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
                swap(gap * i + 1,
                    gap * (i + 1) + 1,
                    numbers[i + 1],
                    numbers[i]);
            }
        }

        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }
}


// Driver program
int main()
{
    setlocale(LC_ALL,"Russian");
    int Choose;
    cout<<"Выберите алгоритм сортировки "<<endl;
    cout<<"1. Bubble Sort\n";
    cout<<"2. Selection Sort\n";
    cout<<"3. Insertion Sort\n";
    cout<<"4. Quick Sort\n";
    cout<<"5. Cocktail Sort\n";
    cout<<"Ваш алгоритм сортировки: ";
    cin >> Choose;
    cout<< "Введите размер массива" << endl;
    cin >> size;

    // auto detection of screen size
    int gd = DETECT, gm;
    int wid1;

    // Graph initialization
    initgraph(&gd, &gm, NULL);

    // setting up window size (gap*size) * (size)
    wid1 = initwindow(gap * size + 1, size + 1);
    setcurrentwindow(wid1);

    // Initializing the array
    for (int i = 1; i <= size; i++)
        numbers.push_back(i);

    // Find a seed and shuffle the array
    // to make it random.
    // Here  different type of array
    // can be taken to results
    // such as nearly sorted, already sorted,
    // reverse sorted to visualize the result
    unsigned seed
        = chrono::system_clock::now()
              .time_since_epoch()
              .count();

    shuffle(numbers.begin(),
            numbers.end(),
            default_random_engine(seed));

    // Initial plot of numbers in graph taking
    // the vector position as x-axis and its
    // corresponding value will be the height of line.
    for (int i = 1; i <= gap * size; i += gap) {
        line(i, size, i, (size - numbers[i / gap]));
    }


    // Delay the code
    delay(200);

    switch (Choose)
    {
    case 1:
        bubbleSort();
    break;
    case 2:
        selsort();
    break;
    case 3:
        insertionSort();
    break;
    case 4:
        quickSort();
    break;
    case 5:
        CocktailSort();
    break;

    default:
        cout << "Такого в списке нет" << endl;
        return 0;
    }


    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Wait for sometime .
    delay(5000);

    // Close the graph
    closegraph();

    return 0;
}
