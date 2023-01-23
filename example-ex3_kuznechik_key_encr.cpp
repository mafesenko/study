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

    /*Присваивание значения, выработанного из заданного пароля, контексту ключа*/
    if(ak_error_ok != ak_bckey_set_key_from_password(&key, password, 8, s, 5))
	return ak_error_get_value();
	
    constexpr size_t size = 128;
    /*Текст для зашифрования*/
    char data[size] = "test data for encrypt";
    /*Область памяти, куда помещается зашифрованная строка*/
    char out[size];

    /*Зашифрование в режиме простой замены*/
    if(ak_error_ok != ak_bckey_encrypt_ecb(&key, data, out, size)) 
	return ak_error_get_value();

    std::cout << "Data: " << data << std::endl;
    std::cout << "Encrypted data: " << out << std::endl;
}
