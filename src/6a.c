#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stropts.h>
#include <asm/termios.h>

unsigned char buffer1[512] = {0};

int set_DMX_baud_linux(int fh, int verbose)
{
	struct termios2 tio = {0};   // linux-specific terminal stuff

	const int rate = 250000;

	if (fh==-1) return -1;

	/* Set up custom speed for UART */
	if (ioctl(fh, TCGETS2, &tio) < 0)   // get current uart state
		return -1;

	tio.c_cflag |= CLOCAL | CREAD;//本地连接和接受使能
	tio.c_iflag &= ~ICRNL;    //禁止将输入中的回车翻译为新行 (除非设置了 IGNCR)
	tio.c_iflag &= ~ISTRIP;   //禁止将所有接收的字符裁减为7比特
	tio.c_cflag &= ~PARENB;   //禁止奇偶校验码的生成和检测功能
	tio.c_cflag |= CSTOPB;   //设置2停止位 ***
	tio.c_cflag &= ~CSIZE;    //清除数据位设置
	tio.c_cflag |=  CS8;      //设置为8数据位
	tio.c_cflag &= ~CRTSCTS;  //禁止硬件流控

	//---
	tio.c_cflag &= ~CBAUD;
	tio.c_cflag |= BOTHER;
	tio.c_ispeed = rate;
	tio.c_ospeed = rate;      // set custom speed directly
	if (ioctl(fh, TCSETS2, &tio) < 0)   // push uart state
		return -1;
	if (verbose > 1)
	{   // if verbose, read and print
		if (ioctl(fh, TCGETS2, &tio) < 0)   // get current uart state
		{
			fprintf(stderr, "Error getting altered settings from port\n");
		}
		else
		{
			fprintf(stderr, "Port speeds are %i in and %i out\n", 
					tio.c_ispeed, tio.c_ospeed);
		}
	}

	return 0;
}

void hhh(int fd1a){
	int status1;
	ioctl(fd1a, TIOCMGET, &status1);
	status1 &= ~TIOCM_DTR;
	ioctl(fd1a, TIOCMSET, &status1); 
}

void lll(int fd1a){
	int status1;
	ioctl(fd1a, TIOCMGET, &status1);
	status1 |= TIOCM_DTR;
	ioctl(fd1a, TIOCMSET, &status1); 
}

void dmx_out(int fd1a){
	lll(fd1a);
	usleep(1*1000);
	hhh(fd1a);
	usleep(1*1000);
	write(fd1a,buffer1,11);
	tcflush(fd1a, TCIOFLUSH);
}

int main (int argc, char *argv[]){
int i1;
	int fd1 = -1;

	if (argc != 11) {
		printf("error ! need 10 of number\n");
		return 1; 
	}

	buffer1[0]=0; // must
	buffer1[1]=atoi(argv[1]);
	buffer1[2]=atoi(argv[2]);
	buffer1[3]=atoi(argv[3]);
	buffer1[4]=atoi(argv[4]);
	buffer1[5]=atoi(argv[5]);
	buffer1[6]=atoi(argv[6]);
	buffer1[7]=atoi(argv[7]);
	buffer1[8]=atoi(argv[8]);
	buffer1[9]=atoi(argv[9]);
	buffer1[10]=atoi(argv[10]);

	for (i1=0;i1<11;i1++){
		printf("%d %d\n",i1,buffer1[i1]);
	}

	fd1 = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);	//Open in non blocking read/write mode

	if (fd1 == -1)
	{
		//ERROR - CAN'T OPEN SERIAL PORT
		printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
		return -1;
	}

	set_DMX_baud_linux(fd1, 2);
	hhh(fd1);

	while (1){
		dmx_out(fd1);
		usleep(30*1000);
	}

	return 0;
}
