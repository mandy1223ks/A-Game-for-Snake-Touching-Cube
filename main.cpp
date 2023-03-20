#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<windows.h>
#include<stdlib.h>
#include<string>
#include<time.h>

//the presence and value of a ball 
struct set{
	int b;
	int c;
	int color;
};

struct ball{
    int x;
    int y;
    int appear;
};

//the location of ball
struct setbackball{ 
	double x;
	int y;
	int bkcolor;
};

struct square_8 
{
	int appear[5];
	int y;	
};

struct square
{
	int a;
	int b[2];
	int x[2];
	int y[2];
};

struct cir
{
	int x;
	int y;
};


class object
{
	int appear[5];
	int num[5];
	int sqcolor[5];
	int magi[5];
	int y;
public:
	object();
	void set_y(int);
	int setsqcolor(int);
	void setnum_2(int ,int ,int [][5]);
	void setnum_2_color();
	void magic(int *);
	void square_wall(setbackball *, int *,int ,set init[][6],int * ,int , int , int );
	void square_wall_1(setbackball *, int *,int ,set init[][6],int * ,int , int , int );
	void square_wall_color(setbackball *, int *,int ,set init[][6],int * ,int);
	int hit_square_color(int *,int ,int *,int *,setbackball *,set init[][6],int ,int);
	int hit_square(int *,int ,int *,int *,setbackball *,set init[][6],int ,int);
	int hit_square_shut(int *,int ,int *,int *,ball *);
	void change_square_orin();
	void square_number_orin();
	int appear_cmp(int ,int );
	void draw_bar2(int);
	void draw_bar2(int ,int );
	void change_color_gl(int *);
	void change_y();
	void change_y2();
	int cmp_y();
	void orin();
	void perish_square(int ,int ,int [][5],int *);
};

object :: object()
{
	int i;
	for(i=0;i<5;i++)
	{
		appear[i]=0;
		num[i]=0;
		y=0;
	}
}

void object :: change_color_gl(int *g_b)
{
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill((*g_b)*70+35,y, BLACK);
}

void object :: draw_bar2(int i)
{
	char str[10];
	setfillstyle(SOLID_FILL,BLUE);
	bar(i*70+3,y+19,(i*70)+70-3,y+109);
	sprintf(str,"%d",num[i]);
	setbkcolor(1);
	if(num[i]<10)
	   outtextxy((i*70*2+70-20)/2,(2*(y)+120-20)/2,str);
	else
	    outtextxy((i*70*2+70-35)/2,(2*(y)+120-20)/2,str);
	setbkcolor(0);
}

void object :: draw_bar2(int i,int color)
{
	setfillstyle(SOLID_FILL,color);
	bar(i*70+3,y+19,(i*70)+70-3,y+109);
	setbkcolor(0);
}

void object :: square_number_orin(){
	int i;
	for(i=0;i<5;i++)
	{
		appear[i]=1;
		num[i]=rand()%2+1;
	}
}


//int rec(int *,int *,int ,int *,setbackball *,set * );

void printscore(int score){
	char str[10];
	settextstyle(4,0,2);
    sprintf(str,"%d",score);
    if(score<100)
        outtextxy(310,20,str);
    else
    	outtextxy(290,20,str);
}

//pass the position of the previous ball to the next 
void changebkball(setbackball *bkball,int ballsum){
	
	if(bkball[1].x<=bkball[0].x+10&&bkball[1].x>=bkball[0].x-10){
		for(int i=ballsum-1;i>=1;i--)
	    	bkball[i].x=bkball[i-1].x;
	}
	else if(bkball[1].x<bkball[0].x-10){
		bkball[1].x=mousex()-8;
		for(int i=2;i<=ballsum-1;i++){
			if(bkball[i].x<bkball[i-1].x)
			    bkball[i].x=bkball[i-1].x-8;
			else if(bkball[i].x>bkball[i-1].x)
			    bkball[i].x=bkball[i-1].x+8;
		}
	}
	else{
		bkball[1].x=mousex()+8;
		for(int i=2;i<=ballsum-1;i++){
			if(bkball[i].x<bkball[i-1].x)
			    bkball[i].x=bkball[i-1].x-8;
			else if(bkball[i].x>bkball[i-1].x)
			    bkball[i].x=bkball[i-1].x+8;
		}
	}
}

void object :: change_y(){
	y+=30;
}

void object :: change_y2(){
	y-=30;
}

void object :: set_y(int i){
	y=-860+i*300;
}

int object :: setsqcolor(int i){
	return sqcolor[i];
}


void  object :: change_square_orin(){
	for(int i=0;i<5;i++)
		sqcolor[i]=2;
}

int object :: cmp_y(){
	if(y>220 && y<310)
		return 1;
	else
		return 0;	
}

void object :: orin(){
	for(int i=0;i<5;i++)
	{
		appear[i]=0;
		num[i]=0;
	}
	y=-4000;
}

void object :: magic(int *g_b){
	int i;
	for(i=0;i<5;i++)
		if(appear[i]==1)
			if(rand()%3 == 2)
			{
				*g_b=i;
				break;
			}
} 

void object :: perish_square(int a,int option,int squ[][5],int *c){
	int i;
	if(option == 3)
		for(i=0;i<5;i++)
			if(appear[i]==1 && squ[a][i]==1)
				if(num[i]==1)
				{
					squ[a][i]=0;
					*c+=1;		
				}	
	for(i=0;i<5;i++)
		if(num[i]<=0)
			appear[i]=0;
} 

//compare whether the value of appear[a] is equal to b 
int object :: appear_cmp(int a,int b){
	if(appear[b]==a)
		return 1;
	else
		return 0;	
}

//set the presence and value(using random) of a ball 
void setnum(set init[][6],int ball_row){
	int i,num;
	for(num=0;num<ball_row;num++){
		for(i=0;i<6;i++)
	    	init[num][i].b=0;
		i=rand()%6;
		init[num][i].b=1;
		init[num][i].c=rand()%6+1;
		if(num==0){
			i=rand()%6;
			init[num][i].b=1;
			init[num][i].c=rand()%6+1;
		}	
	}
}

//set the appearance and value(use random) of a ball  and add the color information
void setnum_color(set init[][6],int ball_row){
	int i,num;
	for(num=0;num<ball_row;num++){
		for(i=0;i<6;i++)
	    	init[num][i].b=0;
		i=rand()%6;
		init[num][i].b=1;
		init[num][i].c=rand()%6+1;
		init[num][i].color=rand()%5+1;
		if(num==0){
			i=rand()%6;
			init[num][i].b=1;
			init[num][i].c=rand()%6+1;
			init[num][i].color=rand()%5+1;
		}	
	}
}


//set whether the box appears and its value 
void object :: setnum_2(int a,int option , int squ[][5]){
	int i,j;
	i=rand()%7;
	if(i==0){
		for(j=0;j<5;j++)
		{	
			appear[j]=1;
			num[j]=rand()%15+1;
		}
	}
	else{
		for(j=0;j<5;j++)
		{
			appear[j]=rand()%2;
			num[j]=rand()%25+1;
		}	
	}
	for(i-0;i<5;i++)
		if(appear[i]==1 && num[i]>=10)
			squ[a][i]=1;
		else
			squ[a][i]=0;	
	if(option == 5)
		appear[rand()%5]=0;		
}

//set the appearance and value of a ball  and add the color information 
void object :: setnum_2_color(){
	int i,j;
	i=rand()%7;
	if(i==0){
		for(j=0;j<5;j++)
		{	
		appear[j]=1;
		num[j]=rand()%15+1;
		sqcolor[j]=rand()%5+1;
		}
	}
	else{
		for(j=0;j<5;j++)
		{
			appear[j]=rand()%2;
			num[j]=rand()%25+1;
			sqcolor[j]=rand()%5+1;
		}	
	}
}


//judging whether the ball has been touched 
void hit_ball(set init[][6],int *ballsum,int n,int y,setbackball *bkball,int ball_row){
	int i,j,k;
	int y1;//the y coordinates of each row of balls 
	char str[10];
	for(k=0;k<ball_row;k++){
		y1=y+300*(k-1);
		for(i=0;i<n;i++){
			if(init[k][i].b==1){
				if(y1==160&&mousex()>=i*60-10&&mousex()<=i*60+40){ //make sure the mouse touches the bottom of the ball 
				    for(int j=*ballsum;j<*ballsum+init[k][i].c;j++){
			    	    bkball[j].x=bkball[*ballsum-1].x;
			        	bkball[j].y=345+20*j;
				    }//set the x coordinate of the newly added ball body to be the same as the original tail 
		    		*ballsum+=init[k][i].c;
					init[k][i].c=0;
		    		break;
		    	}
			}
    	}	
	}
}

//judging whether the ball is touched and then add the color information 
void hit_ball_color(set init[][6],int *ballsum,int n,int y,setbackball *bkball,int ball_row){
	int i,j,k,h;
	int y1;//the y coordinates of each row of balls 

	for(k=0;k<ball_row;k++){
		y1=y+300*(k-1);
		for(i=0;i<n;i++){
			if(init[k][i].b==1){
				if(y1==160&&mousex()>=i*60-10&&mousex()<=i*60+40){ //make sure the mouse touches the bottom of the ball 
				    for(int j=*ballsum;j<*ballsum+init[k][i].c;j++){
			    	    bkball[j].x=bkball[*ballsum-1].x;
			        	bkball[j].y=345+20*j;
				    }//set the x coordinate of the newly added ball body to be the same as the original tail 
		    		*ballsum+=1;
					init[k][i].c=0;
					for(h=*ballsum-1;h>0;h--){
						bkball[h].bkcolor=bkball[h-1].bkcolor;
					}
					bkball[0].bkcolor=init[k][i].color;
		    		break;
		    	}
			}
    	}	
	}
}

void draw_bar(object *rectan,int option)//draw a square 
{
	int i,j,color;
	for(i=0;i<3;i++)
	{
		for(j=0;j<5;j++)
		{
			if(rectan[i].appear_cmp(1,j))
			{
				if(option==2)
					rectan[i].draw_bar2(j,rectan[i].setsqcolor(j));
				else
					rectan[i].draw_bar2(j);	
			}
		}
	} 
} 

//draw a ball 
void drawcircle(int x,int y,int ballcolor){
	switch(ballcolor){
		case 0:
			setfillstyle(SOLID_FILL,YELLOW);
			break;
		case 1:
			setfillstyle(SOLID_FILL,1);
			break;
		case 2:
			setfillstyle(SOLID_FILL,2);
			break;
		case 3:
			setfillstyle(SOLID_FILL,3);
			break;
		case 4:
			setfillstyle(SOLID_FILL,6);
			break;
		case 5:
			setfillstyle(SOLID_FILL,7);
			break;
		case 6:
			setfillstyle(SOLID_FILL,10);
			break;
		case 7:
			setfillstyle(SOLID_FILL,13);
			break;
		case 8:
			setfillstyle(HATCH_FILL,14);
			break;
	}
	circle(x,y,10);
	floodfill(x,y, WHITE);
}

void drawcircle_color(int x,int y,int ballcolor){
	setfillstyle(SOLID_FILL,ballcolor);	
	circle(x,y,10);
	floodfill(x,y, WHITE);
}

