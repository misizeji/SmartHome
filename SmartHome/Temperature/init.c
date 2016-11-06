#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "sqlite3.h"


/*********************************************
*函数功能：实现Qt温湿度的显示初始化
*函数参数：无
*  返回值：温湿度字符串
**********************************************/
char *init()
{
	int fd;
	int flag = 0;		//0正常，1超标
	int flag1 = 0;
	int buffer[2];
	sqlite3 *db = NULL;
	int temperature_max = 50;
	int humidity_max = 35;
	int temperature_min = 0;
	int humidity_min = 0;
    char *str;
	char *sql = NULL;
	char *errmsg;
	char **dbResult;
	int result, nRow, nColumn;
	result = sqlite3_open("./database/tem_info.db",&db);
	if(result != SQLITE_OK)
	{
		printf("open error\n");
        return NULL;
	}
	sql = "select *from temp where id=1;";
	result = sqlite3_get_table(db, sql, &dbResult, &nRow, &nColumn, &errmsg);
	if(result == SQLITE_OK)
	{
		temperature_max = atoi(dbResult[6]);
		temperature_min = atoi(dbResult[8]);
		humidity_max = atoi(dbResult[7]);
		humidity_min = atoi(dbResult[9]);	
	}

	//printf("%d,%d,%d,%d,%d\n", temperature_max,humidity_max,temperature_min,humidity_min,flag);
	fd = open("/dev/am2321b", O_RDWR);
	if(fd < 0){
		perror("open");
	}
	read(fd, buffer, sizeof(buffer));
	if(buffer[1]/10.0 >= temperature_max)
	{
		flag = 1;
	}
	if(buffer[0]/10.0 >= humidity_max)
	{
		flag1 = 1;
	}
    str = (char *)malloc(100);
	//printf("<temperature>: %f\t<humidity>: %f\n", buffer[1]/10.0,buffer[0]/10.0);
	sprintf(str,"%f,%f,%d,%d,%d,%d,%d,%d\n", buffer[1]/10.0, buffer[0]/10.0, 
			temperature_max,humidity_max,temperature_min,humidity_min,flag,flag1);
	sqlite3_free_table(dbResult);
	sqlite3_close(db);
	return str;
}

/*********************************************
*函数功能：实现Qt温湿度的实时显示
*函数参数：无
*  返回值：温湿度字符串
**********************************************/
char *real_time(char *data)
{
	int fd;
	int flag = 0;	//0正常，1超标
    int flag1 = 0;
	int buffer[2];
	int temperature_max = 50;
	int humidity_max = 34;
	int temperature_min = -10;
	int humidity_min = 0;
	sqlite3 *db = NULL;
	char sql[100] = "";
    //char *str;
	char str[100] = "";
	char *errmsg;
	int result = 0;

	//对收到的数据进行切割
	sscanf(data, "%d,%d,%d,%d",&temperature_max,&humidity_max,&temperature_min,&humidity_min);

	result = sqlite3_open("./database/tem_info.db",&db);
	if(result != SQLITE_OK)
	{
		printf("open error\n");
        return NULL;
	}
	sprintf(sql,"update temp set id=1, temperature_max=%d,humidity_max=%d,temperature_min=%d,humidity_min=%d;",
			temperature_max,humidity_max,temperature_min,humidity_min);
	sqlite3_exec(db, sql, NULL, NULL, &errmsg);

	fd = open("/dev/am2321b", O_RDWR);
	if(fd < 0){
		perror("open");
	}
	
	read(fd, buffer, sizeof(buffer));
	if(buffer[1]/10.0 >= temperature_max)
	{
		flag = 1;
	}
	if(buffer[0]/10.0 >= humidity_max)
	{
		flag1 = 1;
	}
    //str = (char *)malloc(100);
	//printf("<temperature>: %f\t<humidity>: %f\n", buffer[1]/10.0,buffer[0]/10.0);
	sprintf(str,"%f,%f,%d,%d,%d,%d,%d,%d\n", buffer[1]/10.0, buffer[0]/10.0, 
			temperature_max,humidity_max,temperature_min,humidity_min,flag,flag1);
			
	sqlite3_close(db);
	printf("\n");
	return str;
}




