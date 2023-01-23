#include <iostream>
#include <string>
#include <libakrypt.h>
#include <libakrypt-base.h>

int main() {
    struct file aaa;
    ak_uint8 sign[128];
    char fileout[128] = "ls.txt";
    ak_file_open_to_read(&aaa, fileout);
    ak_file_read(&aaa, sign, 128);
}