void creat_eat_ball(int y,set init[][6],setbackball *bkball,int ball_row){//create balls (snake parts) that can be eliminated 
	int i,n;
	int y1;//the y coordinates of each row of balls 
	char str[10];
	char ballstr[10];
	for(n=0;n<ball_row;n++)
	{
		y1=y+300*(n-1);
		for(i=0;i<6;i++)
		{
				if(init[n][i].b==1)
				{
					setfillstyle(SOLID_FILL,LIGHTRED);
					circle(i*60+13,y1+219,10);
					floodfill(i*60+13,y1+219,WHITE);
					sprintf(str,"%d",init[n][i].c);
					settextstyle(10,0,1);
					if(init[n][i].c<10)
					    outtextxy(i*60+8,y1+190,str);
					else
				    	outtextxy(i*60+2,y1+190,str);
				}
		}	
	}
}

void creat_eat_ball_color(int y,set init[][6],setbackball *bkball,int ball_row){//create balls (snake parts) that can be eliminated and then adding the color information 
	int i,n;
	int y1;//the y coordinates of each row of balls 
	char str[10];
	char ballstr[10];
	for(n=0;n<ball_row;n++)
	{
		y1=y+300*(n-1);
		for(i=0;i<6;i++)
		{
				if(init[n][i].b==1)
				{
					setfillstyle(SOLID_FILL,init[n][i].color);
					circle(i*60+13,y1+219,10);
					floodfill(i*60+13,y1+219,WHITE);
				}
		}	
	}
}


void object :: square_wall(setbackball *bkball,int *y_ball,int ballsum,set init[][6],int *score,int ball_row,int ballcolor,int option){ //prevent the ball from going through the left and right of the block 
	int i,ball_x=mousex(),u,j,k,a=0,b=0;
	int f[5]={0};
	char str[10];
	char ballstr[10];
		if(y>220 && y<310)
		{
			 
			if(mousex()>=0 && mousex()<=70)
				f[0]=1;
			else
				f[0]=0;	
			if(mousex()>70 && mousex()<=140)
				f[1]=1;
			else
				f[1]=0;	
			if(mousex()>140 && mousex()<=210)
				f[2]=1;
			else
				f[2]=0;	
			if(mousex()>210 && mousex()<=280)
				f[3]=1;
			else
				f[3]=0;	
			if(mousex()>280 && mousex()<=350)
				f[4]=1;
			else
				f[4]=0;
		
			if(appear[mousex()/70]==1)
				if(f[mousex()/70]==1)
					NULL;
			if(appear[mousex()/70]==0)
				if(f[mousex()/70]==1)
					ball_x=mousex();			
			clearviewport();
			printscore(*score);
			if(appear[mousex()/70]==1)
			{	
				if(f[mousex()/70]==1)
				{
					if(mousex()>=ball_x)
					{
						if(appear[mousex()/70]==1)
							if(f[mousex()/70]==1)
								NULL;
						if(appear[mousex()/70]==0)
							if(f[mousex()/70]==1)
								ball_x=mousex();//	
						setfillstyle(SOLID_FILL, YELLOW);
						drawcircle((mousex()/70)*70-10,345,ballcolor);
						changebkball(bkball,ballsum);
						for(i=1;i<ballsum;i++){
							drawcircle((mousex()/70)*70-10,bkball[i].y,ballcolor);
						}
						bkball[0].x=mousex();
						sprintf(ballstr,"%d",ballsum);
						settextstyle(10,0,1);
						outtextxy(mousex()-10,315,ballstr);
						creat_eat_ball(*y_ball,init,bkball,ball_row);
					} 
					else
					{
					   	setfillstyle(SOLID_FILL, YELLOW);
						drawcircle((mousex()/70)*70+80,345,ballcolor);
						changebkball(bkball,ballsum);
						for(i=1;i<ballsum;i++){
							drawcircle((mousex()/70)*70+80,bkball[i].y,ballcolor);
						}
						bkball[0].x=mousex();
					    sprintf(ballstr,"%d",ballsum);
					    settextstyle(10,0,1);
						outtextxy(mousex()-10,315,ballstr);
						creat_eat_ball(*y_ball,init,bkball,ball_row);
					      
					}
				}
				else
				{//
				    setfillstyle(SOLID_FILL, YELLOW);
					drawcircle(mousex(),345,ballcolor);
					changebkball(bkball,ballsum);
					for(i=1;i<ballsum;i++){
						drawcircle(bkball[i].x,bkball[i].y,ballcolor);
						}
					bkball[0].x=mousex();
				    sprintf(ballstr,"%d",ballsum);
				    settextstyle(10,0,1);
					outtextxy(mousex()-10,315,ballstr);
					creat_eat_ball(*y_ball,init,bkball,ball_row);
				}	
				for(i=0;i<5;i++)
				{
					if(appear[i]==1)
					{
						setfillstyle(SOLID_FILL,BLUE);
						bar(i*70+3,y+19,(i*70)+70-3,y+109);
						sprintf(str,"%d",num[i]);
						setbkcolor(1);
						if(num[i]<10)
							outtextxy((i*70*2+70-20)/2,(2*(y)+120-20)/2,str);
						else
							outtextxy((i*70*2+70-35)/2,(2*(y)+120-20)/2,str);
							setbkcolor(0);
					}
				}
			}
				else
				{
				    setfillstyle(SOLID_FILL, YELLOW);
					drawcircle(mousex(),345,ballcolor);
					changebkball(bkball,ballsum);
					for(i=1;i<ballsum;i++){
						drawcircle(bkball[i].x,bkball[i].y,ballcolor);
					}
					bkball[0].x=mousex();
					sprintf(ballstr,"%d",ballsum);
				    settextstyle(10,0,1);
					outtextxy(mousex()-10,315,ballstr);
					creat_eat_ball(*y_ball,init,bkball,ball_row);
					for(i=0;i<5;i++)
					{
						if(appear[i]==1)
						{
							setfillstyle(SOLID_FILL,BLUE);
							bar(i*70+3,y+19,(i*70)+70-3,y+109);
							sprintf(str,"%d",num[i]);
							setbkcolor(1);
							if(num[i]<10)
							   outtextxy((i*70*2+70-20)/2,(2*(y)+120-20)/2,str);
							else
							    outtextxy((i*70*2+70-35)/2,(2*(y)+120-20)/2,str);
							setbkcolor(0);
						}
					}
				}
			if(option==4)
				delay(30);
			else
				delay(65);		
		}
}

void object :: square_wall_color(setbackball *bkball,int *y_ball,int ballsum,set init[][6],int *score,int ball_row){ //prevent the ball from going through the left and right of the block 
	int i,ball_x=mousex(),u,j,k,a=0,b=0;
	int f[5]={0};
	char str[10];
	char ballstr[10];
		if(y>220 && y<310)
		{
			 
			if(mousex()>=0 && mousex()<=70)
				f[0]=1;
			else
				f[0]=0;	
			if(mousex()>70 && mousex()<=140)
				f[1]=1;
			else
				f[1]=0;	
			if(mousex()>140 && mousex()<=210)
				f[2]=1;
			else
				f[2]=0;	
			if(mousex()>210 && mousex()<=280)
				f[3]=1;
			else
				f[3]=0;	
			if(mousex()>280 && mousex()<=350)
				f[4]=1;
			else
				f[4]=0;
		
			if(appear[mousex()/70]==1)
				if(f[mousex()/70]==1)
					NULL;
			if(appear[mousex()/70]==0)
				if(f[mousex()/70]==1)
					ball_x=mousex();			
			clearviewport();
			printscore(*score);
			if(appear[mousex()/70]==1)
			{	
				if(f[mousex()/70]==1)
				{
					if(mousex()>=ball_x)
					{
						if(appear[mousex()/70]==1)
							if(f[mousex()/70]==1)
								NULL;
						if(appear[mousex()/70]==0)
							if(f[mousex()/70]==1)
								ball_x=mousex();//	
						setfillstyle(SOLID_FILL, YELLOW);
						drawcircle_color((mousex()/70)*70-10,345,bkball[0].bkcolor);
						changebkball(bkball,ballsum);
						for(i=1;i<ballsum;i++){
							drawcircle_color((mousex()/70)*70-10,bkball[i].y,bkball[i].bkcolor);
						}
						bkball[0].x=mousex();
						sprintf(ballstr,"%d",ballsum);
						settextstyle(10,0,1);
						outtextxy(mousex()-10,315,ballstr);
						creat_eat_ball_color(*y_ball,init,bkball,ball_row);
					} 
					else
					{
					   	setfillstyle(SOLID_FILL, YELLOW);
						drawcircle_color((mousex()/70)*70+80,345,bkball[0].bkcolor);
						changebkball(bkball,ballsum);
						for(i=1;i<ballsum;i++){
							drawcircle_color((mousex()/70)*70+80,bkball[i].y,bkball[i].bkcolor);
						}
						bkball[0].x=mousex();
					    sprintf(ballstr,"%d",ballsum);
					    settextstyle(10,0,1);
						outtextxy(mousex()-10,315,ballstr);
						creat_eat_ball_color(*y_ball,init,bkball,ball_row);
					      
					}
				}
				else
				{//
				    setfillstyle(SOLID_FILL, YELLOW);
					drawcircle_color(mousex(),345,bkball[0].bkcolor);
					changebkball(bkball,ballsum);
					for(i=1;i<ballsum;i++)
						drawcircle_color(bkball[i].x,bkball[i].y,bkball[i].bkcolor);
					bkball[0].x=mousex();
				    sprintf(ballstr,"%d",ballsum);
				    settextstyle(10,0,1);
					outtextxy(mousex()-10,315,ballstr);
					creat_eat_ball_color(*y_ball,init,bkball,ball_row);
				}	
				for(i=0;i<5;i++)
				{
					if(appear[i]==1)
					{
						setfillstyle(SOLID_FILL,BLUE);
						bar(i*70+3,y+19,(i*70)+70-3,y+109);
						setbkcolor(0);
					}
				}
			}
				else
				{
				    setfillstyle(SOLID_FILL, YELLOW);
					drawcircle_color(mousex(),345,bkball[0].bkcolor);
					changebkball(bkball,ballsum);
					for(i=1;i<ballsum;i++){
						drawcircle_color(bkball[i].x,bkball[i].y,bkball[i].bkcolor);
					}
					bkball[0].x=mousex();
					sprintf(ballstr,"%d",ballsum);
				    settextstyle(10,0,1);
					outtextxy(mousex()-10,315,ballstr);
					creat_eat_ball_color(*y_ball,init,bkball,ball_row);
					for(i=0;i<5;i++)
					{
						if(appear[i]==1)
						{
							setfillstyle(SOLID_FILL,BLUE);
							bar(i*70+3,y+19,(i*70)+70-3,y+109);
							setbkcolor(0);
						}
					}
				}
			delay(70);	
		}
}


