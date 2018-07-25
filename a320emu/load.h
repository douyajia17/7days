#ifndef __LOAD__
#define __LOAD__

  typedef struct {
    char     ident[4];
    uint8_t  unknown[20];
    uint8_t  padding[8];
  }__attribute__((__packed__)) _app_ccdl;

  typedef struct {
    char     ident[4];
    uint32_t unknown;
    uint32_t offset;
    uint32_t size;
    uint8_t  padding[16];
  }__attribute__((__packed__)) _app_impt;

  typedef struct {
    char     ident[4];
    uint32_t unknown;
    uint32_t offset;
    uint32_t size;
    uint8_t  padding[16];
  }__attribute__((__packed__)) _app_expt;

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
  }__attribute__((__packed__)) _app_impt_entry;

  typedef struct {
    uint32_t str_offset;
    uint32_t unknown[2];
    uint32_t offset;
  }__attribute__((__packed__)) _app_expt_entry;

  typedef struct {
    uint32_t addr;
    char *name;
  }sym_entry;

  typedef struct {
    uint32_t file_size;
    uint8_t *file_ptr;
    uint32_t raw_size;
    uint8_t *raw_ptr;
    uint32_t entry_count;
    sym_entry entry_table[255];
  }app_info_t;

  uint8_t* load_app(const char*, int);
  void free_app(void);

#endif

