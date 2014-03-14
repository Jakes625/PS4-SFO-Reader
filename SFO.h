#include "Util.h"

#define MAGIC 0x00505346 // 'PSF' Playstation System File
#define VERS 0x01010000 // assumed to be 1.1

#define HDR_LEN 0x14

class SystemFileObject{

public:
	typedef struct{
		u32 magic;
		u32 version;
		u32 keyTable;
		u32 dataTable;
		u32 entryCount;
	} sfo_header_t;

	#pragma pack (push, 1)

	typedef struct{
		u16 keyOffset; //offset of keytable + keyOffset
		u16 param_fmt;
		u32 paramLen;
		u32 paramMaxLen;
		u32 dataOffset; //offset of datatable + dataOffset
	} entry_t;

	typedef enum FMT : u16{
		SGC = 0x0400, //system generated content
		CSTR = 0x0402, //c string
		INT = 0x0404 //32 bit integer, unsigned
	} FMT_T;

	#pragma pack (pop)

	sfo_header_t header;
	entry_t* entries;

	SystemFileObject(const char* filepath);
	SystemFileObject(u8* fileBuffer, u64 fileSize);

	void DumpData();

private:
	u8* buffer;
	u64 buffersize;

	void Read();
};
