#include <stdint.h>
#include <stdio.h>
#include <openssl/sha.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/mman.h>
#define LONG 1000000
#define TIME 30
int main(int argc, char *argv[]){
	// prevent swapping memory to disk
	mlockall(MCL_FUTURE|MCL_CURRENT);
	FILE *f;
	uint8_t userpass[61], sha1[21], sha1aux[61];
	uint8_t mytime[21], user[7], otpstring[7];
	uint8_t offset, i, ii;
	struct timeval timestamp;
	uint32_t otp=0;
	long int timeotp;

	if(argc == 2){

		f = fopen(argv[1],"r");
		if(f == NULL){

			exit(0);

		}
		printf("Insert OTP code:");
		fflush(stdout);
		fscanf(stdin,"%6s",user);
		fscanf(f,"%48s",userpass);
		fclose(f);
		gettimeofday(&timestamp,NULL);
		timeotp=(timestamp.tv_sec/TIME)-1;
		for(ii=0; ii<3;ii++){

			sprintf(mytime,"%020ld",timeotp+ii);
			SHA1(userpass, strlen(userpass), sha1);
			sha1aux[0]='\0';
			for(i=0;i < 20;i++){
				
				sprintf(sha1aux,"%s%02x",sha1aux,sha1[i]);
			
			}
			sprintf(sha1aux,"%s%s",sha1aux,mytime);
			SHA1(sha1aux, 60, sha1);
			offset = sha1[19]&0x0F;
			for(i=0;i < 4;i++){

				otp=otp<<8;
				otp=otp+sha1[(i+offset)%20];
			
			}
			otp=otp%LONG;
			sprintf(otpstring,"%06d",otp);
			for(i=0;i < 7;i++){

				if(otpstring[i]!=user[i]){
					
					break;
				
				}
			
			}
			if(i==7){
				
				exit(0);
			
			}
		
		}
		exit(-1);
	
	}

}
