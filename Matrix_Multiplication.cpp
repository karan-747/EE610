#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

///////////////////////////////////////////////////////////////// Matrix Implemented using Lists /////////////////////////////////////////////////

// Definition of the ListNode class
class ListNode
{
public:
    int value;
    ListNode *next;

    // Constructor to initialize a ListNode with a value
    ListNode(int val) : value(val), next(nullptr) {}
};

class MatrixUsingLinkList
{
private:
    int n, m;                // Number of rows and columns
    vector<ListNode *> rows; // Vector to store pointers to the beginning of each row

public:
    // Default constructor
    MatrixUsingLinkList() : n(0), m(0) {}

    // Constructor to initialize with a vector of vectors
    MatrixUsingLinkList(const vector<vector<int>> &matrix)
    {
        n = matrix.size();
        m = (n > 0) ? matrix[0].size() : 0;
        rows.resize(n);

        for (int i = 0; i < n; ++i)
        {
            ListNode *currentRow(nullptr);
            for (int j = 0; j < m; ++j)
            {
                if (!currentRow)
                {
                    currentRow = new ListNode(matrix[i][j]);
                    rows[i] = currentRow;
                }
                else
                {
                    currentRow->next = new ListNode(matrix[i][j]);
                    currentRow = currentRow->next;
                }
            }
        }
    }

    // Overload the multiplication operator for matrix multiplication
    MatrixUsingLinkList operator*(const MatrixUsingLinkList &other)
    {
        if (m != other.n)
        {
            throw "Matrix dimensions do not match for multiplication.";
        }

        MatrixUsingLinkList result;
        result.n = n;
        result.m = other.m;
        result.rows.resize(result.n);

        ListNode *currentRowA;
        vector<ListNode *> currentColB(m);
        vector<ListNode *> resultRows = result.rows;
        for (int i = 0; i < n; ++i)
        {

            for (int k = 0; k < m; ++k)
                currentColB[k] = other.rows[k];

            for (int j = 0; j < other.m; ++j)
            {
                currentRowA = rows[i];
                int sum = 0;

                for (int k = 0; k < m; ++k)
                {
                    if (currentRowA == nullptr)
                    {
                        cout << "CURRROW null " << endl;
                        throw "ERROR";
                        break;
                    }
                    if (currentColB[k] == nullptr)
                    {
                        cout << "CURRCOLB null " << endl;
                        throw "ERRPR";
                        break;
                    }
                    sum += currentRowA->value * currentColB[k]->value;
                    ++currentColB[k];
                    ++currentRowA;
                }

                if (!resultRows[i])
                {
                    result.rows[i] = resultRows[i] = new ListNode(sum);
                }
                else
                {
                    resultRows[i]->next = new ListNode(sum);
                    resultRows[i] = resultRows[i]->next;
                }
            }
        }

        return result;
    }
};

/////////////////////////////////////////////////////////// Matrix using array //////////////////////////////////////////////////////////////////

class MatrixUsingArray
{
private:
    int n, m;                // Number of rows and columns
    vector<vector<int>> mat; // 2D vector to store matrix elements

public:
    // Default constructor
    MatrixUsingArray() : n(0), m(0) {}

    // Constructor to initialize with a vector of vectors
    MatrixUsingArray(const vector<vector<int>> &matrix)
    {
        n = matrix.size();
        m = (n > 0) ? matrix[0].size() : 0;
        mat = matrix;
    }

