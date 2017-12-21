#include "../include/Point2.h"
#include "../include/Vector2.h"
#include "../include/VoronoiDiagramGenerator.h"
#include <vector>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <limits>
#include <string>
#include "../include/gazeapi_types.h"
#include "../include/gazeapi.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <boost/polygon/voronoi.hpp>
#include <dos.h>
#include <math.h>
#include <conio.h>
#include <stdarg.h>
#include <fstream>      // std::ifstream
#include "graphics.h"


#define ESC     0x1b                    /* Define the escape key        */
#define TRUE    1                       /* Define some handy constants  */
#define FALSE   0                       /* Define some handy constants  */
#define PI      3.14159                 /* Define a value for PI        */
#define ON      1                       /* Define some handy constants  */
#define OFF     0                       /* Define some handy constants  */

#define NFONTS 11

char *Fonts[NFONTS] = {
	"DefaultFont", "TriplexFont", "SmallFont",
	"SansSerifFont", "GothicFont", "ScriptFont", "SimplexFont", "TriplexScriptFont",
	"ComplexFont", "EuropeanFont", "BoldFont"
};

char *LineStyles[] = {
	"SolidLn", "DottedLn", "CenterLn", "DashedLn", "UserBitLn"
};

char *FillStyles[] = {
	"EmptyFill", "SolidFill", "LineFill", "LtSlashFill",
	"SlashFill", "BkSlashFill", "LtBkSlashFill", "HatchFill",
	"XHatchFill", "InterleaveFill", "WideDotFill", "CloseDotFill"
};

char *TextDirect[] = {
	"HorizDir", "VertDir"
};

char *HorizJust[] = {
	"LeftText", "CenterText", "RightText"
};

char *VertJust[] = {
	"BottomText", "CenterText", "TopText"
};

struct PTS {
	int x, y;
};      /* Structure to hold vertex points      */

int    GraphDriver;             /* The Graphics device driver           */
int    GraphMode;               /* The Graphics mode value              */
double AspectRatio;             /* Aspect ratio of a pixel on the screen*/
int    MaxX, MaxY;              /* The maximum resolution of the screen */
int    MaxColors;               /* The maximum # of colors available    */
int    ErrorCode;               /* Reports any graphics errors          */
struct palettetype palette;             /* Used to read palette info    */

// GLEW
#define GLEW_STATIC
#include <GLEW/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
// Window dimensions
const GLuint WINDOW_WIDTH = 900, WINDOW_HEIGHT = 900;
// Shaders
const GLchar* vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0";
const GLchar* fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";
double normalize(double in, int dimension) {
	return in / (float)dimension*1.8 - 0.9;
}
//globals for use in giving relaxation commands
int relax = 0;
bool startOver = true;
bool relaxForever = false;
// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		++relax;
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
		relax += 10;
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
		startOver = true;
	if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		if (relaxForever) relaxForever = false;
		else relaxForever = true;
	}
}

using namespace std;

// --- MyGaze definition
class MyGaze : public gtl::IGazeListener
{
public:
	MyGaze();
	~MyGaze();
private:
	// IGazeListener
	void on_gaze_data(gtl::GazeData const & gaze_data);
private:
	gtl::GazeApi m_api;
};

// --- MyGaze implementation
MyGaze::MyGaze()
{
	// Connect to the server in push mode on the default TCP port (6555)
	if (m_api.connect(true))
	{
		// Enable GazeData notifications
		m_api.add_listener(*this);
	}
	else
	{
		cout << "Server is not active";
	}
}

MyGaze::~MyGaze()
{
	m_api.remove_listener(*this);
	m_api.disconnect();
}

