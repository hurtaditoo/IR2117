#include <iostream>

int suma(int n) {
	
	int sum = 0;
	sum = (n*(n+1)) / 2;
	return sum;
}

int main() {
  
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;
    
    if (number <= 1) {
        std::cerr << "The number should be greater than 1" << std::endl;
        return 1;
    }
    
    std::cout << "The sum from 1 to " << number << " is: " << suma(number) << std::endl;

    return 0; 
}

