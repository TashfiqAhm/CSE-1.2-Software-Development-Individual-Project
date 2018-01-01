# include <stdio.h>
# include <string.h>
# include "iGraphics.h"
int mposx =0,  mposy =0;

typedef struct snakeBody snk;
typedef struct saveScoreFile saveScoreFile;

struct snakeBody
{
	int x;
	int y;
	int dir;

}s[2000];

struct saveScoreFile
{
	int highScores;
	char playerName[100];

}ssf[11];

int newScore;

int mode=4;

//mode 1 = In Game
//mode 2 = Game Over
//mode 3 = Enter Name Window
//mode 4 = Menu
//mode 5 = Instruction
//mode 6 = High Score

FILE *accessSaveFile;
int temp_score;
char temp_name[100];

int bodyL = 10 ;
char scrCount[10];
char holdHighScore[10];
char name[100];
char name2[100];
int nameL = 0;

int up_button = 0;
int down_button = 0;
int left_button = 0;
int right_button = 0;

int dx = 30;
int dy = 30;
int randx = 150 ;
int randy = 90;
int score = 0;

void snakeReady()
{	
	for(int i= 0 ; i<bodyL ; i++)
	{
	    s[i].x = 300 ;
		s[i].y = 300 - dy * i ;
		s[i].dir = 8;
	}
}

void newFoodLoc()
{
	randx = rand() %  29 * 30  ;
	randy = rand() % 19 * 30  ;

}

void saveScore()
{
	
	ssf[10].highScores = newScore;
	strcpy(ssf[10].playerName,name2);

	accessSaveFile = fopen("High Score.txt", "r");

	for(int i = 0; i<10 ; i++)
	{
		fscanf(accessSaveFile , "%s %d" , &ssf[i].playerName  , &ssf[i].highScores);
	}

	fclose(accessSaveFile);

	for (int i = 0 ; i<10 ; i++)
		for(int j = 10 ; j>i ; j--)
		{
			if( ssf[j].highScores > ssf[j-1].highScores )
			{
				temp_score = ssf[j-1].highScores;
				ssf[j-1].highScores = ssf[j].highScores;
				ssf[j].highScores = temp_score;

				strcpy( temp_name , ssf[j-1].playerName);
				strcpy( ssf[j-1].playerName , ssf[j].playerName);
				strcpy( ssf[j].playerName , temp_name);
			}
		}

	accessSaveFile = fopen("High Score.txt", "w");

	for(int i = 0; i<10 ; i++)
	{
		fprintf(accessSaveFile , "%s\t%d\r\n" , ssf[i].playerName  , ssf[i].highScores);
	}

	fclose(accessSaveFile);

}

void showHighScore()
{
	iSetColor(34 , 148 , 56);
	iFilledRectangle(0 , 0 , 900 , 600);

	accessSaveFile = fopen("High Score.txt", "r");

	for(int i = 0; i<10 ; i++)
	{
		fscanf(accessSaveFile , "%s %d" , &ssf[i].playerName  , &ssf[i].highScores);
	}

	fclose(accessSaveFile);

	iSetColor(0 , 0 , 0);

	iText(100 , 500, "NAME", GLUT_BITMAP_TIMES_ROMAN_24);

	iText(500 , 500, "Score", GLUT_BITMAP_TIMES_ROMAN_24);

	for(int i = 0 ; i<5 ; i++)

	{
		iText( 100 , 400 - i*50 , ssf[i].playerName , GLUT_BITMAP_TIMES_ROMAN_24);
		
		itoa(ssf[i].highScores , holdHighScore , 10);
		iText( 500 , 400 - i*50 , holdHighScore , GLUT_BITMAP_TIMES_ROMAN_24);
	}


	iText( 100 , 100 , "Press B to go back to MENU" , GLUT_BITMAP_TIMES_ROMAN_24);
	
}

void drawTextBox()
{
	iSetColor(0, 204, 0);
	iRectangle(295 , 200, 300, 70); 
}