void MyGaze::on_gaze_data(gtl::GazeData const & gaze_data)
{
	if (gaze_data.state & gtl::GazeData::GD_STATE_TRACKING_GAZE)
	{
		gtl::Point2D const & smoothedCoordinatesLeftEye = gaze_data.lefteye.avg; // smoothed data from left eye
		gtl::Point2D const & smoothedCoordinatesRightEye = gaze_data.righteye.avg; // smoothed data from right eye

		float LeftEyeX = smoothedCoordinatesLeftEye.x;
		float LeftEyeY = smoothedCoordinatesLeftEye.y;

		float RightEyeX = smoothedCoordinatesRightEye.x;
		float RightEyeY = smoothedCoordinatesRightEye.y;

		// Move GUI point, do hit-testing, log coordinates, etc.
		cout << "x = " << (LeftEyeX + RightEyeX) / 2 << " y = " << (LeftEyeY + RightEyeY) / 2 << endl; //center values for left and right eyes, respectively.
		//trackX = (LeftEyeX + RightEyeX) / 2;
		//trackY = (LeftEyeY + RightEyeY) / 2;																			   //m_GraphcsObject.DrawEllipse()

		//circle((LeftEyeX + RightEyeX) / 2, (LeftEyeY + RightEyeY) / 2, gaze_data.lefteye.psize);
	}
}

void Initialize(void)
{
	int xasp, yasp;                       /* Used to read the aspect ratio*/

	GraphDriver = DETECT;                 /* Request auto-detection       */
	initgraph(&GraphDriver, &GraphMode, "");

	ErrorCode = graphresult();            /* Read result of initialization*/
	if (ErrorCode != grOk) {              /* Error occured during init    */
		printf(" Graphics System Error: %s\n", grapherrormsg(ErrorCode));
		exit(1);
	}

	getpalette(&palette);               /* Read the palette from board  */
	MaxColors = getmaxcolor() + 1;        /* Read maximum number of colors*/

	MaxX = getmaxx();
	MaxY = getmaxy();                     /* Read size of screen          */

	getaspectratio(&xasp, &yasp);       /* read the hardware aspect     */
	AspectRatio = (double)xasp / (double)yasp; /* Get correction factor   */

}

void PaletteDemo(void)
{
	int i, j, x, y, color;
	struct viewporttype vp;
	int height, width;

	//MainWindow("Palette Demonstration");
	//StatusLine("Press any key to continue, ESC to Abort");

	getviewsettings(&vp);
	width = (vp.right - vp.left) / 15;   /* get width of the box         */
	height = (vp.bottom - vp.top) / 10;   /* Get the height of the box    */

	x = y = 0;                            /* Start in upper corner        */
	color = 1;                            /* Begin at 1st color           */

	for (j = 0; j<10; ++j) {              /* For 10 rows of boxes         */
		for (i = 0; i<15; ++i) {            /* For 15 columns of boxes      */
			setfillstyle(SOLID_FILL, color++);      /* Set the color of box */
			bar(x, y, x + width, y + height);           /* Draw the box         */
			x += width + 1;                           /* Advance to next col  */
			color = 1 + (color % (MaxColors - 2));    /* Set new color        */
		}                           /* End of COLUMN loop           */
		x = 0;                              /* Goto 1st column              */
		y += height + 1;                    /* Goto next row                */
	}                                     /* End of ROW loop              */

	while (!kbhit()) {                    /* Until user enters a key...   */
		setpalette(1 + random(MaxColors - 2), random(65));
	}

	setallpalette(&palette);

	//Pause();                              /* Wait for user's response     */

}

bool sitesOrdered(const Point2& s1, const Point2& s2) {
	if (s1.y < s2.y)
		return true;
	if (s1.y == s2.y && s1.x < s2.x)
		return true;

	return false;
}

void genRandomSites(std::vector<Point2>& sites, BoundingBox& bbox, unsigned int dimension, unsigned int numSites) {
	bbox = BoundingBox(0, dimension, dimension, 0);
	std::vector<Point2> tmpSites;

	tmpSites.reserve(numSites);
	sites.reserve(numSites);

	Point2 s;

	srand(std::clock());
	for (unsigned int i = 0; i < numSites; ++i) {
		s.x = 1 + (rand() / (double)RAND_MAX)*(dimension - 2);
		s.y = 1 + (rand() / (double)RAND_MAX)*(dimension - 2);
		tmpSites.push_back(s);
	}

	//remove any duplicates that exist
	std::sort(tmpSites.begin(), tmpSites.end(), sitesOrdered);
	sites.push_back(tmpSites[0]);
	for (Point2& s : tmpSites) {
		if (s != sites.back()) sites.push_back(s);
	}
}

int getIndex(std::vector<Point2> sites, Point2 element) {
	for (unsigned int i = 0; i<sites.size(); i++) {
		if (sites[i] == element) {
			return i;
		}
	}
	cout << "Error point not found " << endl;
	return -1;
}

