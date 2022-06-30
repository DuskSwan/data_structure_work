
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h> 
#include<math.h> 

#define WORD_MAXLEN 200 //��󵥴ʳ��� 
#define k_MAX 200 //���ؼ��ʸ��� 
#define article_MAX 2000 //�������/��ҳ���� 
#define id_MAX 100 //����ʶ�ų��� 

struct ArticleInfo //��¼��ƪ���� 
{
	char id[id_MAX]; //���/��ʶ�� 
	int num; //���
	int word_n; //�ܵ����� 
	int TN[k_MAX]; //�ؼ���Ƶ����֮���������Ƶ�� 
	double TF[k_MAX]; //�ؼ���Ƶ�ʱ�
	double sim; //��ض� 
}; 

int N; //��������
int m; //�ؼ�����
int res_n; //��Ҫ��ʾ�Ľ����Ŀ�� 
char keyword[k_MAX][WORD_MAXLEN]; //�ؼ����б�keyword[i]Ϊ�ؼ��� 
int DN[k_MAX]; //�ؼ��ʳ��ִ��� 
double IDF[k_MAX]; //���Ƶ�� 
struct ArticleInfo article[article_MAX]; //������Ϣ�б� 
char dict[418668][WORD_MAXLEN], stop[321][WORD_MAXLEN];
	//�ֵ乲418667����ֹͣ��320�� 

void test(int argc, char** argv);//����һЩ�÷� 
void readDictStop(); //�����ֵ���ֹͣ��
bool check(char word[]); 
void article_analyse();//�����ı��������ֱ�ӱ�����ȫ�ֱ����� 
int find_str(char strs[][WORD_MAXLEN], char *str, int len);
bool check(char word[]);
void print_res();
void show_info(struct ArticleInfo a);
int cmp(const void* a,const void* b);

int main(int argc, char** argv) //argc�ǵ�����Ŀ��argv�ǵ����� 
{
	//test(argc,argv);
	
	/***�����ֵ���ֹͣ��***/
	readDictStop();
	
	/***��ȡ����***/ 
	// 100 edu news article abcdefgh //����
	// 5 edu news article //������ 
	m=0; //��Ч�ؼ��ʸ��� 
	int k;
	for(k=2;k<argc;k++) 
	{
		if(!check(argv[k])) continue; //��Ч�ؼ��� 
		strcpy(keyword[m],argv[k]); //��ֵ
		m++;
	}
		//���Ͻ�����m�ǹؼ��ʸ��� 
	res_n = atoi(argv[1]); //��Ҫ��ʾ�Ľ����Ŀ�� 
	
	/*===========���ڴ��������롿=========*/
	//freopen("article.txt","r",stdin); //ԭ���� 
	freopen("testarticle.txt","r",stdin); //�������� 
	/*===========���ڴ��������롿=========*/
	
	
	/***����article�������ַ�����***/
	article_analyse(); //�����ó������ֵ 
	
	/***������***/
	int i,j;
	double temp; 
	for(i=0;i<m;i++) //��ÿ���ؼ��� 
	{
		if(DN[i]>0) IDF[i]=log10( (double)N/(double)DN[i] );//�������Ƶ�� 
		else IDF[i]=0.0;
	} 
		
	for(j=0;j<N;j++) //��ÿƪ���� 
	{
		temp = 0.0;
		for(i=0;i<m;i++)
			temp += (double)article[j].TF[i] * (double)IDF[i]; //TF��� 
		article[j].sim = temp;  //TF��ͳ���IDF 
	}

	/***������***/ 
	qsort(article,N,sizeof(article[0]),cmp);
	print_res(); 
	
	return 0; 
}

//���Թ��� 
void test(int argc, char** argv)
{
	FILE* fp;
	char word[WORD_MAXLEN];
	
	//��֤�������÷� 
	printf("\n������\n");
	printf("argc=%d\n",argc);
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
	
	 
}

//�����ֵ�ֹͣ�ʱ���������dict��stop�� 
void readDictStop()
{
	int i=0; 
	FILE* fp;
	char word[WORD_MAXLEN];
	//�ֵ� 
	fp = fopen("dictionary.txt","r");
	i=0; 
	while( fscanf(fp, "%s", word) != EOF)
		strcpy(dict[i++],word); //��ֵ
	//ֹͣ�� 
	fp = fopen("stopwords.txt","r");
	i=0; 
	while( fscanf(fp, "%s", word) != EOF)
		strcpy(stop[i++],word); //��ֵ 
}

//���ַ����б��в����ַ��� 
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
        return -1; //û�ҵ�������-1 
    return i; //�ҵ��ˣ��������� 
}

