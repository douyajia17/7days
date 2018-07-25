#ifndef __MEM__
#define __MEM__

  typedef enum {
    SIZE_BYTE = 1,
    SIZE_HALF = 2,
    SIZE_WORD = 4,
  }mem_unit_t;

  void store_mem(uint32_t mipsaddr, mem_unit_t size, uint32_t value);
  uint32_t load_mem(uint32_t mipsaddr, mem_unit_t size);

#endif

