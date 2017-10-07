#ifndef _STDIO_H
#define _STDIO_H

#include <sys/cdefs.h>
#define __need____va_list
#include <stdarg.h>
#define __need_FILE
#define __need_size_t
#include <sys/libc-types.h>

#ifdef __cplusplus
extern "C"
{
#endif
		extern FILE* stderr;
#define stderr stderr
		
		int fflush(FILE*);
		int fprintf(FILE* __restrict, const char* __restrict, ...);

#define SEEK_SET 1
		int fclose(FILE*);
		FILE* fopen(const char* __restrict, const char* __restrict);
		size_t fread(void* __restrict, size_t, size_t, FILE* __restrict);
		int fseek(FILE*, long, int);
		long ftell(FILE*);
		size_t fwrite(const void* __restrict, size_t, size_t, FILE* __restrict);
		void setbuf(FILE* __restrict, char* __restrict);
		int vfprintf(FILE* __restrict, const char* __restrict, __gnuc_va_list);

#ifdef __cplusplus
}
#endif


#endif
