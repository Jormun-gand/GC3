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
// double array make for one matrix
int world[25][25];
int board[27][27];
// start with 0
int gameOn = 0;
// mili is time = update per mili /s
int mili = 400;

//copy the data from board to world
void ontoBoard(){
	for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 25; ++j)
		{
			board[i+1][j+1]=world[i][j];
		}
	}
}

// choose a cell to be alive
void pickCell(int x, int y){
    // make the cell smaller than the original make it easier to see
	glPointSize(gridSize*1.0-1.0);
	// locating the cell
	// block's location
	float bx = floor(x/gridSize)*gridSize;
	float by = floor(y/gridSize)*gridSize;
    //the actual location on the borad
	int ax = (int)(bx/gridSize);
	int ay = (int)(by/gridSize);

    // if the cell is used to be dead, after click is alive, 0 = dead, 1 = alive
	if (world[ax][ay]==0){
		world[ax][ay]=1;board[ax+1][ay+1]=1;
		
		glColor3f(0.90,0.0,0.80);
		glBegin(GL_POINTS);
			glVertex2f(bx+gridSize/2-0.5, by+gridSize/2);
		glEnd();
        //update
		glFlush();
	//else it is alive than dead after click
	}else{world[ax][ay]=0;board[ax+1][ay+1]=0;
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_POINTS);
			glVertex2f(bx+gridSize/2-0.5, by+gridSize/2);
		glEnd();
		glFlush();
	}//alive or dead


}

//check how many cells are around each cell
void check8(){ // update world2
	ontoBoard();
	for (int i = 1; i < 26; ++i){
		for (int j = 1; j < 26; ++j){
			int n=0;
            //check all the cells around the point is dead or alive
			n = board[i-1][j-1]+board[i][j-1]+board[i+1][j-1]
			+board[i-1][j]+board[i+1][j]
			+board[i-1][j+1]+board[i][j+1]+board[i+1][j+1];
			int x = i;
			int y = j;
            // if the cell used to be alive , around <=1, >=4 then it is dead
			if (board[x][y]==1)
			{
				if (n<=1||n>=4){world[x-1][y-1]=0;}
				else{world[x-1][y-1]=1;}
            // if used to be dead, around cells > 3 than alive
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

    
    // if the value in world is 0 than undraw it, if it is 1, draw it.
	for (int i = 0; i < 25; ++i){
		for (int j = 0; j < 25; ++j){
	if (world[i][j]==0){
	glPointSize(gridSize*1.0-1.0);
	
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_POINTS);
	glVertex2f(i*gridSize+gridSize/2-0.5, j*gridSize+gridSize/2);
	glEnd();
	glFlush();
	
	}else{
	glPointSize(gridSize*1.0-1.0);
	glColor3f(0.90,0.0,0.80);
	glBegin(GL_POINTS);
	glVertex2f(i*gridSize+gridSize/2-0.5, j*gridSize+gridSize/2);
	glEnd();
	glFlush();}
	}
}
			
}


void display(void)
{
	
	
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
}


void Timer(int value){
	glutTimerFunc(mili,Timer,0);
	if(gameOn==1){reDraw();}
}


/////// ↑should change the organization
void menu(int value){
	printf("menu action\n");
	switch(value){
		// ("Faster", 1);
        case 1:
			if (mili>1)
            // if mili > 1 than make it /2 than it will be faster
			{mili=mili/2;}
			Timer(0);
			display();
			//reDraw();
		break;
            
        // ("Slower", 2);
		case 2:  
			if (mili>1&&mili<3200)
			{mili=mili*2;}
			Timer(0);
			reDraw();
		break;
 
        // ("Run", 3);
		case 3: 
			gameOn =  1;
			
		break;

        // ("Pause", 4);
		case 4:
			gameOn = 0;
		break;
            
        // ("Random", 5);
		case 5:
			gameOn=0;
            // all the cell in the grid set random dead or alive
			glClear (GL_COLOR_BUFFER_BIT);
			for (int i = 0; i < 25; ++i){
				for (int j = 0; j < 25; ++j){
					world[i][j] = (int)(round)((rand()%100)/100.0) ;
					
				}
			}
			display();
			reDraw();
			gameOn=1;
		break;
            
        // quit
		case 0:
			exit(0);
		break;

        // clear
		case 11:
			gameOn=0;// pause(stop) the game
			glClear (GL_COLOR_BUFFER_BIT);
			
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
	{
		pickCell(cx,cy);
	}
	else {return;}
}



////////////// MOUSE ///////////////


void passive(int x,int y){
	
}

void motion(int x, int y){
	
}
void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27: //escape key
		case 'q': //qite
			exit(0);
			break;
		default:
			break;
	}}

////////// CALLBACKS ////////
void glutCallbacks(){		//

	glutDisplayFunc(display);
	glutPassiveMotionFunc(passive);
	glutMotionFunc(motion);
	glutMouseFunc(mouseClick);
	glutKeyboardFunc(keyboard);
}



/////////////// main ////////////
int main(int argc, char** argv)
{
    //starts up GLUT
	glutInit(&argc, argv);

	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);

	glutCreateWindow("Conway");

	glutCallbacks();

	initMenu();
	/////////////////
	gluOrtho2D(0.0,500.0,500.0,0.0);

	
	Timer(0);
	glutMainLoop();
	
	return(0);		
}
