#include <bits/stdc++.h>
#include <windows.h>
#include <ctime>
#include <conio.h>
using namespace std;

#define getrand(a,b) (rand()%b+a)//��ȡ�����

int len=10;//�ߵĳ��� 
int food=1;//�����Ƿ����ʳ�� 
int fangxiang[5][2]={{ 0, 0},{ 0,-1},{ 0, 1},{-1, 0},{ 1, 0}};//���� 
int xl=20,yl=12;//��ͼ�ĳ��Ϳ�(�������߽�) 
int d=2;//��ǰ�ߵķ��� 
COORD head;//��ͷ���� 
int room[32][32];//���ڴ����ͼ 
void go(int x,int y)  //����ƶ�������X��ʾ�����꣬Y��ʾ�����ꡣ
{
    COORD coord;         //ʹ��ͷ�ļ��Դ�������ṹ
    coord.X=x*2;            //���ｫint����ֵ����short,�����������漰������ֵ�����ᳬ��short��Χ
    coord.Y=y;
    HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);  //��ñ�׼������
    SetConsoleCursorPosition(a,coord);         //�Ա�׼����ľ��Ϊ�������ÿ���̨�������
}
void move()//�ߵ��ƶ� 
{
	head.X+=fangxiang[d][0];
	head.Y+=fangxiang[d][1];//��ͷ��˷����ƶ� 
	if(room[head.Y][head.X]!=0&&room[head.Y][head.X]!=-2)//�����ͷλ�ò��ǿյĻ�ʳ�� 
	{
		return;//�������������ı�room���飬�����������ж���ͷ���Ƿ�δ���ı����ж��Ƿ�ײ�� 
	}
	if(room[head.Y][head.X]==-2)//�����ͷλ����ʳ�� 
	{
		len++;//����++ 
		food=0;//ʳ��״̬��Ϊ������ 
	}
	for(int i=1;i<=xl+1;i++) 
		for(int j=1;j<=yl+1;j++)//���� 
			if(room[j][i]>=1)//�����λ������ 
				if(room[head.Y][head.X]!=-2)//��Ҫ��֤��λ�ò���ʳ�� 
				{
					room[j][i]--;//��λ����ֵ-1,ʹ��λ�������е�λ������仯,��β��Ϊ�� 
					if(room[j][i]==0)//�����λ���Ǳ�Ϊ�յ���β 
					{
						go(i,j);printf("  ");//��� 
					}
				}
				
	room[head.Y][head.X]=len;//��ͷ����Ϊ�ߵĳ���,Ҳ���ǵ�1�� 
	
	go(head.X,head.Y);printf("��");//��ӡ��ͷ 
}
void makefood()//����ʳ�� 
{
	int randx=getrand(1,xl),randy=getrand(1,yl);//�����һ������ 
	while(room[randy][randx]!=0)//��������λ�ò�Ϊ�� 
	{
		randx=getrand(1,xl); 
		randy=getrand(1,yl);//����������� 
	}
	room[randy][randx]=-2;//���ô�λ��Ϊʳ�� 
	go(randx,randy);
	printf("��");//��ӡʳ�� 
	food=1;//ʳ��״̬��Ϊ���� 
}
int main()//������ 
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//���ع�� 

	unsigned seed=time(0);
    srand(seed);//������������� 
    
	for(int i=0;i<=yl+1;i++)
		for(int j=0;j<=xl+1;j++)
			if(i==0||i==yl+1||j==0||j==xl+1)
			{
				room[i][j]=-1;
				go(j,i);
				printf("��");
			}//���ñ߽�  ��ӡ��ͼ
			
	makefood();//���ɵ�һ��ʳ�� 
	
	while(!kbhit()) {Sleep(10);} //���°���ǰ�������κζ��� 
	
	d=-3;//��ʼ������Ϊ����ʹ�䲻�����������ͻ 
    head.X=xl/2+1; 
    head.Y=yl/2+1;//������ͷλ��Ϊ����
    room[head.Y][head.X]=len; //��ͷ��Ϊ�߳� 
	go(head.X,head.Y);printf("��");//��ӡ��ͷ 
	
	while(1)
	{
		int ld=d;//����δ���ĵķ��� 
		int key=-1;
		for(int i=1;i<=25;i++)//�ֶ��ʱ����ⷽ��,������ֻ��һ��ʱ���,�����������������ָ� 
		{
			if(kbhit()&&key==-1)//����а���������δ����ȡ������ʹͬһʱ�䵥λ�ڰ��¶��ʱ������ǰһ�ΰ��������ǵȵ���һʱ�䵥λ��ȡ��������Ӧ����������ʵ�ֵ�ͷ�Ȳ����� 
			{
				key=getch();//��ȡ 
				if(key==224)//��ȡ�����ʱ���ȡ����,��һ�αض���224,�����ж϶�����Ƿ����ʱ���ٶ�ȡһ�� 
				{
					key=getch();
					     if(key==72) d=1;//�� 
					else if(key==80) d=2;//�� 
					else if(key==75) d=3;//�� 
					else if(key==77) d=4;//��				
				}
			} 
			Sleep(5);		
		}
		if(ld!=d&&(ld+d==3||ld+d==7)) d=ld;//������ĺ�ķ�����ԭ���ķ����ͻ(�ɷ�����),���ı䷽�� 
		move();//�ƶ��� 
		if(room[head.Y][head.X]!=len)//�����ͷλ�õ����������ߵĳ���(˵���ƶ��������ж�Ϊײ��,δ�ı���ͷ��ֵ) 
		{
			go(0,yl+3);//ʹ�����������ڵ����� 
			Sleep(250);
			return 0;//�������� 
		}
		
		if(food==0) makefood();//�������û��ʳ��,������һ��ʳ�� 
	}	
	return 0;//�������� 
}