void object :: square_wall_1(setbackball *bkball,int *y_ball,int ballsum,set init[][6],int *score,int ball_row,int ballcolor,int option){ //prevent the ball from going through the left and right of the block 
	int i,ball_x=mousex(),u,j,k,a=0,b=0;
	int f[5]={0};
	char str[10];
	char ballstr[10];
		if(y>220 && y<310)
		{
			 
			if(mousex()>=0 && mousex()<=70)
				f[0]=1;
			else
				f[0]=0;	
			if(mousex()>70 && mousex()<=140)
				f[1]=1;
			else
				f[1]=0;	
			if(mousex()>140 && mousex()<=210)
				f[2]=1;
			else
				f[2]=0;	
			if(mousex()>210 && mousex()<=280)
				f[3]=1;
			else
				f[3]=0;	
			if(mousex()>280 && mousex()<=350)
				f[4]=1;
			else
				f[4]=0;
		
			if(appear[mousex()/70]==1)
				if(f[mousex()/70]==1)
					NULL;
			if(appear[mousex()/70]==0)
				if(f[mousex()/70]==1)
					ball_x=mousex();			
			clearviewport();
			printscore(*score);
			if(appear[mousex()/70]==1)
			{	
				if(f[mousex()/70]==1)
				{
					if(mousex()>=ball_x)
					{
						if(appear[mousex()/70]==1)
							if(f[mousex()/70]==1)
								NULL;
						if(appear[mousex()/70]==0)
							if(f[mousex()/70]==1)
								ball_x=mousex();//	
						setfillstyle(SOLID_FILL, YELLOW);
						drawcircle((mousex()/70)*70-10,345,ballcolor);
						changebkball(bkball,ballsum);
						for(i=1;i<ballsum;i++){
							drawcircle((mousex()/70)*70-10,bkball[i].y,ballcolor);
						}
						bkball[0].x=mousex();
						sprintf(ballstr,"%d",ballsum);
						settextstyle(10,0,1);
						outtextxy(mousex()-10,315,ballstr);
					} 
					else
					{
					   	setfillstyle(SOLID_FILL, YELLOW);
						drawcircle((mousex()/70)*70+80,345,ballcolor);
						changebkball(bkball,ballsum);
						for(i=1;i<ballsum;i++){
							drawcircle((mousex()/70)*70+80,bkball[i].y,ballcolor);
						}
						bkball[0].x=mousex();
					    sprintf(ballstr,"%d",ballsum);
					    settextstyle(10,0,1);
						outtextxy(mousex()-10,315,ballstr);
					      
					}
				}
				else
				{//
				    setfillstyle(SOLID_FILL, YELLOW);
					drawcircle(mousex(),345,ballcolor);
					changebkball(bkball,ballsum);
					for(i=1;i<ballsum;i++){
						drawcircle(bkball[i].x,bkball[i].y,ballcolor);
						}
					bkball[0].x=mousex();
				    sprintf(ballstr,"%d",ballsum);
				    settextstyle(10,0,1);
					outtextxy(mousex()-10,315,ballstr);
				}	
				for(i=0;i<5;i++)
				{
					if(appear[i]==1)
					{
						setfillstyle(SOLID_FILL,BLUE);
						bar(i*70+3,y+19,(i*70)+70-3,y+109);
						sprintf(str,"%d",num[i]);
						setbkcolor(1);
						if(num[i]<10)
							outtextxy((i*70*2+70-20)/2,(2*(y)+120-20)/2,str);
						else
							outtextxy((i*70*2+70-35)/2,(2*(y)+120-20)/2,str);
							setbkcolor(0);
					}
				}
			}
				else
				{
				    setfillstyle(SOLID_FILL, YELLOW);
					drawcircle(mousex(),345,ballcolor);
					changebkball(bkball,ballsum);
					for(i=1;i<ballsum;i++){
						drawcircle(bkball[i].x,bkball[i].y,ballcolor);
					}
					bkball[0].x=mousex();
					sprintf(ballstr,"%d",ballsum);
				    settextstyle(10,0,1);
					outtextxy(mousex()-10,315,ballstr);
					for(i=0;i<5;i++)
					{
						if(appear[i]==1)
						{
							setfillstyle(SOLID_FILL,BLUE);
							bar(i*70+3,y+19,(i*70)+70-3,y+109);
							sprintf(str,"%d",num[i]);
							setbkcolor(1);
							if(num[i]<10)
							   outtextxy((i*70*2+70-20)/2,(2*(y)+120-20)/2,str);
							else
							    outtextxy((i*70*2+70-35)/2,(2*(y)+120-20)/2,str);
							setbkcolor(0);
						}
					}
				}
				delay(35);		
		}
}

int object :: hit_square(int *y_ball,int n,int *k,int *ballsum,setbackball *bkball,set init[][6],int ball_row ,int ballcolor){
	int i,j,c,g=0;
	char str[10];
	char ballstr[10];
		for(i=0;i<n;i++){
			if(appear[i]==1){
				if(y==220&&mousex()>=i*70&&mousex()<=i*70+70) //make sure the mouse is touching the bottom of the block 
	   			{
	   		 		num[i]--;
	   		 		*ballsum=*ballsum-1;
	  				if(num[i]==9) //when changing from a 10-digit number to a one-digit number, the 10-digit number should be cleared 
	  	 			{
		 				//delay(30);
		   	     		clearviewport();
						setfillstyle(SOLID_FILL, YELLOW);
						drawcircle(mousex(),345,ballcolor);
						changebkball(bkball,*ballsum);
						for(i=1;i<*ballsum;i++){
							drawcircle(bkball[i].x,bkball[i].y,ballcolor);
						}
						bkball[0].x=mousex();
					    sprintf(ballstr,"%d",*ballsum);
					    settextstyle(10,0,1);
						outtextxy(mousex()-10,315,ballstr);
						creat_eat_ball(*y_ball,init,bkball,ball_row);
						for(j=0;j<5;j++)
						{
							if(appear[j]==1)
							{
								setfillstyle(SOLID_FILL,BLUE);
								//rectangle(i*70,y+19,(i*70)+70,y+109);
								bar(j*70+3,y+19,(j*70)+70-3,y+109);
								//floodfill(i*70+30,y+50,WHITE);
								sprintf(str,"%d",num[j]);
								setbkcolor(1);
								if(num[j]<10)
								   outtextxy((j*70*2+70-20)/2,(2*(y)+120-20)/2,str);
								else
								    outtextxy((j*70*2+70-35)/2,(2*(y)+120-20)/2,str);
								setbkcolor(0);
							}
						}
	   			 		*(k)=1; 
    		  		}  	
		       		g=1;
		       		delay(20);
				}
			}
			if(*ballsum<=0)
			    break; 
		}
		return g;
}


int object :: hit_square_color(int *y_ball,int n,int *k,int *ballsum,setbackball *bkball,set init[][6],int ball_row ,int ballcolor){
	int i,j,c,g=0;
	char str[10];
	char ballstr[10];
		for(i=0;i<n;i++){
			if(appear[i]==1){
				if(y==220&&mousex()>=i*70&&mousex()<=i*70+70) //make sure the mouse is touching the bottom of the block 
	   			{
	   				if(bkball[0].bkcolor==sqcolor[i]){
	   					num[i]=0;
	   					for(i=0;i<*ballsum;i++)
	   						bkball[i].bkcolor=bkball[i+1].bkcolor;	
	   					*ballsum=*ballsum-1;
					}
	   		 		else{
	   		 			num[i]=1;
	   		 			for(i=0;i<*ballsum;i++)
	   						bkball[i].bkcolor=bkball[i+1].bkcolor;
	   		 			*ballsum=*ballsum-1;
					}	
		       		g=1;
		       		delay(20);
				}
			}
			if(*ballsum<=0)
			    break; 
		}
		return g;
}

int object :: hit_square_shut(int *y_ball,int n,int *k,int *ballsum,ball *shutball){
	int i,j,c,g=0;
	char str[10];
	char ballstr[10];
	for(i=0;i<n;i++){
		if(appear[i]==1){
			for(int k=0;k<25;k++){
				if(y>=shutball[k].y-100 &&y<=shutball[k].y-55 &&shutball[k].x>=i*70&&shutball[k].x<=i*70+70) //make sure the mouse is touching the bottom of the block 
	   			{
	   	 			num[i]--;
	   	 			g=1;
	   	 			shutball[k].appear=0;
	       			delay(20);
				}
				if(y>=295&&y<=390&&mousex()>=i*70&&mousex()<=i*70+70)
					*ballsum=0;
				
				}
		}
		if(*ballsum<=0)
		    break; 
	}
	return g;
}

//return score and the ballsum (the length of the snake) to their initial values 
void inital(int *score,int *ballsum){
	*ballsum=5;
	*score=0;
}

int rec(object *rectan_1,object *rectan_2,int ballsum,int *score,setbackball *bkball,set init[][6],int ball_row,int ballcolor , int option,int *c){
	int i,a=2,y=-860,j,k=0,l,m_1=0,m_2=0,n=0,gl=1,g_a,*g_b,r=0;
	g_b=&r;
	int cur_page = 0;
	char str[10];
	int squ_1[3][5],squ_2[2][5];
	int num,y_1=-860,y_2=-1720;
	char ballstr[10];
	if(option != 2)
	{
		for(i=0;i<3;i++)
			rectan_1[i].change_square_orin();
		for(i=0;i<2;i++)
			rectan_2[i].change_square_orin();	
	}
	for(i=0;i<2;i++)
		rectan_2[i].orin();
	for(i=0;i<3;i++)
	{
		rectan_1[i].setnum_2(i,option,squ_1);			
		rectan_1[i].set_y(i);
		y_1=-860;
	}
	setnum(init,ball_row);
	rectan_1[2].square_number_orin();
	while(ballsum>0)
	{
		if(y_1==40)
			for(i=0;i<2;i++)
			{
				rectan_2[i].set_y(i);
				rectan_2[i].setnum_2(i,option,squ_2);
				y_2=-860;
			}
		if(y_1>880)
		{
			for(i=0;i<3;i++)
			{
				rectan_1[i].setnum_2(i,option,squ_1);			
				rectan_1[i].set_y(i);
				y_1=-860;
			}
			gl++; 
			if(gl==4)
				gl=1;
			setnum(init,ball_row);
		}
		if(gl==3)
		{
			for(i=0;i<3;i++)
			{
				rectan_1[i].magic(g_b);
				if((*g_b)!=0)
				{
					g_a=i;
					break;
				}
			}
			gl=3;
		}
		settextstyle(10,0,4);
		setvisualpage(cur_page);
		cur_page = -cur_page + 1;
		setactivepage(cur_page);
		if(ballsum<=0)
			break;
		else
		{
			clearviewport();
			for(i=0;i<3;i++)
				if(rectan_1[i].cmp_y())
				{
					rectan_1[i].square_wall(bkball,&y_1,ballsum,init,score,i,ballcolor,option);
					draw_bar(rectan_1,option);
					draw_bar(rectan_2,option);
					creat_eat_ball(y_1,init,bkball,ball_row);
					y_1+=30;
					y_2+=30;
					rectan_1[i].change_y();
					n=1;
				}
			for(i=0;i<2;i++)	
				if(rectan_2[i].cmp_y())
				{
					rectan_2[i].square_wall(bkball,&y_2,ballsum,init,score,i,ballcolor,option);
					draw_bar(rectan_1,option);
					draw_bar(rectan_2,option);
					creat_eat_ball(y_1,init,bkball,ball_row);
					y_1+=30;
					y_2+=30;
					rectan_2[i].change_y();
					n=1;
				}
			if(n==0)
			{		
				setfillstyle(SOLID_FILL, YELLOW);
				drawcircle(mousex(),345,ballcolor);
				changebkball(bkball,ballsum);
				for(i=1;i<ballsum;i++){
					drawcircle(bkball[i].x,bkball[i].y,ballcolor);
				}
				bkball[0].x=mousex();
	   			sprintf(ballstr,"%d",ballsum);
	   			settextstyle(10,0,1);
				outtextxy(mousex()-10,315,ballstr);
				creat_eat_ball(y_1,init,bkball,ball_row);
				draw_bar(rectan_1,option);
				draw_bar(rectan_2,option);
				*score+=ballsum;
				i=0;
				for(l=0;l<3;l++)
				{
					m_1=rectan_1[l].hit_square(&y_1,5,&k,&ballsum,bkball,init,ball_row,ballcolor);
					m_2=rectan_2[i].hit_square(&y_2,5,&k,&ballsum,bkball,init,ball_row,ballcolor);
					if(m_1==1 || m_2==1)
						break;
					if(i<1)
						i++;	
				}
				if(m_1==1 || m_2==1)
				{	
					for(j=0;j<3;j++)
						rectan_1[j].change_y2();
					for(j=0;j<2;j++)	
						rectan_2[j].change_y2();
					y_1-=30;
					y_2-=30;	
					m_1=0;
					m_2=0;
				}		
				*score-=ballsum;
				if(*score >=50 && option ==4)
					break;
				printscore(*score);
				y_1+=30;
				y_2+=30;
	   		}
	   		if(gl==3)
			{
				rectan_1[g_a].change_color_gl(g_b);
			}	
	   		for(i=0;i<3;i++)
				rectan_1[i].change_y();
			for(i=0;i<2;i++)	
				rectan_2[i].change_y();
	   		for(i=0;i<3;i++)
				rectan_1[i].perish_square(i,option,squ_1,c);
			for(i=0;i<2;i++)	
				rectan_2[i].perish_square(i,option,squ_2,c);
			if((*c)==3 && option == 3)
				break;	
			hit_ball(init,&ballsum,6,y_1,bkball,ball_row);
			hit_ball(init,&ballsum,6,y_2,bkball,ball_row);
				
			for(num=0;num<3;num++){
				for(i=0;i<6;i++){
					if(init[num][i].c==0)
						init[num][i].b=0;	
				}
			}
			if(ballsum>=50 && option == 6)
				break;
	   		n=0;			
			if(k==0)
				if(option == 4)	
					delay(50);
				else
					delay(80);	
			else 
				k=0;
			gl++;			
			printscore(*score);
		}
	}

	return ballsum;

}

