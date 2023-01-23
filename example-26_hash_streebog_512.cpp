#include <iostream>
#include <string>
#include <libakrypt.h>
#include <libakrypt-base.h>

size_t size = 128;
char data[size] = "test data for hash";
int main() {
ak_uint32 steps;
  struct hash ctx; /* контекст функции хеширования */
  struct random rnd;
  size_t len, offset;
  int error = ak_error_ok;
  bool_t result = ak_true;
  int audit = ak_log_get_level();

 /* буффер длиной 64 байта (512 бит) для получения результата */
  ak_uint8 out[64], out2[64], buffer[512], *ptr = buffer;

 /* инициализируем контекст функции хешиирования */
  if(( error = ak_hash_create_streebog512( &ctx )) != ak_error_ok ) {
    ak_error_message( error, __func__ , "wrong initialization of streenbog512 context" );
    return ak_false;
  }

 /* берем хеш от строки data */
  ak_hash_ptr( &ctx, data, sizeof(data), out, sizeof( out ));
  if(( error = ak_error_get_value()) != ak_error_ok ) {
    ak_error_message( error, __func__ , "invalid calculation of streebog512 code" );
    result = ak_false;
  }
  //выводим )
  for (int i=0;i<sizeof(out);i++){
    std::cout<<out[i];
  }
} 
  