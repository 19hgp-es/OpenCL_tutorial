#include "host.h"

char *get_source_code(const char *file_name, size_t *len){
	char *source_code;
	size_t length;
	FILE *file = fopen(file_name, "r");
	
	if(file == NULL) {
		printf("[%s:%d] Failed to open %s\n", __FILE__, __LINE__, file_name);
		exit(EXIT_FAILURE);
	}
	
	fseek(file, 0, SEEK_END);
	length = (size_t)ftell(file);
	rewind(file);
	
	source_code = (char *)malloc(length +1);
	fread(source_code, length, 1, file);
	source_code[length] = '\0';

	fclose(file);
	
	*len = length;
	return source_code;
}

void mat_mul_seq(float *A, float *B, float *C, int ROW_A, int COL_A, int COL_B)
{
	int i, j, k;
	for(i = 0; i < ROW_A; i++){
		for(j = 0; j < COL_B; j++){
			C[i * COL_B + j] = 0.0f;
			for(k = 0; k < COL_A; k++){
				C[i * COL_B + j] += A[i * COL_A + k] * B[k * COL_B + j];
			}
		}
	}
}

double get_time () {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (double)tv.tv_sec + (double)1e-6 * tv.tv_sec;
}
