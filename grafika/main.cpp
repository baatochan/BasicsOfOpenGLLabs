/*************************************************************************************/
//  Program rusujacy jajko
/*************************************************************************************/
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <gl/glext.h> //deklaracja funkcji z opengl 1.2/1.3
#include <iostream>
#include <cmath>
#include <ctime> //dla time

#define numberOfPoints 20 // poziom szczegolowosci rysunku - im wiecej tym wiecej punktow w jajku

typedef float point3[3];
/*************************************************************************************/

static GLfloat theta[] = {0, 0, 0}; // trzy kąty obrotu

int model = 1; //ktore sciany maja byc rysowane

using namespace std;


void drawTetrahedron() {
	glBegin(GL_TRIANGLES);

	glColor3f(1,1,1);

	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-4.5f, -2.1666f, -2.1666f);
	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(4.5f, -2.1666f, -2.1666f);
	glTexCoord2f(0.5f, 0.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -2.1666f, 4.3334f);

	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(-4.5f, 2.1666f, 2.1666f);
	glVertex3f(-4.5f, -2.1666f, -2.1666f);
	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(-4.5f, 2.1666f, 2.1666f);
	glVertex3f(0.0f, -2.1666f, 4.3334f);
	glTexCoord2f(0.5f, 0.0f);
	glNormal3f(-4.5f, 2.1666f, 2.1666f);
	glVertex3f(0.0f, 4.3334f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(4.5f, 2.1666f, 2.1666f);
	glVertex3f(0.0f, -2.1666f, 4.3334f);
	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(4.5f, 2.1666f, 2.1666f);
	glVertex3f(4.5f, -2.1666f, -2.1666f);
	glTexCoord2f(0.5f, 0.0f);
	glNormal3f(4.5f, 2.1666f, 2.1666f);
	glVertex3f(0.0f, 4.3334f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(0.0f, 2.1666f, -4.3334f);
	glVertex3f(4.5f, -2.1666f, -2.1666f);
	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(0.0f, 2.1666f, -4.3334f);
	glVertex3f(-4.5f, -2.1666f, -2.1666f);
	glTexCoord2f(0.5f, 0.0f);
	glNormal3f(0.0f, 2.1666f, -4.3334f);
	glVertex3f(0.0f, 4.3334f, 0.0f);

	glEnd();
}

// Funkcja rysująca osie układu współrzędnych
void Axes() {
	point3  x_min = {-5.0, 0.0, 0.0};
	point3  x_max = { 5.0, 0.0, 0.0};
// początek i koniec obrazu osi x

	point3  y_min = {0.0, -5.0, 0.0};
	point3  y_max = {0.0,  5.0, 0.0};
// początek i koniec obrazu osi y

	point3  z_min = {0.0, 0.0, -5.0};
	point3  z_max = {0.0, 0.0,  5.0};
//  początek i koniec obrazu osi y
	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y
	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z
	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();
}
/*************************************************************************************/

// Funkcja określająca co ma być rysowane (zawsze wywoływana gdy trzeba
// przerysować scenę)
void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Czyszczenie okna aktualnym kolorem czyszczącym

	glLoadIdentity();
// Czyszczenie macierzy bieżącej
	//Axes();
// Narysowanie osi przy pomocy funkcji zdefiniowanej wyżej

	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);

	drawTetrahedron(); // wywolanie funkcji rysujacej jajko

	glFlush();
// Przekazanie poleceń rysujących do wykonania

	glutSwapBuffers();
//
}

// funkcja definiujaca obracanie bryly
void spinEgg() {
	//theta[0] -= 0.05;
	if( theta[0] > 360.0 ) theta[0] -= 360.0;

	//theta[1] -= 0.05;
	if( theta[1] > 360.0 ) theta[1] -= 360.0;

	//theta[2] -= 0.05;
	if( theta[2] > 360.0 ) theta[2] -= 360.0;

	glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
}

/*************************************************************************************/

