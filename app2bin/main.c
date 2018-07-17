#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
	char     ident[4];
	uint8_t  unknown[20];
	uint8_t  padding[8];
} __attribute__((__packed__)) _app_ccdl;

typedef struct {
	char     ident[4];
	uint32_t unknown;
	uint32_t offset;
	uint32_t size;
	uint8_t  padding[16];
} __attribute__((__packed__)) _app_impt;

typedef struct {
	char     ident[4];
	uint32_t unknown;
	uint32_t offset;
	uint32_t size;
	uint8_t  padding[16];
} __attribute__((__packed__)) _app_expt;

typedef struct {
	char     ident[4];
	uint32_t unknown0;
	uint32_t offset;
	uint32_t size;
	uint32_t unknown1;
	uint32_t entry;
	uint32_t origin;
	uint32_t prog_size;
} __attribute__((__packed__)) _app_rawd;

typedef struct {
	uint32_t str_offset;
	uint32_t unknown[2];
	uint32_t offset;
} __attribute__((__packed__)) _app_impt_entry;

typedef struct {
	uint32_t str_offset;
	uint32_t unknown[2];
	uint32_t offset;
} __attribute__((__packed__)) _app_expt_entry;

uint32_t print_table(uint8_t *src, uint32_t off, uint32_t size)
{
  // find string table
  uint8_t *p = src + off;
  uint32_t str_off = off;
  uint32_t cnt, total = size/sizeof(_app_impt_entry);
	for(cnt=0; cnt<total; cnt++){
    if(((_app_impt_entry*)p)->unknown[1] > 0x20000){
      printf("  string: count(0x%x) offset(0x%x)\n", cnt, str_off);
      break;
    }
		p+= sizeof(_app_impt_entry);
    str_off+= sizeof(_app_impt_entry);
	}

  // print each import item
	p = src + off;
	for(cnt=0; cnt<total; cnt++, p+= sizeof(_app_impt_entry)){
    if(((_app_impt_entry*)p)->unknown[1] == 0x00000){
      continue;
    }
    if(((_app_impt_entry*)p)->unknown[1] > 0x20000){
      break;
    }
		printf("  0x%x(%s)\n", ((_app_impt_entry*)p)->offset, &src[((_app_impt_entry*)p)->str_offset + str_off]);
	}
  return str_off;
}

int main(int argc, char** argv)
{
  // check argument
	printf("decode dingoo app back to binary file\n");
	if(argc != 2){
		printf("usage:\n  app2bin test.app\n");
		return -1;
	}
 
  // read xxx.app
	FILE* file = fopen(argv[1], "rb");
  if(file == NULL) {
    printf("failed to open app: %s", argv[1]);
    return -1;
  }
  fseek(file, 0, SEEK_END);
  uintptr_t len = ftell(file);
	printf("app length: %d\n", len);
  fseek(file, 0, SEEK_SET);
  uint8_t* body = (uint8_t*)malloc(len);
  if(body == NULL) {
    printf("failed to allocate buffer for reading app\n");
    fclose(file);
    return -1;
  }
  fread(body, 1, len, file);
  fclose(file);

  // parsing
	printf("parsing app...\n");	
	_app_ccdl ccdl;
	_app_impt impt;
	_app_expt expt;
	_app_rawd rawd;

  // ccdl table
	uint8_t *ptr = body;
	if(memcmp(ptr, "CCDL", 4) != 0){
		printf("invalid app file format (miss CCDL section)\n");
		goto err;
	}
	ptr+= sizeof(_app_ccdl);

  // import table
	uint32_t cnt=0, total=0;
	uint32_t off = ((_app_impt*)ptr)->offset;
	uint32_t size = ((_app_impt*)ptr)->size;
	if(memcmp(ptr, "IMPT", 4) != 0){
		printf("invalid app file format (miss IMPT section)\n");
		goto err;
	}
	printf("import offset: 0x%x\n", off);
	printf("import size: 0x%x\n", size);
  print_table(body, off, size);
	ptr+= sizeof(_app_impt);

  // export table
	if(memcmp(ptr, "EXPT", 4) != 0){
		printf("invalid app file format (miss EXPT section)\n");
		goto err;
	}
	off = ((_app_rawd*)ptr)->offset;
	size = ((_app_rawd*)ptr)->size;
	printf("export offset: %d\n", off);
	printf("export size: %d\n", size);
  print_table(body, off, size);
	ptr+= sizeof(_app_expt);
	
	if(memcmp(ptr, "RAWD", 4) != 0){
		printf("invalid app file format (miss RAWD section)\n");
		goto err;
	}

  // raw table
	off = ((_app_rawd*)ptr)->offset;
	size = ((_app_rawd*)ptr)->size;
	printf("raw offset: %d\n", off);
	printf("raw size: %d\n", size);
	printf("raw entry: 0x%x\n", ((_app_rawd*)ptr)->entry);
	printf("raw origin: 0x%x\n", ((_app_rawd*)ptr)->origin);
	printf("raw prog_size: %d\n", ((_app_rawd*)ptr)->prog_size);
	ptr+= sizeof(_app_rawd);

	int fd = open("raw.bin", O_CREAT | O_WRONLY, S_IRUSR);
	if(fd < 0){
		printf("failed to create out.elf file\n");
		goto err;
	}
	write(fd, body+off, size);
	close(fd);
	printf("task done !\n");
err:
	free(body);
	return 0;
}

