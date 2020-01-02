
#include <stdio.h>
#include <cpuinfo.h>

int main()
{

  if (cpuinfo_initialize()) {
     printf("Hello WITH successfully initialized cpuinfo\n");
  } else {
     printf("Hello WITHOUT successfully initialized cpuinfo\n");
  }

  if (cpuinfo_has_x86_avx512f()) {
     printf("With avx512 support!\n");
  } else {
     printf("Without avx512 support!\n");
  }

  return 0;

}
