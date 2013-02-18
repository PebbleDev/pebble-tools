#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct
{
  char magic[8]; // PBLAPP\0\0
  unsigned short version;
  unsigned short sdk_version;
  unsigned short app_version;
  unsigned short size;
  unsigned int entry_point;
  unsigned int crc;
  char name[32];
  char company[32];
  unsigned int unknown3; // Always seems to be one?
  unsigned int jump_table; // offset in file
  unsigned int flags;
  unsigned int reloc_list; // offset in file
  unsigned int num_relocs;
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
    goto error_read;
  }

  printf("magic: %.*s\n", 8, hdr.magic);
  printf("Version: %d\n", hdr.version);
  printf("Sdk Version: %d\n", hdr.sdk_version);
  printf("App Version: %d\n", hdr.app_version);
  printf("size: %d (0x%x)\n", hdr.size, hdr.size);
  printf("Entry Point: %u (0x%x)\n", hdr.entry_point, hdr.entry_point);
  printf("crc: %u\n", hdr.crc);
  printf("name: %.*s\n", 32, hdr.name);
  printf("company: %.*s\n", 32, hdr.company);
  printf("unknown3: %d\n", hdr.unknown3);
  printf("jump_table address: %u (0x%x)\n", hdr.jump_table, hdr.jump_table);
  printf("flags: %u\n", hdr.flags);
  printf("relocation list address: %d (0x%x)\n", hdr.reloc_list, hdr.reloc_list);
  printf("number of relocations: %d\n", hdr.num_relocs);

  error_read:
    fclose(file);
  return 0;
};
