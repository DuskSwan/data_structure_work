
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�ṹ�嶨��
struct fre_word
{
  int num;
  char a[18];
}; 

//�����ʼ�ڴ棺
struct fre_word *w;
  w=(struct fre_word *)malloc(100*p*sizeof(struct fre_word));//���ṹ������ʼ�ڴ�

//��ȡ�ı�
printf("��������ļ������֣�");
scanf("%s", filename);                   //������Ҫͳ�ƴ�Ƶ���ļ���
if((fp=fopen(filename, "r"))==NULL)
{
printf("�޷����ļ�\n");
exit(0);
}
   
/****************�����ʳ��ִ�������Ϊ1****************************/
  for(i=0;i<100;i++)
  {  
    (w+i)->num=1;
  }
/****************����ƥ��****************************************/
  i=0;
  while(!feof(fp))//�ļ���δ��ȡ���
  {
    ch=fgetc(fp);
    (w+i)->a[j]='\0';
    if(ch>=65&&ch<=90||ch>=97&&ch<=122)              //ch��Ϊ��ĸ�����
    {
      (w+i)->a[j]=ch;
      j++;
      flag=0;                         //���־λ�ж��Ƿ�������������߿ո�
    }
    else if(!(ch>=65&&ch<=90||ch>=97&&ch<=122)&&flag==0)    //ch��������ĸ����һ���ַ�Ϊ��ĸ
    {    
      i++;
      j=0;
      flag=1;
      for(m=0;m<i-1;m++)                  //ƥ�䵥�ʣ����Ѵ�����num+1
      {
        if(stricmp((w+m)->a,(w+i-1)->a)==0)
        {
          (w+m)->num++;
          i--;
        }
      }
    }
/****************��̬�����ڴ�****************************************/
    if(i==(p*100))                           //��i�жϵ�ǰ�ڴ�����
    {
      p++;
      w=(struct fre_word*)realloc(w,100*p*(sizeof(struct fre_word)));
      for(n=i;n<=100*p;n++)                      //���·����ڴ�Ľṹ�帳��ֵ
        (w+n)->num=1;

    }
  }
