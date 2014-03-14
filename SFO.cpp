#include "SFO.h"
#include <iostream>

SystemFileObject::SystemFileObject(const char* filepath)
{
	if(get_file_size(filepath, &buffersize) < 0)
		return;
	
	buffer = new u8[buffersize];

	if(read_file(filepath, buffer, buffersize) < 0)
		return;

	this->Read();
}

SystemFileObject::SystemFileObject(u8* fileBuffer, u64 fileSize)
{
	buffer = fileBuffer;
	buffersize = fileSize;

	this->Read();
}

void SystemFileObject::Read()
{
	this->header = *(sfo_header_t *)buffer;
	this->entries = new entry_t[ this->header.entryCount ];

	for(u32 i=0; i< this->header.entryCount ; i++)
	{
		this->entries[i] = *(entry_t *)&buffer[HDR_LEN + (sizeof(entry_t) * i)];
	}
}

void SystemFileObject::DumpData() //not really dumping.. rather 'defining' @aerosoul94 ;)
{
	printf("SFO Header Information:\n=========================\n");
	printf("Magic: %X\n", SWAP32(this->header.magic) );
	printf("Version: %X\n", SWAP32(this->header.version) );
	printf("Key Table Offset: 0x%X\n", this->header.keyTable);
	printf("Data Table Offset: 0x%X\n", this->header.dataTable);
	printf("Entry Count: 0x%X\n", this->header.entryCount);
	printf("\n");

	printf("Entries Information:\n=========================\n\n");
	for(u32 i=0; i<this->header.entryCount; i++)
	{
		printf("Entry #%d:\n", i + 1);

		char* key = (char *)&buffer[this->header.keyTable + this->entries[i].keyOffset];
		int len = strlen(key);
		
		//I am using string hashes to figure out which string is which..
		//because C/C++ has no standard way of checking string equality
		int shash = hash(key, len, 0); //use this to generate new hashes as well.. add to the database..

		printf("Key: %s\n", key);
		printf("Type: ");
		switch(this->entries[i].param_fmt)
		{
		case FMT::INT:
			printf("%s\n", "32bit Unsigned Integer");
			break;
		case FMT::CSTR:
			printf("%s\n", "C String");
			break;
		case FMT::SGC:
		default:
			printf("%s\n", "System Generated Content");
			break;
		}
		printf("Param Len: 0x%X\n", this->entries[i].paramLen);
		printf("Param Len (max): 0x%X\n", this->entries[i].paramMaxLen);
		printf("Data Offset: 0x%X\n", this->header.dataTable + this->entries[i].dataOffset);
		printf("Data (if applicable):\n");

		char* val = new char[this->entries[i].paramLen]; //you need these or the default will error.

		switch(this->entries[i].param_fmt)
		{
		case FMT::INT:
			//APP_TYPE is also an enumeration, but I don't have that either so I am just going to dump it's value.
			if(shash != 0x9A10CC96) //ATTRIBUTE
				printf("0x%X\n", *(u32*)&this->buffer[this->header.dataTable + this->entries[i].dataOffset]);
			else
			{
				//attribute is actually an array of flags to enable/disable features
				//since FMT::INT is 32 bits.. they're are a max of 32 flags to enable/disable
				//I do not have an enumeration of the flags.
				//for now we will leave this as 'null'
				printf("N/A\n");
			}
			break;
		case FMT::CSTR:
			printf("%s\n", &this->buffer[this->header.dataTable + this->entries[i].dataOffset]);
			break;
		case FMT::SGC:
		default:
			
			switch(shash)
			{
			case 0xCC7F3E28: //APP_VER
			case 0x6E024379: //CONTENT_ID
			case 0x76482AC5: //FORMAT
			case 0x5DCFAAC7: //PUBTOOLINFO
			case 0x4C9C18CE: //TITLE
			case 0x0EEF1FF5: //TITLE_ID
			case 0x8CA74166: //VERSION
			case 0xEF99AC71: //CATEGORY  THIS IS AN ENUM, AGAIN.. UNSURE OF TRUE VALUES
				memcpy(val, &this->buffer[this->header.dataTable + this->entries[i].dataOffset], this->entries[i].paramLen);
				printf("%s\n", val);
				break;
			default:
				printf("N/A\n");
				break;
			}


			break;
		}

		printf("\n");
	}
}