//�ַ����б��в����ַ���-���ֲ��� 
int find_str2(char strs[][WORD_MAXLEN], char *str, int len)
{
	int left = 0;//���±�
	int right = len - 1;//���±�
	
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		//���������midʱ��(left + right) / 2�������п���Խ��
		if(strcmp(strs[mid],str) < 0)
			left = mid + 1;
		else if (strcmp(strs[mid],str) > 0)
			right = mid - 1;
		else
			return mid;
	}
	if (left > right)
		return -1; //û�ҵ� 
}


//���ĳ������word�Ƿ������壬��������巵��ture������false 
bool check(char word[])
{
	if(find_str2(stop,word,320)>=0)
		return false;
	else if(find_str2(dict,word,418667)>=0)
		return true;
	else 
		return false;
} 



/*******
 * ��stdin�ж���һ�����ʣ�ת����Сд��ĸ�󣬱��浽Ŀ���ַ�У�
 * ����������\f��������з���ĸ�ַ��������ĵ��ʴ������ĵ�һ��
 * ��ĸ�ַ���ʼ��һֱ��������һ������ĸ���ʽ�����
 * ����\f����stdin�С������ȥ���� 
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
        ; // ������ͷ�ķ���ĸ���ַ�

    if (c == EOF) //��ͷ�� 
        return -1;
    else if (c == '\f') //�ָ��� 
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

//�������ºϼ��������ݸ��µ�article������ 
void article_analyse()
{
	int idx=0; //��ǰ��������
	char word[WORD_MAXLEN]; //����һ������ 
	int word_n; //��¼�ʻ��� 
	int word_len; //��¼���ʳ���
	int i;
	while(1) //������ȡ���� 
	{
		word_n = 0; //��ʼ����ǰ���µ�����Ϊ0
		
		scanf("%s", word);//���ȶ�����
		strcpy(article[idx].id, word); //��� 
		article[idx].num = idx+1 ; //���
		//printf("���� %s(����%d) ��ʼ\n",article[idx].id,idx);
		while(1) //������ȡ���� 
		{
			word_len=readWord(word); //��ȡһ������
			if(word_len<=0) break; //���������ֹ���������ȡ���� 
			if(!check(word)) continue; //��Ч�����򲻹� 
			//��Ч���ʵĻ�
			word_n++; //������+1
			for(i=0;i<m;i++)//�����Ƿ�Ϊ�ؼ��� 
				if(strcmp(keyword[i], word) == 0) //���ƥ�䵽��
				{
					article[idx].TN[i]++;
					break;
				} 
			//printf("%s \n",word);
		}//������ȫ������ 

		article[idx].word_n=word_n; //��¼������ 
		for(i=0;i<m;i++)//��ÿ���ؼ��� 
		{
			if(article[idx].TN[i]>0) DN[i]++; //���ֹ� 
			article[idx].TF[i] = (double)(article[idx].TN[i])/(double)word_n*100.0; 
				//����Ƶ�� 
		} 
		//printf("���� %s(����%d)���� ��ֹ����%d\n",article[idx].id,idx,word_len); 
		idx++; //������һƪ���� 
		if(word_len==-1) 
		{
			N=idx;//��������
//			//����
//			for(i=1;i<=N;i++)
//				printf("%s\n",article[i-1].id); 
			return;
		}

	} //���˽���
	 
} 

//��ӡ��� 
void print_res()
{
	int i;
	FILE* fp;
	//��Ļ��� 
	for(i=0;i<5;i++)
		printf("%lf %d %s\n",article[i].sim,article[i].num,article[i].id);
	//txt��� 
	fp = fopen("results.txt", "w");
	for(i=0;i<res_n;i++)
		fprintf(fp,"%lf %d %s\n",article[i].sim,article[i].num,article[i].id);
	
	//������� 
//	freopen("result_more.txt","w",stdout); //��������� 
//	printf("N=%d,m=%d\n",N,m);
//	for(i=0;i<m;i++)
//		printf("%s - DN:%d IDF:%lf\n",keyword[i],DN[i],IDF[i]);
//	for(i=0;i<N;i++)
//	{
//		//printf("����%d��",i+1);
//		show_info(article[i]);
//	}
}

//չʾ������Ϣ 
void show_info(struct ArticleInfo a)
{
	printf("id:%s\n",a.id);
	printf("num:%d\n",a.num);
	printf("word_n:%d\n",a.word_n);
	int i;
	printf("TN:\n");
	for(i=0;i<m;i++) printf("%d ",a.TN[i]);
	printf("\nTF:\n");
	for(i=0;i<m;i++) printf("%lf ",a.TF[i]);
	printf("\nsim:%lf\n\n",a.sim);
} 

//qsort�ıȽϺ���
int cmp(const void* a,const void* b)
{
	struct ArticleInfo *sa,*sb;
	sa = (struct ArticleInfo*)a;
	sb = (struct ArticleInfo*)b;
	double asim,bsim;
	asim = sa->sim;
	bsim = sb->sim;
	if(bsim-asim>0) return 1;
	else if(bsim-asim<0) return -1;
	else 
		return (sa->num) - (sb->num);
} 

