#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if (defined(_MSC_VER) && _MSC_VER >= 1600) || \
      (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
#  include <stdint.h>
#else
#  ifndef UINT32_T
#    define UINT32_T  unsigned int
#  endif
typedef UINT32_T uint32_t;
#endif


static void
xorseed(unsigned int s);

static uint32_t
xor128(void);

#define LENGTHOF(array)  (sizeof(array) / sizeof(array[0]))


static const char *results[] = {
  "大吉", "中吉", "吉", "末吉", "凶", "大凶"
};

static uint32_t seed128[4];


int
main(void)
{
  xorseed((uint32_t) time(NULL));
  printf("%s\n", results[xor128() % LENGTHOF(results)]);
  return EXIT_SUCCESS;
}


static void
xorseed(uint32_t s)
{
  uint32_t i;
  for (i = 1; i <= 4; i++) {
    seed128[i - 1] = s = 1812433253U * (s ^ (s >> 30)) + i;
  }
}


static uint32_t
xor128(void)
{
  uint32_t t = (seed128[0] ^ (seed128[0] << 11));
  seed128[0] = seed128[1];
  seed128[1] = seed128[2];
  seed128[2] = seed128[3];
  return seed128[3] = (seed128[3] ^ (seed128[3] >> 19)) ^ (t ^ (t >> 8));
}
