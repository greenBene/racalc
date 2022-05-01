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

void Nat::add(Nat x) {
    u_limb_t this_val, x_val, result, carry = 0;
    u_size_t this_iterator = 0, x_iterator = 0; 

    bool this_done = false, x_done = false;

    while(x_done != true || carry > 0){

        if(this_iterator < this->size){
            this_val = this->values[this_iterator];
        } else {
            this_val = 0;
        }

        if(x_iterator < x.size){
            x_val = x.values[x_iterator++];
        } else {
            x_val = 0;
            x_done = true;
        }

        result = this_val + x_val + carry;

        if(result >= BASE){
            result %= BASE;
            carry = 1;
        } else {
            carry = 0;
        }

        if(result > 0 || !x_done || carry > 0){
            if(this_iterator < this->size){
                this->values[this_iterator] = result;
                this_iterator++;
            }
            else {
                this->add_limb(result);
            }
        }
    };
}

Nat Nat::add(Nat a, Nat b) {
    Nat result = a.clone();

    result.add(b);
    
    return result;
}

Nat Nat::shift(Nat x, unsigned int n) {
    Nat ret = x.clone();

    for (int i = 0; i < n; i++){
        ret.add(ret);
    }
    
    return ret;
}

Nat Nat::clone() {
    Nat n = Nat();
    n.alloc = this->alloc;
    n.size = this->size;
    memcpy(n.values, this->values, this->size * sizeof(u_size_t));

    return n;
}

void Nat::print() {
    std::string s = "";

    for(u_size_t i = 0; i < this->size; i++){
        s = std::to_string(this->values[i]) + " " + s;
    }

    std::cout << '('<< s << ") base_" << BASE << '\n';
}