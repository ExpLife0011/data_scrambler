/*
 * 
 * Copyright (c) 2003, Michael Carruth All rights reserved.
 * This file is a part of CrashRpt library.
 *
 * Copyright 2010 JiJie Shi
 *
 * This file is part of data_scrambler.
 *
 * data_scrambler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * data_scrambler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with data_scrambler.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __COMMON_FUNC_H__
#define __COMMON_FUNC_H__

#include "crt_mem_leak_dbg.h"
#include "ntstatus_def.h"

#define INLINE __inline 

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif //_WIN32_WINNT

#define _WIN32_WINNT 0x0501

//#define INVALID_PROCESS_ID ( HANDLE )( -1 )

#define INVALID_PROCESS_ID ( HANDLE )( -1 )
#define INVALID_THREAD_ID ( HANDLE )( -1 )

#define RASBASE 600
#define ERROR_BUFFER_TOO_SMALL               (RASBASE+3)

//#define _abs( _x_ ) ( ( _x_ ) >= 0 ? ( _x_ ) : ( -_x_ ) )
#define _abs( val ) ( ( ( val ) >= 0 ) ? ( val ) : -( val ) )

#define MAX_WORK_TIME ( LONGLONG )( ( ( ( LONGLONG )24 * 3600 ) ) * 10000000 )

/*************file system define **********************/

#define MAX_NATIVE_PATH_PREFIX L"\\Device\\HarddiskVolume1\\"
#define MAX_NATIVE_NAME_SIZE ( MAX_PATH + ARRAY_SIZE( MAX_NATIVE_PATH_PREFIX ) )

/******************************************************/

//#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//#undef WIN32_NO_STATUS

#ifndef XMLFILE_ENCODING
#define XMLFILE_ENCODING
enum
{
	XMLFILE_ENCODING_UTF8 = 0,
	XMLFILE_ENCODING_UNICODE = 1,
	XMLFILE_ENCODING_ASNI = 2,
};
#endif //XMLFILE_ENCODING

#define MAX_NUMBER_TEXT_LEN 32

#include <winioctl.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <commctrl.h>
#include <tchar.h>
#include <stdio.h>
#include <errno.h>
#include <commdlg.h>
#include <strsafe.h>
#include <WinVer.h>

#ifndef DUI_LIB
#define DUI_LIB
#endif //DUI_LIB

#ifndef BITSAFE_TEST_TOOL
#include "error_code.h"
#endif //BITSAFE_TEST_TOOL

//#include "sevenfw_err_code.h"

#ifdef __cplusplus
#ifndef DUI_LIB
#include <comdef.h>
#include <atlbase.h>
#include <atlcom.h>
#include <atlapp.h>
#include <atlcrack.h>
#include <atlwin.h>
#include <atlctrls.h>
#include <AtlCtrlx.h>
#include <atlCtrlw.h>
#include <atlmisc.h>
#include <atlframe.h>
#include <atlddx.h>
#include <atlframe.h>
#include <atldlgs.h>
#include "ui_base_tab.h"
#endif //DUI_LIB
#endif //_cplusplus

#ifndef __success
#define __success(x)
#endif //__success

//don't have these macro definition in other compilation environment that's in other computer.

#define PATH_DELIM L'\\'
#define PATH_DELIM_CHAR '\\'
//
// masks for version macros
//
#define OSVERSION_MASK      0xFFFF0000
#define SPVERSION_MASK      0x0000FF00
#define SUBVERSION_MASK     0x000000FF

//
// macros to extract various version fields from the NTDDI version
//
#define OSVER(Version)  ((Version) & OSVERSION_MASK)
#define SPVER(Version)  (((Version) & SPVERSION_MASK) >> 8)
#define SUBVER(Version) (((Version) & SUBVERSION_MASK) )

typedef __success(return >= 0) LONG NTSTATUS;
/*lint -save -e624 */  // Don't complain about different typedefs.
typedef NTSTATUS *PNTSTATUS;
/*lint -restore */  // Resume checking for different typedefs.

#define UPDATE_FILE_NAME _T( "BitSafeUpdate.exe" )
#define DAT_FILE_RES_TYPE _T( "DAT_FILE" )
typedef struct _UNICODE_STRING
{
	USHORT Length; 
	USHORT MaximumLength; 
	LPWSTR Buffer; 
} UNICODE_STRING, *PUNICODE_STRING; 
typedef const UNICODE_STRING *PCUNICODE_STRING;

//
#define MAX_ROOT_NAME_LEN 256
#define MAX_REPLACE_NAME_LEN 64

typedef struct _root_key {
	WCHAR root_name[ MAX_ROOT_NAME_LEN ];
	WCHAR short_name[ MAX_REPLACE_NAME_LEN ];
	ULONG root_name_len; 
	ULONG short_name_len; 
} root_key, *proot_key;

#ifndef ARRAYSIZE
#define ARRAYSIZE( array ) ( sizeof( array ) /sizeof( ( array )[ 0 ] ) )
#endif //ARRAYSIZE

#define ARRAY_SIZE( array ) ( DWORD )( sizeof( array ) / sizeof( ( array )[ 0 ] ) )
#define CONST_STR_LEN( str ) ( ( sizeof( str ) / sizeof( ( str )[ 0 ] ) ) - 1 )

