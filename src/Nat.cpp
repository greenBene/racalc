#include <iostream>
#include "Nat.hpp"
#include <string>


Nat::Nat(unsigned int value){
    u_limb_t limb;
    do{
        limb = value % BASE;
        value /=  BASE;
        this->values.push_front(limb);
    }while(value > 0);
}

Nat::Nat(std::list<u_limb_t> values){
    this->values = values;
}

Nat Nat::add(Nat a, Nat b) {
    std::list<u_limb_t> values;

    std::list<u_limb_t>::reverse_iterator it_values_a = a.values.rbegin();
    std::list<u_limb_t>::reverse_iterator it_values_b = b.values.rbegin();

    u_limb_t a_val, b_val, result, carry = 0;

    bool a_done = false, b_done = false;

    while(a_done != true || b_done != true || carry > 0){

        if(it_values_a!=a.values.rend()){
            a_val = *it_values_a++;
        } else {
            a_val = 0;
            a_done = true;
        }

        if(it_values_b!=b.values.rend()){
            b_val = *it_values_b++;
        } else {
            b_val = 0;
            b_done = true;
        }

        result = a_val + b_val + carry;

        if(result >= BASE){
            result %= BASE;
            carry = 1;
        } else {
            carry = 0;
        }

        if(result > 0 || !a_done || !b_done || carry > 0){
            values.push_front(result);
        }
        
    };
    
    return Nat(values);
}

Nat Nat::shift(Nat x, unsigned int n) {
    Nat ret = x;

    for (int i = 0; i < n; i++){
        ret = Nat::add(ret, ret);
    }
    return ret;
}

void Nat::print() {
    std::string s = "";

    for(u_limb_t limb: this->values){
        s += std::to_string(limb) + " ";
    }

    std::cout << '('<< s << ") base_" << BASE << '\n';
}