#include <stdio.h>
#include "screen.h"
#include <unistd.h>
#include "comm.h"
#include "sound.h"

//main function

int main(void)	{
	FILE *fp;
	fp = fopen("test.wav", "r");
	WAVheader h = readwavhdr(fp);
	displayWAVhdr(h);
	clearscreen();
	wavdata(h, fp);
	fclose(fp);
	getchar();
}
