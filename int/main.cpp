#include"integer.h"
int main()
{
    integer a("2"),b("3");
    bool k1,k2,k3;
    k1 = (a >= b);
    k2 = (a == b);
    k3 = (a < b);
    std::cout<<k1<<" "<<k2<<" "<<k3<<std::endl;
    return 0;
}