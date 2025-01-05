#include <iostream>
#include "Console.h"
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Point {
    int x;
    int y;
};

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void displayScreen(char screen[14][14], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (screen[i][j] == '/') {
                setColor(1); 
            } 
            else if (screen[i][j] == 'm') {
                setColor(14); 
            }
            else if (screen[i][j] == 'b' ){
                setColor(12);
            }
            else if (screen[i][j] == 'X')
            {
                setColor(15);
            }
            else if (screen[i][j] == 'v')
            {
                setColor(13);
            }            

            
            else {
                setColor(7); 
            }
            
            cout << screen[i][j] << ' ';
        }
        cout << endl;
    }
    setColor(7); 
}

void updateScreen(char screen[14][14], int rows, int cols, Point fixedPoints[], int fixedPointsCount, Point enemypoints[] , Point &winpoint , int enemypointscount ,Point &movingPoint , Point &bombpoint) {
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((i % 2 == 0) && (j % 2 == 0)) {
                screen[i][j] = 'X';
            } else {
                screen[i][j] = ' ';
            }
        }
    }
    
    for (int i = 0; i < fixedPointsCount; i++) {
        if (fixedPoints[i].x != -1 && fixedPoints[i].y != -1) {
            screen[fixedPoints[i].x][fixedPoints[i].y] = '/';
        }
    }
    for (int i = 0; i < enemypointscount; i++) {
        if (enemypoints[i].x != -1 && enemypoints[i].y != -1) {
            screen[enemypoints[i].x][enemypoints[i].y] = 'v';
        }
    }
    
    if (bombpoint.x != -1 && bombpoint.y != -1)
    {
        screen[bombpoint.x][bombpoint.y] = 'b';
    }
    
    screen[winpoint.x][winpoint.y] = '';
    screen[movingPoint.x][movingPoint.y] = 'm';
}
Console c;
int main() {
    int chose ;
    int a = c.getMaxX();
    int b = c.getMaxY();
    c.gotoxy(a,b); 
    cout << "HELLO\n 1.play \n 2.help \n";
    cin >> chose;
    if (chose==1)
    { 
    cout << "1.low \n 2.medium \n 3.hard" ;
    int chose2;
    cin >> chose2;
    if (chose2 == 1)
    {
    srand(time(0)); 
    const int rows = 14;
    const int cols = 14;
    char screen[rows][cols];
    Point fixedPoints[2];
    Point enemypoints[1];
    for (int i = 0; i < 2; i++) {
        do {
            fixedPoints[i] = {rand() % rows, rand() % cols};
        } while (fixedPoints[i].x == 0 && fixedPoints[i].y == 0); 
    }
    for (int i = 0; i < 2; i++) {
        do {
            enemypoints[i] = {rand() % rows, rand() % cols};
        } while (enemypoints[i].x == 0 && enemypoints[i].y == 0); 
    }
    Point winpoint;
            do {
            winpoint = {rand() % rows, rand() % cols};
        } while (winpoint.x == 0 && winpoint.y == 0); 
    Point movingPoint = {0, 0};
    Point bombpoint = {-1, -1};

    while (true) 
    {
       
        updateScreen(screen, rows, cols, fixedPoints, 2, enemypoints, winpoint ,1,movingPoint , bombpoint);
        
        system("cls"); 
        displayScreen(screen, rows, cols);

        char input = _getch();
    if (input == 'b') {
      bombpoint.x = movingPoint.x;
      bombpoint.y = movingPoint.y;
}

        if (input == 'w' && movingPoint.x > 0 && screen[movingPoint.x - 1][movingPoint.y] != 'X' && screen[movingPoint.x - 1][movingPoint.y] != '/') movingPoint.x--;
        if (input == 's' && movingPoint.x < rows - 1 && screen[movingPoint.x+1][movingPoint.y] != 'X' && screen[movingPoint.x+1][movingPoint.y] != '/') movingPoint.x++;
        if (input == 'a' && movingPoint.y > 0 && screen[movingPoint.x][movingPoint.y-1] != 'X' && screen[movingPoint.x][movingPoint.y-1] != '/') movingPoint.y--;
        if (input == 'd' && movingPoint.y < cols - 1 && screen[movingPoint.x][movingPoint.y+1] != 'X' && screen[movingPoint.x][movingPoint.y+1] != '/') movingPoint.y++;
        

        for (int i = 0; i < 2; i++) {
            if (screen[fixedPoints[i].x - 1][fixedPoints[i].y] == 'b' || screen[fixedPoints[i].x - 2][fixedPoints[i].y] == 'b' || screen[fixedPoints[i].x + 1][fixedPoints[i].y] == 'b' || screen[fixedPoints[i].x + 2][fixedPoints[i].y] == 'b' || screen[fixedPoints[i].x][fixedPoints[i].y-1] == 'b' || screen[fixedPoints[i].x][fixedPoints[i].y - 2] == 'b' || screen[fixedPoints[i].x][fixedPoints[i].y + 2] == 'b' || screen[fixedPoints[i].x][fixedPoints[i].y + 1] == 'b') {
                fixedPoints[i].x = -1; 
                fixedPoints[i].y = -1;
                bombpoint.x = -1;
                bombpoint.y = -1;
            }
            }
        for (int i = 0; i < 1; i++) {
            if (screen[enemypoints[i].x - 1][enemypoints[i].y] == 'b' || screen[enemypoints[i].x - 2][enemypoints[i].y] == 'b' || screen[enemypoints[i].x + 1][enemypoints[i].y] == 'b' || screen[enemypoints[i].x + 2][enemypoints[i].y] == 'b' || screen[enemypoints[i].x][enemypoints[i].y-1] == 'b' || screen[enemypoints[i].x][enemypoints[i].y - 2] == 'b' || screen[enemypoints[i].x][enemypoints[i].y + 2] == 'b' || screen[enemypoints[i].x][enemypoints[i].y + 1] == 'b') {
                enemypoints[i].x = -1; 
                enemypoints[i].y = -1;
                bombpoint.x = -1;
                bombpoint.y = -1;
            }
            }
            for (int i =0; i < 1 ; i++){

            if (screen[enemypoints[i].x][enemypoints[i].y] == 'm')
            {
                system("cls");
                cout << "you lose ";
                Sleep(30000);
                exit(0);
            }}


    }
    
    } 
    else if (chose2==2)
    {
    srand(time(0)); 
    const int rows = 14;
    const int cols = 14;
    char screen[rows][cols];
    Point fixedPoints[5];
    Point enemypoints[3];
    for (int i = 0; i < 5; i++) {
        do {
            fixedPoints[i] = {rand() % rows, rand() % cols};
        } while (fixedPoints[i].x == 0 && fixedPoints[i].y == 0); 
    }
    for (int i = 0; i < 3; i++) {
        do {
            enemypoints[i] = {rand() % rows, rand() % cols};
        } while (enemypoints[i].x == 0 && enemypoints[i].y == 0); }
    Point winpoint;
            do {
            winpoint = {rand() % rows, rand() % cols};
        } while (winpoint.x == 0 && winpoint.y == 0); 
    Point movingPoint = {0, 0};
    Point bombpoint = {-1, -1};

    while (true) {
       
        updateScreen(screen, rows, cols, fixedPoints, 5, enemypoints, winpoint ,3, movingPoint , bombpoint);
        
        system("cls"); 
        displayScreen(screen, rows, cols);

        char input = _getch();
    if (input == 'b') {
      bombpoint.x = movingPoint.x;
      bombpoint.y = movingPoint.y;
    }

        if (input == 'w' && movingPoint.x > 0 && screen[movingPoint.x - 1][movingPoint.y] != 'X' && screen[movingPoint.x - 1][movingPoint.y] != '/') movingPoint.x--;
        if (input == 's' && movingPoint.x < rows - 1 && screen[movingPoint.x+1][movingPoint.y] != 'X' && screen[movingPoint.x+1][movingPoint.y] != '/') movingPoint.x++;
        if (input == 'a' && movingPoint.y > 0 && screen[movingPoint.x][movingPoint.y-1] != 'X' && screen[movingPoint.x][movingPoint.y-1] != '/') movingPoint.y--;
        if (input == 'd' && movingPoint.y < cols - 1 && screen[movingPoint.x][movingPoint.y+1] != 'X' && screen[movingPoint.x][movingPoint.y+1] != '/') movingPoint.y++;
        

        for (int i = 0; i < 5; i++) {
            if (screen[fixedPoints[i].x - 1][fixedPoints[i].y] == 'b' || screen[fixedPoints[i].x - 2][fixedPoints[i].y] == 'b' || screen[fixedPoints[i].x + 1][fixedPoints[i].y] == 'b' || screen[fixedPoints[i].x + 2][fixedPoints[i].y] == 'b' || screen[fixedPoints[i].x][fixedPoints[i].y-1] == 'b' || screen[fixedPoints[i].x][fixedPoints[i].y - 2] == 'b' || screen[fixedPoints[i].x][fixedPoints[i].y + 2] == 'b' || screen[fixedPoints[i].x][fixedPoints[i].y + 1] == 'b') {
                fixedPoints[i].x = -1; 
                fixedPoints[i].y = -1;
                bombpoint.x = -1;
                bombpoint.y = -1;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (screen[enemypoints[i].x - 1][enemypoints[i].y] == 'b' || screen[enemypoints[i].x - 2][enemypoints[i].y] == 'b' || screen[enemypoints[i].x + 1][enemypoints[i].y] == 'b' || screen[enemypoints[i].x + 2][enemypoints[i].y] == 'b' || screen[enemypoints[i].x][enemypoints[i].y-1] == 'b' || screen[enemypoints[i].x][enemypoints[i].y - 2] == 'b' || screen[enemypoints[i].x][enemypoints[i].y + 2] == 'b' || screen[enemypoints[i].x][enemypoints[i].y + 1] == 'b') {
                enemypoints[i].x = -1; 
                enemypoints[i].y = -1;
                bombpoint.x = -1;
                bombpoint.y = -1;
            }
            }
        for (int i = 0; i < 7; i++)
        {
            if (screen[enemypoints[i].x][enemypoints[i].y] == 'm')
            {
                system("cls");
                cout << "you lose ";
                Sleep(100);
                exit(0);
            }
            
        }
    
    }
    
    } 
    else if (chose2 == 3)
    {
            srand(time(0)); 
    const int rows = 14;
    const int cols = 14;
    char screen[rows][cols];
    Point fixedPoints[10];
    Point enemypoints[7];
    for (int i = 0; i < 10; i++) {
        do {
            fixedPoints[i] = {rand() % rows, rand() % cols};
        } while (fixedPoints[i].x == 0 && fixedPoints[i].y == 0); 
    }
    for (int i = 0; i < 7; i++) {
        do {
            enemypoints[i] = {rand() % rows, rand() % cols};
        } while (enemypoints[i].x == 0 && enemypoints[i].y == 0); }
    Point winpoint;
            do {
            winpoint = {rand() % rows, rand() % cols};
        } while (winpoint.x == 0 && winpoint.y == 0); 
    Point movingPoint = {0, 0};
    Point bombpoint = {-1, -1};

    while (true) {
       
        updateScreen(screen, rows, cols, fixedPoints, 10, enemypoints, winpoint ,7, movingPoint , bombpoint);
        
        system("cls"); 
        displayScreen(screen, rows, cols);

        char input = _getch();
    if (input == 'b') {
      bombpoint.x = movingPoint.x;
      bombpoint.y = movingPoint.y;
}

        if (input == 'w' && movingPoint.x > 0 && screen[movingPoint.x - 1][movingPoint.y] != 'X' ) movingPoint.x--;
        if (input == 's' && movingPoint.x < rows - 1 && screen[movingPoint.x+1][movingPoint.y] != 'X') movingPoint.x++;
        if (input == 'a' && movingPoint.y > 0 && screen[movingPoint.x][movingPoint.y-1] != 'X' ) movingPoint.y--;
        if (input == 'd' && movingPoint.y < cols - 1 && screen[movingPoint.x][movingPoint.y+1] != 'X' ) movingPoint.y++;
        

        for (int i = 0; i < 10; i++) {
            if (screen[fixedPoints[i].x - 1][fixedPoints[i].y] == 'b' || screen[fixedPoints[i].x - 2][fixedPoints[i].y] == 'b' || screen[fixedPoints[i].x + 1][fixedPoints[i].y] == 'b' || screen[fixedPoints[i].x + 2][fixedPoints[i].y] == 'b' || screen[fixedPoints[i].x][fixedPoints[i].y-1] == 'b' || screen[fixedPoints[i].x][fixedPoints[i].y - 2] == 'b' || screen[fixedPoints[i].x][fixedPoints[i].y + 2] == 'b' || screen[fixedPoints[i].x][fixedPoints[i].y + 1] == 'b') {
                fixedPoints[i].x = -1; 
                fixedPoints[i].y = -1;
                bombpoint.x = -1;
                bombpoint.y = -1;
            }
        }
        for (int i = 0; i < 7; i++) {
            if (screen[enemypoints[i].x - 1][enemypoints[i].y] == 'b' || screen[enemypoints[i].x - 2][enemypoints[i].y] == 'b' || screen[enemypoints[i].x + 1][enemypoints[i].y] == 'b' || screen[enemypoints[i].x + 2][enemypoints[i].y] == 'b' || screen[enemypoints[i].x][enemypoints[i].y-1] == 'b' || screen[enemypoints[i].x][enemypoints[i].y - 2] == 'b' || screen[enemypoints[i].x][enemypoints[i].y + 2] == 'b' || screen[enemypoints[i].x][enemypoints[i].y + 1] == 'b') {
                enemypoints[i].x = -1; 
                enemypoints[i].y = -1;
                bombpoint.x = -1;
                bombpoint.y = -1;
            }
            }
        for (int i = 0; i < 7; i++)
        {
            if (screen[enemypoints[i].x][enemypoints[i].y] == 'm')
            {
                system("cls");
                cout << "you lose ";
                Sleep(100);
                exit(0);
            }
            
            
            
        }
        
    }
    
    } 
    }
     
    

    
    
    else {cout << "hello";}
    return 0;
    }






