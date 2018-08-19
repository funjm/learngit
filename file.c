#include "mfun.h"   
 
#include <errno.h>   
 
int isLogin;   
 
int main()   
 
{   
 
       char resbuf[20],ubuf[20],pbuf[20],upath[50];   
 
       printf("------  文件系统演示课设 ------\n");   
 
       while(!isLogin){    
 
              printf(" 操作说明 :\n");   
 
              printf("1 ：登陆 格式: login [username] [password]\n");   
 
              printf("2 ：注册 格式: regist [username] [password]\n");   
 
              printf(" 请输入命令 :");   
 
              scanf("%s %s %s",resbuf,ubuf,pbuf);   
 
              if(strcmp(resbuf,"login") == 0){   
 
                     int lres = login(ubuf,pbuf);   
 
                     if(lres == -1){   
 
                             printf(" 用户'%s'不存在 ,请核对信息或注册 \n",ubuf);   
 
                             continue;   
 
                     }else if(lres == 0){   
 
                             printf(" 密码与'%s'不匹配 ,请核对 \n",ubuf);   
 
                             continue;   
 
                     }else{  
  printf(" 登陆成功 \n");   
 
                      isLogin = 1;   
 
                      sprintf(upath,"/home/lhx/study/kefile/%s/",ubuf);   
 
                      lres = chdir(ubuf);   
 
                      if(lres!=0){   
 
                             printf(" 进入目录失败 \n");   
 
                             printf("Error:%s\n",strerror(errno));   
 
                      }else{   
 
                             printf("  当前工作目录 :%s\n",upath);   
 
                      }   
 
                      system("clear");   
 
               }   
 
       }else if(strcmp(resbuf,"regist") == 0){   
 
               int rres = regist(ubuf,pbuf);   
 
               if(rres == -1){   
 
                      printf(" 注册失败 ,请重试\n");   
 
               }else{   
 
                      printf(" 注册成功，赶快登陆系统演示吧  \n");   
 
                      mkdir(ubuf,0741);   
 
               }   
 
       }else{   
 
               printf(" 您输入的命令无法识别 ,请重试 \n");   
 
       }   
 
}   
 
printf("---------  文件操作演示 ----------\n");   
 
while(1){   
 
        int filedesc;   
 
        printf("--------------------------------------------------\n");   
 
        printf(" 创建文件 :create [filename] [mode](eg:666)\n");   
 
        printf(" 查看文件内容 :type [filename] -n\n");   
 
        printf(" 删除文件 :delete [filename] -n\n");   
 
        printf(" 创建目录 :mkdir [dirname] -n\n");   
 
        printf(" 删除目录 :rmdir [dirname] -n\n");   
 
        printf(" 察看当前目录下的文件 :dir [option](-l:detail,-nl) -n\n");   
 
        printf(" 进入目录 :cd [dirname] -n\n");   
 
        printf(" 请输入操作命令 :");   
 
       scanf("%s %s %s",resbuf,ubuf,pbuf);   
 
        if(strcmp(resbuf,"create")==0)   
 
       {   
 
               int mode = atoi(pbuf);   
 
               if(mode == 0){   
 
                      printf(" 无法识别的文件权限 \n");   
 
                      continue;  

}   
 
       filedesc = creat(ubuf,tentoe(mode));   
 
       if(filedesc == -1){   
 
               printf(" 创建失败，该文件已存在 \n");   
 
       }else{   
 
               printf(" 创建成功 \n");   
 
       }   
 
       close(filedesc);   
 
}else if(strcmp(resbuf,"type") == 0){   
 
       filedesc = open(ubuf,O_RDONLY);   
 
       if(filedesc == -1){   
 
               printf(" 该文件不存在 !\n");   
 
       }else{   
 
               char buf[1025];   
 
               int count;   
 
               printf("'%s' 文件的内容 :\n",ubuf);   
 
               while(1){   
 
                      count = read(filedesc,buf,1024);   
 
                      if(count == 0){   
 
                              break;   
 
                      }   
 
                      buf[count] = 0;   
 
                      printf("%s",buf);   
 
               }   
 
       }   
 
}else if(strcmp(resbuf,"delete") == 0){   
 
       filedesc = unlink(ubuf);   
 
       if(filedesc != 0){   
 
               printf(" 删除失败，文件可能不存在 \n");   
 
       }else{   
 
               printf(" 删除文件 '%s'成功\n",ubuf);   
 
       }   
 
}else if(strcmp(resbuf,"mkdir") == 0){   
 
       filedesc = mkdir(ubuf,0751);   
 
       if(filedesc != 0){   
 
               printf(" 创建目录失败，目录可能已经存在了  \n");   
 
       }else{   
 
               printf(" 创建目录 '%s'成功\n",ubuf);   
 
       }   
 
}else if(strcmp(resbuf,"rmdir") == 0){   
 
       filedesc = rmdir(ubuf);   
 
       if(filedesc != 0){   
 
               printf(" 删除目录失败，目录可能不存在或者目录非空                                            \n");   
 
       }else{  
        printf(" 删除目录 '%s'成功\n",ubuf);   
 
                       }   
 
                }else if(strcmp(resbuf,"cd") == 0){   
 
                       char dpath[50];   
 
                       sprintf(dpath,"%s%s",upath,ubuf);   
 
                       strcpy(upath,dpath);   
 
                       filedesc = chdir(dpath);   
 
                        if(filedesc != 0){   
 
                                printf(" 更改工作目录失败 !\n");   
 
                       }else{   
 
                                printf(" 当前工作目录： %s\n",dpath);   
 
                       }   
 
                }else if(strcmp(resbuf,"dir") == 0){   
 
                        if(strcmp(ubuf,"-nl") == 0){   
 
                                DIR* dir;   
 
                                struct dirent* drt;   
 
                                dir = opendir(upath);   
 
                                while(1){   
 
                                       drt = readdir(dir);   
 
                                       if(drt == NULL){   
 
                                               break;   
 
                                       }   
 
                                       printf("%s\t",drt->d_name);   
 
                                }   
 
                                printf("\n");   
 
                                closedir(dir);   
 
                       }else if(strcmp(ubuf,"-l") == 0){   
 
                                listdtl(upath);   
 
                       }else{   
 
                                printf(" 不能识别的选项 '%s'!\n",ubuf);   
 
                                continue;   
 
                       }   
 
                }else{   
 
                        printf(" 未能识别的命令 ,请核对 !\n");   
 
                }   
 
        }   
 
        return 0;   
 
}   

