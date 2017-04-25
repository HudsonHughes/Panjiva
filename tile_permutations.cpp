#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void printPermutations (int numarr[], char* arr[], int index, int last){
    if (index == last){
        for (int i = 0; i < last; ++i) {
            if (i > 0)
                cout << "_";
            cout << arr[numarr[i] + 1];
        }
        cout << endl;
    }
    else
    {
        for (int i = index; i <= last; i++)
        {
            //put object up front
            swap((numarr[index]), (numarr[i]));
            //go deeper
            printPermutations(numarr, arr, index+1, last);
            //put it back
            swap((numarr[index]), (numarr[i]));
        }
    }
}

int main(int argc, char* argv[])
{
    int numarr[argc - 1];
    for(int i = 1; i < argc - 1; i++) numarr[i - 1] = i;
    printPermutations(numarr, argv, 0, argc - 2);

    return 0;
}
