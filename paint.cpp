// YIFEI HAN 1323752
#include <stdlib.h>
#include <glut/glut.h>
//#include <gl/gl.h>
#include <math.h>
#include <stdio.h>
#include <complex>


/*
	** REFERENCE **

	Draw circle algorithm: Bresenham’s Circle Algorithm
	http://birunthag.blogspot.ca/2014/05/openglc-draw-circle-with-bresenhams.html
	
	Draw line algorithm: Bresenham's line algorithm
	http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm

*/
/*
	reshape is not solved
	delete the unnecessary code
*/

// 	("Red", 1);
// 	("Green", 2);
// 	("Blue", 3);
// 	("Purple", 4);
// 	("Yellow", 5);
// 	("Point", 6);
// 	("Line", 7);
// 	("Rectangle", 8);
// 	("Circle", 9);

int shapeN = 0;
int colorN = 0;
int lx1; 
int lx2; 
int ly1; 
int ly2;
int lNum=0;
int rx1; 
int rx2; 
int ry1; 
int ry2;
int rNum=0;
int cx1; 
int cx2; 
int cy1; 
int cy2;
int cNum=0;

// mouse on
int mouse =0;

// void clearScreen(void){

// }

int randColor(void){int c_olour = rand() % 5 + 1; } //5 different coulor

void resetN(void){
	lNum=0;
	rNum=0;
}
////////////// draw ////////////////////
void display(void)
{
	glBegin(GL_POINTS);
		glVertex2f(-5.0, -5.0);
	glEnd();
	glPointSize(5.0);
	glFlush();
}

void drawP(int x, int y){
	if (mouse == 0){
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
	glutPostRedisplay();}
}

void drawL(float x1,float x2,float y1,float y2){	
	////// Bresenham ///////
	//printf("draw line! \n");
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) + 1;
 
    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) + 1;
 
    drawP(x1, y1);
 
    if (delta_x >= delta_y)
    {
        int error(delta_y - (delta_x >> 1));
 
        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
          
            error += delta_y;
            x1 += ix;
 
            drawP(x1, y1);
        }
    }
    else
    {
        int error(delta_x - (delta_y >> 1));
 
        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
           
            error += delta_x;
            y1 += iy;
 
            drawP(x1, y1);
        }
    }
}

void drawR(float x1, float x2, float y1, float y2){
	if(x2>x1){float temp = x1; x1=x2; x2=temp;}
	if(y2>y1){float temp = y1; y1=y2; y2=temp;}
	drawL(x1,x2,y1,y1);
	drawL(x1,x1,y1,y2);
	drawL(x2,x2,y2,y1);
	drawL(x1,x2,y2,y2);

}

void drawC(float x1, float x2, float y1, float y2){
	float r= sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	// midpoint
	float x=0; float y=r;
	float d=3-2*r; 
	//printf("The radius is: %f\n", r);
	while(x<=y){  
     //Here Transform each x,y coordinates by 500 pixels   
     drawP(x1+x, y1+y);  
     drawP(x1+y, y1+x);  
     drawP(x1-x, y1+y);  
     drawP(x1-x, y1-y);  
     drawP(x1-y, y1+x);  
     drawP(x1-y, y1-x);  
     drawP(x1+y, y1-x);  
     drawP(x1+x, y1-y);  
     if(d<0)  
          d=d+(4*x)+6;  
     else{  
          d=d+(4*(x-y))+10;  
          y--;  
     }  
     x++;  }
 }
int round(float n){
	return (n>=0)?(int)(n+0.5):(int)(n-0.5);  
}  

///////////////// menu handler ////////////////////

void shapeSet(int value){
	// glutAddMenuEntry("Point", 6);
	// glutAddMenuEntry("Line", 7);
	// glutAddMenuEntry("Rectangle", 8);
	// glutAddMenuEntry("Circle", 9);
	switch(value){
		resetN();// reset all the counters
		case 6:
			shapeN = 6;
			// printf("set to 6\n");
			break;
		case 7:
			shapeN = 7;
			break;
		case 8:
			shapeN = 8;
			break;
		case 9:
			shapeN = 9;
			break;
		default:
			break;
	}
}
void colourSet(int value){
	switch(value){
		// 	("Red", 1);
		// 	("Green", 2);
		// 	("Blue", 3);
		// 	("Purple", 4);
		// 	("Yellow", 5);
		case 1:
			glColor3f(1.0,0.0,0.0);
			colorN = 1;
		break;
		case 2:
			glColor3f(0.0,1.0,0.0);
			colorN = 2;
		break;
		case 3:
			glColor3f(0.0,0.0,1.0);
			colorN = 3;
		break;
		case 4:
			glColor3f(1.0,0.0,1.0);
			colorN = 4;
		break;
		case 5:
			glColor3f(1.0,1.0,0.0);
			colorN = 5;
		break;
		default:break;
	}
}

