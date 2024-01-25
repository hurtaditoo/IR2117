#include <iostream>
#include <cmath>

int main() {

    double a, b, c;

    std::cout << "Solving a quadratic ecuation" << std::endl;
    
    std::cout << "Coefficient A: ";
    std::cin >> a;
    
    std::cout << "Coefficient B: ";
    std::cin >> b;
     
    std::cout << "Coefficient C: ";
    std::cin >> c;

    double discriminante = (b * b) - (4 * a * c);

    if (discriminante > 0) {
        double sol1 = (-b + std::sqrt(discriminante)) / (2 * a);
        double sol2 = (-b - std::sqrt(discriminante)) / (2 * a);

        std::cout << "Two solutions: " << sol1 << " and " << sol2 << std::endl;
    } 
    else if (discriminante == 0) {
        double sol = -b / (2 * a);
        std::cout << "One real solution: " << sol << std::endl;
    }
    else {
        std::cout << "Complex solutions: " << (-b/(2*a)) << " + " << (sqrt(discriminante)/(2*a)) << "i and " << (-b/(2*a)) << " - << (sqrt(discriminante)/(2*a)) << "i" << std::endl;
    } 

    return 0;
}