#include <bits/stdc++.h>
#include <windows.h>
#include <ctime>
#include <conio.h>
using namespace std;

#define getrand(a,b) (rand()%b+a)//获取随机数

int len=10;//蛇的长度 
int food=1;//现在是否存在食物 
int fangxiang[5][2]={{ 0, 0},{ 0,-1},{ 0, 1},{-1, 0},{ 1, 0}};//方向 
int xl=20,yl=12;//地图的长和宽(不包括边界) 
int d=2;//当前蛇的方向 
COORD head;//蛇头坐标 
int room[32][32];//用于储存地图 
void go(int x,int y)  //光标移动函数，X表示横坐标，Y表示纵坐标。
{
    COORD coord;         //使用头文件自带的坐标结构
    coord.X=x*2;            //这里将int类型值传给short,不过程序中涉及的坐标值均不会超过short范围
    coord.Y=y;
    HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);  //获得标准输出句柄
    SetConsoleCursorPosition(a,coord);         //以标准输出的句柄为参数设置控制台光标坐标
}
void move()//蛇的移动 
{
	head.X+=fangxiang[d][0];
	head.Y+=fangxiang[d][1];//蛇头向此方向移动 
	if(room[head.Y][head.X]!=0&&room[head.Y][head.X]!=-2)//如果蛇头位置不是空的或食物 
	{
		return;//结束函数，不改变room数组，在主函数中判断蛇头处是否未被改变以判定是否撞到 
	}
	if(room[head.Y][head.X]==-2)//如果蛇头位置是食物 
	{
		len++;//长度++ 
		food=0;//食物状态变为不存在 
	}
	for(int i=1;i<=xl+1;i++) 
		for(int j=1;j<=yl+1;j++)//搜索 
			if(room[j][i]>=1)//如果此位置有蛇 
				if(room[head.Y][head.X]!=-2)//还要保证此位置不是食物 
				{
					room[j][i]--;//此位置数值-1,使此位置在蛇中的位置往后变化,蛇尾变为空 
					if(room[j][i]==0)//如果此位置是变为空的蛇尾 
					{
						go(i,j);printf("  ");//清空 
					}
				}
				
	room[head.Y][head.X]=len;//蛇头处设为蛇的长度,也就是第1节 
	
	go(head.X,head.Y);printf("□");//打印蛇头 
}
void makefood()//生成食物 
{
	int randx=getrand(1,xl),randy=getrand(1,yl);//随机第一组坐标 
	while(room[randy][randx]!=0)//如果随机的位置不为空 
	{
		randx=getrand(1,xl); 
		randy=getrand(1,yl);//重新随机坐标 
	}
	room[randy][randx]=-2;//设置此位置为食物 
	go(randx,randy);
	printf("●");//打印食物 
	food=1;//食物状态设为存在 
}
int main()//主函数 
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//隐藏光标 

	unsigned seed=time(0);
    srand(seed);//设置随机数种子 
    
	for(int i=0;i<=yl+1;i++)
		for(int j=0;j<=xl+1;j++)
			if(i==0||i==yl+1||j==0||j==xl+1)
			{
				room[i][j]=-1;
				go(j,i);
				printf("■");
			}//设置边界  打印地图
			
	makefood();//生成第一个食物 
	
	while(!kbhit()) {Sleep(10);} //按下按键前不做出任何动作 
	
	d=-3;//初始化方向为负数使其不与其他方向冲突 
    head.X=xl/2+1; 
    head.Y=yl/2+1;//设置蛇头位置为中心
    room[head.Y][head.X]=len; //蛇头处为蛇长 
	go(head.X,head.Y);printf("□");//打印蛇头 
	
	while(1)
	{
		int ld=d;//储存未更改的方向 
		int key=-1;
		for(int i=1;i<=25;i++)//分多个时间点检测方向,而不是只有一个时间点,这样可以提升操作手感 
		{
			if(kbhit()&&key==-1)//如果有按键按下且未曾读取按键（使同一时间单位内按下多次时不覆盖前一次按键，而是等到下一时间单位读取并做出相应反馈，方便实现掉头等操作） 
			{
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
		move();//移动蛇 
		if(room[head.Y][head.X]!=len)//如果蛇头位置的数不等于蛇的长度(说明移动函数中判定为撞到,未改变蛇头数值) 
		{
			go(0,yl+3);//使结束反馈不遮挡画面 
			Sleep(250);
			return 0;//结束程序 
		}
		
		if(food==0) makefood();//如果场上没有食物,则生成一个食物 
	}	
	return 0;//结束程序 
}
