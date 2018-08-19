#ifndef _MFUN_H_
#define _MFUN_H_
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
typedef struct userMsg{
char loginName[20];
char loginPasswd[20];
}UserMsg;
int login(char* name,char* passwd){
UserMsg um;
int count = 0,size = sizeof(UserMsg),nres,pres;
int fd = open("/home/fate/study/kefile/login.dat",O_RDONLY);
if(fd == -1){
return -1;
}
while(1)
{
if(read(fd,&um,size) < size){
return -1;
}
nres = strcmp(name,um.loginName);
pres = strcmp(passwd,um.loginPasswd);
if(nres==0 && pres==0){
return 1;
}
if( nres == 0 && pres != 0){
return 0;
}
count++;
lseek(fd,SEEK_SET,size*count);
}
lseek(fd,SEEK_SET,0);
close(fd);
}
 
 

 
int regist(char* name,char* passwd){
UserMsg um;
int count = 0,size = sizeof(UserMsg);
int fd = open("/home/fate/study/kefile/login.dat",O_WRONLY|O_APPEND);
if(fd == -1){
return -1;
}
strcpy(um.loginName,name);
strcpy(um.loginPasswd,passwd);
lseek(fd,SEEK_END,0);
count = write(fd,&um,size);
if(count != size)
{
return -1;
}
return 1;
}
int tentoe(int num){
int res;
if(num > 999 || num <0){
return -1;
}
res = 64*num/100 + 8*(num/10%10) +num%10;
return res;
}
int listdtl(char* pname){
struct dirent** dlist;
int tmp,count;
char fpath[50],*fname;
count = scandir(pname,&dlist,NULL,alphasort);
if(count == -1)return -1;
printf("%10s\t%10s\t%10s\t%10s\t%10s\n","编号       ","类型     ","所有者         ID","大小   ","文件名        ");
for(tmp = 0;tmp < count;tmp++)
{
struct stat st;
sprintf(fpath,"%s/%s",pname,dlist[tmp]->d_name);
stat(fpath,&st);
switch(dlist[tmp]->d_type){
case DT_DIR:
 
 

 
fname = "目录    ";
break;
case DT_LNK:
fname = "软链接       ";
break;
case DT_BLK:
fname = "块设备       ";
break;
case DT_REG:
fname = "普通文件         ";
break;
default:
fname = "其他类型         ";
break;
}
printf("%10lu\t%10s\t%10u\t%10lu\t%10s\n",st.st_ino,fname,st.st_uid,st.st_size,dlist[tmp]->d_name);
}
return 0;
}
#endif

