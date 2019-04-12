// file: lmsw32ba_verbose_1.c
// Verbose Listing for 32-Bit Bin-Address Packets

// 8-Oct-2012 wfj

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>

FILE *streami;
 bitExtracted(int number, int k, int p)
{
	return (((1 << k) - 1) & (number >> (p - 1)));
}

main (int argc, char **argv)
{

	static int i,j,k,i1,j1,j2;
	static int e1, e2;
	static int b1, b2;
	static int let1, let2;
	static int i64_i1;

	static char *in_file;
	static char *out_file;

	static int qb;
	static unsigned int ba, r;
	static int prompt;
	static unsigned int ew1;
	static int pkt;
	static int tag;

	static int ms, dt;		// milliseconds, dead time
	static int hbp, har, vbp, bn, sps, Value;		// horizontal bed position value
	static int hbp_se;	// sign-extended horiz. bed position value
	static int lost;	// lost event tally value
	static int tof_se, tof, test;	// sign-extended tof value

  // get a filename from the command line

	if (argc < 1)	{
		printf ("usage: %s in_file_name\n",argv[0]);
		exit(1);
    }
	else	{ in_file = argv[1], out_file = "bajs.l";}

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
			ba = ew1 & 0x3fffffff; // Extract 30-bit bin-address field
			
			tof_se = ba >> 25;
			tof = tof_se & 0xF;
			Alfons = 0;
			
			if ((tof >> 4) == 1 && ((tof & 0x7) == 1)){
				printf(" EVENT: pkt_cnt: %8d ew1(d): %10d prompt: %1d ba(h): %8x ba(d): %10d Tof: %4d\n",
					i1, ew1, prompt, ba, ba, tof);
				printf("TOF = 1001");
				system("read -n1 -r -p \"Press any key to continue...\" key");
			}
			if ((tof >> 4) == 0 && ((tof & 0xF) >= 7)){
				printf(" EVENT: pkt_cnt: %8d ew1(d): %10d prompt: %1d ba(h): %8x ba(d): %10d Tof: %4d\n",
					i1, ew1, prompt, ba, ba, tof);
				printf("TOF = 0111");
				system("read -n1 -r -p \"Press any key to continue...\" key");
			}
				tof_se = tof;
			

			
		
			
			
			
			printf(" EVENT: pkt_cnt: %8d ew1(d): %10d prompt: %1d ba(h): %8x ba(d): %10d Tof: %4d\n",
							         i1,   ew1,   prompt,     ba,        ba, tof);
			//system("read -n1 -r -p \"Press any key to continue...\" key");
		}

		if ( tag){
			if ( ((ew1 >> 28) & 0xe)  == 8 ) { // Elapsed Time Tag Packet 1
				ms = ew1 & 0x1fffffff; // Extract 29-bit millisecond field
				dt = (ew1 & 0x0007FFFF) & (ew1 & 0x1FF80000);
				printf(" TAG32_ElapsedTime:    pkt_cnt: %8d ew1(h): %8x ms(h): %7x ms(d): %9d dt: %9d\n",
											   i1,		      ew1,        ms, ms, dt);
			}
			if (((ew1 >> 26) & 0x1f) == 0x1d) { // Motion tracking tag
				Value = ew1 & 0x001FFFFF;
				printf(" TAG32_DeadTime:    pkt_cnt: %8d ew1(h): %8x Value: %9d\n",
					i1, ew1, Value);
				
			}
			 

			

			if ( ((ew1 >> 24) & 0xff) == 0xc4 ) { // Horizontal Bed Position Tag Packet 2
				hbp = ew1 & 0xfffff; // Extract 20-bit bed position field
				hbp_se = hbp; // Assume hbp is Zero
				if (((hbp >> 19) & 1) == 1) hbp_se = hbp | 0xfff00000; // Need to Sign Extend
				printf(" TAG32_HorizBedPos:    pkt_cnt: %8d ew1(h): %8x hbp(h):   %6x hbp_se(d): %8d Head I Radial: %8d Vertical BP: %8d\n",
											   i1,		       ew1,        hbp,          hbp_se, har, vbp);
				
			}
			if ( ((ew1 >> 24) & 0xfc) == 0xbc ) { // Lost Event Tally Tag Packet - Type 7 (GIM)
				lost = ew1 & 0xfffff; // Extract 20-bit lost tally field
				printf(" TAG32_LostEventTally: pkt_cnt: %8d ew1(h): %8x lost(d): %7d\n",
											   i1,		      ew1,        lost);
			}
			if (((ew1 >> 24) & 0xff) == 0xc3) { // // vertical Bed Position Tag Packet 2
				vbp = ew1 & 0x3FFF; //verticalkgs
				printf(" TAG32_VerticalBedPos:    pkt_cnt: %8d ew1(h): %8x hbp(h):   %6x hbp_se(d): %8d Head I Radial: %8d Vertical BP: %8d\n",
					i1, ew1, hbp, hbp_se, har, vbp);
				
			}
		}
	}

	fclose (streami);
	printf(" number of 64-bit packets output: %I64d file size: %I64x\n", i1, 8 * i1);


	exit(0);
}