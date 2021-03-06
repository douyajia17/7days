#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "cpu.h"
#include "mem.h"
#include "load.h"
#include "disasm.h"

#define CREATE_RAW_FILE     0
#define PRINT_ENTRY_TABLE   1
#define PRINT_APP_INFO      1

app_info_t app_info={0};

static uint32_t parse_table(uint8_t *src, uint32_t off, uint32_t size)
{
  // find string table
  uint8_t *p = src + off;
  uint32_t str_off = off;
  uint32_t cnt, total = size/sizeof(_app_impt_entry);
	for(cnt=0; cnt<total; cnt++){
    if(((_app_impt_entry*)p)->unknown[1] > 0x20000){
    #if PRINT_APP_INFO
      printf("  string: count(0x%x) offset(0x%x)\n", cnt, str_off);
    #endif
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
    app_info.entry_table[app_info.entry_count].addr = ((_app_impt_entry*)p)->offset;
    app_info.entry_table[app_info.entry_count].name = &src[((_app_impt_entry*)p)->str_offset + str_off];
    app_info.entry_count+= 1;
	}
  return str_off;
}

void free_app(void)
{
  if(app_info.file_ptr){
    free(app_info.file_ptr);
  }
}

uint8_t* load_app(const char* app, int dis)
{
	FILE* file = fopen(app, "rb");
  if(file == NULL) {
    printf("failed to open app: %s", app);
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  uint32_t len = ftell(file);
  fseek(file, 0, SEEK_SET);
  app_info.file_ptr = (uint8_t*)malloc(len + STACK_SIZE);
  if(app_info.file_ptr == NULL) {
    printf("failed to allocate buffer for reading app\n");
    fclose(file);
    return NULL;
  }
  app_info.file_size = len;
  fread(app_info.file_ptr, 1, len, file);
  fclose(file); 
#if PRINT_APP_INFO
  printf("=== app info ===\n");
#endif

  // ccdl table
	uint8_t *ptr = app_info.file_ptr;
	if(memcmp(ptr, "CCDL", 4) != 0){
		printf("invalid app file format (miss CCDL section)\n");
		goto err;
	}
	ptr+= sizeof(_app_ccdl);

  // import table
	uint32_t off = ((_app_impt*)ptr)->offset;
	uint32_t size = ((_app_impt*)ptr)->size;
	if(memcmp(ptr, "IMPT", 4) != 0){
		printf("invalid app file format (miss IMPT section)\n");
		goto err;
	}
#if PRINT_APP_INFO
	printf("import offset: 0x%x\n", off);
	printf("import size: 0x%x\n", size);
#endif
  parse_table(app_info.file_ptr, off, size);
	ptr+= sizeof(_app_impt);

  // export table
	if(memcmp(ptr, "EXPT", 4) != 0){
		printf("invalid app file format (miss EXPT section)\n");
		goto err;
	}
	off = ((_app_rawd*)ptr)->offset;
	size = ((_app_rawd*)ptr)->size;
#if PRINT_APP_INFO
	printf("export offset: %d\n", off);
	printf("export size: %d\n", size);
#endif
  parse_table(app_info.file_ptr, off, size);
	ptr+= sizeof(_app_expt);
	
	if(memcmp(ptr, "RAWD", 4) != 0){
		printf("invalid app file format (miss RAWD section)\n");
		goto err;
	}

  // raw table
  uint32_t app_base=0;
	off = ((_app_rawd*)ptr)->offset;
	size = ((_app_rawd*)ptr)->size;
	app_base = ((_app_rawd*)ptr)->origin;
#if PRINT_APP_INFO
	printf("raw offset: %d\n", off);
	printf("raw size: %d\n", size);
	printf("raw entry: 0x%x\n", ((_app_rawd*)ptr)->entry);
	printf("raw origin: 0x%x\n", app_base);
	printf("raw prog_size: %d\n", ((_app_rawd*)ptr)->prog_size);
#endif
	ptr+= sizeof(_app_rawd);
  app_info.raw_ptr = app_info.file_ptr + off;
  app_info.raw_size = size;
#if PRINT_APP_INFO
  printf("\n");
#endif

#if CREATE_RAW_FILE 
  const char* out="raw.bin";
	int fd = open(out, O_CREAT | O_WRONLY, S_IRUSR);
	if(fd < 0){
		printf("failed to create binary file: %s\n", out);
		goto err;
	}
	write(fd, app_info.file_ptr+off, size);
	close(fd);
#endif

  if(dis){
    uint8_t *p=app_info.raw_ptr;
    printf("=== disasm ===\n");
    for(int i=0; i<size; i+=4, p+=4){
      printf("%08x(0x%08x): ", i, *(inst_t*)p);
      disasm(*(inst_t*)p);
    }
  }

#if PRINT_ENTRY_TABLE
  printf("=== entry table ===\n");
#endif
  uint32_t main=0;
  for(int i=0; i<app_info.entry_count; i++){
    app_info.entry_table[i].addr-= 0x80000000; //app_base;
    if(strcmp(app_info.entry_table[i].name, "AppMain") == 0){
      main = app_info.entry_table[i].addr;
    }
#if PRINT_ENTRY_TABLE
    printf("0x%x: %s\n", app_info.entry_table[i].addr, app_info.entry_table[i].name);
#endif
  }
#if PRINT_ENTRY_TABLE
  printf("\n");
#endif
  return app_info.raw_ptr + main;

err:
	free(app_info.file_ptr);
  exit(-1);
  return NULL;
}