//the rec used ub level one 
int rec1(object *rectan_1,object *rectan_2,int ballsum,int *score,setbackball *bkball,set init[][6],int ball_row,int ballcolor,int option){
	int i,a=2,y=-860,j,k=0,l,m_1=0,m_2=0,n=0;
	int cur_page = 0;
	char str[10];
	int *c,g=0;
	c=&g;
	int squ_1[3][5],squ_2[2][5];
	int num,y_1=-860,y_2=-1720;
	char ballstr[10];
	if(option != 2)
	{
		for(i=0;i<3;i++)
			rectan_1[i].change_square_orin();
		for(i=0;i<2;i++)
			rectan_2[i].change_square_orin();	
	}
	for(i=0;i<2;i++)
		rectan_2[i].orin();
	for(i=0;i<3;i++)
	{
		rectan_1[i].setnum_2(i,option,squ_1);			
		rectan_1[i].set_y(i);
		y_1=-860;
	}
	setnum(init,ball_row);
	rectan_1[2].square_number_orin();
	while(ballsum>0&&*score<=10)
	{
		if(y_1==40)
			for(i=0;i<2;i++)
			{
				rectan_2[i].set_y(i);
				rectan_2[i].setnum_2(i,option,squ_2);
				y_2=-860;
			}
		if(y_1>880)
		{
			for(i=0;i<3;i++)
			{
				rectan_1[i].setnum_2(i,option,squ_1);			
				rectan_1[i].set_y(i);
				y_1=-860;
			}
			setnum(init,ball_row);
		}
		settextstyle(10,0,4);
		setvisualpage(cur_page);
		cur_page = -cur_page + 1;
		setactivepage(cur_page);
		if(ballsum<=0)
			break;
		else
		{
			clearviewport();
			for(i=0;i<3;i++)
				if(rectan_1[i].cmp_y())
				{
					rectan_1[i].square_wall(bkball,&y_1,ballsum,init,score,i,ballcolor,option);
					draw_bar(rectan_1,option);
					draw_bar(rectan_2,option);
					creat_eat_ball(y_1,init,bkball,ball_row);
					y_1+=30;
					y_2+=30;
					rectan_1[i].change_y();
					n=1;
				}
			for(i=0;i<2;i++)	
				if(rectan_2[i].cmp_y())
				{
					rectan_2[i].square_wall(bkball,&y_2,ballsum,init,score,i,ballcolor,option);
					draw_bar(rectan_1,option);
					draw_bar(rectan_2,option);
					creat_eat_ball(y_1,init,bkball,ball_row);
					y_1+=30;
					y_2+=30;
					rectan_2[i].change_y();
					n=1;
				}
			if(n==0)
			{		
				setfillstyle(SOLID_FILL, YELLOW);
				drawcircle(mousex(),345,ballcolor);
				changebkball(bkball,ballsum);
				for(i=1;i<ballsum;i++){
					drawcircle(bkball[i].x,bkball[i].y,ballcolor);
				}
				bkball[0].x=mousex();
	   			sprintf(ballstr,"%d",ballsum);
	   			settextstyle(10,0,1);
				outtextxy(mousex()-10,315,ballstr);
				creat_eat_ball(y_1,init,bkball,ball_row);
				draw_bar(rectan_1,option);
				draw_bar(rectan_2,option);
				*score+=ballsum;
				i=0;
				for(l=0;l<3;l++)
				{
					m_1=rectan_1[l].hit_square(&y_1,5,&k,&ballsum,bkball,init,ball_row,ballcolor);
					m_2=rectan_2[i].hit_square(&y_2,5,&k,&ballsum,bkball,init,ball_row,ballcolor);
					if(m_1==1 || m_2==1)
						break;
					if(i<1)
						i++;	
				}
				if(m_1==1 || m_2==1)
				{	
					for(j=0;j<3;j++)
						rectan_1[j].change_y2();
					for(j=0;j<2;j++)	
						rectan_2[j].change_y2();
					y_1-=30;
					y_2-=30;	
					m_1=0;
					m_2=0;
				}		
				*score-=ballsum;
				printscore(*score);
				y_1+=30;
				y_2+=30;
	   		}
	   		for(i=0;i<3;i++)
				rectan_1[i].change_y();
			for(i=0;i<2;i++)	
				rectan_2[i].change_y();
	   		for(i=0;i<3;i++)
				rectan_1[i].perish_square(i,option,squ_1,c);
			for(i=0;i<2;i++)	
				rectan_2[i].perish_square(i,option,squ_2,c);
			hit_ball(init,&ballsum,6,y_1,bkball,ball_row);
			hit_ball(init,&ballsum,6,y_2,bkball,ball_row);
			for(num=0;num<3;num++){
				for(i=0;i<6;i++){
					if(init[num][i].c==0)
						init[num][i].b=0;	
				}
			}
	   		n=0;			
			if(k==0)	
				delay(70);
			else 
				k=0;		
			printscore(*score);
		}
	}

	return ballsum;

}

int rec2(object *rectan_1,object *rectan_2,int ballsum,int *score,setbackball *bkball,set init[][6],int ball_row,int ballcolor,int option){
	int i,a=2,y=-860,j,k=0,l,m_1=0,m_2=0,n=0;
	int cur_page = 0;
	char str[10];
	int squ_1[3][5],squ_2[2][5];
	int num,y_1=-860,y_2=-1720;
	char ballstr[10];
	int *c,g=0;
	c=&g;
	for(i=0;i<2;i++)
		rectan_2[i].orin();
	for(i=0;i<3;i++)
	{
		rectan_1[i].setnum_2_color();			
		rectan_1[i].set_y(i);
		y_1=-860;
	}
	setnum_color(init,ball_row);
	rectan_1[2].square_number_orin();
	while(ballsum>0&&*score<=40)
	{
		if(y_1==40)
			for(i=0;i<2;i++)
			{
				rectan_2[i].set_y(i);
				rectan_2[i].setnum_2_color();
				y_2=-860;
			}
		if(y_1>880)
		{
			for(i=0;i<3;i++)
			{
				rectan_1[i].setnum_2_color();			
				rectan_1[i].set_y(i);
				y_1=-860;
			}
			setnum_color(init,ball_row);
		}
		settextstyle(10,0,4);
		setvisualpage(cur_page);
		cur_page = -cur_page + 1;
		setactivepage(cur_page);
		if(ballsum<=0)
			break;
		else
		{
			clearviewport();
			for(i=0;i<3;i++)
				if(rectan_1[i].cmp_y())
				{
					rectan_1[i].square_wall_color(bkball,&y_1,ballsum,init,score,i);
					draw_bar(rectan_1,option);
					draw_bar(rectan_2,option);
					creat_eat_ball_color(y_1,init,bkball,ball_row);
					y_1+=30;
					y_2+=30;
					rectan_1[i].change_y();
					n=1;
				}
			for(i=0;i<2;i++)	
				if(rectan_2[i].cmp_y())
				{
					rectan_2[i].square_wall_color(bkball,&y_2,ballsum,init,score,i);
					draw_bar(rectan_1,option);
					draw_bar(rectan_2,option);
					creat_eat_ball_color(y_1,init,bkball,ball_row);
					y_1+=30;
					y_2+=30;
					rectan_2[i].change_y();
					n=1;
				}
			if(n==0)
			{		
				setfillstyle(SOLID_FILL, YELLOW);
				drawcircle_color(mousex(),345,bkball[0].bkcolor);
				changebkball(bkball,ballsum);
				for(i=1;i<ballsum;i++){
					drawcircle_color(bkball[i].x,bkball[i].y,bkball[i].bkcolor);
				}
				bkball[0].x=mousex();
	   			sprintf(ballstr,"%d",ballsum);
	   			settextstyle(10,0,1);
				outtextxy(mousex()-10,315,ballstr);
				creat_eat_ball_color(y_1,init,bkball,ball_row);
				draw_bar(rectan_1,option);
				draw_bar(rectan_2,option);
				*score+=ballsum;
				i=0;
				for(l=0;l<3;l++)
				{
					m_1=rectan_1[l].hit_square_color(&y_1,5,&k,&ballsum,bkball,init,ball_row,ballcolor);
					m_2=rectan_2[i].hit_square_color(&y_2,5,&k,&ballsum,bkball,init,ball_row,ballcolor);
					if(m_1==1 || m_2==1)
						break;
					if(i<1)
						i++;	
				}
				if(m_1==1 || m_2==1)
				{	
					for(j=0;j<3;j++)
						rectan_1[j].change_y2();
					for(j=0;j<2;j++)	
						rectan_2[j].change_y2();
					y_1-=30;
					y_2-=30;	
					m_1=0;
					m_2=0;
				}		
				*score-=ballsum;
				printscore(*score);
				y_1+=30;
				y_2+=30;
	   		}
	   		for(i=0;i<3;i++)
				rectan_1[i].change_y();
			for(i=0;i<2;i++)	
				rectan_2[i].change_y();
	   		for(i=0;i<3;i++)
				rectan_1[i].perish_square(i,option,squ_1,c);
			for(i=0;i<2;i++)	
				rectan_2[i].perish_square(i,option,squ_2,c);
			hit_ball_color(init,&ballsum,6,y_1,bkball,ball_row);
			hit_ball_color(init,&ballsum,6,y_2,bkball,ball_row);
			for(num=0;num<3;num++){
				for(i=0;i<6;i++){
					if(init[num][i].c==0)
						init[num][i].b=0;	
				}
			}
	   		n=0;			
			if(k==0)	
				delay(70);
			else 
				k=0;		
			printscore(*score);
		}
	}

	return ballsum;

}

