
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */

/* 内存相关函数封装:
 * malloc
 * free
 * memalign
 * posix_memalign
 * alloc: malloc + memzero
 *
 * 全局变量:
 * extern ngx_uint_t  ngx_pagesize;
 * extern ngx_uint_t  ngx_pagesize_shift;
 * extern ngx_uint_t  ngx_cacheline_size;
 *
 * 注意：
 * win32平台无内存对齐，需要调用ngx_memalign的函数，均用malloc代替
 * win32平台的代码不增加注释，因为nginx应用场景主要是Linux/Unix
 * */

#ifndef _NGX_ALLOC_H_INCLUDED_
#define _NGX_ALLOC_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


void *ngx_alloc(size_t size, ngx_log_t *log);
void *ngx_calloc(size_t size, ngx_log_t *log);

#define ngx_free          free


/*
 * Linux has memalign() or posix_memalign()
 * Solaris has memalign()
 * FreeBSD 7.0 has posix_memalign(), besides, early version's malloc()
 * aligns allocations bigger than page size at the page boundary
 */

#if (NGX_HAVE_POSIX_MEMALIGN || NGX_HAVE_MEMALIGN)

void *ngx_memalign(size_t alignment, size_t size, ngx_log_t *log);

#else

#define ngx_memalign(alignment, size, log)  ngx_alloc(size, log)

#endif


extern ngx_uint_t  ngx_pagesize;
extern ngx_uint_t  ngx_pagesize_shift;
extern ngx_uint_t  ngx_cacheline_size;


#endif /* _NGX_ALLOC_H_INCLUDED_ */
