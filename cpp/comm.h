#ifndef __COMM_H__
#define __COMM_H__

#ifdef WIN32
	#include <io.h>
	#include <process.h>
    #define _FUNCTION_ __func__
#else
	#include <unistd.h>
	#include <iconv.h>
    #define _FUNCTION_ __FUNCTION__
#endif


#endif