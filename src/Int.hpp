#include <list>

typedef unsigned long long int u_limb_t;
typedef unsigned long long int u_size_t;
// const u_limb_t BASE = 9223372036854775808U; // 2^63
const u_limb_t BASE = 10; // 2^63
const u_size_t STD_SIZE = 4;

class Int {
  private:
    bool isPositive;
    u_limb_t* values;
    u_size_t size;
    u_size_t alloc;
    void resize_values();
    void add_limb(u_limb_t limb);
    void normalize();

  public:
    Int();
    Int(int value);

    void print();
    void add(Int x);
    void sub(Int x);
    Int clone();


    static Int add(Int x, Int y);
    static Int sub(Int v, Int w);
    static bool gEq(Int x, Int y);
    static Int shift_r(Int x, unsigned int k);
    static Int shift(Int x, unsigned n);
};