#include <bits/stdc++.h>
#include <windows.h>
#include <ctime>
#include <conio.h>
using namespace std;
#define getrand(a,b) (rand()%b+a)//��ȡ�����

bool randz=true;	//�Ƿ���������ϰ���(1��� 0�����) 
int skin=0;	//��ɫ��0���� 1���� 2��� 3�̰� 4�ݵ� 5�Ƽ� 6��� 7���� 8���� 9�ڰ� 
char peise[10][5]={"��Լ","����","���","�̰�","�ݵ�","�Ƽ�","���","����","����","�ڰ�"};
char YN[2][3]={"��","��"}; 
int xl=20,yl=12;//��ͼ�ĳ��Ϳ�(�������߽�) 
bool faster=1;

int len=3;//�ߵĳ��� 
int food=1;//�����Ƿ����ʳ�� 
int setspeed=25;

int fangxiang[5][2]=//���� 
{
	{ 0, 0},
	{ 0,-1},
	{ 0, 1},
	{-1, 0},
	{ 1, 0}
};

int d=2;//��ǰ�ߵķ��� 
COORD head;//��ͷ���� 
int room[32][22];//���ڴ����ͼ 

int main();
void choose(); 
int gaming();
void printr();
bool checkr();
void checkr2(int,int);
void go(int,int);
void color(int);
void move();
void makefood();
bool goout(int,int);
int returnspeed();


void pdot(); 
void phead();
void pbody();
void pwall();
void pfood();
void pspace();

