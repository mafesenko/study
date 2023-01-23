#include <stdio.h>
#include <string>
#include <libakrypt.h>
#include <libakrypt-base.h>

int main() {
    struct signkey sk;
    struct random generator;
 
    ak_uint8 sign[128];
    ak_uint8 testkey[32] = {
        0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x27, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x28 
    };
    
    ak_log_set_level(ak_log_maximum);

    // создаем генератор псевдослучайных последовательностей
    if (ak_random_create_lcg(&generator) != ak_error_ok)
        return ak_error_get_value();

    // инициализируем секретный ключ с заданной эллиптической кривой
    if (ak_signkey_create_str(&sk, "cspa") != ak_error_ok)
        return ak_error_get_value();    

    // устанавливаем значение ключа
    if(ak_signkey_set_key(&sk, testkey, sizeof(testkey)) != ak_error_ok)
        return ak_error_get_value();

    // подстраиваем ключ и устанавливаем ресурс
    ak_skey_set_resource_values(&sk.key, key_using_resource,
        "digital_signature_count_resource", 0, time(NULL) + 2592000);

    char data[] = "data for signed";
    ak_pointer out[128];
    // только теперь подписываем данные в качестве которых выступает исполняемый файл
    ak_signkey_sign_ptr(&sk, &generator, data, sizeof(data), out, sizeof(out));

    ak_signkey_destroy(&sk);

    return EXIT_SUCCESS;
}