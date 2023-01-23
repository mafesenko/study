#include <iostream>
#include <string>
#include <libakrypt.h>
#include <libakrypt-base.h>

int main() {
    char str[] = "394B50";
    char a[64];

    ak_hexstr_to_ptr(str, a, sizeof(a), ak_true);

    for (int i = 0; i < sizeof(a); ++i)
        std::cout << a[i] << " ";
}