int main()
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//���ع�� 

	unsigned seed=time(0);
    srand(seed);//������������� 

    go(4,4);pdot();color(240);printf("��ʼ��Ϸ");
	go(4,7);pdot();color(15);printf("������Ϸ");
    
    int a=0;
    int key=0;
    while(key!=13)
    {
    	key=getch();
    	if(key==224)
    	{
    		key=getch();
    		if(key==72||key==80) a=1-a;
    		if(!a)  go(4,4),pdot(),color(240),printf("��ʼ��Ϸ"),go(4,7),pdot(),color(15),printf("������Ϸ");
    		else  go(4,4),pdot(),color(15),printf("��ʼ��Ϸ"),go(4,7),pdot(),color(240),printf("������Ϸ");
		}
	}
    if(a)
	{
		choose();return 0;
	}
    
    while(1)
	{
		if(gaming())
		{
			system("cls");system("color 0F");main();return 0;
		}
	}

	return 0;
} 
void go(int x,int y)  //����ƶ�������X��ʾ�����꣬Y��ʾ�����ꡣ
{
    COORD coord;         //ʹ��ͷ�ļ��Դ�������ṹ
    coord.X=x*2;            //���ｫint����ֵ����short,�����������漰������ֵ�����ᳬ��short��Χ
    coord.Y=y+1;
    HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);  //��ñ�׼������
    SetConsoleCursorPosition(a,coord);         //�Ա�׼����ľ��Ϊ�������ÿ���̨�������
}
void choose()
{
	system("cls");
	system("color 0F");
	color(15);
	go(3,2);printf("��ͼ����");
	go(3,3);printf("��ͼ���");
	go(3,4);printf("�ƶ��ٶ�");
	go(3,5);printf("�Ƿ���������ϰ���");
	go(3,6);printf("�Ƿ����������ٹ���");
	go(3,7);printf("��ɫ");
	
	color(240);
	go(14,2);printf(" <%d> ",xl);
	color(15);
	go(14,3);printf(" <%d>",yl);
	go(14,4);printf(" <%d>",returnspeed());
	go(14,5);printf(" <%s>",YN[randz]);
	go(14,6);printf(" <%s>",YN[faster]);
	go(14,7);printf(" <%s>",peise[skin]);
	
	
	int a=1;
	bool b=0;
	int key=0;
	go(1,1+a);printf(">>");
	while(key!=27)
	{
		key=getch();
		
		if(key==224)
		{
			key=getch();
			if(key==72||key==80)
			{
				if(a==1) go(14,2),color(15),printf(" <%d>  ",xl);
				if(a==2) go(14,3),color(15),printf(" <%d>  ",yl);
				if(a==3) go(14,4),color(15),printf(" <%d>  ",returnspeed());
				if(a==4) go(14,5),color(15),printf(" <%s>  ",YN[randz]);
				if(a==5) go(14,6),color(15),printf(" <%s>  ",YN[faster]);
				if(a==6) go(14,7),color(15),printf(" <%s>  ",peise[skin]);
				go(1,1+a);printf("  ");
			}
			if(key==72)
			{
				if(a>1) a--;
			}
			if(key==80)
			{
				if(a<6) a++;
			}
			if(key==75)
			{
				if(a==1&&xl>8) xl--;
				if(a==2&&yl>8) yl--;
				if(a==3&&setspeed<50) setspeed+=5;
				if(a==4) randz=1-randz;
				if(a==5) faster=1-faster;
				if(a==6) skin--,skin+=(skin<0?10:0);
			}
			if(key==77)
			{
				if(a==1&&xl<30) xl++;
				if(a==2&&yl<20) yl++;
				if(a==3&&setspeed>10) setspeed-=5;
				if(a==4) randz=1-randz;
				if(a==5) faster=1-faster;
				if(a==6) skin++,skin-=(skin>9?10:0);
			}
			if(a==1) go(14,2),color(240),printf(" <%d> ",xl);
			if(a==2) go(14,3),color(240),printf(" <%d> ",yl);
			if(a==3) go(14,4),color(240),printf(" <%d> ",returnspeed());
			if(a==4) go(14,5),color(240),printf(" <%s> ",YN[randz]);
			if(a==5) go(14,6),color(240),printf(" <%s> ",YN[faster]);
			if(a==6) go(14,7),color(240),printf(" <%s> ",peise[skin]);
			go(1,1+a);color(15);printf(">>");
		}

	}
	system("cls");system("color 0F");
	main();
}
int gaming()
{
	system("cls");system("color 0F");
	len=3;
	for(int i=0;i<=xl+1;i++)
		for(int j=0;j<=yl+1;j++)
			if(i==0||j==0||i==xl+1||j==yl+1) room[i][j]=-1;
			else room[i][j]=0;
	if(randz)
	{
		int ii,iii;
		int jj=getrand(2,4)-1;
		for(int j=jj;j<=yl;j+=getrand(1,3))
		{
			ii=getrand(1,xl);
			iii=getrand(1,xl/2.5);
			for(int i=ii;i<=min(ii+iii,xl);i++) room[i][j]=-1;
		}		
				
		while(!checkr())
		{
			for(int i=1;i<=xl;i++)
				for(int j=1;j<=yl;j++)
					room[i][j]=0;
			
			jj=getrand(2,4)-1;
			for(int j=jj;j<=yl;j+=getrand(1,3))
			{
				ii=getrand(1,xl-1);
				iii=getrand(2,xl/2.5);
				for(int i=ii;i<=min(ii+iii,xl);i++) room[i][j]=-1;
			}		
		}		
	}		

	
	
	printr();
			
	makefood();//���ɵ�һ��ʳ�� 
	food=1;
	
	
	d=-5;//��ʼ������ 
	int speed=setspeed;go(xl*0.6,-1),color(7),printf("�ٶȣ�%d",returnspeed());
    while(room[head.X][head.Y]==-1) head.X=getrand(1,xl),head.Y=getrand(1,yl);
    room[head.X][head.Y]=len; 
    go(xl*0.2,-1);color(15);printf("��ǰ���ȣ�%d",len); 
	go(head.X,head.Y);phead();//��ӡ��ͷ 
	
	while(!kbhit()) {Sleep(50);}
	
	int key=0;
	int ld=d;//����δ���ĵķ���
	bool p=0,ped=0; 
	
	
	while(1)
	{
		key=0;
		ld=d;//����δ���ĵķ��� 
		p=0;
		for(int i=1;i<=speed;i++)//�ֶ��ʱ����ⷽ��,������ֻ��һ��ʱ���,�����������������ָ� 
		{
			if(kbhit()&&p==0)//����а������� 
			{
				p=1;
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
		if(!p) ped=1;
		if(ld!=d) ped=0; 
		if(p&&ped&&ld==d&&faster) speed=setspeed/1.5,go(xl*0.6,-1),color(15),printf("������~~");
		if(p==0&&ped&&ld==d||ld!=d) speed=setspeed,go(xl*0.6,-1),color(7),printf("�ٶȣ�%d",returnspeed());
		
		move();//�ƶ��� 
		if(room[head.X][head.Y]!=len)//�����ͷλ�õ����������ߵĳ���(˵���ƶ��������ж�Ϊײ��,δ�ı���ͷ��ֵ) 
		{
			go(0,yl+2);color(79);printf("��ײ���ˣ�");
			go(0,yl+4);pdot();color(240);printf("����һ��"); 
			go(0,yl+5);pdot();color(15);printf("����������");
			key=0;
			int a=0;
			while(key!=13)
			{
				key=getch();
				if(key==224)
				{
					key=getch();
					if(key==72||key==80) a=1-a;
					if(a==0) go(0,yl+4),pdot(),color(240),printf("����һ��"),go(0,yl+5),pdot(),color(15),printf("����������");
					else go(0,yl+4),pdot(),color(15),printf("����һ��"),go(0,yl+5),pdot(),color(240),printf("����������");
				}
			}
			
			return a;//�������� 
		}
		
		if(food==0) makefood();//�������û��ʳ��,������һ��ʳ�� 
		
	}
}
bool checkr()
{
	int flag=0;
	for(int i=1;i<=xl;i++)
	{
		for(int j=1;j<=yl;j++)
		{
			if(room[i][j]==0)
			{
				flag=0;

				if(room[i+1][j]==0) flag++;
				if(room[i-1][j]==0) flag++;
				if(room[i][j+1]==0) flag++;
				if(room[i][j-1]==0) flag++;
				if(flag<2) return false;
			}
		}
	}
	if(room[1][1]==0) checkr2(1,1);
	else if(room[1][2]==0) checkr2(1,2);
	for(int i=1;i<=xl;i++)
		for(int j=1;j<=yl;j++)
			if(room[i][j]==0) return false;
			else if(room[i][j]==-3) room[i][j]=0;

	return true;
}
void checkr2(int x,int y)
{
	if(room[x][y]==0)
	{
		room[x][y]=-3;
		checkr2(x+1,y);
		checkr2(x,y+1);
		checkr2(x-1,y);
		checkr2(x,y-1);
	}
}
void printr()
{
	for(int i=0;i<=xl+1;i++)
		for(int j=0;j<=yl+1;j++)
			if(room[i][j]==-1)
			{
				go(i,j);
				pwall();
			}//��ӡ��ͼ
}
bool goout(int x,int y)
{
	if(x<1||y<1||x>=xl||y>=yl) return false;
	return true;
}
void move()//�ߵ��ƶ� 
{
	head.X+=fangxiang[d][0];
	head.Y+=fangxiang[d][1];//��ͷ��˷����ƶ� 
	if(room[head.X][head.Y]!=0&&room[head.X][head.Y]!=-2)//�����ͷλ�ò��ǿյĻ�ʳ�� 
	{
		return;//��������,���ı�room���� 
	}
	if(room[head.X][head.Y]==-2)//�����ͷλ����ʳ�� 
	{
		len++;//����++ 
		food=0;//ʳ��״̬��Ϊ������
		go(xl*0.2,-1);color(15);printf("��ǰ���ȣ�%d",len); 
	}
	for(int i=1;i<=xl+1;i++) 
		for(int j=1;j<=yl+1;j++)//���� 
			if(room[i][j]>=1)//�����λ������ 
				if(room[head.X][head.Y]!=-2)//�����λ�ò���ʳ�� 
				{
					room[i][j]--;//��λ����ֵ-1,���λ�������е�λ������仯,��β��Ϊ�� 
					if(room[i][j]==0)//�����λ���Ǳ�Ϊ�յ���β 
					{
						go(i,j);pspace();//��� 
					}
					if(room[i][j]==len-1)
					{
						go(i,j);pbody();
					}
				}
				else if(room[i][j]==len-1)
				{
					go(i,j);pbody();
				}
				
	room[head.X][head.Y]=len;//��ͷ����Ϊ�ߵĳ���,Ҳ���ǵ�1�� 
	go(head.X,head.Y);phead();//��ӡ��ͷ 
}
void makefood()//����ʳ�� 
{
	int randx=getrand(1,xl),randy=getrand(1,yl);
	while(room[randx][randy]!=0)//�����λ�ò�Ϊ�� 
	{
		randx=getrand(1,xl); 
		randy=getrand(1,yl);//������� 
	}
	room[randx][randy]=-2;//���ô�λ��Ϊʳ�� 
	go(randx,randy);
	pfood();//��ӡʳ�� 
	food=1;//ʳ��״̬��Ϊ���� 
}
int randcolor(int c[],int n)
{
	return c[getrand(1,n)-1];
} 
void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
// 0, 16,  32  ,48  ,64 , 80,   96,  112 ,128 ,144 ,160 , 176    , 192 ,208,  224 ,240
//�� ���� ���� ǳ��  ��  ����  ���� ǳ�� ��� ���� ����  ����� �Һ� ǳ��  �׻�  �� 

void phead()
{
	if(skin==0) color(15),printf("��");
	if(skin==1) color(63),printf("��");
	if(skin==2) color(79),printf("��");
	if(skin==3) color(175),printf("��");
	if(skin==4) color(175),printf("��");
	if(skin==5) color(159),printf("��");
	if(skin==6) color(getrand(2,15)*16-1),printf("��");
	if(skin==7) color(getrand(0,255)),printf("��");
	if(skin==8) color(79),printf("��");
	if(skin==9) color(120),printf("��");
}
void pbody()
{
	if(skin==0) color(15),printf("��");
	if(skin==1) color(159),printf("��");
	if(skin==2) color(79),printf("��");
	if(skin==3) color(175),printf("��");
	if(skin==4) color(175),printf("��");
	if(skin==5) color(159),printf("��");
	if(skin==6) color(getrand(2,16)*16-1),printf("��");
	if(skin==7) color(getrand(0,255)),printf("��");
	if(skin==8) color(79),printf("��");
	if(skin==9) color(120),printf("��");
}
void pwall()
{
	if(skin==0) color(15);
	if(skin==1) color(143);
	if(skin==2) color(143);
	if(skin==3) color(143);
	if(skin==4) color(42);
	if(skin==5) color(25);
	if(skin==6) color(getrand(2,16)*16-1);
	if(skin==7) color(getrand(0,255));
	if(skin==8) color(76);
	if(skin==9) color(127);

	printf("��");
}
void pfood()
{
	if(skin==0) color(15);
	if(skin==1) color(9);
	if(skin==2) color(12);
	if(skin==3) color(10);
	if(skin==4) color(4);
	if(skin==5) color(3);
	if(skin==6) color(getrand(1,15));
	if(skin==7) color(getrand(0,255));
	if(skin==8) color(4);
	if(skin==9) color(15);

	printf("��");
}
void pspace()
{
	if(skin==0) color(0);
	if(skin==1) color(0);
	if(skin==2) color(0);
	if(skin==3) color(0);
	if(skin==4) color(0);
	if(skin==5) color(0);
	if(skin==6) color(0);
	if(skin==7) color(0);
	if(skin==8) color(0);
	if(skin==9) color(0);

	printf("Ҷ");
}
int returnspeed()
{
	return (60-setspeed);
}
void pdot()
{
	color(15);
	printf("��");
}
