#include <stdio.h>
#include "xoodyak_cycle.h"

#define CU8P const u8 *
#define PLAIN 5
#define TAG 16

void print8(u8 *bytes, size len)
{
  size i;

  FOR(i, len) {
    printf("%02x", bytes[i]);
  }
  printf("\n");
}

//function to compare array elements
int compareArray(u8 a[],u8 b[],int size)	{
	int i;
	for(i=0;i<size;i++){
		if(a[i]!=b[i])
			return 0;
	}
	return 1;
}

int main(void)
{
  u8 plain[PLAIN] = {'p', 'l', 'a', 'i', 'n'};
  u8 tagEnc[TAG];
  u8 tagDec[TAG];
  xoocycle cyc;
  printf("Xoodyak Encryption\n");
  printf("Plain Text - ");
  print8(plain, PLAIN);
  printf("---------------------------------------- ");


  xoocycle_cyclist(&cyc, (CU8P)"key", 3, xoocycle_empty, 0,
                   xoocycle_empty, 0);
  xoocycle_absorb(&cyc, (CU8P)"nonce", 5);
  xoocycle_absorb(&cyc, (CU8P)"associated", 10);
  xoocycle_encrypt(&cyc, plain, PLAIN);

  printf("\nCiphertext after encryption - ");
  print8(plain, PLAIN);
  xoocycle_squeeze(&cyc, tagEnc, TAG);
  printf("Tag - ");
  print8(tagEnc, TAG);
  xoocycle_erase(&cyc);
  printf("Xoodyak Settings Removed!!\n");
  printf("----------------------------------------\n");

  printf("Xoodyak Decryption\n");
  printf("Ciphertext - ");
  print8(plain, PLAIN);
  xoocycle_cyclist(&cyc, (CU8P)"key", 3, xoocycle_empty, 0,
                   xoocycle_empty, 0);
  printf("Xoodyak Settings Done!!\n");

  xoocycle_absorb(&cyc, (CU8P)"nonce", 5);
  xoocycle_absorb(&cyc, (CU8P)"associated", 10);
  xoocycle_decrypt(&cyc, plain, PLAIN);
  printf("Decrypted Text after decryption - ");
  print8(plain, PLAIN);
  xoocycle_squeeze(&cyc, tagDec, TAG);
  printf("Tag - ");
  print8(tagDec, TAG);

  int isEqual = compareArray(tagEnc, tagEnc, TAG );
  if(isEqual) 
    printf("Success\n");
  else
    printf("Failure\n");

  return 0;
}