    // Overload the multiplication operator for matrix multiplication
    MatrixUsingArray operator*(const MatrixUsingArray &other)
    {
        if (m != other.n)
        {
            throw "Matrix dimensions do not match for multiplication.";
        }

        MatrixUsingArray result;
        result.n = n;
        result.m = other.m;
        result.mat.resize(n, vector<int>(other.m, 0));

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < other.m; ++j)
            {
                for (int k = 0; k < m; ++k)
                {
                    result.mat[i][j] += mat[i][k] * other.mat[k][j];
                }
            }
        }

        return result;
    }

    // Overload the << operator for printing the matrix
    friend ostream &operator<<(ostream &os, const MatrixUsingArray &matrix)
    {
        for (int i = 0; i < matrix.n; ++i)
        {
            for (int j = 0; j < matrix.m; ++j)
            {
                os << matrix.mat[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }

    // Overload the >> operator for inputting the matrix
    friend istream &operator>>(istream &is, MatrixUsingArray &matrix)
    {
        is >> matrix.n >> matrix.m;
        matrix.mat.resize(matrix.n, vector<int>(matrix.m));

        for (int i = 0; i < matrix.n; ++i)
        {
            for (int j = 0; j < matrix.m; ++j)
            {
                is >> matrix.mat[i][j];
            }
        }
        return is;
    }
};

/////////////////////////////////////////////////////// Matrix Multiplication using Queue ////////////////////////////////////////////////////////

class MatrixUsingQueue
{
private:
    int n, m;                // Number of rows and columns
    vector<queue<int>> rows; // Vector of queues to store each row's elements

public:
    // Default constructor
    MatrixUsingQueue() : n(0), m(0) {}

    // Constructor to initialize with a vector of vectors
    MatrixUsingQueue(const vector<vector<int>> &matrix)
    {
        n = matrix.size();
        m = (n > 0) ? matrix[0].size() : 0;
        rows.resize(n);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                rows[i].push(matrix[i][j]);
            }
        }
    }

    MatrixUsingQueue operator*(MatrixUsingQueue &other)
    {
        if (m != other.n)
        {
            throw runtime_error("Matrix dimensions do not match for multiplication.");
        }
        MatrixUsingQueue result;
        result.n = n;
        result.m = other.m;
        result.rows.resize(n);
        // cout << "SIZES= " << n << " " << m << " " << other.n << " " << other.m << endl;

        for (int i = 0; i < n; ++i)
        {
            vector<queue<int>> colB = other.rows;
            for (int j = 0; j < other.m; ++j)
            {
                int sum = 0;
                queue<int> rowA = rows[i];

                for (int k = 0; k < m; ++k)
                {

                    sum += rowA.front() * colB[k].front();
                    // cout << "ADDED" << endl;
                    rowA.pop();
                    colB[k].pop();
                }
                // cout << "DONE " << i << " " << j << " row_size=" << rows[i].size() << endl;
                result.rows[i].push(sum);
            }
        }
        return result;
    }

    // Overload the << operator for printing the matrix
    friend ostream &operator<<(ostream &os, const MatrixUsingQueue &matrix)
    {
        for (int i = 0; i < matrix.n; ++i)
        {
            queue<int> currentRow = matrix.rows[i];
            while (!currentRow.empty())
            {
                os << currentRow.front() << " ";
                currentRow.pop();
            }
            os << endl;
        }
        return os;
    }

    // Overload the >> operator for inputting the matrix
    friend istream &operator>>(istream &is, MatrixUsingQueue &matrix)
    {
        is >> matrix.n >> matrix.m;
        matrix.rows.resize(matrix.n);

        for (int i = 0; i < matrix.n; ++i)
        {
            for (int j = 0; j < matrix.m; ++j)
            {
                int value;
                is >> value;
                matrix.rows[i].push(value);
            }
        }
        return is;
    }
};

//////////////////////////////////////////////////// Matrix Using Stack /////////////////////////////////////////////////////////////////////////

class MatrixUsingStack
{
private:
    int n, m;                // Number of rows and columns
    vector<stack<int>> rows; // Vector of stacks to store each row's elements

    void reverse_stack(stack<int> &s)
    {
        stack<int> temp;

        while (!s.empty())
        {
            temp.push(s.top());
            s.pop();
        }

        s = temp;
    }

public:
    // Default constructor
    MatrixUsingStack() : n(0), m(0) {}

    // Constructor to initialize with a vector of vectors
    MatrixUsingStack(const vector<vector<int>> &matrix)
    {
        n = matrix.size();
        m = (n > 0) ? matrix[0].size() : 0;
        rows.resize(n);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                rows[i].push(matrix[i][j]);
            }
        }
    }

    // Overload the multiplication operator for matrix multiplication
    MatrixUsingStack operator*(const MatrixUsingStack &other)
    {
        if (m != other.n)
        {
            throw "Matrix dimensions do not match for multiplication.";
        }

        MatrixUsingStack result;
        result.n = n;
        result.m = other.m;
        result.rows.resize(n);

        for (int i = 0; i < n; ++i)
        { // Create temporary storage for columns of other matrix
            vector<stack<int>> colsB = other.rows;

            for (int j = 0; j < other.m; ++j)
            {

                int sum = 0;
                stack<int> rowA = rows[i];
                for (int k = 0; k < m; ++k)
                {
                    sum += rowA.top() * colsB[m - 1 - k].top();
                    rowA.pop();
                    colsB[m - 1 - k].pop();
                }
                result.rows[i].push(sum);
            }

            reverse_stack(result.rows[i]);
        }

        return result;
    }

    // Overload the << operator for printing the matrix
    friend ostream &operator<<(ostream &os, const MatrixUsingStack &matrix)
    {
        for (int i = 0; i < matrix.n; ++i)
        {
            stack<int> currentRow = matrix.rows[i];
            vector<int> rowValues;

            while (!currentRow.empty())
            {
                rowValues.push_back(currentRow.top());
                currentRow.pop();
            }

            // Print values in the correct order (reversed)
            for (auto it = rowValues.rbegin(); it != rowValues.rend(); ++it)
            {
                os << *it << " ";
            }
            os << endl;
        }
        return os;
    }

    // Overload the >> operator for inputting the matrix
    friend istream &operator>>(istream &is, MatrixUsingStack &matrix)
    {
        is >> matrix.n >> matrix.m;
        matrix.rows.resize(matrix.n);

        for (int i = 0; i < matrix.n; ++i)
        {
            for (int j = 0; j < matrix.m; ++j)
            {
                int value;
                is >> value;
                matrix.rows[i].push(value);
            }
        }
        return is;
    }
};

