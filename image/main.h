#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/time.h>
#include <unistd.h>
#include <CL/cl.h>

#define VEC_LENG 4096

// ANSI TYPE COLOR DEFINE //

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_BLACK "\xlb[30m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

//////////// Error Message ///////////

#define CHECK_ERROR(err) \
	if ( err != CL_SUCCESS ) { \
		printf(ANSI_COLOR_RED "[ERR][%s:%d]\t\tOpenCL error %d\n" ANSI_COLOR_RESET, __FILE__, __LINE__, err); \
		exit(EXIT_FAILURE); \
	}
//////////////////////////////////////

/////////// message Part /////////////

#define INITMSG(msg) \
	printf(ANSI_COLOR_GREEN \
		   "[INIT]\t\t%s\n" \
		   ANSI_COLOR_RESET, msg);

#define NOTICE(msg) \
	printf(ANSI_COLOR_BLUE \
		   "[NOTICE]\t%s\n" \
		   ANSI_COLOR_RESET, msg);

//////////////////////////////////////

/////////// Function Define //////////

char *get_source_code (const char *file_name, size_t *len);

void mat_mul_seq(float * A, float * B, float * C, int ROW_A, int COL_A, int COL_B);

void mat_mul_opencl(float *A, float *B, float *C, int ROW_A, int COL_A, int COL_B);

double get_time();

FILE *connectFile(char *name, char *mode);

int pixel_processing( int Red, int Green, int Blue, int None);
/////////////////////////////////////
