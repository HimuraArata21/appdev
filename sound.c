#include <stdio.h>
#include <math.h>
#include "sound.h"
#include "screen.h"
#include "comm.h"

WAVheader readwavhdr(FILE *fp)	{
	WAVheader myh;
	fread(&myh, sizeof(myh), 1, fp);
	return myh;
}

//this function will print out all of the following detail of the .wav file

void displayWAVhdr(WAVheader h)	{
	printf("chunk ID: ");
	for(int i=0; i<4; i++) printf("%c", h.chunkID[i]);
	printf("\n");
	printf("chunk size: %d\n", h.chunkSize);
	printf("Num of Channels: %d\n", h.numChannels);
	printf("Sample rate: %d\n", h.sampleRate);
	printf("Block align: %d\n", h.blockAlign);
	printf("Bits per sample: %d\n", h.bitsPerSample);
	//to be continued
}

void wavdata(WAVheader h, FILE *fp)	{
	// in this function we will read sound sample for the opened file
	// the sample are calculated in to decibal value using Root Mean Square
	// (RMS) formula. We will display a 5-sec recorded sound into bar chart
	// our sound file uses samplerate of 16000, for  5 seconds, there are
	// 5*16000 = 800000 samples, we want to display them into 160 bars

	short samples[500];	//to read 500 samples from wav file
	int peaks=0, flag=0;
	double max = 0.0;	//set the maximum decbel
	char postdata[100];
	for(int i=0; i<160; i++)	{
		fread(samples, sizeof(samples), 1, fp);
		double sum = 0.0;	//accumulate the sum
		for(int j=0; j<500; j++)	{
			sum = sum + samples[j]*samples[j];
		}
		double re = sqrt(sum/500);
#ifdef SDEBUG
		printf("db[%d] = %f\n", i+1, 20*log10(re));
#else
		//find out the maximum decibel
		if(20*log10(re)>max)
			max = 20*log10(re);
		//display for re value
		if(20*log10(re)>60)	{
			setfgcolor(RED);
			if(flag == 0)	{
				flag = 1;
				peaks++;
			}
		}
		else	{
			setfgcolor(WHITE);
			flag = 0;
		}
		drawbar(i+1, (int)20*log10(re)/3);
#endif
	}
	//print out the following detail
	gotoXY(1,1);
	printf("Sample Rate: %d\n", h.sampleRate);
	gotoXY(1,75);
	printf("Duration: %f s\n", (float)h.subchunk2Size/h.byteRate);
	gotoXY(1, 150);
	printf("Peaks: %d\n", peaks);
	gotoXY(2, 1);
	printf("Maximum: %f\n", max);

	//send data to PHP program
	sprintf(postdata, "peaks=%d&max=%f\n", peaks, max);
	senddata(URL, postdata);
}
//end of file