// Function to test matrix multiplication across different implementations
vector<long double> test(const vector<vector<int>> &matA, const vector<vector<int>> &matB)
{
    vector<long double> res;

    // MatrixUsingArray
    try
    {
        MatrixUsingArray A_array(matA);
        MatrixUsingArray B_array(matB);

        auto start = chrono::high_resolution_clock::now();
        MatrixUsingArray C_array = A_array * B_array;
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<long double> duration_array = end - start;
        res.push_back(duration_array.count());
    }
    catch (const char *e)
    {
        cout << "MatrixUsingArray Error: " << e << endl;
        res.push_back(-1.0); // Indicate error with -1.0
    }

    // MatrixUsingLinkList

    try
    {
        MatrixUsingLinkList A_linkList(matA);
        MatrixUsingLinkList B_linkList(matB);

        auto start = chrono::high_resolution_clock::now();
        MatrixUsingLinkList C_linkList = A_linkList * B_linkList;
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<long double> duration_linkList = end - start;
        res.push_back(duration_linkList.count());
    }
    catch (const char *e)
    {
        cout << "MatrixUsingLinkList Error: " << e << endl;
        res.push_back(-1.0);
    }

    // MatrixUsingQueue

    try
    {
        MatrixUsingQueue A_queue(matA);
        MatrixUsingQueue B_queue(matB);

        auto start = chrono::high_resolution_clock::now();
        MatrixUsingQueue C_queue = A_queue * B_queue;
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<long double> duration_queue = end - start;
        res.push_back(duration_queue.count());
    }
    catch (const char *e)
    {
        cout << "MatrixUsingQueue Error: " << e << endl;
        res.push_back(-1.0);
    }

    // MatrixUsingStack

    try
    {
        MatrixUsingStack A_stack(matA);
        MatrixUsingStack B_stack(matB);

        auto start = chrono::high_resolution_clock::now();
        MatrixUsingStack C_stack = A_stack * B_stack;
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<long double> duration_stack = end - start;
        res.push_back(duration_stack.count());
    }
    catch (const char *e)
    {
        cout << "MatrixUsingStack Error: " << e << endl;
        res.push_back(-1.0);
    }

    return res;
}

int main()
{
    // Define test parameters
    const int NUMBER_OF_ITERATIONS = 10;
    const int STEP_SIZE = 10;
    const int START = 20;
    const int END = 120;

    // Seed for random number generation
    srand(time(0));

    // Open a file to write the results (optional)
    ofstream outfile("matrix_multiplication_times.csv");
    outfile << "Size,Array,LinkList,Queue,Stack\n";

    // Iterate over different matrix sizes
    for (int size = START; size <= END; size += STEP_SIZE)
    {
        // Generate two random matrices of size 'size x size'
        vector<vector<int>> matA(size, vector<int>(size));
        vector<vector<int>> matB(size, vector<int>(size));

        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                matA[i][j] = rand() % 100; // Random values between 0 and 99
                matB[i][j] = rand() % 100;
            }
        }

        // Variables to accumulate times
        long double total_array = 0.0, total_linkList = 0.0, total_queue = 0.0, total_stack = 0.0;

        // Perform multiple iterations for averaging
        for (int iter = 0; iter < NUMBER_OF_ITERATIONS; ++iter)
        {
            vector<long double> times = test(matA, matB);
            // cout<<"FINAL: "; for(auto&k:times) cout<<k<<" "; cout<<endl;
            if (times[0] != -1.0)
                total_array += times[0];
            if (times[1] != -1.0)
                total_linkList += times[1];
            if (times[2] != -1.0)
                total_queue += times[2];
            if (times[3] != -1.0)
                total_stack += times[3];
        }

        // Calculate average times
        long double avg_array = total_array / NUMBER_OF_ITERATIONS;
        long double avg_linkList = total_linkList / NUMBER_OF_ITERATIONS;
        long double avg_queue = total_queue / NUMBER_OF_ITERATIONS;
        long double avg_stack = total_stack / NUMBER_OF_ITERATIONS;

        // convert in micro seconds
        avg_array *= 1e6;
        avg_linkList *= 1e6;
        avg_queue *= 1e6;
        avg_stack *= 1e6;

        // Output the results
        cout << "Size: " << size << "x" << size << endl;
        cout << "Average Time - Array: " << avg_array << " us, LinkList: " << avg_linkList
             << " us, Queue: " << avg_queue << " us, Stack: " << avg_stack << " us\n"
             << endl;

        // Write to file
        outfile << size << "," << avg_array << "," << avg_linkList << "," << avg_queue << "," << avg_stack << "\n";
    }

    outfile.close();
    return 0;
}
