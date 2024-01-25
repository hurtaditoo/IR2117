#include <iostream>

int main() {
  
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;

    int sum = 0;
    for (int i = 1; i <= number; ++i) {
        sum += i;
    }
    
    std::cout << "The sum from 1 to " << number << " is: " << sum << std::endl;

    return 0; 
}

