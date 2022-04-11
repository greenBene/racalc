#include <iostream>
#include "Nat.hpp"
#include <string>


Nat::Nat(){
    this->values = new u_limb_t[STD_SIZE];
    this->alloc = STD_SIZE;
    this->size = 0;
}

Nat::Nat(unsigned int value): Nat(){
    u_limb_t limb;
    do{
        limb = value % BASE;
        value /=  BASE;
        this->add_limb(limb);
    }while(value > 0);
}

void Nat::resize_values(){
    if(this->size == this->alloc){
        this->alloc = this->alloc * 2;
        u_limb_t* new_values_array = new u_limb_t[this->alloc];

        memcpy(new_values_array, this->values, this->size * sizeof(u_size_t));
        delete this->values;
        this->values = new_values_array;
    }
}

void Nat::add_limb(u_limb_t limb){
    this->values[this->size] = limb;
    this->size++;
    this->resize_values();
}

Nat Nat::add(Nat a, Nat b) {
    u_limb_t* values = new u_limb_t[STD_SIZE];
    Nat new_nat = Nat();

    u_limb_t a_val, b_val, result, carry = 0;
    u_size_t a_iterator = 0, b_iterator = 0; 
    bool a_done = false, b_done = false;

    while(a_done != true || b_done != true || carry > 0){

        if(a_iterator < a.size){
            a_val = a.values[a_iterator++];
        } else {
            a_val = 0;
            a_done = true;
        }

        if(b_iterator < b.size){
            b_val = b.values[b_iterator++];
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
            new_nat.add_limb(result);
        }
    };
    
    return new_nat;
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

    for(u_size_t i = 0; i < this->size; i++){
        s = std::to_string(this->values[i]) + " " + s;
    }

    std::cout << '('<< s << ") base_" << BASE << '\n';
}