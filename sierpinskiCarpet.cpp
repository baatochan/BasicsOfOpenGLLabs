typedef float point2[2];

#include <windows.h>
#include <iostream> //dla cout/cin
#include <gl/gl.h>
#include <gl/glut.h>
#include <stdlib.h> // dla rand
#include <time.h> //dla time

using namespace std;

int perturbationLevel; // Poziom deformacji dywanu (0-5)
int numberOfStepsToDraw; // Ilosc krokow dywanu do narysowania (0-5)
bool askUser; // Czy pytac użytwkownika o wartosci powyzszych zmiennych

// funckja zwracajaca losowa wartosc z zakresu [0,1]; przydatna do podawania losowych kolorow
float getRandomColor() {
    int random = rand() % 10001; //generuj losowa wartosc z zakresu [0, 10000]
    float color = (float)random / 10000; // podziel na 10k, wiec zakres zmienia sie na [0,1]

    return color;
}

//funckja zwracajaca losowa wartosc z zakresu [-side/4, side/4]
float getRandomOffset(float side) {
    int random = (rand() % 201) - 100; // generuj losowa wartosc z zakresu [-100,100]
    random *= perturbationLevel; //pomnoz to przez poziom znieksztalcen

    int maxOffset = 2000; // maksymalna wartosc 4*random*perturbationLevel

    float result = (float)random * side;
    result /= (float)maxOffset; // result moza przyjmowac wartosci [-side/4, side/4]

    return result;
}

// Rekurencyjna funkcja rysujaca dywan
void drawCarpet(int numberOfStepsToDraw, point2 leftTopCorner, point2 rightBottomCorner) {
    float sideOfSquare = rightBottomCorner[0] - leftTopCorner[0]; // bok kwadratu
    if (numberOfStepsToDraw == 0) { // gdy poziom rekurencji wynosi 0 => narysuj kwadrat
        // wartosci wspolrzednych kwadratu do nmarysowania z uwzglednieniem przesuniecia w wyniku perturbacji
        point2 finalLeftTopCorner = { leftTopCorner[0] + getRandomOffset(sideOfSquare), leftTopCorner[1] + getRandomOffset(sideOfSquare) };
        point2 finalRightTopCorner = { rightBottomCorner[0] + getRandomOffset(sideOfSquare), leftTopCorner[1] + getRandomOffset(sideOfSquare) };
        point2 finalLeftBottomCorner = { leftTopCorner[0] + getRandomOffset(sideOfSquare), rightBottomCorner[1] + getRandomOffset(sideOfSquare) };
        point2 finalRightBottomCorner = { rightBottomCorner[0] + getRandomOffset(sideOfSquare), rightBottomCorner[1] + getRandomOffset(sideOfSquare) };

        glBegin(GL_QUADS);
            glColor3f(getRandomColor(), getRandomColor(), getRandomColor()); // ustaw losowy kolor
            glVertex2fv(finalRightTopCorner); // ustaw wierzcholek

            glColor3f(getRandomColor(), getRandomColor(), getRandomColor());
            glVertex2fv(finalRightBottomCorner);

            glColor3f(getRandomColor(), getRandomColor(), getRandomColor());
            glVertex2fv(finalLeftBottomCorner);

            glColor3f(getRandomColor(), getRandomColor(), getRandomColor());
            glVertex2fv(finalLeftTopCorner);
        glEnd();

        return;
    } else if (numberOfStepsToDraw < 0) { // jesli poziom rekurencji jest ponizej 0 wyrzuc blad
        cout<<"Cos jest nie tak. Aplikacja nie moze kontynuowac."<<endl;
        return;
    } else {
        numberOfStepsToDraw--; // zmniejsz poziom rekurencji
        point2 leftTopOfSmaller; // deklaracja wierzcholkow dla mniejszych kwadratow
        point2 rightBottomOfSmaller;
        float sideOfSmallerSquare = sideOfSquare/3; // wyliczenie dlugosci wierzcholka mniejszego kwadratu
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (i == 1 && j == 1) continue; // pomin srodkowy
                // wyliczenia wspolrzednych kolejnych mniejszych kwadratow
                leftTopOfSmaller[0] = leftTopCorner[0] + j * sideOfSmallerSquare;
                leftTopOfSmaller[1] = leftTopCorner[1] - i * sideOfSmallerSquare;
                rightBottomOfSmaller[0] = (rightBottomCorner[0] - sideOfSquare) + (j+1) * sideOfSmallerSquare;
                rightBottomOfSmaller[1] = (rightBottomCorner[1] + sideOfSquare) - (i+1) * sideOfSmallerSquare;
                drawCarpet(numberOfStepsToDraw, leftTopOfSmaller, rightBottomOfSmaller); // wywolanie rekurencyjnej funkcji rusyjacej mneisjzy kwadrat
            }
        }
        return;
    }
}

