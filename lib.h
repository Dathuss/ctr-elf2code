#define _LARGEFILE_SOURCE
#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <dirent.h>
#include <wchar.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>

	
#ifdef _WIN32
	#include <io.h>
	#include <direct.h>
	#include <windows.h>
#endif


#include "types.h"
#include "utils.h"
#include "ncch_build.h"