#ifndef ERROR_ERRORS_ENCOUNTERED
#define ERROR_ERRORS_ENCOUNTERED 0xC0000001 
#endif //ERROR_ERRORS_ENCOUNTERED

#define SAFE_SET_ERROR_CODE( ret_val ) ret_val = GetLastError(); if( ret_val == ERROR_SUCCESS ) { log_trace( ( MSG_ERROR, "!!!!the last error code is the success code \n" ) ); ret_val = ERROR_ERRORS_ENCOUNTERED; } 
#define SAFE_SET_SOCKET_ERROR_CODE( ret_val ) ret_val = WSAGetLastError(); if( ret_val == ERROR_SUCCESS ) { log_trace( ( MSG_ERROR, "!!!!the last error code is the success code \n" ) ); ret_val = ERROR_ERRORS_ENCOUNTERED; } 

#ifdef _DEBUG
#define DebugTrace( x ) OutputDebugString( x )
#else
#define DebugTrace( x ) 
#endif //_DEBUG

#ifdef _DEBUG
#ifdef ASSERT
#undef ASSERT
#endif //ASSERT

#include <assert.h>
#define ASSERT( x ) assert( x )
#else
#ifdef ASSERT
#undef ASSERT
#endif //ASSERT
#define ASSERT( x )
#endif //_DEBUG

#define INLINE __inline

#define MODE_DEBUG_OUTPUT 0x01
#define MODE_MESSAGE_BOX 0x02

typedef unsigned long ULONG, *PULONG; 
typedef int INT32; 
typedef unsigned char BYTE, *PBYTE; 

typedef struct _DISK_NAME_MAP
{
	CHAR sign[ 3 ]; 
	CHAR dev_name[ 64 ]; 
} DISK_NAME_MAP, *PDISK_NAME_MAP; 

