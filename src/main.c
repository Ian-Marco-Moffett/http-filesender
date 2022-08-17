#include <content.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) { 
  if (argc < 2) {
    printf("Please pass the path of the file you want to transfer or pass raw text like so:\n");
    printf("sudo %s \"$(echo -e \"Some text.\")\"\n", argv[0]);
    return 1;
  }

  FILE* fp = fopen(argv[1], "r");

  if (fp == NULL) {
    printf("Treating argument passed as raw text.\n");

    return send_data(argv[1], strlen(argv[1]));
  }

  fseek(fp, 0, SEEK_END);
  size_t fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char* buf = calloc(fsize + 1, sizeof(char));
  fread(buf, sizeof(char), fsize, fp);

  return send_data(buf, fsize);
}
