# Assignment1multithread
Carlos Sanchez Ruiz COP4520 Assignment 1
Main=Assignment1Multithread

# Problem and Requirements

Problem 1 (100 points) 
Your non-technical manager assigns you the task to find all primes between 1 and 
108.  The assumption is that your company is going to use a parallel machine that 
supports eight concurrent threads. Thus, in your design you should plan to spawn 8 
threads that will perform the necessary computation. Your boss does not have a strong 
technical background but she is a reasonable person. Therefore, she expects to see that 
the work is distributed such that the computational execution time is approximately 
equivalent among the threads. Finally, you need to provide a brief summary of your 
approach and an informal statement reasoning about the correctness and efficiency of 
your design. Provide a summary of the experimental evaluation of your approach. 
Remember, that your company cannot afford a supercomputer and rents a machine by 
the minute, so the longer your program takes, the more it costs. Feel free to use any 
programming language of your choice that supports multi-threading as long as you 
provide a ReadMe file with instructions for your manager explaining how to compile and 
run your program from the command prompt.   
  
Required Output: 
Please print the following output to a file named primes.txt: 
<execution time>  <total number of primes found>  <sum of all primes found> 
<top ten maximum primes, listed in order from lowest to highest> 
  
Notes on Output: 
1. Zero and one are neither prime nor composite, so please don't include them in 
the total number of primes found and the sum of all primes found. 
2. The execution time should start prior to spawning the threads and end after all 
threads complete.



# Approach and methods used/experimental evaluation of approach.
First I wanted to make sure I could make a function that would determine which numbers where prime numbers up to 10^8.
For my algorithm i decided to go with the Primality Test algorithm. This method checks whether the input number given is evenly divisible by any prime number between 2 and sqrt(N), meaning remainder is 0. If this is the case it means n is composite and if it isnt then it is a prime number.Now that I had my function for primes I needed to have in this function a variable that could be locked and unwrap so it could be used for the threads later on. Used atomic variable as long long int for botrh counter (c) and the sum (sum). On the if statements in all of the places where it was proved the numbers where prime i had local variables inside the prime function that would increment the counter and another that kept track of the sum. First i had used atomic variables but it would be innaccurate so instead first in for loop had them kept track with locals and after calculations were done had the atomic variables increment by themselves and their respective local variables. As for my last requirement of having the top then store i used a local vector  that would only run in last thread for efficiency depending on a flag. After the local list is done we will push the values from the local to the global vector. Now that the function was done i needed to make the 8 threads and run them parallel. So i made 8 threads and had each one run from 1/8 increment of the number 10^8 so that the work would be somewhat distributed even though the later threads do slightly more work than the ones before. After this I join all 8 threads and proceeded to print out requirements and added the execution runtime too start at when threads are made to when last one is joined using std chrono.
 It ended up taking 5 seconds so i decided to keepp it like this but if it had to be improved it would have to maybe use a  sieves method.(I used primality test method sqrt)

# Proving that the primality test found all of the prime numbers and its efficiency explained
  Using 100 as example
  It is divisible by 2,4,5,10,20,25 and 50 which are its factors
  now when we test all divisors up to n/2 we notice they repeat twice for example
  2*50,4*25,5*20,10*10,20*5,25*4,50*2
  the numbers that repeat are 10*10 and 5*20 and 20*5
  This happens with all numbers and shows that divisors of any number are less than or equal to sqrt(n) and this is why we   only use numbers up to that on the prime function.
  
  Now on the function itself when we check whether a number is prime first we see if its 2 or 3 which would make it prime we increment counter and make sum = itself and the number we just checked.After this we check whether it is 0 or1 and if its even or can be divided by 3 if so it wouldnt be a prime number so below this statement we have it continue to next number.Then we have a for loo[ that skips 4 because if its even it was covered by last statement which checked if it had remainder after divided by 2.In this for loop we will check whether the number is divisible by any of the factors in the range given. We check if the number is divisible by 5 then by 7 and if so breakand then continue by a flag and if not the it keeps for looping with incrementing by 6 which will keep ittesting odd numbers until sqrt(N).
  
  Since we are using a function that checks for all primes up to the sqrt(n). Since this function checks whether a number is prime or not and does it at a polynomial runtime O(n^k) this would make it faster than the other methods depending on the input size and as we are working with 10^8 which has huge inputs it works better than O(n), O(1) and O(log n)
  
# Installation and running from command prompt
1. Open a terminal
2. Navigate to the location of assignment1multithread.cpp
3. Compile the program with the following command: 
g++ assignment1multithread.cpp
4. Run program with: 
  .\a.exe

  