int rec_5(object *rectan_1,object *rectan_2,int ballsum,int *score,setbackball *bkball,set init[][6],int ball_row,int ballcolor , int option,int *c){
	int i,a=2,y=-860,j,k=0,l,m_1=0,m_2=0,n=0;
	int cur_page = 0;
	char str[10];
	int squ_1[3][5],squ_2[2][5];
	int num,y_1=-860,y_2=-1720;
	char ballstr[10];
	if(option != 2)
	{
		for(i=0;i<3;i++)
			rectan_1[i].change_square_orin();
		for(i=0;i<2;i++)
			rectan_2[i].change_square_orin();	
	}
	for(i=0;i<2;i++)
		rectan_2[i].orin();
	for(i=0;i<3;i++)
	{
		rectan_1[i].setnum_2(i,option,squ_1);			
		rectan_1[i].set_y(i);
		y_1=-860;
	}
	setnum(init,ball_row);
	rectan_1[2].square_number_orin();
	while(ballsum>0)
	{
		if(y_1==40)
			for(i=0;i<2;i++)
			{
				rectan_2[i].set_y(i);
				rectan_2[i].setnum_2(i,option,squ_2);
				y_2=-860;
			}
		if(y_1>880)
		{
			for(i=0;i<3;i++)
			{
				rectan_1[i].setnum_2(i,option,squ_1);			
				rectan_1[i].set_y(i);
				y_1=-860;
			}
			setnum(init,ball_row);
			(*c)+=1;
		}
		if((*c)==7)
			break;
		settextstyle(10,0,4);
		setvisualpage(cur_page);
		cur_page = -cur_page + 1;
		setactivepage(cur_page);
		if(ballsum<=0)
			break;
		else
		{
			clearviewport();
			for(i=0;i<3;i++)
				if(rectan_1[i].cmp_y())
				{
					rectan_1[i].square_wall_1(bkball,&y_1,ballsum,init,score,i,ballcolor,option);
					draw_bar(rectan_1,option);
					draw_bar(rectan_2,option);
					y_1+=30;
					y_2+=30;
					rectan_1[i].change_y();
					n=1;
				}
			for(i=0;i<2;i++)	
				if(rectan_2[i].cmp_y())
				{
					rectan_2[i].square_wall_1(bkball,&y_2,ballsum,init,score,i,ballcolor,option);
					draw_bar(rectan_1,option);
					draw_bar(rectan_2,option);
					y_1+=30;
					y_2+=30;
					rectan_2[i].change_y();
					n=1;
				}
			if(n==0)
			{		
				setfillstyle(SOLID_FILL, YELLOW);
				drawcircle(mousex(),345,ballcolor);
				changebkball(bkball,ballsum);
				for(i=1;i<ballsum;i++){
					drawcircle(bkball[i].x,bkball[i].y,ballcolor);
				}
				bkball[0].x=mousex();
	   			sprintf(ballstr,"%d",ballsum);
	   			settextstyle(10,0,1);
				outtextxy(mousex()-10,315,ballstr);
				draw_bar(rectan_1,option);
				draw_bar(rectan_2,option);
				*score+=ballsum;
				i=0;
				for(l=0;l<3;l++)
				{
					m_1=rectan_1[l].hit_square(&y_1,5,&k,&ballsum,bkball,init,ball_row,ballcolor);
					m_2=rectan_2[i].hit_square(&y_2,5,&k,&ballsum,bkball,init,ball_row,ballcolor);
					if(m_1==1 || m_2==1)
						break;
					if(i<1)
						i++;	
				}
				if(m_1==1 || m_2==1)
				{	
					for(j=0;j<3;j++)
						rectan_1[j].change_y2();
					for(j=0;j<2;j++)	
						rectan_2[j].change_y2();
					y_1-=30;
					y_2-=30;	
					m_1=0;
					m_2=0;
				}		
				*score-=ballsum;
				if(*score >=50 && option ==4)
					break;
				printscore(*score);
				y_1+=30;
				y_2+=30;
	   		}
	   		for(i=0;i<3;i++)
				rectan_1[i].change_y();
			for(i=0;i<2;i++)	
				rectan_2[i].change_y();
	   		for(i=0;i<3;i++)
				rectan_1[i].perish_square(i,option,squ_1,c);
			for(i=0;i<2;i++)	
				rectan_2[i].perish_square(i,option,squ_2,c);
			if((*c)==3 && option == 3)
				break;	
			for(num=0;num<3;num++){
				for(i=0;i<6;i++){
					if(init[num][i].c==0)
						init[num][i].b=0;	
				}
			}
			if(ballsum>=50 && option == 6)
				break;
	   		n=0;			
			if(k==0)
				delay(55);	
			else 
				k=0;		
			printscore(*score);
		}
	}

	return ballsum;

}

int rec9(object *rectan_1,object *rectan_2,int ballsum,int *score,setbackball *bkball,set init[][6],int ball_row,int ballcolor , int option,int *c,ball *shutball){
	int i,a=2,y=-860,j,k=0,l,m_1=0,m_2=0,n=0;
	int cur_page = 0;
	char str[10];
	int squ_1[3][5],squ_2[2][5];
	int num,y_1=-860,y_2=-1720;
	char ballstr[10];
	if(option != 2)
	{
		for(i=0;i<3;i++)
			rectan_1[i].change_square_orin();
		for(i=0;i<2;i++)
			rectan_2[i].change_square_orin();	
	}
	for(i=0;i<2;i++)
		rectan_2[i].orin();
	for(i=0;i<3;i++)
	{
		rectan_1[i].setnum_2(i,option,squ_1);			
		rectan_1[i].set_y(i);
		y_1=-860;
	}
	setnum(init,ball_row);
	while(ballsum>0)
	{
		if(y_1==40)
			for(i=0;i<2;i++)
			{
				rectan_2[i].set_y(i);
				rectan_2[i].setnum_2(i,option,squ_2);
				y_2=-860;
			}
		if(y_1>880)
		{
			for(i=0;i<3;i++)
			{
				rectan_1[i].setnum_2(i,option,squ_1);			
				rectan_1[i].set_y(i);
				y_1=-860;
			}
			setnum(init,ball_row);
		}
		settextstyle(10,0,4);
		setvisualpage(cur_page);
		cur_page = -cur_page + 1;
		setactivepage(cur_page);
		if(ballsum<=0)
			break;
		else
		{
			clearviewport();
			setfillstyle(SOLID_FILL,LIGHTRED);
			bar(mousex()-20,385,mousex()+20,425);
			setfillstyle(SOLID_FILL,YELLOW);
			for(int j=0;j<25;j++)
				if(shutball[j].appear==1){
					printf("h\n");
					setfillstyle(SOLID_FILL,WHITE);
					circle(shutball[j].x,shutball[j].y,5);
				}
			if(n<=0)
			{		
				draw_bar(rectan_1,option);
				draw_bar(rectan_2,option);
				*score+=ballsum;
				i=0;
				for(l=0;l<3;l++)
				{
					m_1=rectan_1[l].hit_square_shut(&y_1,5,&k,&ballsum,shutball);
					m_2=rectan_2[i].hit_square_shut(&y_2,5,&k,&ballsum,shutball);
					if(m_1==1 || m_2==1)
						break;
					if(i<1)
						i++;	
				}	
				*score-=ballsum;
				if(*score >=50 && option ==4)
					break;
				printscore(*score);
				y_1+=30;
				y_2+=30;
				for(int j=0;j<13;j++){
					if(shutball[j].appear==1)
						circle(shutball[j].x,shutball[j].y,5);
					shutball[j].y-=30;	
					if(shutball[j].y<=-25){
						shutball[j].y=365;
						shutball[j].appear=1;
					}
					if(shutball[j].y==365)
						shutball[j].x=mousex();
				}
	   		}
	   		for(i=0;i<3;i++)
				rectan_1[i].change_y();
			for(i=0;i<2;i++)	
				rectan_2[i].change_y();
	   		for(i=0;i<3;i++)
				rectan_1[i].perish_square(i,option,squ_1,c);
			for(i=0;i<2;i++)	
				rectan_2[i].perish_square(i,option,squ_2,c);
			if((*c)==3 && option == 3)
				break;
			for(num=0;num<3;num++){
				for(i=0;i<6;i++){
					if(init[num][i].c==0)
						init[num][i].b=0;	
				}
			}
			if(ballsum>=50 && option == 6)
				break;
	   		n=0;			
			if(k==0)
				if(option == 4)	
					delay(50);
				else
					delay(85);	
			else 
				k=0;		
			printscore(*score);
		}
	}

	return ballsum;

}

