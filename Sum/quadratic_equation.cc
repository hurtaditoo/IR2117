#include <iostream>
#include <cmath>

int main() {

    int a, b, c;

    std::cout << "Solving a quadratic ecuation" << std::endl;
    
    std::cout << "Coefficient A: ";
    std::cin >> a;
    
    std::cout << "Coefficient B: ";
    std::cin >> b;
     
    std::cout << "Coefficient C: ";
    std::cin >> c;

    int discriminante = (b * b) - (4 * a * c);

    if(discriminante>=0) {

        double sol1 = (-b + std::sqrt(discriminante)) / (2 * a);
        double sol2 = (-b - std::sqrt(discriminante)) / (2 * a);

        std::cout << "Two solutions: " << sol1 << " and " << sol2 << std::endl;

    }

    return 0;
}