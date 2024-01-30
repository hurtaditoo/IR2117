#include <iostream>
#include <cmath>
#include <complex>

int main() {

    double a, b, c;

    std::cout << "Solving a quadratic equation" << std::endl;
    
    std::cout << "Coefficient A: ";
    std::cin >> a;
    
    std::cout << "Coefficient B: ";
    std::cin >> b;
     
    std::cout << "Coefficient C: ";
    std::cin >> c;

    double discriminant = (b * b) - (4 * a * c);

    if (discriminant > 0) {
        double sol1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double sol2 = (-b - std::sqrt(discriminant)) / (2 * a);

        std::cout << "Two solutions: " << sol1 << " and " << sol2 << std::endl;
    } 
    else if (discriminant == 0) {
        double sol = -b / (2 * a);
        std::cout << "One real solution: " << sol << std::endl;
    }
    else {
		std::complex<double> complex_discriminant = (b * b) - (4 * a * c);
        std::complex<double> complex = std::sqrt(complex_discriminant);
        std::complex<double> sol_complex1 = (-b + complex) / (2 * a);
        std::complex<double> sol_complex2 = (-b - complex) / (2 * a);

        std::cout << "Complex solutions-> " << std::imag(sol_complex1) << "i+" << std::real(sol_complex1) << " and " <<std::imag(sol_complex2) << "i" << std::real(sol_complex2) << std::endl;
    } 

    return 0;
}
