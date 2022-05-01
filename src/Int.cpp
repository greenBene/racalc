#include <iostream>
#include "Int.hpp"
#include <string>

Int::Int(){
    this->values = new u_limb_t[STD_SIZE];
    this->alloc = STD_SIZE;
    this->size = 0;
    this->isPositive = true;
}

Int::Int(int value): Int(){
    u_limb_t limb;

    this->isPositive = (value > 0);

    if(value < 0) {
        value *= -1;
    }

    do{
        limb = value % BASE;
        value /=  BASE;
        this->add_limb(limb);
    }while(value > 0);
}

void Int::resize_values(){
    if(this->size == this->alloc){
        this->alloc = this->alloc * 2;
        u_limb_t* new_values_array = new u_limb_t[this->alloc];

        memcpy(new_values_array, this->values, this->size * sizeof(u_size_t));
        delete this->values;
        this->values = new_values_array;
    }
}

void Int::add_limb(u_limb_t limb){
    this->values[this->size] = limb;
    this->size++;
    this->resize_values();
}

void Int::normalize(){
    while(this->size > 0 && this->values[this->size-1] == 0){
        this->size--;
    }
}

void Int::add(Int x) {
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

Int Int::sub(Int v, Int w) {
    if (!v.isPositive || !w.isPositive) {
        if (!v.isPositive && w.isPositive){
            Int v_pos = v.clone();
            v_pos.isPositive = true;
            Int result = Int::add(v_pos, w);
            result.isPositive = false;
            return result;
        } else if (v.isPositive && !w.isPositive){
            Int w_pos = w.clone();
            w_pos.isPositive = true;
            return Int::add(v, w_pos);
        } else {
            Int v_pos = v.clone(), w_pos = w.clone();
            v_pos.isPositive = true;
            w_pos.isPositive = true;
            Int result = Int::sub(v_pos, w_pos);
            result.isPositive = !result.isPositive;
            return result;
        }
    }

    if (!Int::gEq(v, w)){
        Int result =  Int::sub(w, v);
        result.isPositive = false;
        return result;
    }

    int v_i = 0, w_i = 0, s_i = 0, u_i = 0, temp = 0;
    Int u = Int();

    for(int i = 0; i< v.size; i++){
        v_i = v.values[i];
        w_i = (w.size > i? w.values[i]: 0);

        temp = (v_i - w_i + s_i);
        s_i = (temp >= 0 ? 0 : -1);
        u_i = (temp - s_i * BASE) % BASE;

        u.add_limb(u_i);
    }
    u.normalize();
    return u;
}

Int Int::add(Int a, Int b) {
    Int result = a.clone();

    result.add(b);
    
    return result;
}


bool Int::gEq(Int x, Int y) {
    if (x.isPositive != y.isPositive)
        return x.isPositive;
    else if (x.size != y.size && x.isPositive)
        return x.size > y.size;
    else if (x.size != y.size && !x.isPositive)
        return x.size < y.size;
    else if (x.isPositive)
        return x.values[x.size-1] >= y.values[y.size-1];
    else 
        return x.values[x.size-1] <= y.values[y.size-1];
}

Int Int::shift(Int x, unsigned int n) {
    Int ret = x.clone();

    for (int i = 0; i < n; i++){
        ret.add(ret);
    }
    
    return ret;
}

Int Int::clone() {
    Int n = Int();
    n.alloc = this->alloc;
    n.size = this->size;
    memcpy(n.values, this->values, this->size * sizeof(u_size_t));

    return n;
}

void Int::print() {
    std::string s = "";

    for(u_size_t i = 0; i < this->size; i++){
        s = " " + std::to_string(this->values[i]) + s;
    }

    if (this->size == 0)
        s = " 0";

    std::cout << '(' << (this->isPositive? "+": "-") << s << ") base_" << BASE << '\n';
}