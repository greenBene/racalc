#include <list>
typedef unsigned long long int u_limb_t;
const u_limb_t BASE = 1024;

class Nat {
  private:
    Nat(std::list<u_limb_t> values);
    std::list<u_limb_t> values;

  public:
    Nat(unsigned int value);

    void print();

    static Nat add(Nat x,Nat y);
    static Nat shift(Nat x, unsigned n);
};