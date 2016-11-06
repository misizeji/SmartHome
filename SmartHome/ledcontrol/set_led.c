#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "s5pv210-gpio.h"


/***************************************************
*函数功能：打开设备文件函数
****************************************************/
static int open_dev(const char *devname)
{
	int fd = -1;
	
	fd = open(devname, O_RDWR);
	if(fd < 0)
	{
            _exit(-1);
	}
	return fd;
}

/*****************************************************
*函数名称：led初始化读取函数
*函数功能：将当前的点亮的led数读取
*函数返回值：返回的是亮灯数字组成字符串
*******************************************************/
int led_init()
{	
	int led = 0x00;
	int led1 = 0;
	int led2 = 0;
	int led3 = 0;
	char init[50] = "";
	
	int gpio_fd = open_dev("/dev/gpH0");
	read(gpio_fd, &led, sizeof(led));

	switch(led&0x0e)
	{
		case 0x0e:
			led1 = 1;
			led2 = 1;
			led3 = 1;
			break;
		case 0x0c:
			led1 = 0;
			led2 = 1;
			led3 = 1;
			break;
		case 0x0a:
			led1 = 1;
			led2 = 0;
			led3 = 1;
			break;	
		case 0x08:
			led1 = 0;
			led2 = 0;
			led3 = 1;
			break;
		case 0x06:
			led1 = 1;
			led2 = 1;
			led3 = 0;
			break;
		case 0x04:
			led1 = 0;
			led2 = 1;
			led3 = 0;
			break;
		case 0x02:
			led1 = 1;
			led2 = 0;
			led3 = 0;
			break;
		case 0x00:
			led1 = 0;
			led2 = 0;
			led3 = 0;
			break;
		default:
			break;
	}

	sprintf(init,"%d%d%d",led1,led2,led3);
	printf("%s",init);
	return atoi(init);
}

/************************************************************
*函数名称:led控制函数
*函数功能：将需要的点灯led灯点亮
*函数返回值：0
*************************************************************/
int led_ctl(int num)
{	
	int gpio_fd = 0;
	int led = 0x00;
	char *data = NULL;
	int lednum = num;
	
	gpio_fd = open_dev("/dev/gpH0");
	
	ioctl(gpio_fd, GPIO_SET_PIN_OUT, 0x1);
	ioctl(gpio_fd, GPIO_SET_PIN_OUT, 0x2);
	ioctl(gpio_fd, GPIO_SET_PIN_OUT, 0x3);

	read(gpio_fd, &led, sizeof(led));

	switch(lednum)
	{
		case 1:
			led ^= 0x02;
			break;
		case 2:
			led ^= 0x04;
			break;
		case 3:
			led ^= 0x08;
			break;
		case 4:
		if((led&0x0e) == 0x0e)
		{
			led = 0x01;
		}
		else
		{
			led = 0x0e;
		}
		break;
	
		default:
			break;
	}

	write(gpio_fd,&led,sizeof(led));
	close(gpio_fd);
	return 0;
}
