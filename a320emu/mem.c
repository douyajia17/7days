#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "load.h"
#include "mem.h"

uint8_t *mem=NULL;
extern app_info_t app_info;

int access_ok(uint32_t mipsaddr, mem_unit_t size)
{
	if(mipsaddr < 1){
		return 0;
	}
	if(size == SIZE_BYTE){
		return (mipsaddr < app_info.raw_size);
	}
	if(size == SIZE_HALF){
		if((mipsaddr + 1 >= app_info.raw_size)){
			return 0;
		}
		if((mipsaddr & 0x00000001) != 0){
			return 0;
    }
	}
	
  if(size == SIZE_WORD){
		if((mipsaddr + 3 >= app_info.file_size)){
			return 0;
		}
		if((mipsaddr & 0x00000003) != 0){
			return 0;
    }
	}
	return 1;
}

void store_mem(uint32_t mipsaddr, mem_unit_t size, uint32_t value)
{
	if(!access_ok(mipsaddr, size)){
		fprintf(stderr, "%s: bad write=%08x\n", __func__, mipsaddr);
		exit(0);
	}

	switch(size){
	case SIZE_HALF:
		*(mem + mipsaddr) = value & 0xff;
		*(mem + mipsaddr + 1) = value & 0xff00;
		break;
	case SIZE_WORD:
		*(mem + mipsaddr) = value & 0xff;
		*(mem + mipsaddr + 1) = ((value & 0xff00) >> 8);
		*(mem + mipsaddr + 2) = ((value & 0xff0000) >> 16);
		*(mem + mipsaddr + 3) = ((value & 0xff000000) >> 24);
		break;
	case SIZE_BYTE:
		*(mem + mipsaddr) = value;
		break;
	}
}

uint32_t load_mem(uint32_t mipsaddr, mem_unit_t size)
{
	if(!access_ok(mipsaddr, size)){
		fprintf(stderr, "%s: bad read=%08x\n", __func__, mipsaddr);
		exit(0);
	}

	switch(size){
	case SIZE_HALF:
		return *(uint16_t*)(mem + mipsaddr);
		break;
	case SIZE_WORD:
		return *(uint32_t*)(mem + mipsaddr);
		break;
	case SIZE_BYTE:
		return *(uint8_t*)(mem + mipsaddr);
		break;
	}
	return *(uint32_t*)(mem + mipsaddr);
}