// Funkcaja określająca, co ma być rysowane
// (zawsze wywoływana, gdy trzeba przerysować scenę)
void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Czyszczenie okna aktualnym kolorem czyszczącym

    glColor3f(1.0f, 0.0f, 0.0f); // ustawienie koloru na czerwony (potem i tak zmieniany na losowy)

    point2 leftTopCorner = { -80.0f, 80.0f }; // lewy gorny wierzcholek dywanu
    point2 rightBottomCorner = { 80.0f, -80.0f }; // prawy dolny wierzcholek dywanu

    drawCarpet(numberOfStepsToDraw, leftTopCorner, rightBottomCorner); // wywolanie funkcji rysujacej dywan

    glFlush(); // Przekazanie poleceń rysujących do wykonania
}

// Funkcja ustalająca stan renderowania
void MyInit(void)
{
    glClearColor(0.969f, 0.725f, 0.808f, 1.0f);
    // Kolor okna wnętrza okna - ustawiono na kolor grzywy Fluttershy c:
}

// Funkcja służąca do kontroli zachowania proporcji rysowanych obiektów
// niezależnie od rozmiarów okna graficznego
void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szerokość i wysokość okna) są
// przekazywane do funkcji za każdym razem, gdy zmieni się rozmiar okna
{
    GLfloat AspectRatio;
    // Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna

    if (vertical == 0)
        // Zabezpieczenie pzred dzieleniem przez 0
        vertical = 1;

    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkościokna okna urządzenia (Viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)

    glMatrixMode(GL_PROJECTION);
    // Określenie układu współrzędnych obserwatora
    glLoadIdentity();
    // Określenie przestrzeni ograniczającej
    AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
    // Wyznaczenie współczynnika proporcji okna
    // Gdy okno na ekranie nie jest kwadratem wymagane jest
    // określenie okna obserwatora.
    // Pozwala to zachować właściwe proporcje rysowanego obiektu
    // Do określenia okna obserwatora służy funkcja glOrtho(...)

    if (horizontal <= vertical)
        glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
    else
        glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    // Określenie układu współrzędnych
    glLoadIdentity();
}

// Główny punkt wejścia programu. Program działa w trybie konsoli
int main(int argc, char* argv[])
{
    srand(time(0)); // ziarno dla liczb pseudo losowych
    askUser = true; // czy pytac uzytkownika o stopien zdeformowania i ilosc krokow

    if (askUser) {
        do {
            cout << "Podaj stopien zdeformowania (0-5):";
            cin >> perturbationLevel;
        } while (perturbationLevel < 0 || perturbationLevel > 5); // stopien zdeformowania moze miec wartosci od 0 do 5

        do {
            cout << "Podaj ilosc krokow (poziom rekurencji) (0-5):";
            cin >> numberOfStepsToDraw;
        } while (numberOfStepsToDraw < 0 || numberOfStepsToDraw > 5); // ilosc krokow moze miec wartosc od 0 do 5
    } else {
        // Jesli chcesz podac dane bez pytania uzytkownika ustaw askUser na false i podaj tu dane
        perturbationLevel = 3;
        numberOfStepsToDraw = 3;
    }

    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    // Ustawienie trybu wyświetlania
    // GLUT_SINGLE - pojedynczy bufor wyświetlania
    // GLUT_RGBA - model kolorów RGB

    glutCreateWindow("Dywan Sierpinskiego z perturbacjami");
    // Utworzenie okna i określenie treści napisu w nagłówku okna

    glutDisplayFunc(RenderScene);
    // Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
    // Biblioteka GLUT będzie wywoływała tą funkcję za każdym razem, gdy
    // trzeba będzie przerysować okno


    glutReshapeFunc(ChangeSize);
    // Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną za
    // zmiany rozmiaru okna

    MyInit();
    // Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie
    // inicjalizacje konieczneprzed przystąpieniem do renderowania

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

    return 0;
}