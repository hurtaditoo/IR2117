#include <iostream>

int main(){
    int a, b;
    
    do {
        std::cout << "Enter a number >=1: ";
        std::cin >> a;
    } while (a < 1);
    
    do {
        std::cout << "Enter b number >=1: ";
        std::cin >> b;
    } while (b < 1);
    
    do {
        std::cout << "Enter b number >=1: ";
        std::cin >> b;
    } while (a > b);
    
    int sum = 0;
    for(int i = a; i <= b; i++) {
        sum += i;
    }
    
    std::cout << "The sum from " << a << " to " << b << " is " << sum << std::endl;

    return 0;
}