#ifdef __cplusplus
extern "C"
{
#endif 

	INLINE NTSTATUS is_valid_mem_region( PVOID addr, ULONG buf_size )
	{
		NTSTATUS ntstatus = STATUS_SUCCESS; 
		INT32 ret; 

		do 
		{
			ret = IsBadReadPtr( addr, buf_size ); 

			if( ret == TRUE )
			{
				ntstatus = STATUS_INVALID_PARAMETER_1; 
				break; 
			}

		}while( FALSE );

		return ntstatus; 
	}

	LRESULT WINAPI disable_wow_64( LPVOID* dwOldValue ); 
	
	LRESULT WINAPI revert_wow_64( LPVOID dwOldValue ); 

	INLINE LRESULT check_file_exist( LPCTSTR file_name )
	{
		LRESULT ret = ERROR_SUCCESS; 
		HANDLE file_handle; 

		ASSERT( file_name != NULL ); 

		file_handle = CreateFile( file_name,
			0,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			); 

		if( file_handle == INVALID_HANDLE_VALUE )
		{
			ret = GetLastError(); 
			if( ret != ERROR_FILE_NOT_FOUND 
				&& ret != ERROR_PATH_NOT_FOUND )
			{
				ret = ERROR_SUCCESS; 
			}

			goto _return; 
		}

		CloseHandle( file_handle ); 
_return:
		return ret; 
	}

	INLINE LRESULT check_dir_exist( LPCTSTR file_name )
	{
		LRESULT ret = ERROR_SUCCESS; 
		HANDLE file_handle; 

		ASSERT( file_name != NULL ); 

		file_handle = CreateFile( file_name,
			0,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_DIRECTORY,
			NULL
			); 

		if( file_handle == INVALID_HANDLE_VALUE )
		{
			ret = GetLastError(); 
			if( ret != ERROR_FILE_NOT_FOUND 
				&& ret != ERROR_PATH_NOT_FOUND )
			{
				ret = ERROR_SUCCESS; 
			}

			goto _return; 
		}

		CloseHandle( file_handle ); 
_return:
		return ret; 
	}

	INLINE VOID lock_cr( CRITICAL_SECTION *lock )
	{
		ASSERT( lock != NULL ); 

		EnterCriticalSection( lock ); 
	}

	INLINE VOID unlock_cr( CRITICAL_SECTION *lock )
	{
		ASSERT( lock != NULL ); 

		LeaveCriticalSection( lock ); 
	}

	LRESULT get_all_proc_list( PROCESSENTRY32 *proc_entrys, ULONG max_entry_num, ULONG *entry_num_output ); 

LRESULT safe_create_dir( LPCTSTR tmp_dir_path, LPCTSTR dir_path ); 

#include <malloc.h>
FORCEINLINE size_t mem_block_size( PVOID _block_ ) 
{
	return _msize( _block_ ); 
}

//INLINE PVOID realloc_safe( PVOID old_block, ULONG old_size, ULONG size )
//{
//	PVOID block = NULL; 
//	ULONG copy_size; 
//
//	do 
//	{
//		block = malloc( size ); 
//		if( block == NULL )
//		{
//			if( old_block != NULL )
//			{
//				free( old_block ); 
//			}
//
//			break; 
//		}
//
//		if( old_size < size )
//		{
//			memcpy( block, old_block, old_size ); 
//		}
//		else
//		{
//			memcpy( block, old_block, size ); 
//		}
//
//		free( old_block ); 
//
//	}while( FALSE );
//
//	return block; 
//}

//INT32 prepend_app_path( LPCWSTR file_name, LPWSTR file_name_out, ULONG buf_len ); 

INT32 _tcsdigit( LPCTSTR str ); 
INT32 error_handle( LPCSTR msg, DWORD mode, DWORD flags );
BOOL windows_shutdown(UINT uFlags); 
BOOL windows_hibernate(); 
LRESULT add_sys_drv_path_to_file_name( LPTSTR file_name_out, ULONG buf_len, LPCTSTR file_name, INT32 chk_exist ); 
LRESULT add_app_path_to_file_name( LPTSTR file_name_out, ULONG cc_buf_len, LPCTSTR file_name, INT32 chk_exist ); 
LRESULT add_app_sub_dir_path_to_file_name( LPTSTR file_name_out, ULONG buf_len, LPCTSTR sub_dir,  LPCTSTR file_name, INT32 chk_exist ); 

INT32 get_proc_img_path( DWORD dwProcessId, LPWSTR FileName, DWORD dwFileNameLen, LPWSTR NativeFileName, DWORD dwNativeFileNameLen ); 
LRESULT file_exists( LPCTSTR file_name, INT32 is_sys_path ); 
LRESULT WINAPI adjust_proc_token();  
INT32 show_popup_menu( HWND hwnd, ULONG menu_id ); 

LRESULT _mcbs_to_unicode( UINT32 code_page, LPCSTR mcbs, LPWSTR unicode, ULONG cch_len, PULONG ret_len ); 
LRESULT _unicode_to_mcbs( UINT32 code_page, LPCWSTR unicode, LPSTR mcbs, ULONG cch_len, PULONG ret_len ); 

INLINE LRESULT mcbs_to_unicode( LPCSTR mcbs, LPWSTR unicode, ULONG cch_len, PULONG ret_len )
{
	return _mcbs_to_unicode( CP_ACP, mcbs, unicode, cch_len, ret_len ); //CP_OEMCP
}

INLINE LRESULT unicode_to_mcbs( LPCWSTR unicode, LPSTR mcbs, ULONG cch_len, PULONG ret_len ) 
{
	return _unicode_to_mcbs( CP_ACP, unicode, mcbs, cch_len, ret_len ); 
}

INLINE LRESULT utf8_to_unicode( LPCSTR mcbs, LPWSTR unicode, ULONG cch_len, PULONG ret_len )
{
	return _mcbs_to_unicode( CP_UTF8, mcbs, unicode, cch_len, ret_len ); 
}

INLINE LRESULT unicode_to_utf8( LPCWSTR unicode, LPSTR mcbs, ULONG cch_len, PULONG ret_len ) 
{
	return _unicode_to_mcbs( CP_UTF8, unicode, mcbs, cch_len, ret_len ); 
}

LRESULT init_op_temp_buf( OUT PBYTE *buf, IN ULONG len, OUT PULONG out_len ); 

#define CREATE_FILE_ERR -11
LRESULT read_file( ULONG pos, PVOID data, ULONG data_len, LPCTSTR file_name ); 
LRESULT write_file( ULONG pos, PVOID data, ULONG data_len, LPCTSTR file_name ); 

LRESULT get_tmp_file_name( LPTSTR file_name, ULONG buf_len ); 

LRESULT clone_start_self(); 
LRESULT start_clone_process(); 
LRESULT run_proc_sync( LPCTSTR cmd_line ); 
LRESULT run_proc( LPCTSTR cmd_line, ULONG *proc_id ); 
LRESULT construct_file_path_a( LPSTR file_name_out, ULONG size, LPCSTR dir_path, LPCSTR file_name ); 
LRESULT construct_file_path_w( LPWSTR file_name_out, ULONG size, LPCWSTR dir_path, LPCWSTR file_name ); 

#ifdef _UNICODE
#define construct_file_path construct_file_path_w
#else
#define construct_file_path construct_file_path_a
#endif //_UNICODE

LRESULT create_file_from_res( HINSTANCE hResMod, 
						   LPCTSTR pszName, 
						   LPCTSTR pszType, 
						   LPCTSTR pszSysFile, 
						   INT32 sys_path ); 
void write_log( LPCSTR log_file, char* msg ); 
LRESULT create_share_mem( DWORD size, LPCTSTR name, HANDLE *mem_handle, PVOID *mem_addr ); 
LRESULT open_share_mem( LPCTSTR name, HANDLE *mem_handle, PVOID *mem_addr ); 
VOID close_share_mem( HANDLE mem_handle, PVOID mem_addr ); 
LRESULT get_sys_info( __out LPSYSTEM_INFO sys_info ); 
LRESULT is_wow64_proc( INT32 *is_wow64 ); 
LRESULT get_sys_bits( INT32 *os_bit_out, INT32 *wow64_out ); 
INLINE INT32 get_proc_bits()
{
	return sizeof( INT32* ) * 8; 
}

VOID uninit_op_temp_buf( IN OUT PBYTE *buf, IN OUT PULONG len ); 
#define REALLOC_INC_LEN 4096

LRESULT realloc_if_need( PBYTE *buf, ULONG len, PULONG max_len, ULONG need_len ); 

LRESULT str_2_ipv4_addr( LPCTSTR ip_addr, ULONG *output ); 
LRESULT str_2_port( LPCTSTR port, USHORT *output ); 
LRESULT ip_addr_2_str( ULONG ip_addr, TCHAR *buf, ULONG buf_len ); 
LRESULT port_2_str( USHORT port, TCHAR *buf, ULONG buf_len ); 

LRESULT enum_symbolic_links( WCHAR *sym_name, WCHAR *dev_name, ULONG buf_len ); 
LRESULT get_disk_dev_name(); 
CHAR *find_dev_name( CHAR *sign_name ); 

#ifdef __cplusplus
}
#endif

