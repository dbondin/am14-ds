#include <stdio.h>
#include <stdlib.h>

#include "lzwy.h"

int main(int argc, char ** argv) {
  
  int size;
  int status;
  const char * infile;
  const char * outfile;

  if(argc < 4) {
    fprintf(stderr, "Usage: pack size infile outfile\n");
    return 1;
  }

  size = atoi(argv[1]);
  infile = argv[2];
  outfile = argv[3];

  printf("LZWY: %s\n", lzwy_version());

  status = lzwy_pack(size, infile, outfile);

  if(status == 0) {
    printf("OK\n");
  }
  else {
    printf("FAILURE\n");
  }

  return ( status != 0 );
}
