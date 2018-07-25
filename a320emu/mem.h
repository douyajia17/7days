#ifndef __MEM__
#define __MEM__

  typedef enum {
    SIZE_BYTE = 1,
    SIZE_HALF = 2,
    SIZE_WORD = 4,
  }mem_unit;

  #define MEM_SIZE (65 * 1024 * 1024) // 65M

  void store_mem(uint32_t mipsaddr, mem_unit size, uint32_t value);
  uint32_t load_mem(uint32_t mipsaddr, mem_unit size);

#endif

