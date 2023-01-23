#include <iostream>
#include <string>
#include <libakrypt.h>
#include <libakrypt-base.h>

int main() {
    /*Структура для хранения контекста ключа*/
    bckey key;

    /*Значение контекстного ключа вырабатывается из данного пароля*/
    char password[] = "password";
    /*Случайный вектор в виде строки символов*/
    char s[] = "sugar";

    /*Инициализация секретного ключа алгоритма блочного шифрования Кузнечик*/
    if (ak_error_ok != ak_bckey_create_kuznechik(&key))
	return ak_error_get_value();	

    /*Структура для хранения случайного (псевдослучайного) значения*/
    struct random rand;
    /*Создание случайного (псевдослучайного) значения NLFSR генератором*/
    ak_random_create_nlfsr(&rand);

    /*Присваивание контексту ключа алгоритма блочного шифрования случайное (псевдослучайное)
    значение, вырабатываемое заданным генератором случайных (псевдослучайных) чисел.*/
    if(ak_error_ok != ak_bckey_set_key_random(&key, &rand))
	return ak_error_get_value();
	
    constexpr size_t size = 128;
    /*Текст для зашифрования*/
    char data[size] = "test data for encrypt";
    /*Область памяти, куда помещается зашифрованная строка*/
    char out[size];
    /*Синхрпосылка*/
    ak_uint8 openssl_ivcbc[32] = {
        	0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xce, 0xf0, 0xa1, 0xb2, 0xc3, 0xd4, 0xe5, 0xf0, 0x01, 0x12,
		0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x90, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19
	};


    if(ak_error_ok != ak_bckey_encrypt_cbc(&key, data, out, size, openssl_ivcbc, sizeof(openssl_ivcbc)))
	return ak_error_get_value();

    /*Область памяти, куда помещается расшифрованная строка*/
    char decrypt[size];
    if (ak_error_ok != ak_bckey_decrypt_cbc(&key, out, decrypt, size, openssl_ivcbc, sizeof(openssl_ivcbc)))
	return ak_error_get_value();
	
    if (std::equal(data, data + size, decrypt))
	return 0;

}
