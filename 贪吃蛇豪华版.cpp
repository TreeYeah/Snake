#include <bits/stdc++.h>
#include <windows.h>
#include <ctime>
#include <conio.h>
using namespace std;
#define getrand(a,b) (rand() % (b - a + 1) + a) //获取随机数

bool randz=true;	//是否随机生成障碍物(1随机 0不随机) 
int skin=0;	//配色：0经典 1蓝白 2红白 3绿白 4草地 5科技 6随机 7混乱 8浪漫 9黑白 
char peise[10][5]={"简约","蓝白","红白","绿白","草地","科技","随机","混乱","浪漫","黑白"};
char YN[2][3]={"否","是"}; 
int xl=20,yl=12;//地图的长和宽(不包括边界) 
bool faster=1;

int len=3;//蛇的长度 
int food=1;//现在是否存在食物 
int setspeed=25;

int fangxiang[5][2]=//方向 
{
	{ 0, 0},
	{ 0,-1},
	{ 0, 1},
	{-1, 0},
	{ 1, 0}
};

int d=2;//当前蛇的方向 
COORD head;//蛇头坐标 
int room[32][22];//用于储存地图 

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
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//隐藏光标 

	unsigned seed=time(0);
    srand(seed);//设置随机数种子 

    go(4,4);pdot();color(240);printf("开始游戏");
	go(4,7);pdot();color(15);printf("设置游戏");
    
    int a=0;
    int key=0;
    while(key!=13)
    {
    	key=getch();
    	if(key==224)
    	{
    		key=getch();
    		if(key==72||key==80) a=1-a;
    		if(!a)  go(4,4),pdot(),color(240),printf("开始游戏"),go(4,7),pdot(),color(15),printf("设置游戏");
    		else  go(4,4),pdot(),color(15),printf("开始游戏"),go(4,7),pdot(),color(240),printf("设置游戏");
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
void go(int x,int y)  //光标移动函数，X表示横坐标，Y表示纵坐标。
{
    COORD coord;         //使用头文件自带的坐标结构
    coord.X=x*2;            //这里将int类型值传给short,不过程序中涉及的坐标值均不会超过short范围
    coord.Y=y+1;
    HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);  //获得标准输出句柄
    SetConsoleCursorPosition(a,coord);         //以标准输出的句柄为参数设置控制台光标坐标
}
void choose()
{
	system("cls");
	system("color 0F");
	color(15);
	go(3,2);printf("地图长度");
	go(3,3);printf("地图宽度");
	go(3,4);printf("移动速度");
	go(3,5);printf("是否随机生成障碍物");
	go(3,6);printf("是否开启长按加速功能");
	go(3,7);printf("配色");
	
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
			
	makefood();//生成第一个食物 
	food=1;
	
	
	d=-5;//初始化方向 
	int speed=setspeed;go(xl*0.6,-1),color(7),printf("速度：%d",returnspeed());
    while(room[head.X][head.Y]==-1) head.X=getrand(1,xl),head.Y=getrand(1,yl);
    room[head.X][head.Y]=len; 
    go(xl*0.2,-1);color(15);printf("当前长度：%d",len); 
	go(head.X,head.Y);phead();//打印蛇头 
	
	while(!kbhit()) {Sleep(50);}
	
	int key=0;
	int ld=d;//储存未更改的方向
	bool p=0,ped=0; 
	
	
	while(1)
	{
		key=0;
		ld=d;//储存未更改的方向 
		p=0;
		for(int i=1;i<=speed;i++)//分多个时间点检测方向,而不是只有一个时间点,这样可以提升操作手感 
		{
			if(kbhit()&&p==0)//如果有按键按下 
			{
				p=1;
				key=getch();//读取 
				if(key==224)//读取方向键时需读取两次,第一次必定是224,所以判断读入的是方向键时则再读取一次 
				{
					key=getch();
					     if(key==72) d=1;//上 
					else if(key==80) d=2;//下 
					else if(key==75) d=3;//左 
					else if(key==77) d=4;//右				
				}
				
			} 
			Sleep(5);		
		}
		
		if(ld!=d&&(ld+d==3||ld+d==7)) d=ld;//如果更改后的方向与原来的方向冲突(成反方向),不改变方向
		if(!p) ped=1;
		if(ld!=d) ped=0; 
		if(p&&ped&&ld==d&&faster) speed=setspeed/1.5,go(xl*0.6,-1),color(15),printf("加速中~~");
		if(p==0&&ped&&ld==d||ld!=d) speed=setspeed,go(xl*0.6,-1),color(7),printf("速度：%d",returnspeed());
		
		move();//移动蛇 
		if(room[head.X][head.Y]!=len)//如果蛇头位置的数不等于蛇的长度(说明移动函数中判定为撞到,未改变蛇头数值) 
		{
			go(0,yl+2);color(79);printf("你撞死了！");
			go(0,yl+4);pdot();color(240);printf("再来一次"); 
			go(0,yl+5);pdot();color(15);printf("返回主界面");
			key=0;
			int a=0;
			while(key!=13)
			{
				key=getch();
				if(key==224)
				{
					key=getch();
					if(key==72||key==80) a=1-a;
					if(a==0) go(0,yl+4),pdot(),color(240),printf("再来一次"),go(0,yl+5),pdot(),color(15),printf("返回主界面");
					else go(0,yl+4),pdot(),color(15),printf("再来一次"),go(0,yl+5),pdot(),color(240),printf("返回主界面");
				}
			}
			
			return a;//结束程序 
		}
		
		if(food==0) makefood();//如果场上没有食物,则生成一个食物 
		
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
			}//打印地图
}
bool goout(int x,int y)
{
	if(x<1||y<1||x>=xl||y>=yl) return false;
	return true;
}
void move()//蛇的移动 
{
	head.X+=fangxiang[d][0];
	head.Y+=fangxiang[d][1];//蛇头向此方向移动 
	if(room[head.X][head.Y]!=0&&room[head.X][head.Y]!=-2)//如果蛇头位置不是空的或食物 
	{
		return;//结束函数,不改变room数组 
	}
	if(room[head.X][head.Y]==-2)//如果蛇头位置是食物 
	{
		len++;//长度++ 
		food=0;//食物状态变为不存在
		go(xl*0.2,-1);color(15);printf("当前长度：%d",len); 
	}
	for(int i=1;i<=xl+1;i++) 
		for(int j=1;j<=yl+1;j++)//搜索 
			if(room[i][j]>=1)//如果此位置有蛇 
				if(room[head.X][head.Y]!=-2)//如果此位置不是食物 
				{
					room[i][j]--;//此位置数值-1,则此位置在蛇中的位置往后变化,蛇尾变为空 
					if(room[i][j]==0)//如果此位置是变为空的蛇尾 
					{
						go(i,j);pspace();//清空 
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
				
	room[head.X][head.Y]=len;//蛇头处设为蛇的长度,也就是第1节 
	go(head.X,head.Y);phead();//打印蛇头 
}
void makefood()//生成食物 
{
	int randx=getrand(1,xl),randy=getrand(1,yl);
	while(room[randx][randy]!=0)//随机的位置不为空 
	{
		randx=getrand(1,xl); 
		randy=getrand(1,yl);//重新随机 
	}
	room[randx][randy]=-2;//设置此位置为食物 
	go(randx,randy);
	pfood();//打印食物 
	food=1;//食物状态设为存在 
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
//黑 深蓝 深绿 浅蓝  红  深紫  土黄 浅灰 深灰 亮蓝 亮绿  最淡的蓝 桃红 浅紫  米黄  白 

void phead()
{
	if(skin==0) color(15),printf("□");
	if(skin==1) color(63),printf("■");
	if(skin==2) color(79),printf("■");
	if(skin==3) color(175),printf("■");
	if(skin==4) color(175),printf("■");
	if(skin==5) color(159),printf("■");
	if(skin==6) color(getrand(2,15)*16-1),printf("■");
	if(skin==7) color(getrand(0,255)),printf("■");
	if(skin==8) color(79),printf("■");
	if(skin==9) color(120),printf("■");
}
void pbody()
{
	if(skin==0) color(15),printf("□");
	if(skin==1) color(159),printf("■");
	if(skin==2) color(79),printf("■");
	if(skin==3) color(175),printf("■");
	if(skin==4) color(175),printf("■");
	if(skin==5) color(159),printf("■");
	if(skin==6) color(getrand(2,16)*16-1),printf("■");
	if(skin==7) color(getrand(0,255)),printf("■");
	if(skin==8) color(79),printf("■");
	if(skin==9) color(120),printf("■");
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

	printf("■");
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

	printf("●");
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

	printf("叶");
}
int returnspeed()
{
	return (60-setspeed);
}
void pdot()
{
	color(15);
	printf("·");
}
