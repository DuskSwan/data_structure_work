#include<stdio.h>
#include<string.h>
#define WORD_MAXLEN 50

struct wordinfo
{
	int num;
	char w[WORD_MAXLEN];
};

bool 

//���Թ��� 
void test(int argc, char** argv)
{
	FILE* fp;
	char word[WORD_MAXLEN];
	
	//��֤�������÷� 
	printf("\n������\n");
	for(int i=0;i<argc;i++)
		printf("%s\n",argv[i]);
		//ʵ��������0��λ���ϻ���exe����·������Ҫע�� 
	
	//�����ֵ�
	printf("\n�ֵ����\n");
	fp = fopen("wordtest.txt","r");
	while( fscanf(fp, "%s", word) != EOF)
		printf("%s\n",word);
	
	//������ļ�
	printf("\n������ļ�\n");
	fp = fopen("output.txt", "w");
	fprintf(fp, "9\n");
	fprintf(fp, "test\n");
	fprintf(fp, "#$^^&$*&RRT");
	
	//���������б�
	freopen("article.txt","r",stdin);
	while((scanf("%s", a)) != EOF)
	 
}

//��Ե��ʴ����д��ĸ�������ַ�
void wordJob(char word[]){
    int i,k;
    char *specialChar = ",.;:'?!><+=|*&^%$#@\"";//���������ַ���
    
    for(i = 0;i<strlen(word);i++){
        //ɸѡ�����ַ����еĴ�д��ĸת��ΪСд��ĸ
        if(word[i]>='A'&& word[i]<='Z'){
            word[i] += 32;
        }
        //ɸѡ��ȥ���ַ����е������ַ�
        for(k = 0;k<strlen(specialChar);k++){
            
            if(word[i] == specialChar[k]){
                
                while(i<strlen(word)){
                    word[i] = word[i+1];
                    i++;
                }
               
            }
        }
    }
 
int main(int argc, char** argv) //argc�ǵ�����Ŀ��argv�ǵ����� 
{
	test(argc,argv);
}
