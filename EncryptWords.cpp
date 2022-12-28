#include <stdio.h>
#include <string>
#include <cstdlib>
#include <libakrypt.h>
#include <libakrypt-base.h>

std::string encrypt(const std::string& str, int &pos) {
	// так как массив должен заканчиваться \0 то выделяем на один символ больше(здесь размер in должен быть 3)
	ak_uint8 in[4];
	// копируем 3 входных символа с нужной позиции в наш массив in
	strncpy(reinterpret_cast<char*>(in), str.c_str() + pos, 3);
	// добавляем в конец \0 чтобы функция ak_base64_encodeblock понимала где конец строки
	in[3] = '\0';
	// увеличиваем текущую позицию во входной строке
	pos += 3;

	// заводим выходной массив
	ak_uint8 out[4];
	// кодируем
	ak_base64_encodeblock(in, out, 3);

	// ak_uint8 - unsigned char
	// std::string хранит char
	// приводим типы, чтобы записать наш выходной массив в std::string
	return std::string(reinterpret_cast<char *>(out), 4);
}

std::string encrypt_size_1(const std::string& str, int &pos) {
	// так как массив должен заканчиваться \0 то выделяем на один символ больше(здесь размер in должен быть 1)
	ak_uint8 in[2];

	// копируем 1 входной символ с нужной позиции в наш массив in
	strncpy(reinterpret_cast<char *>(in), str.c_str() + pos, 1);
	// добавляем в конец \0 чтобы функция ak_base64_encodeblock понимала где конец строки
	in[1] = '\0';
	// увеличиваем текущую позицию во входной строке
	pos += 1;

	// заводим выходной массив
	ak_uint8 out[4];
	// кодируем
	ak_base64_encodeblock(in, out, 1);

	// ak_uint8 - unsigned char
	// std::string хранит char
	// приводим типы, чтобы записать наш выходной массив в std::string
	return std::string(reinterpret_cast<char*>(out), 4);
}

std::string encrypt_size_2(const std::string& str, int& pos) {
	// так как массив должен заканчиваться \0 то выделяем на один символ больше(здесь размер in должен быть 2)
	ak_uint8 in[3];

	// копируем 3 входных символа с нужной позиции в наш массив in
	strncpy(reinterpret_cast<char*>(in), str.c_str() + pos, 2);
	// добавляем в конец \0 чтобы функция ak_base64_encodeblock понимала где конец строки
	in[2] = '\0';
	// увеличиваем текущую позицию во входной строке
	pos += 2;

	// заводим выходной массив
	ak_uint8 out[4];
	// кодируем
	ak_base64_encodeblock(in, out, 2);

	// ak_uint8 - unsigned char
	// std::string хранит char
	// приводим типы, чтобы записать наш выходной массив в std::string
	return std::string(reinterpret_cast<char*>(out), 4);
}

std::string encrypt_string(char* str) {
	// сохраняем входную строку в std::string для удобства
	std::string tmp(str);
	// строка с выходным результатом, пока пустая
	std::string ret;
	// текущая позиция в строке
	int pos = 0;

	// делаем цикл пока не дойдем до конца строки
	// после каждого действия добавляем полученный результат в конец выходной строки(std::string ret)
	// pos нужен для хождения по строке, так как размер может быть каким угодно
	while(tmp.size() - pos) {
		// смотрим размер
		switch (tmp.size() - pos) {
		// если размер входной строки 0(такого не может быть, но нужно написать для удобства), то выходим
		case 0:
			break;
		// если размер 1, то вызываем функцию кодирования для строки размером 1
		case 1:
			ret.append(encrypt_size_1(tmp, pos));
			break;
		// если размер 2, то вызываем функцию кодирования для строки размером 2
		case 2:
			ret.append(encrypt_size_2(tmp, pos));
			break;
		// для всех остальных размеров
		default:
			ret.append(encrypt(tmp, pos));
			break;
		}
	}

	return ret;
}

// для английских букв работает
// для русских и тд не особо понятно как оно должно работать, если надо - сделаем
int main(int argc, char *argv[]) {
	// если нам не дали входных аргументов то просто выходим и печатаем no input data
	if (argc < 1) {
		printf("No input data");
		return 0;
	}

	// делаем цикл по всем переданным аргументам
	for (int i = 1; i < argc; ++i) {
		printf("Text: %s\n", argv[i]);
		const auto& str = encrypt_string(argv[i]);
		printf("\tBase64: %s\n\n", str.c_str());
	}
}