#define lock_cs( locker ) EnterCriticalSection( &( locker ) ); 
#define unlock_cs( locker ) LeaveCriticalSection( &( locker ) ); 
#define init_cs_lock( locker ) InitializeCriticalSection( &( locker ) );
#define uninit_cs_lock( locker ) DeleteCriticalSection( &( locker ) ); 

#define wait_event( event, wait_time ) WaitForSingleObject( event, wait_time )
#define signal_event( event ) SetEvent( event )
#define init_event() CreateEvent( NULL, FALSE, FALSE, NULL )
#define uninit_event( event ) CloseHandle( event )

INLINE LPCSTR get_wait_ret_desc( DWORD wait_ret )
{
	LPCSTR ret_desc = ""; 
	switch( wait_ret )
	{
	case WAIT_OBJECT_0:
		ret_desc = "WAIT_OBJECT_0"; 
		break; 
	case WAIT_TIMEOUT:
		ret_desc = "WAIT_TIMEOUT"; 
			break; 
	case WAIT_ABANDONED:
		ret_desc = "WAIT_ABANDONED"; 
			break; 
	case WAIT_FAILED:
		ret_desc = "WAIT_FAILED"; 
			break; 
	default:
		ASSERT( FALSE ); 
		break; 
	}

	return ret_desc; 
}

INLINE VOID uninit_mutex( HANDLE mutex )
{
	CloseHandle( mutex ); 
}

#ifndef InitializeListHead
//
//  VOID
//  InitializeListHead(
//      PLIST_ENTRY ListHead
//      );
//

#define InitializeListHead(ListHead) (\
    (ListHead)->Flink = (ListHead)->Blink = (ListHead))

//
//  BOOLEAN
//  IsListEmpty(
//      PLIST_ENTRY ListHead
//      );
//

#define IsListEmpty(ListHead) \
    ((ListHead)->Flink == (ListHead))

//
//  PLIST_ENTRY
//  RemoveHeadList(
//      PLIST_ENTRY ListHead
//      );
//

#define RemoveHeadList(ListHead) \
    (ListHead)->Flink;\
    {RemoveEntryList((ListHead)->Flink)}

//
//  PLIST_ENTRY
//  RemoveTailList(
//      PLIST_ENTRY ListHead
//      );
//

#define RemoveTailList(ListHead) \
    (ListHead)->Blink;\
    {RemoveEntryList((ListHead)->Blink)}

//
//  VOID
//  RemoveEntryList(
//      PLIST_ENTRY Entry
//      );
//

#define RemoveEntryList(Entry) {\
    PLIST_ENTRY _EX_Blink;\
    PLIST_ENTRY _EX_Flink;\
    _EX_Flink = (Entry)->Flink;\
    _EX_Blink = (Entry)->Blink;\
    _EX_Blink->Flink = _EX_Flink;\
    _EX_Flink->Blink = _EX_Blink;\
    }

//
//  VOID
//  InsertTailList(
//      PLIST_ENTRY ListHead,
//      PLIST_ENTRY Entry
//      );
//

#define InsertTailList(ListHead,Entry) {\
    PLIST_ENTRY _EX_Blink;\
    PLIST_ENTRY _EX_ListHead;\
    _EX_ListHead = (ListHead);\
    _EX_Blink = _EX_ListHead->Blink;\
    (Entry)->Flink = _EX_ListHead;\
    (Entry)->Blink = _EX_Blink;\
    _EX_Blink->Flink = (Entry);\
    _EX_ListHead->Blink = (Entry);\
    }

//
//  VOID
//  InsertHeadList(
//      PLIST_ENTRY ListHead,
//      PLIST_ENTRY Entry
//      );
//

#define InsertHeadList(ListHead,Entry) {\
    PLIST_ENTRY _EX_Flink;\
    PLIST_ENTRY _EX_ListHead;\
    _EX_ListHead = (ListHead);\
    _EX_Flink = _EX_ListHead->Flink;\
    (Entry)->Flink = _EX_Flink;\
    (Entry)->Blink = _EX_ListHead;\
    _EX_Flink->Blink = (Entry);\
    _EX_ListHead->Flink = (Entry);\
    }

#define LIST_OPERA_DEFINED

#define ListView_InsertItemA(hWnd, pitem)   \
    (int)SNDMSG((hWnd), LVM_INSERTITEMA, 0, (LPARAM)(const LV_ITEM *)(pitem))
