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

//测试功能 
void test(int argc, char** argv)
{
	FILE* fp;
	char word[WORD_MAXLEN];
	
	//验证命令行用法 
	printf("\n命令行\n");
	for(int i=0;i<argc;i++)
		printf("%s\n",argv[i]);
		//实践表明，0号位置上会有exe绝对路径，需要注意 
	
	//读入字典
	printf("\n字典读入\n");
	fp = fopen("wordtest.txt","r");
	while( fscanf(fp, "%s", word) != EOF)
		printf("%s\n",word);
	
	//输出到文件
	printf("\n输出到文件\n");
	fp = fopen("output.txt", "w");
	fprintf(fp, "9\n");
	fprintf(fp, "test\n");
	fprintf(fp, "#$^^&$*&RRT");
	
	//分析文章列表
	freopen("article.txt","r",stdin);
	while((scanf("%s", a)) != EOF)
	 
}

//针对单词处理大写字母及特殊字符
void wordJob(char word[]){
    int i,k;
    char *specialChar = ",.;:'?!><+=|*&^%$#@\"";//定义特殊字符集
    
    for(i = 0;i<strlen(word);i++){
        //筛选并将字符串中的大写字母转化为小写字母
        if(word[i]>='A'&& word[i]<='Z'){
            word[i] += 32;
        }
        //筛选并去除字符串中的特殊字符
        for(k = 0;k<strlen(specialChar);k++){
            
            if(word[i] == specialChar[k]){
                
                while(i<strlen(word)){
                    word[i] = word[i+1];
                    i++;
                }
               
            }
        }
    }
 
int main(int argc, char** argv) //argc是单词数目，argv是单词列 
{
	test(argc,argv);
}

/*******
 * 从stdin中读入一个单词，转换成小写字母后，保存到目标地址中，
 * 会跳过除了\f以外的所有非字母字符，读到的单词从遇到的第一个
 * 字母字符开始，一直到遇到第一个非字母单词结束。读到\f后会放
 * 回stdin中。
 * 
 * @param dest 函数会把单词[转为小写字母后]放到该目标数组中
 * 
 * @return 返回值非负时，为读到的单词长度。
 * 		   为-1时，代表已经读到了文件末尾
 *******/

int readWord(char dest[])
{
    int size = 0;
    char c;

    while ((c = getchar()) && c != EOF && !isalpha(c) && c != '\f')
        ; // 跳过非字母的字符

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