void drawMenuBox(int x_co , int y_co , int box_len , int box_wid)
{
	if(mposx >= x_co && mposx <= x_co + box_len && mposy >= y_co && mposy <= y_co + box_wid)
	iSetColor(60,160,100);
	else
	iSetColor(60,200,100);
	iFilledRectangle(x_co , y_co , box_len , box_wid);
}

void scoreCount()
{
	iText(10, 10, "Score: ", GLUT_BITMAP_TIMES_ROMAN_24);

	iText(80, 10, scrCount , GLUT_BITMAP_TIMES_ROMAN_24);

	if(s[0].x == randx && s[0].y == randy)

	{
		score++;
		bodyL++;
		newFoodLoc();

		itoa(score , scrCount , 10);
	}

}

void gameOver()
{
	if((s[0].x > 900 || s[0].x <0) || (s[0].y > 600 || s[0].y <0) )
	{
		up_button = 0;
		down_button = 0;
		left_button = 0;
		right_button = 0;
		snakeReady();
		newScore = score;
		score = 0;
		mode=2;		
	}

	for(int i = 1 ; i<bodyL ; i++)
	{
		if(s[0].x == s[i].x  &&  s[0].y == s[i].y)
		{
			up_button = 0;
			down_button = 0;
			left_button = 0;
			right_button = 0;
			snakeReady();
			newScore = score;
			score = 0;
			mode=2;

		}
	}
}

void showSnakeFood()
{
	for(int i = 1 ; i<bodyL ; i++)
	{
		if (randx==s[i].x  &&  randy==s[i].y)
			newFoodLoc();
	}
	iShowBMP2(randx , randy , "snake\\food.bmp" , 255);
}

void mode_1()
{

	if(mode==1)
	{

		iClear();

		iSetColor(255 , 255 , 255);
		iFilledRectangle(0 , 0 , 900, 600);

		iSetColor(0 , 0 , 0);
		
		for(int i=0 ; i<bodyL-1 ; i++)
		{
			//code for calculating head direction

			if(s[0].dir == 8)
				iShowBMP2(s[0].x , s[0].y , "snake\\head up.bmp" , 255);
			else if (s[0].dir == 2)
				iShowBMP2(s[0].x , s[0].y , "snake\\head down.bmp" , 255);
			else if (s[0].dir == 6)
				iShowBMP2(s[0].x , s[0].y , "snake\\head right.bmp" , 255);
			else if (s[0].dir == 4)
				iShowBMP2(s[0].x , s[0].y , "snake\\head left.bmp" , 255);

			//code for calculating tail and rest of the body direction

			if(s[i].dir == 8 )
			{	

				iShowBMP2(s[bodyL-1].x , s[bodyL-1].y , "snake\\tail up.bmp" , 255);

				if( i != 0 && s[i].dir == 8 && s[i-1].dir == 6)
					iShowBMP2(s[i].x , s[i].y , "snake\\upRightBend.bmp" , 255);
				else if (i != 0 && s[i].dir == 8 && s[i-1].dir == 4)
					iShowBMP2(s[i].x , s[i].y , "snake\\upLeftBend.bmp" , 255);
				else
				iShowBMP2(s[i].x , s[i].y , "snake\\snake body up down.bmp" , 255);
			}

			if(s[i].dir == 2) 
			{
				
				iShowBMP2(s[bodyL-1].x , s[bodyL-1].y , "snake\\tail down.bmp" , 255);

				if( i != 0 && s[i].dir == 2 && s[i-1].dir == 6)
					iShowBMP2(s[i].x , s[i].y , "snake\\downRightBend.bmp" , 255);
				else if (i != 0 && s[i].dir == 2 && s[i-1].dir == 4)
					iShowBMP2(s[i].x , s[i].y , "snake\\downLeftBend.bmp" , 255);
				else
				iShowBMP2(s[i].x , s[i].y , "snake\\snake body up down.bmp" , 255);
			}

			if(s[i].dir == 6)
			{

				iShowBMP2(s[bodyL-1].x , s[bodyL-1].y , "snake\\tail right.bmp" , 255);

				if( i != 0 && s[i].dir == 6 && s[i-1].dir == 8)
					iShowBMP2(s[i].x , s[i].y , "snake\\rightUpBend.bmp" , 255);
				else if (i != 0 && s[i].dir == 6 && s[i-1].dir == 2)
					iShowBMP2(s[i].x , s[i].y , "snake\\rightDownBend.bmp" , 255);
				else 
					iShowBMP2(s[i].x , s[i].y , "snake\\snake body left right.bmp" , 255);
			}

			if(s[i].dir == 4) 
			{
				
				iShowBMP2(s[bodyL-1].x , s[bodyL-1].y , "snake\\tail left.bmp" , 255);

				if( i != 0 && s[i].dir == 4 && s[i-1].dir == 8)
					iShowBMP2(s[i].x , s[i].y , "snake\\leftUpBend.bmp" , 255);
				else if (i != 0 && s[i].dir == 4 && s[i-1].dir == 2)
					iShowBMP2(s[i].x , s[i].y , "snake\\leftDownBend.bmp" , 255);
				else

				iShowBMP2(s[i].x , s[i].y , "snake\\snake body left right.bmp" , 255);
			}		
	}

	gameOver();

	showSnakeFood();
	
	scoreCount();

	}
}