int game(square s1,square s2){
	s1.x[0]=150;
	s2.x[0]=270;
	s1.y[0]=450;
	s2.y[0]=150;
	s1.b[0]=0;
	s1.b[1]=0;
	s2.b[0]=0;
	s2.b[1]=0;
	char str[10];
	struct cir cir_cle[1000];
	int i_x1=10 , j_x1=-10 , i_y1=15 , j_y1=15 , i_x2=-10 , j_x2=10 , i_y2=-15 , j_y2=15 , w=2 , c_1=0 , c_2=0 , cur_page=0 , n_cir=0 ,n=0,i,life=1;
	while(w){
		setvisualpage(cur_page);
		cur_page = -cur_page + 1;
		setactivepage(cur_page);
		clearviewport();
		if(s1.a>=0)
		{
			setfillstyle(SOLID_FILL,BLUE);
			bar(s1.x[0]-50,s1.y[0]-50,s1.x[0]+50,s1.y[0]+50);
			sprintf(str,"%d",s1.a);
			settextstyle(4,0,4);
			if(s1.a<10)
	   			outtextxy(s1.x[0]-20,s1.y[0]-10,str);
			else
			    outtextxy(s1.x[0]-25,s1.y[0]-15,str);
			s1.x[0]-=i_x1;
			s1.y[0]-=i_y1;
			if(s1.x[0]<=50 || s1.x[0]>=300)
				i_x1=-i_x1;
			if(s1.y[0]>=450 || s1.y[0]<=50)
				i_y1=-i_y1;	   
		}
		
		if(s1.b[0]!=0 || s1.b[1]!=0)
		{
			if(s1.b[0]!=0)
			{
				setfillstyle(SOLID_FILL,BLUE);
				bar(s1.x[0]-35,s1.y[0]-35,s1.x[0]+35,s1.y[0]+35);
				sprintf(str,"%d",s1.b[0]);
				settextstyle(4,0,2);
				if(s1.a<10)
	   				outtextxy(s1.x[0]-18,s1.y[0]-9,str);
				else
				    outtextxy(s1.x[0]-21,s1.y[0]-13,str);
				s1.x[0]-=i_x1;
				s1.y[0]-=i_y1;	
			}
			if(s1.b[1]!=0)
			{
				setfillstyle(SOLID_FILL,BLUE);
				bar(s1.x[1]-35,s1.y[1]-35,s1.x[1]+35,s1.y[1]+35);
				sprintf(str,"%d",s1.b[1]);
				settextstyle(4,0,2);
				if(s1.a<10)
	   				outtextxy(s1.x[1]-18,s1.y[1]-9,str);
				else
				    outtextxy(s1.x[1]-21,s1.y[1]-13,str);
				s1.x[1]-=i_x2;
				s1.y[1]-=i_y2;	
			}
			if(s1.x[0]<=35 )
			{
				i_x1=-i_x1;
				s1.x[0]=35;
			}
			if(s1.x[0]>=300)
			{
				i_x1=-i_x1;
				s1.x[0]=300;
			}	
			if(s1.y[0]>=465)
			{
				i_y1=-i_y1;
				s1.y[0]=450	;
			}
			if (s1.y[0]<=35)
			{
				i_y1=-i_y1;
				s1.y[0]=50;
			}
			if(s1.x[1]<=35 )
			{
				i_x2=-i_x2;
				s1.x[1]=35;
			}
			if(s1.x[1]>=315)
			{
				i_x2=-i_x2;
				s1.x[1]=315;
			}
			if(s1.y[1]>=465 )
			{
				i_y2=-i_y2;
				s1.y[1]=465;
			}
			if(s1.y[1]<=35)
			{
				i_y2=-i_y2;
				s1.y[1]=35;
			}
		}
		
		if(s2.a>=0)
		{
			setfillstyle(SOLID_FILL,BLUE);
			bar(s2.x[0]-50,s2.y[0]-50,s2.x[0]+50,s2.y[0]+50);
			sprintf(str,"%d",s2.a);
			settextstyle(4,0,4);
			if(s2.a<10)
	   			outtextxy(s2.x[0]-20,s2.y[0]-10,str);
			else
			    outtextxy(s2.x[0]-25,s2.y[0]-15,str);
			s2.x[0]-=j_x1;
			s2.y[0]-=j_y1;
			if(s2.x[0]<=50 || s2.x[0]>=300)
				j_x1=-j_x1;
			if(s2.y[0]>=450 || s2.y[0]<=50)
				j_y1=-j_y1;	   
		}
		
		if(s2.b[0]!=0 || s2.b[1]!=0)
		{
			if(s2.b[0]!=0)
			{
				setfillstyle(SOLID_FILL,BLUE);
				bar(s2.x[0]-35,s2.y[0]-35,s2.x[0]+35,s2.y[0]+35);
				sprintf(str,"%d",s2.b[0]);
				settextstyle(4,0,2);
				if(s2.a<10)
	   				outtextxy(s2.x[0]-18,s2.y[0]-9,str);
				else
				    outtextxy(s2.x[0]-21,s2.y[0]-13,str);
				s2.x[0]-=j_x1;
				s2.y[0]-=j_y1;	
			}
			if(s2.b[1]!=0)
			{
				setfillstyle(SOLID_FILL,BLUE);
				bar(s2.x[1]-35,s2.y[1]-35,s2.x[1]+35,s2.y[1]+35);
				sprintf(str,"%d",s2.b[1]);
				settextstyle(4,0,2);
				if(s2.a<10)
	   				outtextxy(s2.x[1]-18,s2.y[1]-9,str);
				else
				    outtextxy(s2.x[1]-21,s2.y[1]-13,str);
				s2.x[1]-=j_x2;
				s2.y[1]-=j_y2;	
			}
			if(s2.x[0]<=35 )
			{
				j_x1=-j_x1;
				s2.x[0]=35;
			}
			if(s2.x[0]>=300)
			{
				j_x1=-j_x1;
				s2.x[0]=300;
			}	
			if(s2.y[0]>=465)
			{
				j_y1=-j_y1;
				s2.y[0]=450;
			}
			if (s2.y[0]<=35)
			{
				j_y1=-j_y1;
				s2.y[0]=50;
			}
			if(s2.x[1]<=35 )
			{
				j_x2=-j_x2;
				s2.x[1]=35;
			}
			if(s2.x[1]>=315)
			{
				j_x2=-j_x2;
				s2.x[1]=315;
			}
			if(s2.y[1]>=465 )
			{
				j_y2=-j_y2;
				s2.y[1]=465;
			}
			if(s2.y[1]<=35)
			{
				j_y2=-j_y2;
				s2.y[1]=35;
			}
		}
		
		setfillstyle(SOLID_FILL,3);
		circle(mousex(),500,10);
		floodfill(mousex(),500, WHITE);
		setfillstyle(SOLID_FILL,4);
		for(i=0;i<n_cir;i++)
		{
			circle(cir_cle[i].x , cir_cle[i].y , 7);
			floodfill(cir_cle[i].x , cir_cle[i].y , WHITE);
		}
		for(i=0;i<n_cir;i++)
			cir_cle[i].y-=15;	
		if(ismouseclick(WM_LBUTTONDOWN))
		{
			if(n>5)
			{
				cir_cle[i].x=mousex();
				cir_cle[i].y=480;
				clearmouseclick(WM_LBUTTONDOWN);
				n_cir++;
				n=0;
			}
		}
		if(s1.a>=0)
			for(i=0;i<n_cir;i++)
			{
				if((cir_cle[i].x > s1.x[0]-50) && (cir_cle[i].x < s1.x[0]+50) && (cir_cle[i].y > s1.y[0]-50) && (cir_cle[i].y < s1.y[0]+50))
				{
					cir_cle[i].y=-1000;
					s1.a--;
				}
			}
		
		if(s1.b[0]!=0)	
		{
			for(i=0;i<n_cir;i++)
			{
				if((cir_cle[i].x > s1.x[0]-35) && (cir_cle[i].x < s1.x[0]+35) && (cir_cle[i].y > s1.y[0]-35) && (cir_cle[i].y < s1.y[0]+35))
				{
					cir_cle[i].y=-1000;
					s1.b[0]--;
				}
			}
		}
		
		if(s1.b[1]!=0)	
		{
			for(i=0;i<n_cir;i++)
			{
				if((cir_cle[i].x > s1.x[1]-35) && (cir_cle[i].x < s1.x[1]+35) && (cir_cle[i].y > s1.y[1]-35) && (cir_cle[i].y < s1.y[1]+35))
				{
					cir_cle[i].y=-1000;
					s1.b[1]--;
				}
			}
		}
		
		if(s2.a>=0)
			for(i=0;i<n_cir;i++)
			{
				if((cir_cle[i].x > s2.x[0]-50) && (cir_cle[i].x < s2.x[0]+50) && (cir_cle[i].y > s2.y[0]-50) && (cir_cle[i].y < s2.y[0]+50))
				{
					cir_cle[i].y=-1000;
					s2.a--;
				}
			}
		
		if(s2.b[0]!=0)	
		{
			for(i=0;i<n_cir;i++)
			{
				if((cir_cle[i].x > s2.x[0]-35) && (cir_cle[i].x < s2.x[0]+35) && (cir_cle[i].y > s2.y[0]-35) && (cir_cle[i].y < s2.y[0]+35))
				{
					cir_cle[i].y=-1000;
					s2.b[0]--;
				}
			}
		}
		
		if(s2.b[1]!=0)	
		{
			for(i=0;i<n_cir;i++)
			{
				if((cir_cle[i].x > s2.x[1]-35) && (cir_cle[i].x < s2.x[1]+35) && (cir_cle[i].y > s2.y[1]-35) && (cir_cle[i].y < s2.y[1]+35))
				{
					cir_cle[i].y=-1000;
					s2.b[1]--;
				}
			}
		}
		
		if(s1.a==0)
		{
			s1.b[0]=25;
			s1.b[1]=25;
			s1.x[1]=s1.x[0]-40;
			s1.x[0]=s1.x[0]+40;
			s1.y[1]=s1.y[0]+40;
			s1.y[0]=s1.y[0]-40;
			i_x2=-i_x1;
			i_y2=-i_y1;
			s1.a=-1;
		}
		
		if(s2.a==0)
		{
			s2.b[0]=25;
			s2.b[1]=25;
			s2.x[1]=s2.x[0]-40;
			s2.x[0]=s2.x[0]+40;
			s2.y[1]=s2.y[0]+40;
			s2.y[0]=s2.y[0]-40;
			j_x2=-j_x1;
			j_y2=-j_y1;
			s2.a=-1;
		}
		
		if(s1.a>0)
		{
			if(mousex()>s1.x[0]-50 && mousex()<s1.x[0]+50 && s1.y[0] >=450)
			{
				life=0;
				break;
			}
		}
		if(s1.b[0] !=0 || s1.b[1]!=0)
		{
			if(s1.b[0]!=0)
				if(mousex()>s1.x[0]-35 && mousex()<s1.x[0]+35 && s1.y[0]>=470)
				{
					life=0;
					break;
				}		
			if(s1.b[1]!=0)
				if(mousex()>s1.x[1]-35 && mousex()<s1.x[1]+35 && s1.y[1]>=470)
				{
					break;
					life=0;
				}
		}
		
		if(s2.a>0)
		{
			if(mousex()>s2.x[0]-50 && mousex()<s2.x[0]+50 && s2.y[0] >=440)
			{
				life=0;
				break;
			}
		}
		if(s1.b[0] !=0 || s1.b[1]!=0)
		{
			if(s2.b[0]!=0)
				if(mousex()>s2.x[0]-35 && mousex()<s2.x[0]+35 && s2.y[0]>=470)
				{
					life=0;
					break;
				}
					
			if(s2.b[1]!=0)
				if(mousex()>s2.x[1]-35 && mousex()<s2.x[1]+35 && s2.y[1]>=470)
				{
					life=0;
					break;
				}
		}
		if(s1.a<0 && s2.a<0 && s1.b[0]==0 && s1.b[1]==0 && s2.b[0]==0 && s2.b[1]==0)
			break;		
		delay(60);
		n++;
		
	} 	
	return (life);
	 	
}

