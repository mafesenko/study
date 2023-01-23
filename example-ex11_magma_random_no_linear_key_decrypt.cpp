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

    /*Инициализация секретного ключа алгоритма блочного шифрования Магма*/
    if (ak_error_ok != ak_bckey_create_magma(&key))
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

    /*Зашифрование в режиме простой замены*/
    if(ak_error_ok != ak_bckey_encrypt_ecb(&key, data, out, size)) 
	return ak_error_get_value();

    /*Область памяти, куда помещается расшифрованная строка*/
    char decrypt[size];
    /*Расшифрование в режиме простой замены*/
    if (ak_error_ok != ak_bckey_decrypt_ecb(&key, out, decrypt, size))
	return ak_error_get_value();

    if (std::equal(data, data + size, decrypt))
	return 0;
}
