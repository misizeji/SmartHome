#include <stdio.h>
#include <string.h>
#include "../database/sqlite3.h"

/********************************************************
*函数名称：用户正常登录函数
*函数参数：用户名，密码
*函数返回值：返回 -1：文件打开错误 0：登录失败 1：登录成功
*********************************************************/
int normal_login(char *usr_name,char *pass_word)
{

	//char usr_name[20] = "root";
	//char pass_word[20] = "123456";
	
	//在数据库中查找账号是否存在
	sqlite3 *COUNT;	//数据库指针
	char *errmsg = NULL;
	char *sql = "select * from usr_list;";
	char **resultp = NULL;
	int nrow = 0;
	int ncolumn = 0;
	int i = 0;
	
    int ret = sqlite3_open("./database/usr_list.db",&COUNT);
	if (ret !=SQLITE_OK)
	{
		perror("sqlite3_open");
		return -1;
	}
	
	sqlite3_get_table(COUNT,sql,&resultp,&nrow,&ncolumn,&errmsg);
	if (errmsg != NULL)
	{
		printf("%s\n",errmsg);
		return -1;
	}
	
	for (i = 2;i < (nrow*ncolumn+2); i++)//屏蔽了类别名称
	{
		if((i%2) == 0)//获得号码
		{	
			//printf("__usr_name_%s\n",*(resultp + i));//i+1就能将密码取出来
			if((strcmp(usr_name,*(resultp + i)) == 0) &&((strcmp(pass_word,*(resultp + i+1))) == 0))
			{
				//数据库中有此账号且密码相同
				//printf("the user is %s\n",*(resultp + i));
				//printf("the password is  %s\n",*(resultp + i+1));
				break;
			}
			else if(i == (nrow*ncolumn))//数据库中没有此人
			{
				//printf("there is nobody\n");
				sqlite3_free_table(resultp);
				sqlite3_close(COUNT);
				return 0;
			}
		}
	}
	sqlite3_free_table(resultp);
	sqlite3_close(COUNT);
	return 1;
}