int game_8 (square_8 *s1 )
{ 
	int cur_page=0 , cir_x=300 , cir_y=400, i_x=5 , i_y=10,t=0,i,j,n=3,life=1;
	for(i=0;i<2;i++)
		for(j=0;j<5;j++)
			s1[i].appear[j]=rand()%2;
	for(i=2;i<20;i++)
		for(j=0;j<5;j++)
			s1[i].appear[j]=rand()%6;	
	s1[0].y=190;		
	for(i=1;i<20;i++)
		s1[i].y=180-i*70;			
	while(2)
	{
		setvisualpage(cur_page);
		cur_page = -cur_page + 1;
		setactivepage(cur_page);
		clearviewport();
		setfillstyle(SOLID_FILL,3);
		line(mousex()-40,490,mousex()+40,490);
		setfillstyle(SOLID_FILL,3);
		circle(cir_x,cir_y,10);
		floodfill(cir_x,cir_y, WHITE);
		for(i=0;i<n;i++)
		{
			for(j=0;j<5;j++)
			{
				if(s1[i].appear[j]==1)
				{
					setfillstyle(SOLID_FILL,BLUE);
					bar(j*70+3,s1[i].y-30,(j*70)+70-3,s1[i].y+30);
				}
				if(s1[i].appear[j]==2)
				{
					setfillstyle(SOLID_FILL,12);
					bar(j*70+3,s1[i].y-30,(j*70)+70-3,s1[i].y+30);
				}
				if(s1[i].appear[j]==3)
				{
					setfillstyle(SOLID_FILL,9);
					bar(j*70+3,s1[i].y-30,(j*70)+70-3,s1[i].y+30);
				}
				if(s1[i].appear[j]==4)
				{
					setfillstyle(SOLID_FILL,14);
					bar(j*70+3,s1[i].y-30,(j*70)+70-3,s1[i].y+30);
				}
				if(s1[i].appear[j]==5)
				{
					setfillstyle(SOLID_FILL,15);
					bar(j*70+3,s1[i].y-30,(j*70)+70-3,s1[i].y+30);
				}
			}
		}
		if(t>400)
		{
			for(i=0;i<20;i++)
				s1[i].y+=80;
			n++;
			t=0;
		}
		for(i=0;i<n;i++)
		{
			for(j=0;j<5;j++)
			{
				if(s1[i].appear[j]>0)
				{
					if(cir_x >= j*70+3 && cir_x <= (j*70)+70-3 && cir_y == s1[i].y+40)
					{
						i_y=-i_y;
						s1[i].appear[j]--;
					}
					if(cir_x <= j*70-3 &&cir_x >= j*70-10   && cir_y <= s1[i].y+40 && cir_y >= s1[i].y-40)
					{
						i_x=-i_x;
						s1[i].appear[j]--;
					}
					if(cir_x >= (j*70)+70 && cir_x <= (j*70)+70+10  && cir_y <= s1[i].y+40 && cir_y >= s1[i].y-40)
					{
						i_x=-i_x;
						s1[i].appear[j]--;
					}
					if(cir_x >= j*70+3 && cir_x <= (j*70)+70-3 && cir_y == s1[i].y-40)
					{
						i_y=-i_y;
						s1[i].appear[j]--;
					}
				}
			}
		}	
		cir_x-=i_x;
		cir_y-=i_y;
		if(cir_x>=mousex()-3 && cir_x<=mousex()+3 && cir_y==480)
		{
			i_x=0;
			i_y=-i_y;
		}
		if(cir_x>=mousex()-15 && cir_x<mousex()-3 && cir_y==480)
		{
			i_x=2;
			i_y=-i_y;
		}
		if(cir_x>=mousex()-30 && cir_x<mousex()-15 && cir_y==480)
		{
			i_x=4;
			i_y=-i_y;
		}
		if(cir_x>=mousex()-45 && cir_x<mousex()-30 && cir_y==480)
		{
			i_x=6;
			i_y=-i_y;
		}
		if(cir_x<=mousex()+15 && cir_x>mousex()+3 && cir_y==480)
		{
			i_x=-2;
			i_y=-i_y;
		}
		if(cir_x<=mousex()+30 && cir_x>mousex()+15 && cir_y==480)
		{
			i_x=-4;
			i_y=-i_y;
		}
		if(cir_x<=mousex()+45 && cir_x>mousex()+30 && cir_y==480)
		{
			i_x=-6;
			i_y=-i_y;
		}
		if(cir_y<=10)
			i_y=-i_y;
		if(cir_x<=10)
			i_x=-i_x;
		if(cir_x>=340)
			i_x=-i_x;
		if(cir_y>=590)
			i_y=-i_y;
		if(cir_y>=590)
		{
			life=0;
			break;
		}
		t++;	
		delay(30);				
	}	
}

void remember_point(int score){
	FILE *fp;
	int a[1000],i=0,j=0,k;
	fp = fopen("rank.txt","r+");
	rewind(fp);
	while(!feof(fp) && fscanf(fp,"%d",&a[i]) !=EOF )
		i++;
	fclose(fp);
	fp = fopen("rank.txt","w+");
	rewind(fp);
	while(j<i)
	{
		if(score>a[j])
			break;
		j++;	
	}
	for(k=i-1;k>=j;k--)
		a[k+1]=a[k];
	a[j]=score;
	for(j=0;j<=i;j++)
		fprintf(fp,"   %d   ",a[j]);
	fclose(fp);		
}

void viewgameover(int score){
	char str[10];
	settextstyle(2,0,17);
    outtextxy(100,300,"¡½");
    delay(500);
    outtextxy(170,300,"¡½");
    delay(500);
    outtextxy(240,300,"¡½");
    delay(500);
    clearviewport();
	readimagefile("gameover.jpg",0,0,355,600);
    settextstyle(4,0,3);
    sprintf(str,"%d",score);
    outtextxy(80,400,"SCORE:");
    outtextxy(240,400,str);
}
void viewgameover(){
	settextstyle(2,0,17);
    outtextxy(100,300,"¡½");
    delay(500);
    outtextxy(170,300,"¡½");
    delay(500);
    outtextxy(240,300,"¡½");
    delay(500);
    clearviewport();
	readimagefile("gameover.JPG",0,0,355,600);	
}

int choose(int ballcolor){
	if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=115&&mousey()>=45&&mousex()>=40&&mousex()<=97)
		return 0;
	else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=115&&mousey()>=45&&mousex()>=147&&mousex()<=205)
		return 1;
	else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=115&&mousey()>=45&&mousex()>=256&&mousex()<=314)
		return 2;
	else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=245&&mousey()>=178&&mousex()>=40&&mousex()<=97)
		return 3;
	else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=245&&mousey()>=178&&mousex()>=147&&mousex()<=205)
		return 4;
	else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=245&&mousey()>=178&&mousex()>=256&&mousex()<=314)
		return 5;
	else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=375&&mousey()>=306&&mousex()>=40&&mousex()<=97)
		return 6;
	else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=375&&mousey()>=306&&mousex()>=147&&mousex()<=205)
		return 7;
	else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=375&&mousey()>=306&&mousex()>=256&&mousex()<=314)
		return 8;
	else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=513&&mousey()>=458&&mousex()>=106&&mousex()<=245)
		return ballcolor;
	else 
		return 9;
}

