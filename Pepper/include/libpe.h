#pragma once
#include <Imagehlp.h>

#if defined(ILIBPE_EXPORT)
#define ILIBPEAPI __declspec(dllexport) __cdecl
#else 
#define ILIBPEAPI __declspec(dllimport) __cdecl
#endif

typedef const IMAGE_DOS_HEADER *PLIBPE_DOSHEADER;
typedef std::vector<std::tuple<WORD, WORD, DWORD>> LIBPE_RICH;
typedef const LIBPE_RICH *PLIBPE_RICH;
typedef std::tuple<IMAGE_NT_HEADERS32, IMAGE_NT_HEADERS64> LIBPE_NTHEADER;
typedef const LIBPE_NTHEADER *PLIBPE_NTHEADER;
typedef const IMAGE_FILE_HEADER *PLIBPE_FILEHEADER;
typedef std::tuple<IMAGE_OPTIONAL_HEADER32, IMAGE_OPTIONAL_HEADER64> LIBPE_OPTHEADER;
typedef const LIBPE_OPTHEADER *PLIBPE_OPTHEADER;
typedef std::vector<std::tuple<IMAGE_DATA_DIRECTORY, std::string>> LIBPE_DATADIRS;
typedef const LIBPE_DATADIRS *PLIBPE_DATADIRS;
typedef std::vector<IMAGE_SECTION_HEADER> LIBPE_SECHEADER;
typedef LIBPE_SECHEADER *PLIBPE_SECHEADER;
typedef std::tuple<IMAGE_EXPORT_DIRECTORY, std::string, std::vector<std::tuple<DWORD, DWORD, std::string, std::string>>> LIBPE_EXPORT;
typedef const LIBPE_EXPORT *PLIBPE_EXPORT;
typedef std::vector<std::tuple<IMAGE_IMPORT_DESCRIPTOR, std::string, std::vector<std::tuple<LONGLONG, std::string, LONGLONG>>>> LIBPE_IMPORT;
typedef const LIBPE_IMPORT *PLIBPE_IMPORT;

///////////////////Resources by Levels////////////////////////////////////
//Totally 3 levels of resources. Highest level include lowest levels./////
//////////////////////////////////////////////////////////////////////////
//Level 3 (the lowest) vector.
typedef std::vector<std::tuple<IMAGE_RESOURCE_DIRECTORY_ENTRY, std::wstring/*ResName*/,
	IMAGE_RESOURCE_DATA_ENTRY, std::vector<std::byte>>> LIBPE_RESOURCE_VEC_LVL3;
typedef const LIBPE_RESOURCE_VEC_LVL3 *PLIBPE_RESOURCE_VEC_LVL3;
//Level 2 vector
typedef std::vector<std::tuple<IMAGE_RESOURCE_DIRECTORY_ENTRY, std::wstring/*ResName*/,
	IMAGE_RESOURCE_DATA_ENTRY, std::vector<std::byte>,
	/*///LvL3*/std::tuple<IMAGE_RESOURCE_DIRECTORY, LIBPE_RESOURCE_VEC_LVL3>>> LIBPE_RESOURCE_VEC_LVL2;
typedef const LIBPE_RESOURCE_VEC_LVL2 *PLIBPE_RESOURCE_VEC_LVL2;
//Level 1 (Root) vector
typedef std::vector<std::tuple<IMAGE_RESOURCE_DIRECTORY_ENTRY, std::wstring/*ResName*/,
	IMAGE_RESOURCE_DATA_ENTRY, std::vector<std::byte>,
	/*///LvL2*/std::tuple<IMAGE_RESOURCE_DIRECTORY, LIBPE_RESOURCE_VEC_LVL2>>> LIBPE_RESOURCE_VEC_ROOT;
typedef const LIBPE_RESOURCE_VEC_ROOT *PLIBPE_RESOURCE_VEC_LVL1;
//Tuples of resource directories. Includes IMAGE_RESOURCE_DIRECTORY (Header) and Vector of resources itself.
typedef std::tuple<IMAGE_RESOURCE_DIRECTORY, LIBPE_RESOURCE_VEC_LVL3> LIBPE_RESOURCE_LVL3;
typedef std::tuple<IMAGE_RESOURCE_DIRECTORY, LIBPE_RESOURCE_VEC_LVL2> LIBPE_RESOURCE_LVL2;
typedef std::tuple<IMAGE_RESOURCE_DIRECTORY, LIBPE_RESOURCE_VEC_ROOT> LIBPE_RESOURCE_ROOT;
typedef const LIBPE_RESOURCE_ROOT *PLIBPE_RESOURCE_ROOT;
typedef const LIBPE_RESOURCE_LVL2 *PLIBPE_RESOURCE_LVL2;
typedef const LIBPE_RESOURCE_LVL3 *PLIBPE_RESOURCE_LVL3;
////////////////////////////////////////////////////////////////////////////

