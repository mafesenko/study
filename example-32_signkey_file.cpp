#include <stdio.h>
#include <string>
#include <libakrypt.h>
#include <libakrypt-base.h>

int main(int argc, char ** argv) {
    struct signkey sk;
    struct verifykey pk;
    struct random generator;
 
    ak_uint8 sign[128];
    ak_uint8 testkey[32] = {
        0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x27, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x28 
    };
    
    ak_log_set_level(ak_log_maximum);

    // ������� ��������� ��������������� �������������������
    if(ak_random_create_lcg(&generator) != ak_error_ok)
        return ak_error_get_value();

    // �������������� ��������� ���� � �������� ������������� ������
    if (ak_signkey_create_str(&sk, "cspa") != ak_error_ok)
        return ak_error_get_value();    

    // ������������� �������� �����
    if(ak_signkey_set_key(&sk, testkey, sizeof(testkey)) != ak_error_ok)
        return ak_error_get_value();

    // ������������ ���� � ������������� ������
    ak_skey_set_resource_values(&sk.key, key_using_resource,
        "digital_signature_count_resource", 0, time(NULL) + 2592000);

    // ������ ������ ����������� ������ � �������� ������� ��������� ����������� ����
    ak_signkey_sign_file(&sk, &generator, argv[0], sign, sizeof(sign));
    printf("file:   %s\nsign:   %s\n", argv[0], ak_ptr_to_hexstr(sign, ak_signkey_get_tag_size(&sk), ak_false));

    // ��������� �������� ����
    ak_verifykey_create_from_signkey(&pk, &sk);
    // ��������� �������
    if (ak_verifykey_verify_file(&pk, argv[0], sign) == ak_true)
        printf("verify: Ok\n");
    else { 
        printf("verify: Wrong\n"); 
        return ak_error_get_value();
    }

    ak_signkey_destroy(&sk);
    ak_verifykey_destroy(&pk);

    return EXIT_SUCCESS;
}