#define ListView_InsertItemW(hWnd, pitem)   \
    (int)SNDMSG((hWnd), LVM_INSERTITEMW, 0, (LPARAM)(const LV_ITEM *)(pitem))

#define ListView_SetItemA(hWnd, pitem) \
    (BOOL)SNDMSG((hWnd), LVM_SETITEMA, 0, (LPARAM)(const LV_ITEM *)(pitem))
#define ListView_SetItemW(hWnd, pitem) \
    (BOOL)SNDMSG((hWnd), LVM_SETITEMW, 0, (LPARAM)(const LV_ITEM *)(pitem))

#endif //InitializeListHead

#define DBG_BRK() //__asm int 3; 

typedef enum _IO_DIRECTION
{
	IO_INPUT_TO_DATA, 
	IO_OUTPUT_FROM_DATA, 
	MAX_IO_DIRECTION, 
} IO_DIRECTION, *PIO_DIRECTION; 

#ifdef _DEBUG
#ifdef _WIN64
#define DBG_BP() DebugBreak(); 
#else
#define DBG_BP() //__asm int 3; 
#endif //_WIN64
#else
#define DBG_BP() 
#endif //_DEBUG

#define MAX_LOG_FILE_SIZE ( INT32 )( 1024 * 1024 )

#define DBG_CONSOLE_OUT 0x00010000
#define DBG_LOG_OUT 0x00020000
#define DBG_DBG_BUF_OUT 0x00040000
#define DBG_ERROR_MSG 0x00080000
#define DBG_MSG_BOX_OUT 0x00100000
#define DBG_INTERNET_ERR 0x00200000
#define DBG_SOCKET_ERR 0x00400000

#define DBG_MSG_AND_ERROR_OUT ( MSG_ERROR | DBG_DBG_BUF_OUT | DBG_ERROR_MSG )
#define DBG_INET_MSG_AND_ERROR_OUT ( DBG_INTERNET_ERR | DBG_MSG_AND_ERROR_OUT )
#define DBG_SOCKET_ERROR_OUT ( DBG_SOCKET_ERR | DBG_MSG_AND_ERROR_OUT )

#define MSG_INFO 0
#define MSG_WARNING 1
#define MSG_ERROR 2
#define MSG_FATAL_ERROR 3
#define MSG_IMPORTANT 3
#define MSG_MAX_LEVEL 4

#define DUMP_MEM dump_mem

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

	BOOL is_xp_last(); 
	BOOL is_win64(); 
	BOOL is_downloaded_file( LPCTSTR lpPath ); 

	LRESULT dbg_print(
		ULONG lvl_and_mode,
		LPCSTR dbg_msg,
		...
		);

	LRESULT dbg_print_w(
		ULONG lvl_and_mode,
		LPCWSTR dbg_msg,
		... ); 

#ifdef _DEBUG

#ifdef LOG_THREAD_SAFE
	VOID init_log_context(); 
	VOID uninit_log_context(); 
	VOID logger_lock(); 
	VOID logger_unlock(); 
#endif //LOG_THREAD_SAFE


#define log_trace_file_line( _x_ ) \
	{ \
		dbg_print( "FILE:%s\t\tLINE:%d\t\t", __FILE__, __LINE__ );\
		dbg_print _x_; \
	} \

#define log_trace(x) dbg_print x
#define log_trace_ex( _msg_level_, _msg_,...) { dbg_print( _msg_level_, "(%s:%d) "_msg_"\n", __FUNCTION__, __LINE__, __VA_ARGS__ ); }

#else //_DEBUG

#ifdef PUBLISH
#define log_trace(x) 
#define log_trace_ex( msg,...) 
#else
#define log_trace(x) dbg_print x 
#define log_trace_ex( _msg_level_, _msg_,...) { dbg_print( _msg_level_, "(%s:%d) "_msg_"\n", __FUNCTION__, __LINE__, __VA_ARGS__ ); }
#endif //PUBLISH

#endif //_DEBUG

#ifdef _USE_WINSOCK
	LRESULT init_socket_env(); 
	VOID uninit_socket_env(); 
