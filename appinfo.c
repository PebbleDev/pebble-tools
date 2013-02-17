#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct
{
  char magic[8]; // PBLAPP\0\0
  unsigned short version;
  unsigned short unknown1; // another version?
  unsigned short unknown2;
  unsigned short size;
  unsigned int entry_point;
  unsigned int crc;
  char name[32];
  char company[32];
  unsigned int unknown3; // Always seems to be one?
  unsigned int unknown4; // Some offset in file
  unsigned int unknown5;
  unsigned int unknown6; // Some offset in file
  unsigned int unknown7;
} pblapp;

int main(int argc, char **argv)
{
  FILE *file;
  pblapp hdr = {};
  if(argc < 2)
  {
    fprintf(stderr, "Usage: %s <pebble-app.bin>\n", argv[0]);
    return 1;
  }

  file = fopen(argv[1], "rb");
  if(file == NULL)
  {
    fprintf(stderr, "Unable to open file %s: %s\n", argv[1], strerror(errno));
    return 2;
  }

  if ((fread(&hdr, sizeof(pblapp), 1, file)) != 1){
    fprintf(stderr, "Unable to parse file %s: %s\n", argv[1], strerror(errno));
  }
  fclose(file);

  printf("magic: %.*s\n", 8, hdr.magic);
  printf("Version: %d\n", hdr.version);
  printf("unknown1: %d\n", hdr.unknown1);
  printf("unknown2: %d\n", hdr.unknown2);
  printf("size: %d (0x%x)\n", hdr.size, hdr.size);
  printf("entry_point: %u (0x%x)\n", hdr.entry_point, hdr.entry_point);
  printf("crc: %u\n", hdr.crc);
  printf("name: %.*s\n", 32, hdr.name);
  printf("company: %.*s\n", 32, hdr.company);
  printf("unknown3: %d\n", hdr.unknown3);
  printf("unknown4: %u (0x%x)\n", hdr.unknown4, hdr.unknown4);
  printf("unknown5: %u\n", hdr.unknown5);
  printf("unknown6: %d (0x%x)\n", hdr.unknown6, hdr.unknown6);
  printf("unknown7: %d\n", hdr.unknown7);

  return 0;
};
