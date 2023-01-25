#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm> // std::sort
using namespace std;
using namespace std::chrono;
std::atomic<long long int> c = 0;   // works like a lock for counter
std::atomic<long long int> sum = 0; // works like a lock and unwrap but for sum
vector<int> list2;

void isPrime(int n, int mult, int flag)
{
    int max = 12500000;
    long long int c2 = 0;
    long long int sum2 = 0;
    vector<int> list;
    int notp = 0;
    for (int i = n; i < max * mult; i++)
    {
        notp = 0;
        if (i == 2 || i == 3)
        {

            c2 += 1;
            sum2 = i + sum2;
            if (flag == 1)
                list.push_back(i);
            continue;
        }

        if (i <= 1 || i % 2 == 0 || i % 3 == 0)
        {
            continue;
        }

        for (int j = 5; j * j <= i; j += 6)
        {
            if (i % j == 0 || i % (j + 2) == 0)
            {
                notp = 1;
                break;
            }
        }
        if (notp == 1)
        {
            continue;
        }
        c2 += 1;
        sum2 = i + sum2;
        if (flag == 1)
            list.push_back(i);
    }
    c += c2;
    sum += sum2;
    if (flag == 1)
    {
        for (int o = 0; o < list.size(); o++)
        {
            list2.push_back(list[o]);
        }
        // Sort the vector in descending order
        std::sort(list2.begin(), list2.end(), greater<int>());
    }
}

int main()
{
    auto start = high_resolution_clock::now();
    std::thread t1(isPrime, 0, 1, 0);
    std::thread t2(isPrime, 12500000, 2, 0);
    std::thread t3(isPrime, 25000000, 3, 0);
    std::thread t4(isPrime, 37500000, 4, 0);
    std::thread t5(isPrime, 50000000, 5, 0);
    std::thread t6(isPrime, 62500000, 6, 0);
    std::thread t7(isPrime, 75000000, 7, 0);
    std::thread t8(isPrime, 87500000, 8, 1);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    auto stop = high_resolution_clock::now();
    std::chrono::duration<double> duration = stop - start;
    cout << "Time taken by function: "
         << duration.count() << " seconds" << endl;
    cout << c << " ";
    cout << sum << " ";
    cout << "[";
    for (int i = 9; i >= 0; i--)
        cout << list2[i] << ",";
    cout << "]";

    ofstream fw("primes.txt", std::ofstream::out);
    if (fw.is_open())
    {
        fw << "Time taken by function: "
         << duration.count() << " seconds" << endl;

        fw << c << "\n";
        fw << sum << "\n";
        fw << "[";
        for (int i = 9; i >= 0; i--)
            fw << list2[i] << ",";
        fw << "]";
        fw.close();
    }
    else
        cout << "Problem with opening file";
    return 0;
}