void mode_2()
{
	if(mode == 2)

	{
		iClear();

		iSetColor(255 , 255 , 255);
		iFilledRectangle(0 , 0 , 1000, 600);

		iShowBMP2(200 , 300 , "snake\\game_over.bmp" , 255);

		drawTextBox();

		iSetColor(0 , 0 , 0);

		iText(225 , 325 , "Enter your Name: ( Click to activate the box ) " , GLUT_BITMAP_TIMES_ROMAN_24);

	}

}

void mode_3()
{
	if(mode == 3)
	{
		iClear();

		iSetColor(255 , 255 , 255);
		iFilledRectangle(0 , 0 , 1000, 600);

		iShowBMP2(200 , 300 , "snake\\game_over.bmp" , 255);

		drawTextBox();

		iSetColor(0 , 0 , 0);

		iText(225 , 325 , "Enter your Name: ( Click to activate the box ) " , GLUT_BITMAP_TIMES_ROMAN_24);
		iText(100 , 100 , "Press 'Left Arrow' key to delete character " , GLUT_BITMAP_TIMES_ROMAN_24);

		
		iText(305 , 230 , name ,GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void mode_4()
{
	if(mode == 4 )
	{
		iClear();
		iSetColor(255 , 255 , 255);
		iFilledRectangle(0 , 0 , 900, 600);
		iShowBMP(0 , 0, "snake\\menu.bmp"  );


		drawMenuBox(675, 200, 200, 50);
		iSetColor(0,0,0);
		iText(715, 215 , "Start Game ",GLUT_BITMAP_TIMES_ROMAN_24);

		drawMenuBox(675, 140, 200, 50);
		iSetColor(0,0,0);
		iText(715, 155 , "Instructions ",GLUT_BITMAP_TIMES_ROMAN_24);

		drawMenuBox(675, 80, 200, 50);
		iSetColor(0,0,0);
		iText(715, 95 , "High Score ",GLUT_BITMAP_TIMES_ROMAN_24);

		drawMenuBox(675, 20, 200, 50);
		iSetColor(0,0,0);
		iText(750, 35 , "Exit ",GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(255,255,255);
		iText(50, 100 , "Tashfiq Ahmed  ",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(50, 50 , "ID: 17.01.04.038  ",GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void mode_5()
{
	if(mode==5)
	{
		iClear();
		iShowBMP(0,0,"snake\\instructions.bmp");
	}
}

void mode_6()
{
	if(mode == 6)
	{
		iClear();
		showHighScore();
	}
}

void inGame()
{

	mode_1();
	mode_2();
	mode_3();
	mode_4();
	mode_5();
	mode_6();

}

void moveSnake()
{	

	if(up_button == 1 )
		{
			int temp = s[0].y + dy;
		
  		    for(int i = bodyL - 1 ; i>0 ; i--)
			{
				s[i].y = s[i-1].y ;
				s[i].x = s[i-1].x ;
				s[i].dir = s[i-1].dir ;			
			}

			s[0].dir = 8;
			s[0].y = temp;		
		}

	if(down_button == 1 )

		{	
			int temp = s[0].y - dy ;

			for(int i = bodyL - 1 ; i>0 ; i--)
			{
				s[i].y= s[i-1].y ;
				s[i].x = s[i-1].x ;
				s[i].dir = s[i-1].dir ;
			}

			s[0].dir = 2;
			s[0].y = temp;
		}


	if(left_button == 1)
		{
			int temp = s[0].x - dx ;

			for(int i = bodyL - 1 ; i>0 ; i--)
			{
				s[i].x= s[i-1].x ;
				s[i].y = s[i-1].y ;
				s[i].dir = s[i-1].dir ;		
			}

			s[0].dir = 4;
			s[0].x = temp;
		}

	if(right_button == 1 )

		{
			int temp = s[0].x + dx ;

			for(int i = bodyL - 1 ; i>0 ; i--)
			{
				s[i].x= s[i-1].x ;
				s[i].y = s[i-1].y ;
				s[i].dir = s[i-1].dir ;
			}

			s[0].dir = 6;
			s[0].x = temp;
		}
}

void iDraw()
{
	
	inGame();
}

void iMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		if(mx >= 675 && mx <= 875 && my >= 200 && my <= 250 && mode == 4)
		{
			mode = 1;
		}

		if(mx >= 675 && mx <= 875 && my >= 140 && my <= 190 && mode == 4)
		{
			mode = 5;
		}

		if(mx >= 675 && mx <= 875 && my >= 20 && my <= 70 && mode == 4)
		{
			exit(0);
		}

		if(mx >= 675 && mx <= 875 && my >= 80 && my <= 130 && mode == 4)
		{
			mode = 6 ;
		}

		if(mx >= 295 && mx <= 595 && my >= 200 && my <= 270 && mode == 2)
		{
			mode = 3;
		}
	}

	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}

void iPassiveMouseMove(int mx,int my)
{

 mposx = mx;
 mposy = my;
 
}

void iKeyboard(unsigned char key)
{

	int i;
	if(mode == 3)
	{
        if(key == '\r')
		{
			mode = 4;
			strcpy( name2 , name);
			saveScore();
			score = 0;
			strcpy(scrCount,"\0");
	
			for(i = 0 ; i < nameL ; i++)
				name[i] = 0;
			nameL = 0;
		}
		else
		{
			name[nameL] = key;
			nameL++;
		}
	}

	if (key == 'r')
	{

		iResumeTimer(0);

	}
	if (key == 'p')
	{

		iPauseTimer(0);
	}	

	if(key == 'q')
	{
		bodyL++;
		score++;
		itoa(score , scrCount , 10);
	}

	if(key == 'b')
	{
		mode=4;
	}
}

void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}

	if(key == GLUT_KEY_UP)
	{
		if (down_button==0)
		{
			up_button = 1;
			left_button = 0;
		    right_button = 0;
		}
	}

	if(key == GLUT_KEY_DOWN)
	{
		if (up_button==0)
		{
			down_button = 1;
			left_button = 0;
		    right_button = 0;
		}
	}

	if(key == GLUT_KEY_LEFT)
	{
		if(mode==1)
		{	
			if (right_button==0)
			{
				left_button = 1;
				up_button = 0;
				down_button = 0;
			}
		}

		else if (mode ==3)
		{
			nameL--;
			name[nameL] = 0;
		}
	}

	if(key == GLUT_KEY_RIGHT)
	{
		if (left_button==0)
		{
			right_button = 1;
			up_button = 0;
		    down_button = 0;
		}
	}
}

int main()
{
	snakeReady();
	iSetTimer(100,moveSnake);
	iInitialize(900, 600, "38_Game");
	return 0;
}
