#include <iostream>
#include <cmath>
#include <complex>

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
        std::complex<double> complex = std::sqrt(-discriminante);
        std::complex<double> complex1 = (-b + complex) / (2 * a);
        std::complex<double> complex2 = (-b - complex) / (2 * a);

        std::cout << "Complex solutions: " << complex1 << " and " << complex2 << std::endl;
    } 

    return 0;
}