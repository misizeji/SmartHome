#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

/*******************************************************
*函数名称：Qt发送留言给远程网页函数
*函数参数：将要留言的函数
*函数返回值：
**********************************************************/
int msg_send(char *data)
{
	int fd = 0; 

        fd = open("./msg_leave",O_WRONLY | O_TRUNC);
	if(fd < 0)
	{
		close(fd);
		return -1;
	}
	close(fd);
        fd = open("./msg_leave",O_WRONLY);
	if(fd < 0)
	{
		close(fd);
		return -1;
	}
	write(fd, data, strlen(data));
	close(fd);
	return 0;
}
