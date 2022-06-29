#include<stdio.h>
#include<string.h>
#include<ctype.h>
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

/*******
 * ��stdin�ж���һ�����ʣ�ת����Сд��ĸ�󣬱��浽Ŀ���ַ�У�
 * ����������\f��������з���ĸ�ַ��������ĵ��ʴ������ĵ�һ��
 * ��ĸ�ַ���ʼ��һֱ��������һ������ĸ���ʽ���������\f����
 * ��stdin�С�
 * 
 * @param dest ������ѵ���[תΪСд��ĸ��]�ŵ���Ŀ��������
 * 
 * @return ����ֵ�Ǹ�ʱ��Ϊ�����ĵ��ʳ��ȡ�
 * 		   Ϊ-1ʱ�������Ѿ��������ļ�ĩβ
 *******/

int readWord(char dest[])
{
    int size = 0;
    char c;

    while ((c = getchar()) && c != EOF && !isalpha(c) && c != '\f')
        ; // ��������ĸ���ַ�

    if (c == EOF)
        return -1;
    else if (c == '\f') {
        ungetc(c, stdin);
        return 0;
    }

    dest[size++] = tolower(c);
    while ((c = getchar()) && isalpha(c))
        dest[size++] = tolower(c);
    dest[size] = '\0';

    if (c == '\f')
        ungetc(c, stdin);

    return size;
}