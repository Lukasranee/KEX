// file: lmsw32ba_verbose_1.c
// Verbose Listing for 32-Bit Bin-Address Packets

// 8-Oct-2012 wfj

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

FILE *streami;

main (int argc, char **argv)
{

	static int i,j,k,i1,j1,j2;
	static int i64_i1;

	static char *in_file;

	static int qb;
	static unsigned int ba;
	static int prompt;
	static unsigned int ew1;
	static int pkt;
	static int tag;

	static int ms;		// milliseconds
	static int hbp;		// horizontal bed position value
	static int hbp_se;	// sign-extended horiz. bed position value
	static int lost;	// lost event tally value
	static int tof_se;	// sign-extended tof value

  // get a filename from the command line

	if (argc < 1)	{
		printf ("usage: %s in_file_name\n",argv[0]);
		exit(1);
    }
	else	{ in_file = argv[1];}

 	streami = fopen (in_file, "rb");
	if ( streami == NULL) {
		printf ("No file opened %s\n",in_file);
		exit (1);
		}

	k = 0; i64_i1 = 0; 
		
	while  ((i = fread (&ew1, sizeof(qb), 1, streami) ) != 0) {
		
		pkt = pkt + 1;
		
		i1 = i1 + 1;

		tag = ((ew1>>31)&1)!=0;

		prompt = 0;

		if(!tag) {
			prompt = (ew1>>30) & 1;
			ba = ew1 & 0x3fffffff;
			printf(" EVENT: pkt_cnt: %8x ew1(h): %8x prompt: %1d ba(h): %8x ba(d): %10d\n",
							         i1,   ew1,		   prompt,     ba,        ba);
		}

		if ( tag){
			if ( ((ew1 >> 28) & 0xe)  == 8 ) { // Elapsed Time Tag Packet
				ms = ew1 & 0x1fffffff; // Extract 29-bit millisecond field
				printf(" TAG32_ElapsedTime:    pkt_cnt: %8x ew1(h): %8x ms(h): %7x ms(d): %9d\n",
											   i1,		      ew1,        ms, ms);
			}
			if ( ((ew1 >> 24) & 0xff) == 0xc4 ) { // Horizontal Bed Position Tag Packet
				hbp = ew1 & 0xfffff; // Extract 20-bit bed position field
				hbp_se = hbp; // Assume hbp is Zero
				if (((hbp >> 19) & 1) == 1) hbp_se = hbp | 0xfff00000; // Need to Sign Extend
				printf(" TAG32_HorizBedPos:    pkt_cnt: %8x ew1(h): %8x hbp(h):   %6x hbp_se(d): %8d\n",
											   i1,		       ew1,        hbp,          hbp_se);
			}
			if ( ((ew1 >> 24) & 0xfc) == 0xbc ) { // Lost Event Tally Tag Packet - Type 7 (GIM)
				lost = ew1 & 0xfffff; // Extract 20-bit lost tally field
				printf(" TAG32_LostEventTally: pkt_cnt: %8x ew1(h): %8x lost(d): %7d\n",
											   i1,		      ew1,        lost);
			}
		}
	}

	fclose (streami);

	exit(0);
}