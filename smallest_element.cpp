#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7; // A large constant to represent infinity

int main()
{
    int n;
    cin >> n; // Input size of the array

    // If the number of elements is less than 3, the third smallest doesn't exist
    if (n < 3)
    {
        cout << "Third smallest does not exist\n";
        return 0;
    }

    vector<int> a(n); // Declare a vector of size n
    for (int &k : a)
        cin >> k; // Input elements into the array

    // Initialize the smallest, second smallest, and third smallest with infinity
    int mi = INF, mi1 = INF, mi2 = INF;

    // Iterate through the array to find the third smallest element
    for (const int &k : a)
    {
        if (k <= mi) // Update smallest and shift the other two
        {
            mi2 = mi1;
            mi1 = mi;
            mi = k;
        }
        else if (k <= mi1) // Update second smallest and shift the third
        {
            mi2 = mi1;
            mi1 = k;
        }
        else if (k < mi2) // Update third smallest
        {
            mi2 = k;
        }
    }

    // Output the third smallest element
    cout << "Third smallest element is " << mi2 << endl;
    return 0;
}
