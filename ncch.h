#pragma once
#include "lib.h"

typedef enum
{
	NCCH_MEMERROR = -1,
	SAVE_DATA_TOO_LARGE = -2,
	NCCH_SECTION_NOT_EXIST = -3,
	UNABLE_TO_LOAD_NCCH_KEY = -4,
	NCCH_EXPORT_BUFFER_TOO_SMALL = -5,
	NO_ROMFS_IN_CFA = -6,
	NO_EXHEADER_IN_CXI = -7,
	NO_EXEFS_IN_CXI = -8,
	// SigCheck Errors
	CXI_CORRUPT = -9,
	ACCESSDESC_SIG_BAD = -10,
	NCCH_HDR_SIG_BAD = -11,
	// HashCheck Errors
	EXHDR_CORRUPT = -12,
	LOGO_CORRUPT = -13,
	EXEFS_CORRUPT = -14,
	ROMFS_CORRUPT = -15,
	// Others
	NCCH_BAD_RSF_SET = -16,
	DATA_POS_DNE = -17,
} ncch_errors;

typedef enum
{
	ncch_exhdr = 1,
	ncch_exefs,
	ncch_romfs,
} ncch_section;

typedef enum
{
	ncchflag_CONTENT_KEYX = 3,
	ncchflag_CONTENT_PLATFORM = 4,
	ncchflag_CONTENT_TYPE = 5,
	ncchflag_CONTENT_BLOCK_SIZE = 6,
	ncchflag_OTHER_FLAG = 7
} ncch_flags;

typedef enum
{
	otherflag_Clear = 0,
	otherflag_FixedCryptoKey = (1 << 0),
	otherflag_NoMountRomFs = (1 << 1),
	otherflag_NoCrypto = (1 << 2),
} ncch_otherflag_bitmask;

typedef enum
{
	form_Unassigned,
	form_SimpleContent,
	form_ExecutableWithoutRomfs,
	form_Executable
} ncch_form_type;

typedef enum
{
	content_Application,
	content_SystemUpdate,
	content_Manual,
	content_Child,
	content_Trial,
	content_ExtendedSystemUpdate
} ncch_content_bitmask;

typedef enum
{
	platform_CTR = 0x1,
	platform_SNAKE = 0x2
} ncch_platform;

typedef enum
{
	keyx_regular = 0x00,
	keyx_7_0 = 0x01,
	keyx_9_3 = 0x0A,
	keyx_9_6 = 0x0B,
} ncch_keyx_id;

typedef struct
{
	u16 formatVersion;
	u32 exhdrOffset;
	u32 exhdrSize;
	u32 acexOffset;
	u32 acexSize;
	u64 logoOffset;
	u64 logoSize;
	u64 plainRegionOffset;
	u64 plainRegionSize;
	u64 exefsOffset;
	u64 exefsSize;
	u64 exefsHashDataSize;
	u64 romfsOffset;
	u64 romfsSize;
	u64 romfsHashDataSize;
	u64 titleId;
	u64 programId;
} ncch_info;

typedef struct
{
	u8 signature[0x100];
	u8 magic[4];
	u8 ncchSize[4];
	u8 titleId[8];
	u8 makerCode[2];
	u8 formatVersion[2];
	u8 padding0[4];
	u8 programId[8];
	u8 padding1[0x10];
	u8 logoHash[0x20]; // SHA-256 over the entire logo region
	u8 productCode[0x10];
	u8 exhdrHash[0x20]; // SHA-256 over exhdrSize of the exhdr region
	u8 exhdrSize[4];
	u8 padding2[4];
	u8 flags[8];
	u8 plainRegionOffset[4];
	u8 plainRegionSize[4];
	u8 logoOffset[4];
	u8 logoSize[4];
	u8 exefsOffset[4];
	u8 exefsSize[4];
	u8 exefsHashSize[4];
	u8 padding4[4];
	u8 romfsOffset[4];
	u8 romfsSize[4];
	u8 romfsHashSize[4];
	u8 padding5[4];
	u8 exefsHash[0x20];
	u8 romfsHash[0x20];
} ncch_hdr;