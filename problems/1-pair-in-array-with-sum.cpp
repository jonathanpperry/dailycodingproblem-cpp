#include <iostream>
#include <unordered_set>
using namespace std;

void printPairs(int arr[], int arr_size, int sum)
{
    unordered_set<int> s;
    for (int i = 0; i < arr_size; i++)
    {
        int neededDiffVal = sum - arr[i];

        if (s.find(neededDiffVal) != s.end())
        {
            cout << "There exists a pair adding to the given sum value";
            return;
        }
        s.insert(arr[i]);
    }
}

/* Driver Code */
int main()
{
    int A[] = {1, 15, 4, 45, 6, 10, 8};
    int n = 16;
    int arr_size = sizeof(A) / sizeof(A[0]);

    // Function calling
    printPairs(A, arr_size, n);

    return 0;
}