/*************************************************************************************/
// Funkcja wczytuje dane obrazu zapisanego w formacie TGA w pliku o nazwie
// FileName, alokuje pamięć i zwraca wskaźnik (pBits) do bufora w którym
// umieszczone są dane.
// Ponadto udostępnia szerokość (ImWidth), wysokość (ImHeight) obrazu
// tekstury oraz dane opisujące format obrazu według specyfikacji OpenGL
// (ImComponents) i (ImFormat).
// Jest to bardzo uproszczona wersja funkcji wczytującej dane z pliku TGA.
// Działa tylko dla obrazów wykorzystujących 8, 24, or 32 bitowy kolor.
// Nie obsługuje plików w formacie TGA kodowanych z kompresją RLE.
/*************************************************************************************/
GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat)
{

/*************************************************************************************/

// Struktura dla nagłówka pliku  TGA


#pragma pack(1)
	typedef struct
	{
		GLbyte    idlength;
		GLbyte    colormaptype;
		GLbyte    datatypecode;
		unsigned short    colormapstart;
		unsigned short    colormaplength;
		unsigned char     colormapdepth;
		unsigned short    x_orgin;
		unsigned short    y_orgin;
		unsigned short    width;
		unsigned short    height;
		GLbyte    bitsperpixel;
		GLbyte    descriptor;
	}TGAHEADER;
#pragma pack(8)

	FILE *pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;
	GLbyte    *pbitsperpixel = NULL;


/*************************************************************************************/

// Wartości domyślne zwracane w przypadku błędu

	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;

	pFile = fopen(FileName, "rb");
	if(pFile == NULL)
		return NULL;

/*************************************************************************************/
// Przeczytanie nagłówka pliku


	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);


/*************************************************************************************/

// Odczytanie szerokości, wysokości i głębi obrazu

	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;


/*************************************************************************************/
// Sprawdzenie, czy głębia spełnia założone warunki (8, 24, lub 32 bity)

	if(tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;

/*************************************************************************************/

// Obliczenie rozmiaru bufora w pamięci


	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;


/*************************************************************************************/

// Alokacja pamięci dla danych obrazu


	pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

	if(pbitsperpixel == NULL)
		return NULL;

	if(fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
	{
		free(pbitsperpixel);
		return NULL;
	}


/*************************************************************************************/

// Ustawienie formatu OpenGL


	switch(sDepth)

	{

		case 3:

			*ImFormat = GL_BGR_EXT;

			*ImComponents = GL_RGB8;

			break;

		case 4:

			*ImFormat = GL_BGRA_EXT;

			*ImComponents = GL_RGBA8;

			break;

		case 1:

			*ImFormat = GL_LUMINANCE;

			*ImComponents = GL_LUMINANCE8;

			break;

	};



	fclose(pFile);



	return pbitsperpixel;

}

/*************************************************************************************/

/*************************************************************************************/
// Funkcja ustalająca stan renderowania
/*************************************************************************************/
void MyInit(void)
{

/*************************************************************************************/

// Zmienne dla obrazu tekstury



	GLbyte *pBytes;
	GLint ImWidth, ImHeight, ImComponents;
	GLenum ImFormat;

	/*************************************************************************************/

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// Kolor czyszcący (wypełnienia okna) ustawiono na czarny

	/*************************************************************************************/

//  Definicja materiału z jakiego zrobione jest jajko
//  i definicja źródła światła

/*************************************************************************************/


/*************************************************************************************/
// Definicja materiału z jakiego zrobione jest jajko

	GLfloat mat_ambient[]  = {1.0, 1.0, 1.0, 1.0};
	// współczynniki ka =[kar,kag,kab] dla światła otoczenia

	GLfloat mat_diffuse[]  = {1.0, 1.0, 1.0, 1.0};
	// współczynniki kd =[kdr,kdg,kdb] światła rozproszonego

	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	// współczynniki ks =[ksr,ksg,ksb] dla światła odbitego

	GLfloat mat_shininess  = {20.0};
	// współczynnik n opisujący połysk powierzchni


/*************************************************************************************/
// Definicja źródła światła


	GLfloat light_position[] = {0, 5, 20.0, 1.0};
	// położenie źródła


	GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1.0};
	// składowe intensywności świecenia źródła światła otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	// składowe intensywności świecenia źródła światła powodującego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[]= {1.0, 1.0, 1.0, 1.0};
	// składowe intensywności świecenia źródła światła powodującego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]

	GLfloat att_constant  = {1.0};
	// składowa stała ds dla modelu zmian oświetlenia w funkcji
	// odległości od źródła

	GLfloat att_linear    = {0.05};
	// składowa liniowa dl dla modelu zmian oświetlenia w funkcji
	// odległości od źródła

	GLfloat att_quadratic  = {0.001};
	// składowa kwadratowa dq dla modelu zmian oświetlenia w funkcji
	// odległości od źródła

/*************************************************************************************/
// Ustawienie parametrów materiału i źródła światła

/*************************************************************************************/
// Ustawienie patrametrów materiału


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);


