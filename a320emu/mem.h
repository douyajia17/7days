#ifndef __MEM__
#define __MEM__

  typedef enum {
    SIZE_BYTE = 1,
    SIZE_HALF = 2,
    SIZE_WORD = 4,
  }mem_unit_t;

  #define STACK_SIZE  (64*1024)
  void store_mem(uint32_t, mem_unit_t, uint32_t);
  uint32_t load_mem(uint32_t, mem_unit_t);

#endif