int main(){
	initwindow(350,600,"Lin");
	FILE *fp;
	char rank_1[5];
	int ballcolor=0;//color of the snake 
	int score=0;//score 
	int a=2,i,b=2,c=2,rank_0[5],n,*q,o=0;
	q=&o;
	struct square s1,s2;
	int resu;
	int ball_row=3;//numbers of rows of balls 
	object rectan_1[3],rectan_2[2];
	set init[ball_row][6];
	setbackball bkball[100];
	int ballsum=5;//the length of the snake 
	char ballstr[10],str[10];
	for(i=0;i<ballsum;i++){
			bkball[i].x=mousex();
			bkball[i].y=345+20*i;
	}
	srand(time(NULL));
	readimagefile("page.JPG",0,0,355,600);
	setcolor(15);
	setbkcolor(0);
	//enter the main game 
	while(a){
		if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=506&&mousey()>=457&&mousex()>=125&&mousex()<=226)
		{
			clearmouseclick(WM_LBUTTONDOWN);
			clearviewport();	
			while(a)
			{
				printscore(score);
				setnum(init,ball_row);
				settextstyle(10,0,4);
			    ballsum=rec(rectan_1,rectan_2,ballsum,&score,bkball,init,ball_row,ballcolor,0,q);
		        if(ballsum<=0){
	    	    	setactivepage(0);
	        		setvisualpage(0);
	        		clearviewport();
	        		remember_point(score);
		       		viewgameover(score);
	       			getch();
	       			ballsum=5;
	       			score=0;
	       			clearmouseclick(WM_LBUTTONDOWN);
	       			break;
				}
	    	}
    	readimagefile("page.JPG",0,0,355,600);
        }
        //enter the level game mode 
        else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=562&&mousey()>=499&&mousex()>=19&&mousex()<=73){
			clearviewport();
			clearmouseclick(WM_LBUTTONDOWN);
			readimagefile("roundpage.jpg",0,0,355,600);
			while(b){
				//Level 1 : Score more than 10 points 
				if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=115&&mousey()>=45&&mousex()>=40&&mousex()<=97){
					clearviewport();
					clearmouseclick(WM_LBUTTONDOWN);
					settextstyle(4,0,4);
					outtextxy(50,350,"[±o¤À>=10¤À]");
					delay(2000);
					clearviewport();	
					while(a&&score<10)
					{
						printscore(score);
						setnum(init,ball_row);
						settextstyle(10,0,4);
					    ballsum=rec1(rectan_1,rectan_2,ballsum,&score,bkball,init,ball_row,ballcolor,1);
				        if(ballsum<=0&&score<10){
	    			    	setactivepage(0);
	        				setvisualpage(0);
	        				settextstyle(4,0,5);
	        				outtextxy(1,350,"YOU LOSE!");
				        	delay(1000);
	        				clearviewport();
	        				viewgameover();
		    	   			outtextxy(1,350,"YOU LOSE!");
			       			getch();
			       			inital(&score,&ballsum);
		       				break;
						}
	    			}
	    			if(score>=10){
	    				setactivepage(0);
	        			setvisualpage(0);
	        			settextstyle(4,0,5);
	        			outtextxy(60,350,"Success!");
	    				delay(1000);
	    				clearviewport();
	    				viewgameover();
	    				outtextxy(60,350,"Success!");
	    				getch();
	    				inital(&score,&ballsum);
					}
					clearviewport();
    				readimagefile("page.JPG",0,0,355,600);
    				clearmouseclick(WM_LBUTTONDOWN);
					break;
				}
				
				//Level 2 
				else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=115&&mousey()>=45&&mousex()>=147&&mousex()<=205){//number of balls>50 
					clearviewport();
					clearmouseclick(WM_LBUTTONDOWN);
					settextstyle(4,0,3);
					outtextxy(5,350,"[color mode : score over 10]");
					delay(2000);
					clearviewport();
					ballsum=10;
					for(i=0;i<ballsum;i++)
						bkball[i].bkcolor=rand()%5+1;	
					while(a&&score<10)
					{
						printscore(score);
						setnum_color(init,ball_row);
						settextstyle(10,0,4);
					    ballsum=rec2(rectan_1,rectan_2,ballsum,&score,bkball,init,ball_row,ballcolor,2);
				        if(ballsum<=0&&score<40){
	    			    	setactivepage(0);
	        				setvisualpage(0);
	        				settextstyle(4,0,5);
	        				outtextxy(1,350,"YOU LOSE!");
				        	delay(1000);
	        				clearviewport();
	        				viewgameover();
		    	   			outtextxy(1,350,"YOU LOSE!");
			       			getch();
			       			inital(&score,&ballsum);
		       				break;
						}
	    			}
	    			if(score>=10){
	    				setactivepage(0);
	        			setvisualpage(0);
	        			settextstyle(4,0,5);
	        			outtextxy(60,350,"Success!");
	    				delay(1000);
	    				clearviewport();
	    				viewgameover();
	    				outtextxy(60,350,"Success!");
	    				getch();
	    				inital(&score,&ballsum);
					}
					clearviewport();
    				readimagefile("page.JPG",0,0,355,600);
    				clearmouseclick(WM_LBUTTONDOWN);
					break;
				}
				//Level 3 
				else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=115&&mousey()>=45&&mousex()>=256&&mousex()<=314){//hit 3 squares with a number greater than 10 
					clearmouseclick(WM_LBUTTONDOWN);
					clearviewport();
					settextstyle(4,0,3);
					outtextxy(5,350,"[hit 3 squares with a number greater than 10]");
					delay(2000);
					clearviewport();
					int *t,h=0;
					t=&h;
					(*t)=0;
					while(a&&score<10)
					{
						printscore(score);
						setnum(init,ball_row);
						settextstyle(10,0,4);
					    ballsum=rec(rectan_1,rectan_2,ballsum,&score,bkball,init,ball_row,ballcolor,3,t);
				        if(ballsum<=0 || *t==3){
	    			    	setactivepage(0);
	        				setvisualpage(0);
	        				clearviewport();
			    	   		readimagefile("gameover.JPG",0,0,355,600);
		    	   			settextstyle(4,0,5);
		    	   			if(ballsum<=0)
		    	   				outtextxy(10,400,"YOU LOSE!");
		    	   			else
							   	outtextxy(10,400,"Congratulations!");
			       			getch();
			       			ballsum=5;
		    	   			score=0;
		       				break;
						}
	    			}
	    			clearviewport();
    				readimagefile("page.JPG",0,0,355,600);
    				clearmouseclick(WM_LBUTTONDOWN);
					break;
				}
				//Level 4 
				else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=245&&mousey()>=178&&mousex()>=40&&mousex()<=97){//get the score of 50 points in boost mode
					clearmouseclick(WM_LBUTTONDOWN);
					clearviewport();
					settextstyle(4,0,4);
					outtextxy(5,350,"[get 50 points ft.boost mode]");
					delay(2000);
					clearviewport();
					while(a&&score<10)
					{
						printscore(score);
						setnum(init,ball_row);
						settextstyle(10,0,4);
					    ballsum=rec(rectan_1,rectan_2,ballsum,&score,bkball,init,ball_row,ballcolor,4,q);
				        if(ballsum<=0 || score>=50){
	    			    	setactivepage(0);
	        				setvisualpage(0);
	        				clearviewport();
			    	   		readimagefile("gameover.JPG",0,0,355,600);
		    	   			settextstyle(4,0,5);
		    	   			if(ballsum<=0)
		    	   				outtextxy(10,400,"YOU LOSE!");
		    	   			else
							   	outtextxy(10,400,"Congratulations!");
			       			getch();
			       			ballsum=5;
		    	   			score=0;
		       				break;
						}
	    			}
	    			clearviewport();
    				readimagefile("page.JPG",0,0,355,600);
					clearmouseclick(WM_LBUTTONDOWN); 
					break;
				}
				//Level 5 
				else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=245&&mousey()>=178&&mousex()>=147&&mousex()<=205){//survive with only one life (one ball) 
					clearmouseclick(WM_LBUTTONDOWN);
					clearviewport();
					settextstyle(4,0,4);
					outtextxy(5,350,"[survive with only one life]");
					delay(2000);
					clearviewport();
					ballsum=1;
					while(a&&score<10)
					{
						printscore(score);
						setnum(init,ball_row);
						settextstyle(10,0,4);
					    ballsum=rec_5(rectan_1,rectan_2,ballsum,&score,bkball,init,ball_row,ballcolor,5,q);
				        if(ballsum<=0 || (*q)>=7){
	    			    	setactivepage(0);
	        				setvisualpage(0);
	        				clearviewport();
			    	   		readimagefile("gameover.JPG",0,0,355,600);
		    	   			settextstyle(4,0,5);
		    	   			if(ballsum<=0)
		    	   				outtextxy(10,400,"YOU LOSE!");
		    	   			else
							   	outtextxy(10,400,"Congratulations!");
			       			getch();
			       			(*q)=0;
			       			ballsum=5;
		    	   			score=0;
		       				break;
						}
	    			}
	    			clearviewport();
    				readimagefile("page.JPG",0,0,355,600);
    				clearmouseclick(WM_LBUTTONDOWN);
					break;
				}
				else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=245&&mousey()>=178&&mousex()>=256&&mousex()<=314){
					clearviewport();
					clearmouseclick(WM_LBUTTONDOWN);
					settextstyle(4,0,4);
					outtextxy(50,350,"[the number of balls is larger than 50]");
					delay(2000);
					clearviewport();
					while(a)
					{
						printscore(score);
						setnum(init,ball_row);
						settextstyle(10,0,4);
					    ballsum=rec(rectan_1,rectan_2,ballsum,&score,bkball,init,ball_row,ballcolor,6,q);
				        if(ballsum<=0 || ballsum>=50){
	    			    	setactivepage(0);
	        				setvisualpage(0);
	        				clearviewport();
			    	   		readimagefile("gameover.JPG",0,0,355,600);
		    	   			settextstyle(4,0,5);
		    	   			if(ballsum>=50)
		    	   				outtextxy(10,400,"Congratulations!");
		    	   			else
		    	   				outtextxy(10,400,"YOU LOSE!");
			       			getch();
			       			ballsum=5;
		    	   			score=0;
		       				break;
						}
	    			}
	    			clearviewport();
    				readimagefile("page.JPG",0,0,355,600);
    				clearmouseclick(WM_LBUTTONDOWN);
					break;
				}
				//Level 6 
				else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=375&&mousey()>=306&&mousex()>=40&&mousex()<=97){
					clearviewport();
					clearmouseclick(WM_LBUTTONDOWN);
					settextstyle(4,0,3);
					outtextxy(50,350,"[touch two big squares]");
					delay(2000);
					clearviewport();
					s1.a=40;
					s2.a=40;
					resu=game(s1,s2);
					setactivepage(0);
	        		setvisualpage(0);
	        		clearviewport();
			    	readimagefile("gameover.JPG",0,0,355,600);
		    	   	settextstyle(4,0,5);
					if(resu==1)
						outtextxy(10,400,"Congratulations!");
					else	
						outtextxy(10,400,"YOU LOSE!");
					getch();
					clearviewport();
    				readimagefile("page.JPG",0,0,355,600);
    				clearmouseclick(WM_LBUTTONDOWN);
					break;	
				}
				else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=375&&mousey()>=306&&mousex()>=147&&mousex()<=205){
					clearviewport();
					clearmouseclick(WM_LBUTTONDOWN);
					settextstyle(4,0,3);
					outtextxy(50,350,"[colorful snake and square]");
					delay(2000);
					clearviewport();
					struct square_8 s1[20];
					resu=game_8(s1);
					setactivepage(0);
	        		setvisualpage(0);
	        		clearviewport();
			    	readimagefile("gameover.JPG",0,0,355,600);
		    	   	settextstyle(4,0,5);
					if(resu==1)
						outtextxy(10,400,"Congratulations!");
					else
						outtextxy(10,400,"YOU LOSE!");	
					getch();
					clearviewport();
    				readimagefile("page.JPG",0,0,355,600);
    				clearmouseclick(WM_LBUTTONDOWN);
					break;
				}
				//Level 9 
				else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=375&&mousey()>=306&&mousex()>=256&&mousex()<=314){
					clearviewport();
					clearmouseclick(WM_LBUTTONDOWN);
					settextstyle(4,0,3);
					outtextxy(50,350,"[balls pick up the gun]");
					delay(2000);
					clearviewport();
					int i=0;
					int cur_page=0;
					ball shutball[14];
					for(int j=0;j<14;j++){
					shutball[j].appear=1;
					shutball[j].x=400;
					shutball[j].y=365+j*30;
					}
					while(a){
						
						setnum(init,ball_row);
			    		
						printscore(score);
						settextstyle(10,0,4);
						setvisualpage(cur_page);
						cur_page = -cur_page + 1;
						setactivepage(cur_page);
						clearviewport();
						setfillstyle(SOLID_FILL,LIGHTRED);
						bar(mousex()-20,385,mousex()+20,425);
						setfillstyle(SOLID_FILL,YELLOW);
						for(int j=0;j<13;j++){
							if(shutball[j].y==365)
								shutball[j].x=mousex();
							if(shutball[j].appear==1)
								circle(shutball[j].x,shutball[j].y,5);
							shutball[j].y-=30;	
							if(shutball[j].y<=-10)
								shutball[j].y=365;
						}
						ballsum=rec9(rectan_1,rectan_2,ballsum,&score,bkball,init,ball_row,ballcolor,0,q,shutball);
						if(ballsum<=0){
	    	    			setactivepage(0);
	        				setvisualpage(0);
	        				clearviewport();
	        				remember_point(score);
		       				viewgameover(score);
	       					getch();
	       					ballsum=5;
	       					score=0;
	       					break;
						}
						delay(30);
					}
					break;
				}
		
				else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=513&&mousey()>=458&&mousex()>=106&&mousex()<=245){
					break;
				}
			}
			clearmouseclick(WM_LBUTTONDOWN);
			readimagefile("page.JPG",0,0,355,600);
		}
		//enter a mode where you can choose the color of the snake 
		else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=562&&mousey()>=499&&mousex()>=281&&mousex()<=333){
			clearviewport();
			clearmouseclick(WM_LBUTTONDOWN);
			readimagefile("choosepage.jpg",0,0,355,600);
			while(c){
				ballcolor=choose(ballcolor);
				if(ballcolor<=8)
					break;
				else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=513&&mousey()>=458&&mousex()>=106&&mousex()<=245){
					clearmouseclick(WM_LBUTTONDOWN);
					break;
				} 
			}
			clearmouseclick(WM_LBUTTONDOWN);
			clearviewport();
			readimagefile("page.JPG",0,0,355,600);
			c=2;
			clearmouseclick(WM_LBUTTONDOWN);
		}
		
		//enter the leaderboard
		else if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=373&&mousey()>=321&&mousex()>=54&&mousex()<=296){
			clearmouseclick(WM_LBUTTONDOWN);
			clearviewport();
			readimagefile("rank.jpg",0,0,355,600);
			while(b){
				fp = fopen("rank.txt","r+");
				rewind(fp);
				for(i=0;i<5;i++)
				{
					fscanf(fp,"%d",&rank_0[i]);
					sprintf(rank_1,"%d",rank_0[i]);
					settextstyle(10,0,5);
					outtextxy(170,i*58+140,rank_1);
				}	
				while(a){
					if(ismouseclick(WM_LBUTTONDOWN)&&mousey()<=513&&mousey()>=458&&mousex()>=106&&mousex()<=245)
					{
						clearmouseclick(WM_LBUTTONDOWN);
						b=0;
						break;
					}
				}
				fclose(fp);
				clearviewport();
				readimagefile("outpage.JPG",0,0,355,600);
			}
			b=2;
			clearviewport();
			readimagefile("page.JPG",0,0,355,600);
			clearmouseclick(WM_LBUTTONDOWN);
		}
		
	}
	getch();
	closegraph();
		
}
