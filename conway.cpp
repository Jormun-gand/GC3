// YIFEI HAN 1323752
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>
#include <stdio.h>
#include <complex>


 /*
 	Ramdom
 	Fast and Slow
 */
// set grid size
int gridSize = 20;
int world[25][25];
//int world2[25][25];
int board[27][27];
int gameOn = 0;
int mili = 400;

void ontoBoard(){
	for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 25; ++j)
		{
			board[i+1][j+1]=world[i][j];
			// board[i][0]=0;
			// board[0][i]=0;
		}
	}
}

void pickCell(int x, int y){
	glPointSize(gridSize*1.0-1.0);
	// locating the cell
	// block's location
	float bx = floor(x/gridSize)*gridSize;
	float by = floor(y/gridSize)*gridSize;

	int ax = (int)(bx/gridSize);
	int ay = (int)(by/gridSize);

	if (world[ax][ay]==0){
		world[ax][ay]=1;board[ax+1][ay+1]=1;
		//printf("Coordinate: %f %f \n",bx, by );
		glColor3f(0.90,0.0,0.80);
        //choose color
		glBegin(GL_POINTS);
			glVertex2f(bx+gridSize/2-0.5, by+gridSize/2);
		glEnd();
		glFlush();
		//glutPostRedisplay();
	}else{world[ax][ay]=0;board[ax+1][ay+1]=0;
		glColor3f(0.0f,0.0f,0.0f); //choose color
		glBegin(GL_POINTS);
			glVertex2f(bx+gridSize/2-0.5, by+gridSize/2);
		glEnd();
		glFlush();
	}//alive or dead


}


void check8(){ // update world2
	ontoBoard();
	for (int i = 1; i < 26; ++i){
		for (int j = 1; j < 26; ++j){
			int n=0;
			n = board[i-1][j-1]+board[i][j-1]+board[i+1][j-1]
			+board[i-1][j]+board[i+1][j]
			+board[i-1][j+1]+board[i][j+1]+board[i+1][j+1];
			// alive or dead cell
			int x = i;
			int y = j;
			if (board[x][y]==1)
			{
				if (n<=1||n>=4){world[x-1][y-1]=0;}
				else{world[x-1][y-1]=1;}

			}else if(board[x][y]==0){
				if (n==3){world[x-1][y-1]=1;}
				else{world[x-1][y-1]=0;}
			}
		}
	}
	
}





void reDraw(){
	 check8(); // updated world by checking board

	 // have a new world now and paint

	for (int i = 0; i < 25; ++i){
		for (int j = 0; j < 25; ++j){
	if (world[i][j]==0){
	glPointSize(gridSize*1.0-1.0);
	//printf("Coordinate: %f %f \n",bx, by );
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_POINTS);
	glVertex2f(i*gridSize+gridSize/2-0.5, j*gridSize+gridSize/2);
	glEnd();
	glFlush();
	//glutPostRedisplay();
	}else{
	glPointSize(gridSize*1.0-1.0);
	glColor3f(0.90,0.0,0.80);
	glBegin(GL_POINTS);
	glVertex2f(i*gridSize+gridSize/2-0.5, j*gridSize+gridSize/2);
	glEnd();
	glFlush();}
	}
}
			//printf("Now the timer is: %i\n",mili );
}


void display(void)
{
	
	//glClear (GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glColor3f (0.737255,0.560784,0.560784);
	glLineWidth(1.0);
		for (int i = gridSize; i < 500; i=i+gridSize){

			glBegin(GL_LINES);
			glVertex2f(i,0);
			glVertex2f(i,500);

			glVertex2f(0,i);
			glVertex2f(500,i);
			glEnd();
		}
	glFlush();

	// for (int i = 0; i < 25; ++i){
	// 			for (int j = 0; j < 25; ++j){
	// 				printf("%d ", world[i][j]);
	// 			}printf("\n");
	// 		}printf("\n");

}


void Timer(int value){ //set the timer
	glutTimerFunc(mili,Timer,0);
	//if(gameOn==0){display();}
	if(gameOn==1){reDraw();}
}


/////// ↑should change the organization
void menu(int value){
	printf("menu action\n");
	switch(value){
		case 1:
			if (mili>1)
			{mili=mili/2;}
			Timer(0);
			display();
			//reDraw();
		break;

		case 2:
			if (mili>1&&mili<3200)
			{mili=mili*2;}
			Timer(0);
			reDraw();
		break;
 
		case 3:
			gameOn =  1;
			//check8();
			// for (int i = 0; i < 25; ++i){
			// 	for (int j = 0; j < 25; ++j){
			// 		printf("%d ", world[i][j]);
			// 	}printf("\n");
			// }
			// for (int i = 0; i < 25; ++i){
			// 	for (int j = 0; j < 25; ++j){
			// 		printf("%d ", world2[i][j]);
			// 	}printf("\n");
			// }
		break;

		case 4:
			gameOn = 0;
		break;

		case 5:
			gameOn=0;
			glClear (GL_COLOR_BUFFER_BIT);
			for (int i = 0; i < 25; ++i){
				for (int j = 0; j < 25; ++j){
					world[i][j] = (int)(round)((rand()%100)/100.0) ;
					//printf("%i \n",world[i][j]);
				}
			}//printf("\n");
			display();
			reDraw();
			gameOn=1;
		break;

		case 0:
			exit(0);
		break;

		case 11:
			gameOn=0;// pause(stop) the game
			glClear (GL_COLOR_BUFFER_BIT);
			// world[25][25];
			// world2[25][25];
			//memset(world, 0, 25*25);memset(world2, 0, 25*25);
			for (int i = 0; i < 25; ++i){
				for (int j = 0; j < 25; ++j){
					world[i][j]=0;
					board[i+1][j+1]=0;
				}
			}
			//ontoBoard();
			display();
		break;

		default:
			break;
	}
}



//////////////// menu initilizer ////////////

void initMenu(){
	////// main menu //////
	int id = glutCreateMenu(menu);
	glutSetMenu(id);
	
	glutAddMenuEntry("Faster", 1);
	glutAddMenuEntry("Slower", 2);
	glutAddMenuEntry("Run", 3);
	glutAddMenuEntry("Pause", 4);
	glutAddMenuEntry("Random", 5);

	glutAddMenuEntry("Clear", 11);
	glutAddMenuEntry("Quit", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void mouseClick(int button,int state,int cx, int cy){
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && gameOn==0)
	{ // click left button and game is on at the same time
		pickCell(cx,cy);
	}
	else {return;}
}



////////////// MOUSE ///////////////


void passive(int x,int y){
	//printf("passive: %i,%i\n", x, y);
}

void motion(int x, int y){
	
}
void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27: //escape key with fall through
		case 'q':
			exit(0);
			break;
		default:
			break;
	}}

////////// CALLBACKS ////////
void glutCallbacks(){

	glutDisplayFunc(display);
	glutPassiveMotionFunc(passive);
	glutMotionFunc(motion);
	glutMouseFunc(mouseClick);
	glutKeyboardFunc(keyboard);
}



/////////////// main ////////////
int main(int argc, char** argv)
{	
	glutInit(&argc, argv);		//starts up GLUT

	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);

	glutCreateWindow("Conway");	//creates the window

	glutCallbacks();

	initMenu();
	/////////////////
	gluOrtho2D(0.0,500.0,500.0,0.0);

	
	Timer(0);
	glutMainLoop();				//starts the event loop
	
	return(0);		
}
