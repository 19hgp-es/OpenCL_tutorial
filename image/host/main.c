#include "main.h"

int main (int argc, char *argv[])
{
	int num = 0;
	unsigned char tt[60], buf[4], file[20];
	long Red, Green, Blue, None;
	unsigned char obuf[4];
	FILE *fpr, *fpw;
	
	if( argc < 2 ){
		printf("[ERROR] Usage\t: %s <src file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}	
	
	fpr = connectFile(argv[0], "r");
	fpw = connectFile("../outputs/output.bmp", "w");
	
	fread(tt, 54, 1, fpr);
	fwrite(tt, 54, 1, fpw);

	int iWidth = *(int *)&tt[18];
	int iHeight = *(int *)&tt[22];
	printf("width : %d(%c), height : %d($c)\n", iWidth,tt[18], iHeight, tt[22]);

	while(fread(buf, 4, 1, fpr) != 0){
		num += 1;
	
		Red = (long)buf[2];
		Green = (long)buf[1];
		Blue = (long)buf[0];
		None = (long)buf[3];
		pixel_processing(Red, Green, Blue, None, obuf);
		fwrite(obuf, sizeof(int), 1, fpw);
	}

	fclose(fpw);
	fclose(fpr);
	printf("process END.\n");
	return 0;
}





