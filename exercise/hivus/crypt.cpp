#include "hivus.h"
#include <string>

#define file_ct "1207081514_6415.ktg"
#define file_pt "1207081514_6415.psw"

int main()
{
  char *argv[4];
  char mode = 'u';
  // pt
  argv[1] = (char *)(file_pt);
  /// ct"
  argv[2] = (char *)(file_ct);

  argv[3] = (char *)"key2";
  //printf("aaaaaaa%s\n", argv[2]);

  switch (mode)
  {
  case 'c':
    crypt_cmd(argv[1], argv[2], argv[3]);
    break;
  case 'u':
    uncrypt_cmd(argv[1], argv[2], argv[3]);
    break;
  default:
    printf("ERROR cmd programs arguments!!!\n");
    break;
  }
}
