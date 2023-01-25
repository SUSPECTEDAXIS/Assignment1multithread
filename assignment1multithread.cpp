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
    int max = 12500000;// this is so each thread does up to 12500000 on for loop
    long long int c2 = 0;//local counter
    long long int sum2 = 0;//local sum
    vector<int> list; //local vector
    int notp = 0; //flag indicating not prime
    for (int i = n; i < max * mult; i++)  //for loop for threads
    {
        notp = 0;  //flag reset
        if (i == 2 || i == 3)   //if it is 2 or 3 it is prime
        {

            c2 += 1;   //counter increment
            sum2 = i + sum2;  //calculating sum based on currrent sumber plus those before that were already stored
            if (flag == 1)  //this runs on last thread used for top ten primes
                list.push_back(i);   //adding to vector
            continue;
        }

        if (i <= 1 || i % 2 == 0 || i % 3 == 0)  // if number is even or divisible by 3 or 0 or 1 it is not a prime go to next number
        {
            continue;
        }
        //In this for loop we will check whether the number is divisible by any of the factors in the range given.
        for (int j = 5; j * j <= i; j += 6)
        {
            if (i % j == 0 || i % (j + 2) == 0)
            {
                notp = 1;
                break;
            }
        }
        if (notp == 1)  //if flag is marked go to next number
        {
            continue;
        }
        c2 += 1;
        sum2 = i + sum2;
        if (flag == 1)
            list.push_back(i);
    }
    c += c2;  //atomic variables will now be equal to what they were before/initialized plus the end resullt of local variables of counter and sum
    sum += sum2;
    if (flag == 1)  //on last thread makes sure we add the values to the global vector
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
    //start runtime right before threads are made
    auto start = high_resolution_clock::now();
    //below code runs thread parallel and sets each one to specific numbers so it wont overlap
    std::thread t1(isPrime, 0, 1, 0);
    std::thread t2(isPrime, 12500000, 2, 0);
    std::thread t3(isPrime, 25000000, 3, 0);
    std::thread t4(isPrime, 37500000, 4, 0);
    std::thread t5(isPrime, 50000000, 5, 0);
    std::thread t6(isPrime, 62500000, 6, 0);
    std::thread t7(isPrime, 75000000, 7, 0);
    std::thread t8(isPrime, 87500000, 8, 1);
    //join the threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    //stops timer after all threads joined
    auto stop = high_resolution_clock::now();
    //calculate the duration based on start and stop
    std::chrono::duration<double> duration = stop - start;
    //below is code to print to console which was used for debugging
    /*cout << "Time taken by function: "
         << duration.count() << " seconds" << endl;
    cout << c << " ";
    cout << sum << " ";
    cout << "[";
    for (int i = 9; i >= 0; i--)
        cout << list2[i] << ",";
    cout << "]";*/

    //writes required output to primes.txt and the format needed
    ofstream fw("primes.txt", std::ofstream::out);
    if (fw.is_open())
    {
        fw << "<execution time> "
         << duration.count() << " seconds" << endl;

        fw <<"<total number of primes found> " << c << "\n";
        fw << "<sum of all primes found> " << sum << "\n";
        fw << "<top ten maximum primes, listed in order from lowest to highest> ";
        fw << "[ ";
        for (int i = 9; i >= 0; i--)
            fw << list2[i] << "  ";
        fw << "]";
        fw.close();
    }
    else
        cout << "Problem with opening file";
    return 0;
}