#endif //_USE_WINSOCK


	INLINE LRESULT init_mutex( HANDLE *mutex_out )
	{
		LRESULT ret = ERROR_SUCCESS; 
		HANDLE mutex; 

		ASSERT( mutex_out != NULL ); 
		*mutex_out = NULL; 

		//#if 0
		//	mutex = CreateMutexEx( NULL, NULL, CREATE_MUTEX_INITIAL_OWNER, MUTEX_ALL_ACCESS ); 
		//#endif 

		mutex = CreateMutex( NULL, FALSE, NULL ); ; 

		if( mutex == NULL )
		{
			SAFE_SET_ERROR_CODE( ret ); 
			goto _return; 
		}

		*mutex_out = mutex; 

_return:
		return ret; 
	}

	INLINE size_t __cdecl wcsnlen(const wchar_t *wcs, size_t maxsize)
	{
		size_t n;

		/* Note that we do not check if s == NULL, because we do not
		* return errno_t...
		*/

		for (n = 0; n < maxsize && *wcs; n++, wcs++)
			;

		return n;
	}

	INLINE LRESULT lock_mutex( HANDLE mutex )
	{
		LRESULT ret = ERROR_SUCCESS; 
		DWORD wait_ret; 

		wait_ret = WaitForSingleObject( mutex, INFINITE ); 
		if( wait_ret != WAIT_OBJECT_0 )
		{
			if( wait_ret != WAIT_TIMEOUT 
				&& wait_ret != WAIT_ABANDONED )
			{
				log_trace( ( DBG_MSG_AND_ERROR_OUT, "wait syncronous event failed will exit\n" ) ); 
				SAFE_SET_ERROR_CODE( ret ); 
				goto _return; 
			}

			log_trace( ( MSG_ERROR, "wait the mutex failed %s( 0x%0.8x )\n", get_wait_ret_desc( wait_ret ), wait_ret ) ); 

			ret = ERROR_ERRORS_ENCOUNTERED; 
			goto _return; 
		}

_return:
		return ret; 
	}

	INLINE LRESULT unlock_mutex( HANDLE mutex )
	{
		LRESULT ret = ERROR_SUCCESS; 
		BOOL _ret; 

		ASSERT( mutex != NULL ); 
		_ret = ReleaseMutex( mutex ); 
		if( _ret == FALSE )
		{
			SAFE_SET_ERROR_CODE( ret ); 
			goto _return; 
		}

_return:
		return ret; 
	}

//#define DBGPRINT( _x_ ) OutputDebugStringA _x_

	FORCEINLINE void dump_mem(void *mem, int size)
	{
		unsigned char str[20];
		unsigned char *m = ( BYTE* )mem;
		int i,j;

		for (j = 0; j < size / 8; j++)
		{
			memset (str,0,sizeof str);
			for (i = 0; i < 8; i++) 
			{
				if (m[i] > ' ' && m[i] <= '~')
					str[i]=m[i];
				else
					str[i]='.';
			}

			log_trace( ( MSG_INFO, "0x%0.8x  %0.2x %0.2x %0.2x %0.2x %0.2x %0.2x %0.2x %0.2x  %s\n",
				m, m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], str ) );

			m+=8;
		}

		//memset (str,0,sizeof str); 
		for (i = 0; i < ( size % 8 ); i++) 
		{
			if (m[ i ] > ' ' && m[i] <= '~')
				str[i]=m[i];
			else
				str[i]='.';
		}

		str[ i ] = '\0';

		log_trace( ( MSG_INFO, "0x%0.8x  ", m ) );
		for (i = 0; i < ( size % 8 ); i++) 
		{
			log_trace( ( MSG_INFO, "%0.2x ", m[ i ] ) );
		}

		log_trace( ( MSG_INFO, "%s \n", str ) );
	}

	VOID dump_data( PVOID data, ULONG len ); 

	FORCEINLINE VOID print_ip_addr( ULONG *IPAddr )
	{
		BYTE *_IPAddr = ( BYTE* )IPAddr;
		log_trace( ( MSG_INFO, "%d.%d.%d.%d \n", 
			*_IPAddr, 
			*( _IPAddr + 1 ), 
			*( _IPAddr + 2 ), 
			*( _IPAddr + 3 )
			) );
	}

	
	INLINE LRESULT start_thread( PTHREAD_START_ROUTINE thread_proc, PVOID thread_arg, HANDLE *kthread )
	{
		//CreateThread()
		;return ERROR_SUCCESS; 
	}

	INLINE LRESULT stop_thread( HANDLE thread, HANDLE wakeup_event )
	{
		//NTSTATUS ntstatus; 

		ASSERT( thread != NULL ); 

		if( NULL != wakeup_event )
		{
			SetEvent( wakeup_event/*, IO_NO_INCREMENT, FALSE */);
		}

		//ntstatus = WaitForSingleObject( thread, Executive, KernelMode, FALSE, NULL );

		return ERROR_SUCCESS; 
	}

	INT32 WINAPI is_vista_or_later(); 
	INT32 WINAPI check_uac_opened(); 
	LRESULT get_user_path( LPWSTR file_name, ULONG buf_len ); 
	LRESULT get_desktop_path( LPWSTR file_name, ULONG buf_len ); 
	LRESULT get_win_ver_info( OSVERSIONINFOEX *osvi ); 
	LRESULT fix_win_ver_info( OSVERSIONINFOEX *osvi ); 
	INT32 parse_win_ver( OSVERSIONINFOEX *osvi ); 
	LRESULT get_win_ver( INT *nWindowsVersion, INT *nSP ); 
	/**
	* @retval   >0  current OS is greater than compared version
	* @retval   <0  current OS is less than compared version
	* @retval   0   current OS is equal to compared version
	*/
	INT32 compare_win_ver(DWORD dwMajorVer, DWORD dwMinorVer); 
	
	enum E_WinVersion 
	{
		WINUNKNOWN = 0,
		WIN32S,
		WIN95,
		WIN98,
		WINME,
		WINNT,
		WIN2K,
		WINXP,
		WIN2003,
		WINVISTA,
		WIN7,
		WIN2005,
		WIN2008,
		WIN2008R2,
	};

	enum {
		em_OS_MajorVer_Vista    = 6,
		em_OS_MajorVer_Win2k3   = 5,
		em_OS_MajorVer_WinXP    = 5,

		em_OS_MinorVer_Win2k3   = 2,
		em_OS_MinorVer_WinXP    = 1,
	};

	BOOL is_vista_or_later_ex(); 

