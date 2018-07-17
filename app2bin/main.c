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

int main(int argc, char** argv)
{
	printf("decode dingoo app back to binary file\n");
	if(argc != 2){
		printf("usage:\n  app2bin test.app\n");
		return -1;
	}
  
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

	printf("parsing app...\n");
	
	_app_ccdl ccdl;
	_app_impt impt;
	_app_expt expt;
	_app_rawd rawd;

	uint8_t *ptr = body;
	if(memcmp(ptr, "CCDL", 4) != 0){
		printf("invalid app file format (miss CCDL section)\n");
		goto err;
	}
	ptr+= sizeof(_app_ccdl);

	uint32_t cnt=0;
	uint32_t off = ((_app_impt*)ptr)->offset;
	uint32_t size = ((_app_impt*)ptr)->size;
	if(memcmp(ptr, "IMPT", 4) != 0){
		printf("invalid app file format (miss IMPT section)\n");
		goto err;
	}
	printf("import offset: %d\n", off);
	printf("import size: %d\n", size);
	/*
	uint8_t *p = body + off;
	for(cnt=0; cnt<size/sizeof(_app_impt_entry); cnt++){
		printf("  %x: 0x%x\n", ((_app_impt_entry*)p)->str_offset, ((_app_impt_entry*)p)->offset);
		p+= sizeof(_app_impt_entry);
	}
	*/
	ptr+= sizeof(_app_impt);

	if(memcmp(ptr, "EXPT", 4) != 0){
		printf("invalid app file format (miss EXPT section)\n");
		goto err;
	}
	printf("export offset: %d\n", ((_app_expt*)ptr)->offset);
	printf("export size: %d\n", ((_app_expt*)ptr)->size);
	ptr+= sizeof(_app_expt);
	
	if(memcmp(ptr, "RAWD", 4) != 0){
		printf("invalid app file format (miss RAWD section)\n");
		goto err;
	}

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

