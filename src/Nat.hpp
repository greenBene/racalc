#include <list>

typedef unsigned long long int u_limb_t;
typedef unsigned long long int u_size_t;
const u_limb_t BASE = 9223372036854775808U; // 2^63
const u_size_t STD_SIZE = 4;

class Nat {
  private:
    u_limb_t* values;
    u_size_t size;
    u_size_t alloc;
    void resize_values();
    void add_limb(u_limb_t limb);

  public:
    Nat();
    Nat(unsigned int value);

    void print();
    void add(Nat x);
    Nat clone();

    static Nat add(Nat x, Nat y);
    static Nat shift(Nat x, unsigned n);
};