typedef std::vector<_IMAGE_RUNTIME_FUNCTION_ENTRY> LIBPE_EXCEPTION;
typedef const LIBPE_EXCEPTION *PLIBPE_EXCEPTION;
typedef std::vector<std::tuple<WIN_CERTIFICATE, std::vector<std::byte>>> LIBPE_SECURITY;
typedef const LIBPE_SECURITY *PLIBPE_SECURITY;
typedef std::vector<std::tuple<IMAGE_BASE_RELOCATION, std::vector<std::tuple<WORD, WORD>>>> LIBPE_RELOCATION;
typedef const LIBPE_RELOCATION *PLIBPE_RELOCATION;
typedef std::vector<IMAGE_DEBUG_DIRECTORY> LIBPE_DEBUG;
typedef LIBPE_DEBUG *PLIBPE_DEBUG;
typedef std::tuple<IMAGE_TLS_DIRECTORY32, IMAGE_TLS_DIRECTORY64, std::vector<std::byte>/*Raw Data*/, std::vector<DWORD>> LIBPE_TLS;
typedef const LIBPE_TLS *PLIBPE_TLS;
typedef std::tuple<IMAGE_LOAD_CONFIG_DIRECTORY32, IMAGE_LOAD_CONFIG_DIRECTORY64> LIBPE_LOADCONFIGTABLE;
typedef const LIBPE_LOADCONFIGTABLE *PLIBPE_LOADCONFIGTABLE;
typedef std::vector<std::tuple<IMAGE_BOUND_IMPORT_DESCRIPTOR, std::string, std::vector<std::tuple<IMAGE_BOUND_FORWARDER_REF, std::string>>>> LIBPE_BOUNDIMPORT;
typedef const LIBPE_BOUNDIMPORT *PLIBPE_BOUNDIMPORT;
typedef std::vector<std::tuple<IMAGE_DELAYLOAD_DESCRIPTOR, std::string, std::vector<std::tuple<LONGLONG, std::string, LONGLONG, LONGLONG, LONGLONG, LONGLONG>>>> LIBPE_DELAYIMPORT;
typedef const LIBPE_DELAYIMPORT *PLIBPE_DELAYIMPORT;

//Pure Virtual base class Ilibpe
class __declspec(novtable) Ilibpe
{
public:
	virtual HRESULT LoadPe(LPCWSTR lpszFile) = 0;
	virtual HRESULT GetFileSummary(DWORD* pFileSummary) = 0;
	virtual HRESULT GetMSDOSHeader(PLIBPE_DOSHEADER*) = 0;
	virtual HRESULT GetMSDOSRichHeader(PLIBPE_RICH*) = 0;
	virtual HRESULT GetNTHeader(PLIBPE_NTHEADER*) = 0;
	virtual HRESULT GetFileHeader(PLIBPE_FILEHEADER*) = 0;
	virtual HRESULT GetOptionalHeader(PLIBPE_OPTHEADER*) = 0;
	virtual HRESULT GetDataDirectories(PLIBPE_DATADIRS*) = 0;
	virtual HRESULT GetSectionHeaders(PLIBPE_SECHEADER*) = 0;
	virtual HRESULT GetExportTable(PLIBPE_EXPORT*) = 0;
	virtual HRESULT GetImportTable(PLIBPE_IMPORT*) = 0;
	virtual HRESULT GetResourceTable(PLIBPE_RESOURCE_ROOT*) = 0;
	virtual HRESULT GetExceptionTable(PLIBPE_EXCEPTION*) = 0;
	virtual HRESULT GetSecurityTable(PLIBPE_SECURITY*) = 0;
	virtual HRESULT GetRelocationTable(PLIBPE_RELOCATION*) = 0;
	virtual HRESULT GetDebugTable(PLIBPE_DEBUG*) = 0;
	virtual HRESULT GetTLSTable(PLIBPE_TLS*) = 0;
	virtual HRESULT GetLoadConfigTable(PLIBPE_LOADCONFIGTABLE*) = 0;
	virtual HRESULT GetBoundImportTable(PLIBPE_BOUNDIMPORT*) = 0;
	virtual HRESULT GetDelayImportTable(PLIBPE_DELAYIMPORT*) = 0;