void read_data(std::vector<Point2> *sites, std::vector<int> *colorVector, std::vector<int> *formVector, double *size_form) {
	ifstream inputFileStream("../../Experience/test.txt");
	int count;

	Point2 s;
	int ptX;
	int ptY;
	int ptForm;
	int ptColor;

	inputFileStream >> *size_form;
	*size_form = *size_form / 100.0;
	inputFileStream >> count;
	cout << "size form " << *size_form << endl;
	for (int i = 0; i < count; i++)
	{
		inputFileStream >> ptX;
		inputFileStream >> ptY;
		inputFileStream >> ptForm;
		inputFileStream >> ptColor;
		s.x = ptX;
		s.y = ptY;
		sites->push_back(s);
		colorVector->push_back(ptColor);
		formVector->push_back(ptForm);
		std::cout << ptX << "\n" << ptY << "\n" << ptForm << "\n" << ptColor << "\n\n";
	}

	std::vector<Point2> copySites = *sites;
	std::vector<int> copyColor = *colorVector;
	std::vector<int> copyForm = *formVector;

	std::sort(copySites.begin(), copySites.end(), sitesOrdered);
	for (int i = 0; i < count; i++) {
		int j = getIndex(*sites, copySites[i]);
		colorVector->operator[](i) = copyColor[j];
		formVector->operator[](i) = copyForm[j];
	}
	sites = &copySites;
}



void genOurSites(std::vector<Point2>* sites, BoundingBox& bbox, unsigned int dimension, std::vector<int>* colors, std::vector<int>* forms, double *size_form) {
	bbox = BoundingBox(0, dimension, dimension, 0);
	read_data(sites, colors, forms, size_form);

}

void setColor(int color)
{
	switch (color) {
	case 0: //RED
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	case 1: // BLUE
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	case 2: // YELLOW
		glColor3f(1.0f, 1.0f, 0.0f);
		break;
	case 3: // GREEN
		glColor3f(0.0f, 1.0f, 0.0f);
		break;
	case 4://Violet
		glColor3f(0.4f, 0.0f, 0.6f);
		break;
	default:
		glColor3f(0.0f, 0.0f, 0.0f);
		break;
	}

}

void draw_losange(Point2 center, int color, double size_form)
{
	setColor(color);
	glLineWidth(1.7f);
	glBegin(GL_QUADS);
	glVertex3d(center.x, center.y - size_form, 0);
	glVertex3d(center.x - size_form, center.y, 0);
	glVertex3d(center.x, center.y + size_form, 0);
	glVertex3d(center.x + size_form, center.y, 0);
	glEnd();

}

void draw_cross(Point2 center, int color, double size_form)
{
	setColor(color);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3d(center.x - size_form, center.y - size_form, 0);
	glVertex3d(center.x + size_form, center.y + size_form, 0);
	glVertex3d(center.x + size_form, center.y - size_form, 0);
	glVertex3d(center.x - size_form, center.y + size_form, 0);
	glEnd();


}

void draw_square(Point2 center, int color, double size_form)
{
	setColor(color);
	glLineWidth(1.7f);
	glBegin(GL_QUADS);
	glVertex3d(center.x - size_form, center.y - size_form, 0);
	glVertex3d(center.x + size_form, center.y - size_form, 0);
	glVertex3d(center.x + size_form, center.y + size_form, 0);
	glVertex3d(center.x - size_form, center.y + size_form, 0);
	glEnd();

}

void draw_triangle(Point2 center, int color, double size_form)
{

	setColor(color);
	glLineWidth(1.7f);
	glBegin(GL_TRIANGLES);
	glVertex3d(center.x, center.y + size_form, 0);
	glVertex3d(center.x + size_form, center.y - size_form, 0);
	glVertex3d(center.x - size_form, center.y - size_form, 0);
	glEnd();
}




void draw_button(Point2 center, double size_form)
{
	setColor(5);
	glLineWidth(1.7f);
	glBegin(GL_LINE_STRIP);
	glVertex3d(center.x - size_form * 2, center.y - size_form * 3 / 2, 0);
	glVertex3d(center.x + size_form * 2, center.y - size_form * 3 / 2, 0);
	glVertex3d(center.x + size_form * 2, center.y + size_form * 3 / 2, 0);
	glVertex3d(center.x - size_form * 2, center.y + size_form * 3 / 2, 0);
	glVertex3d(center.x - size_form * 2, center.y - size_form * 3 / 2, 0);
	glEnd();
}


