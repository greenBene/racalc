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
    if(this->size >= this->alloc){

        while(this->size >= this->alloc){
            this->alloc = this->alloc * 2;
        }

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
    if(!this->isPositive || !x.isPositive){
        if(this->isPositive && !x.isPositive){
            Int x_pos = x.clone();
            x_pos.isPositive = true;
            this->sub(x_pos);
            return;
        }
        else if(!this->isPositive && x.isPositive) {
            Int this_pos = this->clone();
            this_pos.isPositive = true;
            Int result = Int::sub(x, this_pos);

            this->alloc = result.alloc;
            this->size = result.size;
            this->isPositive = result.isPositive;
            this->values = result.values;

            return;
        } else {
            Int x_pos = x.clone();
            x_pos.isPositive = true;
            this->isPositive = true;
            this->add(x_pos);
            this->isPositive = false;
        }
    }


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

        if(x_iterator >= x.size && this_iterator >= this->size && carry == 0){
            x_done = true;
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

void Int::sub(Int v){
    Int result = Int::sub(*this, v);
    this->alloc = result.alloc;
    this->size = result.size;
    this->isPositive = result.isPositive;
    this->values = result.values;
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
    else if (x.isPositive){
        for (int i = x.size -1; i>=0; i--){
            if (x.values[i] != y.values[i]) {
                return x.values[i] >= y.values[i];
            }
        }
        return true;
    }
    else {
        for (int i = x.size -1; i>=0; i--){
            if (x.values[i] != y.values[i]) {
                return x.values[i] <= y.values[i];
            }
        }
        return true;
    }
}


Int Int::shift_r(Int x, unsigned int k){
    Int result = Int();

    result.isPositive = x.isPositive;
    result.size = x.size + k;
    result.alloc = result.size + 1;
    result.values = new u_limb_t[result.alloc];

    memcpy(result.values + k, x.values, x.size * sizeof(u_size_t));

    return result;
};


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

Int Int::mul(Int x, u_limb_t m){
    if(m >= BASE || m < 0 ){
        std::cerr << "invalid m \n";
        return Int();
    }

    Int result = Int();
    result.isPositive = x.isPositive;
    
    u_limb_t s_i = 0;
    u_limb_t temp = 0;

    for (int i = 0; i < x.size; i++){
        temp = (x.values[i] * m) + s_i;
        result.add_limb(temp % BASE);
        s_i = temp / BASE;
    }

    if(s_i != 0){
        result.add_limb(s_i);
    }

    result.normalize();

    return result;
}


Int Int::fams(Int x, Int y, unsigned int k, u_limb_t m){
    // x + m * y * r ^k
    if(m >= BASE || m < 0 ){
        std::cerr << "invalid m \n";
        return Int();
    }

    Int x_1 = Int::shift_r(y, k);
    Int x_2 = Int::mul(x_1, m);

    Int max = (Int::gEq(x, x_2)?x:x_2);
    Int min = (Int::gEq(x, x_2)?x_2:x);

    Int x_3 = Int::add(max, min);

    return x_3;
}

Int Int::mul(Int v, Int w){
    Int sum = Int();

    for(int i = 0; i < w.size; i++){
        Int temp = Int::mul(v, w.values[i]);
        temp = Int::shift_r(temp, i);

        Int max = (Int::gEq(temp, sum)?temp:sum);
        Int min = (Int::gEq(temp, sum)?sum:temp);
        sum = Int::add(max, min);
    }

    return sum;
}

Int Int::high(Int x){
    int lenght = (x.size / 2) + (x.size % 2);
    Int result = Int();
    result.size = lenght;
    result.alloc = x.alloc;
    result.values = new u_limb_t[result.alloc];
    
    memcpy(result.values, x.values + (x.size - lenght), lenght * sizeof(u_size_t));
    return result;
}


Int Int::low(Int x){
    int lenght = (x.size / 2);

    Int result = Int();
    result.size = lenght;
    result.alloc = x.alloc;
    result.values = new u_limb_t[result.alloc];
    
    memcpy(result.values, x.values, lenght * sizeof(u_size_t));
    return result;
}