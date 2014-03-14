#ifndef _UTIL_H_
#define _UTIL_H_

#if defined(_WIN32) && defined(_MSC_VER)
	typedef unsigned __int64 u64;
#else
	typedef unsigned long long int u64;
#endif

typedef unsigned long int u32;
typedef unsigned short int u16;
typedef unsigned char u8;

int get_file_size(const char *file_path, u64 *size);
int read_file(const char *file_path, u8 *data, u64 size);
int write_file(const char *file_path, u8 *data, u64 size);
const char* str_c(const char* a, const char* b);

unsigned int hash(const void* key, int len, unsigned int seed);

#define SWAP32(val) ((u32) ( \
	(((u32)val & 0xFF) << 24) | \
	(((u32)val & 0xFF00) << 8) | \
	(((u32)val >> 8) & 0xFF00) | \
	(((u32)val >> 24) & 0xFF)))

#define SWAP64(val) ((u64) ( \
    (((u64) (val) & (u64) 0x00000000000000ff) << 56) | \
    (((u64) (val) & (u64) 0x000000000000ff00) << 40) | \
    (((u64) (val) & (u64) 0x0000000000ff0000) << 24) | \
    (((u64) (val) & (u64) 0x00000000ff000000) <<  8) | \
    (((u64) (val) & (u64) 0x000000ff00000000) >>  8) | \
    (((u64) (val) & (u64) 0x0000ff0000000000) >> 24) | \
    (((u64) (val) & (u64) 0x00ff000000000000) >> 40) | \
    (((u64) (val) & (u64) 0xff00000000000000) >> 56)))

#endif
