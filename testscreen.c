#include <stdio.h>
#include "screen.h"
#include <unistd.h>
#include "comm.h"
#include "sound.h"

int main(void)
{
/*    Position cur = getscreensize();
    char poststr[100];
    sprintf(poststr, "row=%d&col=%d", cur.row, cur.col);
    senddata(poststr, URL);
    setcursor(1,1);
    printf("Screen size,ROW-%d, COL-%d\n", cur.row, cur.col);
    printf("HTTP post is sent to %s\n", URL);
    getchar();
*/

	FILE *fp;
	fp = fopen("test.wav", "r");
	WAVheader h = readwavhdr(fp);
	displayWAVhdr(h);
	wavdata(h, fp);
	fclose(fp);
}
