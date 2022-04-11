#include <iostream>

#include "Nat.hpp"

int main(int argc, char *argv[]){

    Nat::add(Nat::shift(Nat(1234567890), 100), Nat(1)).print();
    
    // if (argc == 3) {
    //     try{
    //         int x1 = std::stoi(argv[1]);
    //         int x2 = std::stoi(argv[2]);

    //         Nat n1 = Nat(x1);
    //         // n1.print();

    //         // Nat n2 = Nat(x2);
    //         // // n2.print();

    //         // Nat::add(n1, n2).print();

    //         Nat::shift(n1, x2).print();
    //     } catch (std::exception const &e) {
    //         std::cerr << "./racalc [NUMBER]\n";
    //     }
    // } 
}