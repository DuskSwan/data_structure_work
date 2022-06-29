
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//结构体定义
struct fre_word
{
  int num;
  char a[18];
}; 

//分配初始内存：
struct fre_word *w;
  w=(struct fre_word *)malloc(100*p*sizeof(struct fre_word));//给结构体分配初始内存

//读取文本
printf("输入读入文件的名字：");
scanf("%s", filename);                   //输入需要统计词频的文件名
if((fp=fopen(filename, "r"))==NULL)
{
printf("无法打开文件\n");
exit(0);
}
   
/****************将单词出现次数设置为1****************************/
  for(i=0;i<100;i++)
  {  
    (w+i)->num=1;
  }
/****************单词匹配****************************************/
  i=0;
  while(!feof(fp))//文件尚未读取完毕
  {
    ch=fgetc(fp);
    (w+i)->a[j]='\0';
    if(ch>=65&&ch<=90||ch>=97&&ch<=122)              //ch若为字母则存入
    {
      (w+i)->a[j]=ch;
      j++;
      flag=0;                         //设标志位判断是否存在连续标点或者空格
    }
    else if(!(ch>=65&&ch<=90||ch>=97&&ch<=122)&&flag==0)    //ch若不是字母且上一个字符为字母
    {    
      i++;
      j=0;
      flag=1;
      for(m=0;m<i-1;m++)                  //匹配单词，若已存在则num+1
      {
        if(stricmp((w+m)->a,(w+i-1)->a)==0)
        {
          (w+m)->num++;
          i--;
        }
      }
    }
/****************动态分配内存****************************************/
    if(i==(p*100))                           //用i判断当前内存已满
    {
      p++;
      w=(struct fre_word*)realloc(w,100*p*(sizeof(struct fre_word)));
      for(n=i;n<=100*p;n++)                      //给新分配内存的结构体赋初值
        (w+n)->num=1;

    }
  }