/*************************************************************************************/
// Ustawienie parametrów źródła

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);


/*************************************************************************************/
// Ustawienie opcji systemu oświetlania sceny

	glShadeModel(GL_SMOOTH); // właczenie łagodnego cieniowania
	glEnable(GL_LIGHTING);   // właczenie systemu oświetlenia sceny
	glEnable(GL_LIGHT0);     // włączenie źródła o numerze 0
	glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora

/*************************************************************************************/
/*************************************************************************************/

// Teksturowanie będzie prowadzone tyko po jednej stronie ściany

	glEnable(GL_CULL_FACE);


/*************************************************************************************/

//  Przeczytanie obrazu tekstury z pliku o nazwie tekstura.tga

	pBytes = LoadTGAImage("../../tekstury/D3_t.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);

	if (pBytes == nullptr) {
		cout<<"Failed to load texture file!";
	}

	/*************************************************************************************/

// Zdefiniowanie tekstury 2-D

	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);

/*************************************************************************************/

// Zwolnienie pamięci

	free(pBytes);


/*************************************************************************************/

// Włączenie mechanizmu teksturowania

	glEnable(GL_TEXTURE_2D);

/*************************************************************************************/

// Ustalenie trybu teksturowania

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

/*************************************************************************************/

// Określenie sposobu nakładania tekstur

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glCullFace(GL_FRONT);
}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.
void ChangeSize(GLsizei horizontal, GLsizei vertical ) {
	GLfloat AspectRatio;
// Deklaracja zmiennej AspectRatio  określającej proporcję
// wymiarów okna
	if(vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
// Ustawienie wielkościokna okna widoku (viewport)
// W tym przypadku od (0,0) do (horizontal, vertical)
	glMatrixMode(GL_PROJECTION);
// Przełączenie macierzy bieżącej na macierz projekcji
	glLoadIdentity();
// Czyszcznie macierzy bieżącej
	AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
// Wyznaczenie współczynnika  proporcji okna
// Gdy okno nie jest kwadratem wymagane jest określenie tak zwanej
// przestrzeni ograniczającej pozwalającej zachować właściwe
// proporcje rysowanego obiektu.
// Do okreslenia przestrzeni ograniczjącej służy funkcja
// glOrtho(...)
	if(horizontal <= vertical)
		glOrtho(-7.5,7.5,-7.5/AspectRatio,7.5/AspectRatio,10.0, -10.0);
	else
		glOrtho(-7.5*AspectRatio,7.5*AspectRatio,-7.5,7.5,10.0,-10.0);
	glMatrixMode(GL_MODELVIEW);
// Przełączenie macierzy bieżącej na macierz widoku modelu
	glLoadIdentity();
// Czyszcenie macierzy bieżącej
}
/*************************************************************************************/

// funckja reakcji na klawiature - zmiana modelu rysowanego w zaleznosci od klawisza
void keys(unsigned char key, int x, int y)
{
	if(key == '1') model = 1;
	if(key == '2') model = 2;
	if(key == '3') model = 3;
	if(key == '4') model = 4;
	if(key == '5') model = 5;

	RenderScene(); // przerysowanie obrazu sceny
}

// Główny punkt wejścia programu. Program działa w trybie konsoli
int main(int argc, char* argv[]) {
	srand(time(0)); // ziarno dla liczb pseudo losowych

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);

	glutInit(&argc, argv);

	glutInitWindowSize(300, 300);

	glutCreateWindow("trojkat - tekstury");

	glutDisplayFunc(RenderScene);
// Określenie, że funkcja RenderScene będzie funkcją zwrotną
// (callback function).  Bedzie ona wywoływana za każdym razem
// gdy zajdzie potrzba przeryswania okna
	glutReshapeFunc(ChangeSize);
// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
// zazmiany rozmiaru okna

	glutIdleFunc(spinEgg); //zdefiniowanie funckji obrotu jajka

	MyInit();
// Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
// inicjalizacje konieczne  przed przystąpieniem do renderowania
	glEnable(GL_DEPTH_TEST);
// Włączenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
// Funkcja uruchamia szkielet biblioteki GLUT

	return 0;
}
/*************************************************************************************/