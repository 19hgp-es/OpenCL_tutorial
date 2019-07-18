#include "main.h"

void mat_mul_opencl (float *A, float *B, float *C, int ROW_A, int COL_A, int COL_B){
	cl_platform_id platform;
	cl_device_id device;
	cl_context context;
	cl_command_queue queue;
	cl_program program;
	char *kernel_source;
	size_t kernel_source_size;
	cl_kernel kernel;
	cl_int err;
	
	INITMSG("Start Initial Program Settings");
	
	INITMSG("Get Platform ID");
	err = clGetPlatformIDs(1, &platform, NULL);
	CHECK_ERROR(err);

	INITMSG("Get GPU Device form Got Platform ID");
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	CHECK_ERROR(err);

	INITMSG("make Point spot to Create Context");
	context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
	CHECK_ERROR(err);

	INITMSG("Create Command Queue form Created Context");
	queue = clCreateCommandQueue(context, device, 0, &err);
	CHECK_ERROR(err);

	INITMSG("Get Source Code From Custom kernel Function");
	kernel_source = get_source_code("kernel.cl", &kernel_source_size);
	program = clCreateProgramWithSource(context, 1, (const char **)&kernel_source, &kernel_source_size, &err);
	CHECK_ERROR(err);

	INITMSG("Create Program");
	err = clBuildProgram(program, 1, &device, "", NULL, NULL);
	// CHECK kernel initial program build OK.
	if( err == CL_BUILD_PROGRAM_FAILURE) {
		size_t log_size;
		char *log;
		
		err = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		CHECK_ERROR(err);

		log = (char *)malloc(log_size + 1);
		err = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);	
		CHECK_ERROR(err);

		log[log_size] = '\0';
		printf("[LOG]\t\tCompiler error: \n%s\n", log);
		free(log);
		exit(0);
	}
	CHECK_ERROR(err);

	INITMSG("Make Kenrel Program which function name is vec_add");
	kernel = clCreateKernel(program, "mat_mul", &err);
	CHECK_ERROR(err);
	
	INITMSG("Create Buffer with bufA, bufB, bufC");
	cl_mem bufA, bufB, bufC;
	bufA = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) *ROW_A *COL_A, NULL, &err);
	CHECK_ERROR(err);
	bufB = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int) *COL_A *COL_B, NULL, &err);
	CHECK_ERROR(err);
	bufC = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) *ROW_A *COL_B, NULL, &err);
	CHECK_ERROR(err);

	double start_time = get_time(); // check time before write args at buffer
	
	INITMSG("Write Buffer at SEP buffer");
	err = clEnqueueWriteBuffer(queue, bufA, CL_FALSE, 0, sizeof(float) *ROW_A *COL_A, A, 0, NULL, NULL);
	CHECK_ERROR(err);
	err = clEnqueueWriteBuffer(queue, bufB, CL_FALSE, 0, sizeof(float) *COL_A *COL_B, B, 0, NULL, NULL);
	CHECK_ERROR(err);
	
	INITMSG("SET kernel which ready to write ARGs");
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufA);
	CHECK_ERROR(err);
	err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufB);
	CHECK_ERROR(err);
	err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufC);
	CHECK_ERROR(err);
	err = clSetKernelArg(kernel, 3, sizeof(cl_int), &ROW_A);
	CHECK_ERROR(err);
	err = clSetKernelArg(kernel, 4, sizeof(cl_int), &COL_A);
	CHECK_ERROR(err);
	err = clSetKernelArg(kernel, 5, sizeof(cl_int), &COL_B);
	CHECK_ERROR(err);
	
	INITMSG("SET global & local size which depenc on column and row");
	size_t global_size[2] = {COL_B, ROW_A};
	size_t local_size[2] = {16, 16};
	global_size[0] = (global_size[0] + local_size[0] - 1) / local_size[0] * local_size[0];
	global_size[1] = (global_size[1] + local_size[1] - 1) / local_size[1] * local_size[1];

	err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, local_size, 0, NULL, NULL);
	CHECK_ERROR(err);
	err = clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, sizeof(float) *ROW_A *COL_B, C, 0, NULL, NULL);	
	CHECK_ERROR(err);
	
	double end_time = get_time();
	printf("Elapsed time ( excl. initialization): %f sec\n", end_time - start_time);
	
	clReleaseMemObject(bufA);
	clReleaseMemObject(bufB);
	clReleaseMemObject(bufC);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);
	
	NOTICE("Finished Excelerating!");
}
