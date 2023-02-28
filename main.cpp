//Tilly Dewing - Computer Graphics Assignment 1 - 2/28/2023
//Sam Houston State University - COSC 4332 - Dr. Islam

#include<windows.h>
#include <GL/glut.h>
#include <math.h>

//Data structure for storing and rotating 2D points
//Probably not needed but made functions cleaner
struct Vector2
{
    GLfloat x;
    GLfloat y;
    //Constructor
    Vector2(GLfloat x1, GLfloat y1)
    {
        x = x1;
        y = y1;
    }
    //rotate point about 0,0 by theta degrees
    void Rotate(GLfloat theta)
    {
        //get theta in radians
        theta = theta * (M_PI / 180);
        //create another struct to store temp values
        Vector2 rotated = Vector2(x,y);
        //Rotate point
        rotated.x = x * cos(theta) - y * sin(theta);
        rotated.y = x * sin(theta) + y * cos(theta);
        //Set values
        x = rotated.x;
        y = rotated.y;
        //return rotated;
    }
};

//Color struct for generating pseudo random colors
//Also not necessary but random colors were more fun.
//Colors of shapes are randomized every draw call.
struct Color
{
    GLfloat r;
    GLfloat g;
    GLfloat b;

    Color()
    {
        r = (float)rand()/(float)RAND_MAX;
        g = (float)rand()/(float)RAND_MAX;
        b = (float)rand()/(float)RAND_MAX;
    }
};

//draw a n sided unfilled polygon
//Param Defs:   | x & y pos to draw at  | # of sides  | radius of polygon
void DrawPolygon(GLint posX, GLint posY, int numSides, GLint scale)
{
    //Get random color and set it to draw color
    Color randCol = Color();
    glColor3f(randCol.r, randCol.g, randCol.b);

    //Can draw a n sided polygon by rotating n points by 360/n degrees
    float theta = -360.0f / numSides; //Number of degrees between each vertex
    //Starting point before rotation.
    Vector2 point = Vector2(0,1); //Arbitrary can be any point on a circle with radius 1, controls final polygon rotation

    glBegin(GL_LINES); //Begin drawing lines

    //Define starting point before loop
    glVertex2f((point.x * scale) + posX, (point.y * scale) + posY);

    for(int i = 1; i <= numSides; i++)
    {
        point.Rotate(theta); //get next point position
        glVertex2f((point.x * scale) + posX, (point.y * scale) + posY); //Ending point of last line
        glVertex2f((point.x * scale) + posX, (point.y * scale) + posY); //Starting point of next line
    }
    glEnd(); //End polygon draw
}

//draw a n sided filled polygon
//Param Defs:         | x & y pos to draw at  | # of sides  | radius of polygon
void DrawFilledPolygon(GLint posX, GLint posY, int numSides, GLint scale)
{
    //Get random color and set it to draw color
    Color randCol = Color();
    glColor3f(randCol.r, randCol.g, randCol.b);

    //Can draw a n sided polygon by rotating n points by 360/n degrees
    float theta = -360.0f / numSides;
    //Starting point before rotation.
    Vector2 point = Vector2(0,1);//Arbitrary can be any point on a circle with radius 1, controls final polygon rotation

    //Fill shape by drawing triangles fanning out from center(origin) of polygon
    glBegin(GL_TRIANGLES); //Begin drawing triangles
    for(int i = 1; i <= numSides; i++)
    {
        glVertex2f(posX,posY); //point 1 origin of polygon
        point.Rotate(theta);
        glVertex2f((point.x * scale) + posX, (point.y * scale) + posY);//point 2 1st rotation
        point.Rotate(theta);
        glVertex2f((point.x * scale) + posX, (point.y * scale) + posY);//point 3 2nd rotation
        point.Rotate(-theta); //Rotate back once to avoid throwing of next triangle draw
    }
    glEnd();
}

// Initialization function sets the background color, color for drawing, size of dots, and the projection matrix
void init()
{
    glutSetWindowTitle("Computer Graphics Assign 1 : Tilly Dewing");
    // Set the background color to white
    glClearColor(0.5, 0.5, 0.55, 0.0);

    // Set the orthographic projection matrix with the specified left, right, bottom, and top values
    gluOrtho2D(0, 1024, 0, 768);
}

// Display function performs the actual drawing
void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    //Draw unfilled polygons
    DrawPolygon(60,700, 3, 50); //Triangle
    DrawPolygon(360,700, 4, 50); //Square
    DrawPolygon(660,700, 5, 50); //Pentagon
    DrawPolygon(60,500, 6, 50); //Hexagon
    DrawPolygon(360,500, 7, 50); //heptagon
    DrawPolygon(660,500, 8, 50); //octagon
    DrawPolygon(60,300, 25, 50); //Circle

    //Draw filled polygons
    DrawFilledPolygon(200, 700, 3, 50); // Triangle
    DrawFilledPolygon(500, 700, 4, 50); // Square
    DrawFilledPolygon(800, 700, 5, 50); // Pentagon
    DrawFilledPolygon(200, 500, 6, 50); // Hexagon
    DrawFilledPolygon(500, 500, 7, 50); // Heptagon
    DrawFilledPolygon(800, 500, 8, 50); // Octagon
    DrawFilledPolygon(200, 300, 25, 50); // Circle

    // Send all output to the screen
    glFlush();
}

// Main function
int main(int argc, char** argv) {
    // Initialize the GLUT toolkit
    glutInit(&argc, argv);

    // Set the display mode to single buffering, RGBA model
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Set the window size on the screen
    glutInitWindowSize(1024, 768);

    // Set the window position on the screen
    glutInitWindowPosition(100, 500);

    // Open the screen window
    glutCreateWindow(argv[0]);

    // Call the initialization function
    init();

    // Point to the display function
    glutDisplayFunc(display);

    // Go into perpetual loop
    glutMainLoop();

    // Return 0
    return 0;
}

//2D point object