	virtual HRESULT Release() = 0;
};

extern "C" HRESULT ILIBPEAPI Getlibpe(Ilibpe**);

#define	CALL_LOADPE_FIRST					0xFFFF
#define	FILE_OPEN_FAILED					0x0010
#define	FILE_SIZE_TOO_SMALL					0x0011
#define	FILE_CREATE_FILE_MAPPING_FAILED		0x0012
#define	FILE_MAP_VIEW_OF_FILE_FAILED		0x0013
#define	IMAGE_TYPE_UNSUPPORTED				0x0014
#define	IMAGE_DOS_SIGNATURE_MISMATCH		0x0015
#define	IMAGE_HAS_NO_RICH_HEADER			0x0016
#define	IMAGE_NT_SIGNATURE_MISMATCH			0x0017
#define	IMAGE_HAS_NO_DATA_DIRECTORIES		0x0018
#define	IMAGE_HAS_NO_SECTIONS				0x0019
#define	IMAGE_HAS_NO_EXPORT_DIR				0x001A
#define	IMAGE_HAS_NO_IMPORT_DIR				0x001B
#define	IMAGE_HAS_NO_RESOURCE_DIR			0x001C
#define	IMAGE_HAS_NO_EXCEPTION_DIR			0x001D
#define	IMAGE_HAS_NO_SECURITY_DIR			0x001E
#define	IMAGE_HAS_NO_BASERELOC_DIR			0x001F
#define	IMAGE_HAS_NO_DEBUG_DIR				0x0020
#define	IMAGE_HAS_NO_ARCHITECTURE_DIR		0x0021
#define	IMAGE_HAS_NO_GLOBALPTR_DIR			0x0022
#define	IMAGE_HAS_NO_TLS_DIR				0x0023
#define	IMAGE_HAS_NO_LOADCONFIG_DIR			0x0024
#define	IMAGE_HAS_NO_BOUNDIMPORT_DIR		0x0025
#define	IMAGE_HAS_NO_IAT_DIR				0x0026
#define	IMAGE_HAS_NO_DELAY_IMPORT_DIR		0x0027
#define	IMAGE_HAS_NO_COMDESCRIPTOR_DIR		0x0028

#define IMAGE_HAS_FLAG(dword, flag) ((dword) & (flag))
#define IMAGE_PE32_FLAG						0x00000001
#define IMAGE_PE64_FLAG						0x00000002
#define IMAGE_DOS_HEADER_FLAG				0x00000004
#define IMAGE_RICH_HEADER_FLAG				0x00000008
#define IMAGE_NT_HEADER_FLAG				0x00000010
#define IMAGE_FILE_HEADER_FLAG				0x00000020
#define IMAGE_OPTIONAL_HEADER_FLAG			0x00000040
#define IMAGE_DATA_DIRECTORIES_FLAG			0x00000080
#define IMAGE_SECTION_HEADERS_FLAG			0x00000100
#define IMAGE_EXPORT_DIRECTORY_FLAG			0x00000200
#define IMAGE_IMPORT_DIRECTORY_FLAG			0x00000400
#define IMAGE_RESOURCE_DIRECTORY_FLAG		0x00000800
#define IMAGE_EXCEPTION_DIRECTORY_FLAG		0x00001000
#define IMAGE_SECURITY_DIRECTORY_FLAG		0x00002000
#define IMAGE_BASERELOC_DIRECTORY_FLAG		0x00004000
#define IMAGE_DEBUG_DIRECTORY_FLAG			0x00008000
#define IMAGE_ARCHITECTURE_DIRECTORY_FLAG	0x00010000
#define IMAGE_GLOBALPTR_DIRECTORY_FLAG		0x00020000
#define IMAGE_TLS_DIRECTORY_FLAG			0x00040000
#define IMAGE_LOADCONFIG_DIRECTORY_FLAG		0x00080000
#define IMAGE_BOUNDIMPORT_DIRECTORY_FLAG	0x00100000
#define IMAGE_IAT_DIRECTORY_FLAG			0x00200000
#define IMAGE_DELAYIMPORT_DIRECTORY_FLAG	0x00400000
#define IMAGE_COMDESCRIPTOR_DIRECTORY_FLAG	0x00800000