#define FILE_APP_DIR 0x00000000
#define FILE_SYS_DIR 0x00000001
#define FILE_IS_WHOLE_PATH 0x00000002
#define FILE_TARGET_DIR 0x00000003

	LRESULT delete_file_spec_dir( LPCTSTR file_name, ULONG flags ); 

	LRESULT create_global_name( LPCWSTR name, HANDLE *name_handle ); 
	LRESULT check_global_name_exist( LPCWSTR name, HANDLE *name_handle ); 
	LRESULT close_global_name( LPCWSTR name, HANDLE name_handle ); 

	typedef LRESULT ( CALLBACK *file_found_callback )( LPCTSTR root_path, WIN32_FIND_DATA *find_data, PVOID context ); 

	LRESULT find_whole_path( LPCTSTR file_path, file_found_callback on_file_found, PVOID context ); 
	INT32 hex_dump_to_buf( PVOID data, ULONG len, PVOID buf, ULONG buf_len ); 

	typedef LRESULT ( CALLBACK *data_download_callback )( PVOID data, 
		ULONG all_data_len, 
		ULONG read_len, 
		ULONG downloaded, 
		ULONG download_time, 
		PVOID context ); 

	LRESULT recv_data_from_internet( LPCSTR url, PVOID data, ULONG read_len, ULONG *readed_len, data_download_callback download_tip_func, PVOID context ); 
	LRESULT get_file_version( LPCTSTR file_name, LARGE_INTEGER *version ); 
	LRESULT output_file_from_res( HINSTANCE hResMod, LPCTSTR pszName, LPCTSTR pszType, LPCTSTR file_name ); 

#define DBG_MODE_MASK 0xffff0000
#define DBG_LVL_MASK 0x0000ffff
#define DBG_LVL_VALUE_PART_MASK 0x0000000f
#define DBG_LVL_NONE_PRINT 0x0000000f
#define DBG_LVL_ALL_VALUE_PRINT 0x00000000
#define DBG_LVL_ALL_MASK_PRINT 0xffffffff
#define DBG_LVL_ALL_PRINT ( ~DBG_LVL_VALUE_PART_MASK )

	VOID set_dbg_log_level( ULONG lvl ); 

	INT32 compare_str( LPCWSTR src_str, ULONG src_str_len, LPCWSTR dest_str, ULONG dest_str_len ); 

	ULONG get_dbg_log_level(); 
	LPCWSTR find_sub_str( LPCWSTR src_str, ULONG src_str_len, LPCWSTR dest_str, ULONG dest_str_len, ULONG find_time ); 

#define DUMP_MEM_ADDR 0x00000001

	LRESULT _dump_mem_in_buf_w( WCHAR *dump_to_buf, ULONG buf_ccb_len, USHORT ln_byte, void *mem, int size, ULONG flags ); 