/////// ↑should change the organization
void menu(int value){
	//printf("menu action\n");
	switch(value){
		case 0:
		exit(0);
			break;
		case 10:
			colourSet(randColor());
		break;
		case 11: //clear screen
			// store current color
			glColor3f(0.0,0.0,0.0);
			glPointSize(200.0);
			drawP(100.0,100.0);
			drawP(300.0,100.0);
			drawP(100.0,300.0);
			drawP(300.0,300.0);
			drawP(500.0,100.0);
			drawP(500.0,300.0);
			drawP(100.0,500.0);
			drawP(300.0,500.0);
			drawP(500.0,500.0);
			glPointSize(5.0);
			colourSet(colorN);
			shapeSet(shapeN);
		break;
		default:
			break;
	}
}



//////////////// menu initilizer ////////////

void initMenu(){
	// id -> menu identifier
	// (func) -> func handle menu events for newly created menu.
	
	///// colour menu /////
	int colourid = glutCreateMenu(colourSet);
	glutSetMenu(colourid);

	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Purple", 4);
	glutAddMenuEntry("Yellow", 5);

	///// colour menu /////
	int shapeid = glutCreateMenu(shapeSet);
	glutSetMenu(shapeid);

	glutAddMenuEntry("Point", 6);
	glutAddMenuEntry("Line", 7);
	glutAddMenuEntry("Rectangle", 8);
	glutAddMenuEntry("Circle", 9);


	////// main menu //////
	int id = glutCreateMenu(menu);
	glutSetMenu(id);
	
	glutAddSubMenu("Colour", colourid);
	glutAddSubMenu("Shapes", shapeid);
	glutAddMenuEntry("Random Color", 10);
	glutAddMenuEntry("Clear", 11);
	glutAddMenuEntry("Quit", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void mouseClick(int button,int state,int cx, int cy){
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		//("shapeN at mouseClick:  %10d \n", shapeN);
		switch(shapeN){
			// 	("Point", 6);
			// 	("Line", 7);
			// 	("Rectangle", 8);
			// 	("Circle", 9);
		case 6:
			//if (state == GLUT_UP){
			drawP(cx,cy);//}
			break;
		case 7:
			// printf("shapeN: \n", shapeN);
			switch(lNum){
			// p1 p2 are full 
			case 1:
				lx2 = cx;
				ly2 = cy;
				// printf("points are: %i,%i\n", lx1, lx2);
				// printf("num is: %i \n",lNum);
				drawL(lx1*1.0,lx2*1.0,ly1*1.0,ly2*1.0);
				lNum=2;
				break;
			case 0: // nothing filled
			case 2: // two p filled-> overwrite p1 p2
				lx1 = cx;
				ly1 = cy;
				// drawL(float x1,float x2,float y1,float y2)
				// printf("points are: %i,%i\n", lx1, lx2);
				// printf("num is: %i,%i\n",lNum);
				drawP(lx1,ly1);
				//drawP(lx1,ly1);
				lNum=1;
				break;
			default:
			break;
			}break;
		case 8:
			switch(rNum){
			case 0:
			case 2:// different situations
			rx1 = cx;
			ry1 = cy;
			rNum = 1;
			drawP(rx1,ry1);
			break;
			case 1:
			rx2 = cx;
			ry2 = cy;
			rNum = 2;
			drawR(rx1, rx2, ry1, ry2);
			break;
			}
			break;
		case 9:
			switch(cNum){
			case 0:
			case 2:// 2 situations
			cx1 = cx;
			cy1 = cy;
			cNum = 1;
			drawP(cx1,cy1);
			break;
			case 1:
			cx2 = cx;
			cy2 = cy;
			cNum = 2;
			drawC(cx1, cx2, cy1, cy2);
			break;
			break;
			default:
			break;
		}
		//drawP(cx,cy);
	}
}else {return;}
}


void reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluOrtho2D(0,w,h,0);
	glMatrixMode(GL_MODELVIEW);
}

////////////// MOUSE ///////////////


void passive(int x,int y){
	//printf("passive: %i,%i\n", x, y);
}
void motion(int x, int y){
	if (shapeN==6 && mouse==0) {drawP(x,y);};
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
	//glutReshapeFunc(reshape);

	glutPassiveMotionFunc(passive);
	glutMotionFunc(motion);
	glutMouseFunc(mouseClick);

	glutKeyboardFunc(keyboard);
}

////////////// main ////////////
int main(int argc, char** argv)
{	
	glutInit(&argc, argv);		//starts up GLUT


	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);

	glutCreateWindow("Canvas");	//creates the window

	glutCallbacks();

	initMenu();
	//drawPoint();
	
	//set random color when started
	colourSet(randColor());
	/////////////////
	gluOrtho2D(0.0,500.0,500.0,0.0);
	glutMainLoop();				//starts the event loop

	return(0);		
}