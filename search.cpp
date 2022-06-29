#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h> 
#include<math.h> 

#define WORD_MAXLEN 50 //最大单词长度 
#define k_MAX 20 //最大关键词个数 
#define article_MAX 2000 //最大文章/网页个数 
#define id_MAX 10 //最大标识号长度 

struct TN //记录单词k在文章d的频数，k与d体现在数组编号中 
{
	char w[WORD_MAXLEN];//单词 
	int f;//频数 
};

struct ArticleInfo //记录单篇文章 
{
	char id[id_MAX]; //编号/标识号 
	int num; //序号
	int word_n; //总单词数 
	int TN[k_MAX]; //关键词频数表，之后会用来算频率 
	double TF[k_MAX]; //关键词频率表
	double sim; //相关度 
}; 

int N; //总文章数
int m; //关键词数
int res_n; //需要显示的结果条目数 
char keyword[k_MAX][WORD_MAXLEN]; //关键词列表，keyword[i]为关键词 
int DN[k_MAX]; //关键词出现次数 
double IDF[k_MAX]; //逆词频数 
struct ArticleInfo article[article_MAX]; //文章信息列表 
char dict[418668][WORD_MAXLEN], stop[321][WORD_MAXLEN];
	//字典共418667条，停止词320条 

void test(int argc, char** argv);//测试一些用法 
void readDictStop(); //读入字典与停止词
bool check(char word[]); 
void article_analyse();//分析文本，结果会直接保存在全局变量中 
int find_str(char strs[][WORD_MAXLEN], char *str, int len);
bool check(char word[]);
void print_func();

int main(int argc, char** argv) //argc是单词数目，argv是单词列 
{
	//test(argc,argv);
	
	/***读入字典与停止词***/
	readDictStop();
	
//	char t[10]="abaction";
//	printf("%d\n",check(t));
//	printf("%d\n",find_str(dict,t,418667));
	
	/***获取参数***/ 
	// 100 edu news article abcdefgh //样例
	// 5 edu news article //自制 
	m=0; //有效关键词个数 
	int k;
	for(k=2;k<argc;k++) 
	{
		if(!check(argv[k])) continue; //无效关键词 
		strcpy(keyword[m],argv[k]); //赋值
		m++;
	}
		//以上结束后，m是关键词个数 
	res_n = atoi(argv[1]); //需要显示的结果条目数 
	//printf("%d,%d",m,k);
	
	/***读入article，并逐字符分析***/
	freopen("testarticle.txt","r",stdin); //设置输入流 
	article_analyse(); //分析得出所需的值 
	
	/***计算结果***/
	int i,j;
	double temp; 
	for(i=0;i<m;i++) //对每个关键词 
	{
		if(DN[i]>0) IDF[i]=log10( (double)N/(double)DN[i] );//计算逆词频数 
		else IDF[i]=0.0;
	} 
		
	for(j=0;j<N;j++) //对每篇文章 
	{
		temp = 0.0;
		for(i=0;i<m;i++)
			temp += (double)article[j].TF[i] * (double)IDF[i]; //TF求和 
		article[j].sim = temp;  //TF求和乘以IDF 
	}

	/***输出结果***/ 
		//此处应有排序
	print_func(); 
	
	return 0; 
}

//测试功能 
void test(int argc, char** argv)
{
	FILE* fp;
	char word[WORD_MAXLEN];
	
	//验证命令行用法 
	printf("\n命令行\n");
	printf("argc=%d\n",argc);
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
	
	 
}

//读入字典停止词保存在数组dict、stop中 
void readDictStop()
{
	int i=0; 
	FILE* fp;
	char word[WORD_MAXLEN];
	//字典 
	fp = fopen("dictionary.txt","r");
	i=0; 
	while( fscanf(fp, "%s", word) != EOF)
		strcpy(dict[i++],word); //赋值
	//停止词 
	fp = fopen("stopwords.txt","r");
	i=0; 
	while( fscanf(fp, "%s", word) != EOF)
		strcpy(stop[i++],word); //赋值 
}

//从字符串列表中查找字符串 
int find_str(char strs[][WORD_MAXLEN], char *str, int len)
{
    int i = 0;
    while(i < len)
	{
        if(strcmp(strs[i], str) == 0) 
			break;
        i++;
    }
    if(i == len)
        return -1; //没找到，返回-1 
    return i; //找到了，返回索引 
}


//检查某个单词word是否有意义，如果有意义返回ture，否则false 
bool check(char word[])
{
	if(find_str(stop,word,320)>=0)
		return false;
	else if(find_str(dict,word,418667)>=0)
		return true;
	else 
		return false;
} 



/*******
 * 从stdin中读入一个单词，转换成小写字母后，保存到目标地址中，
 * 会跳过除了\f以外的所有非字母字符，读到的单词从遇到的第一个
 * 字母字符开始，一直到遇到第一个非字母单词结束。
 * 读到\f后会放stdin中。←这个去掉了 
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
        ; // 跳过开头的非字母的字符

    if (c == EOF) //到头了 
        return -1;
    else if (c == '\f') //分隔符 
	{ 
        //ungetc(c, stdin);
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

//分析文章合集，将数据更新到article数组中 
void article_analyse()
{
	int idx=0; //当前文章索引
	char word[WORD_MAXLEN]; //保存一个单词 
	int word_n; //记录词汇数 
	int word_len; //记录单词长度
	int i;
	while(1) //持续读取文章 
	{
		//printf("文章%d\n",idx); 
		word_n = 0; //初始化当前文章单词数为0
		
		scanf("%s", word);//首先读入编号
		strcpy(article[idx].id, word); //编号 
		article[idx].num = idx+1 ; //序号
		while(1) //持续读取单词 
		{
			word_len=readWord(word); //获取一个单词
			if(word_len<=0)break; //如果遇到终止符则结束读取单词 
			if(!check(word)) continue; //无效单词则不管 
			//有效单词的话
			word_n++; //单词数+1
			for(i=1;i<=m;i++)//检索是否为关键词 
				if(strcmp(keyword[i], word) == 0) //如果匹配到了
				{
					article[idx].TN[i]++;
					break;
				} 
		}//找完了全部单词 

		article[idx].word_n=word_n; //记录单词数 
		for(i=0;i<m;i++)//对每个关键词 
		{
			if(article[idx].TN[i]>0) DN[i]++; //出现过 
			article[idx].TF[i] = (double)article[idx].TN[i]/(double)word_n*100.0; 
				//计算频数 
		} 
			
		idx++;
		if(word_len==-1) 
		{
			N=idx;//文章总数
//			//测试
//			for(i=1;i<=N;i++)
//				printf("%s\n",article[i-1].id); 
			return;
		}

	} //到此结束
	 
} 

void print_func()
{
	int i,j;
	for(i=0;i<res_n;i++)
		printf("%lf %d %s\n",article[i].sim,article[i].num,article[i].id);
		
	//其他输出 
	printf("N=%d,m=%d\n",N,m);
	
	for(i=0;i<m;i++)
		printf("%s - DN:%d IDF:%lf\n",keyword[i],DN[i],IDF[i]);
	for(i=0;i<N;i++)
	{
		printf("文章%d：",i+1);
		for(j=0;j<m;j++) printf("%lf ",article[i].TF[j]);
		printf("\n");
	}
	
}
