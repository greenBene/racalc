#include <iostream>

#include "Nat.hpp"

int main(int argc, char *argv[]){

    // Nat::add(Nat::shift(Nat(1234567890), 100), Nat(1)).print();
    
    if (argc == 3) {
        try{
            int x1 = std::stoi(argv[1]);
            int x2 = std::stoi(argv[2]);

            if (x1 < 0 || x2 < 0 ) {
                exit(1);
            }

            std::cout << "N1:\n";
            Nat n1 = Nat(x1);
            n1.print();

            std::cout << "\nN2:\n";
            Nat n2 = Nat(x2);
            n2.print();

            std::cout << "\nN1 * 2 ^ N2:\n";
            Nat::shift(n1, x2).print();
        } catch (std::exception const &e) {
            std::cerr << "./racalc [NUMBER>=0] [NUMBER>=0]\n";
        }
    } 
}