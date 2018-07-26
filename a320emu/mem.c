#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "load.h"
#include "mem.h"

uint8_t *mem=NULL;
extern app_info_t app_info;

void store_mem(uint32_t mipsaddr, mem_unit_t size, uint32_t value)
{
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

