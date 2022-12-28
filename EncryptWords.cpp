#include <stdio.h>
#include <string>
#include <cstdlib>
#include "D:\test\libakrypt-0.x\build\libakrypt.h"
#include "D:\test\libakrypt-0.x\build\libakrypt-base.h"

std::string encrypt(const std::string& str, int &pos) {
	// ��� ��� ������ ������ ������������� \0 �� �������� �� ���� ������ ������(����� ������ in ������ ���� 3)
	ak_uint8 in[4];
	// �������� 3 ������� ������� � ������ ������� � ��� ������ in
	strncpy(reinterpret_cast<char*>(in), str.c_str() + pos, 3);
	// ��������� � ����� \0 ����� ������� ak_base64_encodeblock �������� ��� ����� ������
	in[3] = '\0';
	// ����������� ������� ������� �� ������� ������
	pos += 3;

	// ������� �������� ������
	ak_uint8 out[4];
	// ��������
	ak_base64_encodeblock(in, out, 3);

	// ak_uint8 - unsigned char
	// std::string ������ char
	// �������� ����, ����� �������� ��� �������� ������ � std::string
	return std::string(reinterpret_cast<char *>(out), 4);
}

std::string encrypt_size_1(const std::string& str, int &pos) {
	// ��� ��� ������ ������ ������������� \0 �� �������� �� ���� ������ ������(����� ������ in ������ ���� 1)
	ak_uint8 in[2];

	// �������� 1 ������� ������ � ������ ������� � ��� ������ in
	strncpy(reinterpret_cast<char *>(in), str.c_str() + pos, 1);
	// ��������� � ����� \0 ����� ������� ak_base64_encodeblock �������� ��� ����� ������
	in[1] = '\0';
	// ����������� ������� ������� �� ������� ������
	pos += 1;

	// ������� �������� ������
	ak_uint8 out[4];
	// ��������
	ak_base64_encodeblock(in, out, 1);

	// ak_uint8 - unsigned char
	// std::string ������ char
	// �������� ����, ����� �������� ��� �������� ������ � std::string
	return std::string(reinterpret_cast<char*>(out), 4);
}

std::string encrypt_size_2(const std::string& str, int& pos) {
	// ��� ��� ������ ������ ������������� \0 �� �������� �� ���� ������ ������(����� ������ in ������ ���� 2)
	ak_uint8 in[3];

	// �������� 3 ������� ������� � ������ ������� � ��� ������ in
	strncpy(reinterpret_cast<char*>(in), str.c_str() + pos, 2);
	// ��������� � ����� \0 ����� ������� ak_base64_encodeblock �������� ��� ����� ������
	in[2] = '\0';
	// ����������� ������� ������� �� ������� ������
	pos += 2;

	// ������� �������� ������
	ak_uint8 out[4];
	// ��������
	ak_base64_encodeblock(in, out, 2);

	// ak_uint8 - unsigned char
	// std::string ������ char
	// �������� ����, ����� �������� ��� �������� ������ � std::string
	return std::string(reinterpret_cast<char*>(out), 4);
}

std::string encrypt_string(char* str) {
	// ��������� ������� ������ � std::string ��� ��������
	std::string tmp(str);
	// ������ � �������� �����������, ���� ������
	std::string ret;
	// ������� ������� � ������
	int pos = 0;

	// ������ ���� ���� �� ������ �� ����� ������
	// ����� ������� �������� ��������� ���������� ��������� � ����� �������� ������(std::string ret)
	// pos ����� ��� �������� �� ������, ��� ��� ������ ����� ���� ����� ������
	while(tmp.size() - pos) {
		// ������� ������
		switch (tmp.size() - pos) {
		// ���� ������ ������� ������ 0(������ �� ����� ����, �� ����� �������� ��� ��������), �� �������
		case 0:
			break;
		// ���� ������ 1, �� �������� ������� ����������� ��� ������ �������� 1
		case 1:
			ret.append(encrypt_size_1(tmp, pos));
			break;
		// ���� ������ 2, �� �������� ������� ����������� ��� ������ �������� 2
		case 2:
			ret.append(encrypt_size_2(tmp, pos));
			break;
		// ��� ���� ��������� ��������
		default:
			ret.append(encrypt(tmp, pos));
			break;
		}
	}

	return ret;
}

// ��� ���������� ���� ��������
// ��� ������� � �� �� ����� ������� ��� ��� ������ ��������, ���� ���� - �������
int main(int argc, char *argv[]) {
	// ���� ��� �� ���� ������� ���������� �� ������ ������� � �������� no input data
	if (argc < 1) {
		printf("No input data");
		return 0;
	}

	// ������ ���� �� ���� ���������� ����������
	for (int i = 1; i < argc; ++i) {
		printf("Text: %s\n", argv[i]);
		const auto& str = encrypt_string(argv[i]);
		printf("\tBase64: %s\n\n", str.c_str());
	}
}