#define DEF_DUMP_LINE_BYTE_COUNT 12
	INLINE LRESULT dump_mem_in_buf_w( WCHAR *dump_to_buf, ULONG buf_ccb_len, void *mem, int size, ULONG flags )
	{
		return _dump_mem_in_buf_w( dump_to_buf, buf_ccb_len, DEF_DUMP_LINE_BYTE_COUNT, mem, size, flags ); 
	}

	LRESULT dump_mem_in_buf( CHAR *dump_to_buf, ULONG buf_len, void *mem, int size ); 

	typedef struct _PRIORITY_INFO
	{
		ULONG OldPriority; 
		ULONG OldPriorityClass; 
	}PRIORITY_INFO, *PPRIORITY_INFO; 

	INT32 RiseThreadPriority( PRIORITY_INFO *PriorityInfo ); 
	INT32 LowerThreadPriority( PRIORITY_INFO *PriorityInfo ); 

	LRESULT init_std_lib_mbc_local_lang(); 

	LRESULT WINAPI string_to_time( LPCWSTR text, LARGE_INTEGER *time ); 

	#define TIME_FIELD_COUNT 7
	LRESULT WINAPI string_to_local_time( LPCWSTR text, LARGE_INTEGER *time ); 

	LRESULT WINAPI sprint_file_time( LPWSTR text, ULONG cch_buf_len, FILETIME *time ); 

	#define CHECK_DIRECTORY 0x000000001

	INT32 WINAPI create_directory_ex( LPWSTR FilePath, ULONG FilePathLen, ULONG BeginDirLevel ); 

	INLINE LRESULT WINAPI time_to_local_time( LARGE_INTEGER *time )
	{
		LRESULT ret = ERROR_SUCCESS; 
		INT32 _ret; 
		FILETIME file_time; 
		FILETIME local_file_time; 

		do 
		{
			ASSERT( time != NULL ); 

			file_time.dwHighDateTime = time->HighPart; 
			file_time.dwLowDateTime = time->LowPart; 

			//if return error, must be not change the value of the time. 

			_ret = FileTimeToLocalFileTime( &file_time, &local_file_time ); 
			if( _ret == FALSE )
			{
				SAFE_SET_ERROR_CODE( ret ); 
				break; 
			}

			time->HighPart = local_file_time.dwHighDateTime; 
			time->LowPart = local_file_time.dwLowDateTime; 

		}while( FALSE ); 

		return ret; 
	}

	LRESULT WINAPI sprint_time( LPWSTR text, ULONG ccb_buf_len, LARGE_INTEGER time ); 
	LRESULT WINAPI sprint_local_time( LPWSTR text, ULONG ccb_buf_len, LARGE_INTEGER time ); 

	LRESULT WINAPI check_time_valid( LARGE_INTEGER *time ); 

	LRESULT WINAPI open_folder_dlg( LPWSTR folder_path, ULONG cc_buf_len ); 

	INT32 WINAPI FindDiskFromBusType( LPCSTR BusTypeName, PULONG DeviceIndexes, ULONG BufCount, ULONG *RetCount ); 
	INT32 WINAPI IsUsbDevice( LPCSTR VolumeName ); 
	LRESULT WINAPI safe_disable_wow64( PVOID *wow_old_value ); 
	
	enum WinVerMajor

	{
		WIN_MAJOR_NT4_ME_98_95          = 4,
		WIN_MAJOR_2K3R2_2K3_XP_2K       = 5,
		WIN_MAJOR_WIN7_2K8R2_2K8_VISTA_WIN8_WIN2012  = 6,
	};



	// 定义目前存在的操作系统次版本号

	enum WinVerminor

	{
		WIN_MINOR_2K8_VISTA_2K_NT4_95   = 0,
		WIN_MINOR_WIN7_2K8R2_XP         = 1,
		WIN_MINOR_2K3R2_2K3_XP64_WIN8_WIN2012        = 2,
		WIN_MINOR_98                    = 10,
		WIN_MINOR_ME                    = 90,

	};

	typedef enum
	{
		WINX86,
		WINX64
	};

	typedef enum
	{
		OSWIN98,
		OSWIN2000,
		OSWINXP,
		OSWIN2003,
		OSWIN2003R2,
		OSWINVISTA,
		OSWIN2008,
		OSWIN2008R2,
		OSWIN7,
		OSWIN8,
		OSWIN2012,
		OSOTHER, 
		OSINVALID, 
	};

	INT32 WINAPI get_windows_os_version_build_num(); 
	INT32 WINAPI get_windows_os_version(); 

	INT32 _get_file_version( LPCWSTR FileName, 
		VS_FIXEDFILEINFO* FixedFileInfo ); 

#define INVALID_DISK_NO ( ULONG )( -1 )

	INT32 WINAPI GetDiskNumbers( HANDLE VolumeDev, 
		ULONG *DiskNumbers, 
		ULONG Count, 
		ULONG *RetCount ); 

	wchar_t * __cdecl wcsistr (
		const wchar_t * wcs1,
		const wchar_t * wcs2
		); 

	LRESULT WINAPI send_copy_data_message( HWND taget_wnd, 
		LPVOID data, 
		ULONG data_size ); 

	typedef struct _thread_manage
	{
		INT32 stop_run; 
		HANDLE thread_handle;
		DWORD id;
		HANDLE notify; 
		BOOLEAN self_notify; 
		PVOID param;
		PVOID context; 
	} thread_manage, *pthread_manage; 

	LRESULT _create_work_thread( thread_manage *work_thread, 
		PTHREAD_START_ROUTINE thread_routine, 
		HANDLE notifier, 
		PVOID context, 
		PVOID param ); 

	FORCEINLINE LRESULT create_work_thread( thread_manage *work_thread, 
		PTHREAD_START_ROUTINE thread_routine, 
		PVOID context, 
		PVOID param )
	{
		return _create_work_thread( work_thread, thread_routine, NULL, context, param ); 
	}

	LRESULT stop_work_thread( thread_manage *work_thread ); 

	LRESULT WINAPI hex2text(IN PVOID data,IN DWORD data_len,IN OUT LPWSTR text,IN DWORD cc_buf_len); 

	INLINE VOID wait_loop()
	{
		for( ; ; )
		{
			Sleep( 1 ); 
		}
	}

#define LINE_TERM L"\r\n" 
#define LINE_TERM_A "\r\n" 
#define LINE_TERM_LEN ( CONST_STR_LEN( LINE_TERM ) )

#define ERR_EXCEED_MAX_LN_LEN -141
#define ERR_DISCONNECT -142

#define TEXT_POOL_LEN ( 4096 * 4 )

	INT32 WINAPI memmem( CHAR* mem_find, LONG mem_find_len, CHAR* mem, LONG memlen ); 
	INT32 WINAPI read_line_continue( HANDLE file, LPSTR line, LPSTR pool_backup, ULONG *remain_len, ULONG buf_len ); 
	INT32 WINAPI read_line_continue_w( HANDLE file, 
		LPWSTR line, 
		LPWSTR pool_backup, 
		ULONG *remain_len, 
		ULONG buf_len ); 

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__COMMON_FUNC_H__