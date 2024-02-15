#include <iostream>

int CountDivisors(int n) {
    int divisors = 0;
    for(int i=1; i<=n; ++i){
        if (n%i == 0){
            divisors++;
        }
    }
    return divisors;
}

int main(){
    int n, divisors, count = 0, max;
    std::cout << "Enter a number: ";
    std::cin >> n;

    for (int i=1; i<=n; ++i){
        divisors = CountDivisors(i);
        if (divisors >= count){
            count = divisors;
            max = i;
        }
    }

    std::cout << "The number with most divisors is " << max << " (it has " << count << ")" << std::endl;
    return 0;
}