void draw_Form(Point2 p, int colors, int forms, double size_form) {
	draw_button(p, size_form);
	cout << "Draw : " << p.x << ";" << p.y << " | " << forms << " | " << colors << " | " << size_form << endl;
	switch (forms) {
	case 0: //losange
		draw_losange(p, colors, size_form);
		break;
	case 1: //

		draw_cross(p, colors, size_form);
		break;
	case 2:
		draw_square(p, colors, size_form);
		break;
	case 3:
		draw_triangle(p, colors, size_form);
		break;
	default:
		cout << "ERROR, form missing in draw_points " << endl;
		break;
	}
}

int main() {
	unsigned int dimension = 1000;
	VoronoiDiagramGenerator vdg = VoronoiDiagramGenerator();
	Diagram* diagram = nullptr;
	double size_form;
	std::vector<Point2>* sites;
	std::vector<int>* colors;
	std::vector<int>* forms;
	BoundingBox bbox;

	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Voronoi Diagram Generator", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();
	// Define the viewport dimensions
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	// Uncommenting this call will result in wireframe polygons.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//MyGaze gazeReceiver;
	while (!glfwWindowShouldClose(window)) {
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		std::clock_t start;
		double duration;

		if (startOver) {
			std::cout << "\nUsage - When the OpenGL window has focus:\n"
				"\tPress 'R' to perform Lloyd's relaxation once.\n"
				"\tPress 'T' to perform Lloyd's relaxation ten times.\n"
				"\tPress 'Y' to toggle continuous Lloyd's relaxation.\n"
				"\tPress 'X' to generate a new diagram with a different number of sites.\n"
				"\tPress 'Esc' to exit.\n\n";
			startOver = false;
			relaxForever = false;
			relax = 0;
			sites = new std::vector<Point2>();
			colors = new std::vector<int>();
			forms = new std::vector<int>();

			genOurSites(sites, bbox, dimension, colors, forms, &size_form);
			//std::cout << "How many points? ";
			//std::cin >> nPoints;
			//genRandomSites(*sites, bbox, dimension, nPoints);
			start = std::clock();
			diagram = vdg.compute(*sites, bbox);
			duration = 1000 * (std::clock() - start) / (double)CLOCKS_PER_SEC;
			//std::cout << "Computing a diagram of " << nPoints << " points took " << duration << "ms.\n";
			delete sites;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLfloat background[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glClearBufferfv(GL_COLOR, 0, background);
		setColor(5);

		//glBegin(GL_POINTS);
		int i = 0;
		for (Cell* c : diagram->cells) {
			Point2& p = c->site.p;
			Point2 p_norm = Point2(normalize(p.x, dimension), -normalize(p.y, dimension));
			draw_Form(p_norm, colors->operator[](i), forms->operator[](i), size_form);
			//glVertex3d(normalize(p.x, dimension), -normalize(p.y, dimension), 0.0);
			i++;
		}
		//glEnd();
		setColor(5);
		glLineWidth(0.7f);
		for (Edge* e : diagram->edges) {
			if (e->vertA && e->vertB) {
				glBegin(GL_LINES);
				Point2& p1 = *e->vertA;
				Point2& p2 = *e->vertB;

				glVertex3d(normalize(p1[0], dimension), -normalize(p1[1], dimension), 0.0);
				glVertex3d(normalize(p2[0], dimension), -normalize(p2[1], dimension), 0.0);
				glEnd();
			}
		}

		if (relax || relaxForever) {
			Diagram* prevDiagram = diagram;
			start = std::clock();
			diagram = vdg.relax();
			duration = 1000 * (std::clock() - start) / (double)CLOCKS_PER_SEC;
			delete prevDiagram;

			//std::cout << "Computing a diagram of " << nPoints << " points took " << duration << "ms.\n";
			if (diagram->cells.size() != 4) {
				int x = 0;
			}
			--relax;
			if (relax < 0) relax = 0;
		}

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by it.
	glfwTerminate();

	delete diagram;
	return 0;
}
