#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>

#define MIN_X 83
#define MAX_X 629
#define MIN_Y 30
#define MAX_Y 409
#define MAX_BUTTONS 22
#define MAX_COLPAT 28

#define CLEAR 0
#define MARK_OP 8
#define CLIP_OP 10
#define TRANS_OP 11
#define ROTATE_OP 12
#define DELETE_OP 13
#define FLIP 14
#define MIRROR 15
#define LOAD_OP 16
#define SAVE_OP 17
#define SCALE_OP 18

typedef struct button_desc {
    int xmin, ymin, xmax, ymax;
    int button_no;
    char* desc;
} button;

button buttons[MAX_BUTTONS];

typedef struct color_button {
    int xmin, ymin, xmax, ymax;
    int color;
    int colflag;
} color_but;

color_but colorbuttons[28];
/*/color_but patternbuttons[16];*/

/*/ structure to mark an area      */
struct
    {
    int top, left, bottom, right;
} marker;

int marked = 0; /*/ to store whether marked or not*/

char FileName[40] = "Untitled";
int saved = 1; /*/to store if file has been saved or not*/
int LeftButtonPressed;
int RightButtonPressed;
int mousex, mousey;
int prevx, prevy;
int Current_Color = BLACK; /*/ to  Store the current color           */
int Current_Pattern = EMPTY_FILL; /*/ to store the current Pattern*/
int Current_Button = 1; /*/ to store the current button pressed*/
int Prev_Button = 1; /*/ to store the previous button              */

void init();
void init_button(int, int, int, int, int, char*);
void init_color_button(int, int, int, int, int, int);
void New_ico(int x1, int y1);
void Open_ico(int x1, int y1);
void Save_ico(int x1, int y1);
void Line_ico(int x1, int y1);
void Rectangle_ico(int x1, int y1);
void Circle_ico(int x1, int y1);
void Ellipse_ico(int x1, int y1);
void Sphere_ico(int x1, int y1);
void Spiral_ico(int x1, int y1);
void Brush_ico(int x1, int y1);
void Erase_ico(int x1, int y1);
void Alphabet_ico(int x, int y);
void Mark_ico(int x1, int y1);
void Clip_ico(int x1, int y1);
void Translate_ico(int x, int y);
void Rotate_ico(int x, int y);
void Scale_ico(int x, int y);
void Bucket_ico(int x, int y);
void Cube_ico(int x, int y);
void Del_ico(int x, int y);
void color_ico(int x1, int y1, int c);
void size_up_ico(int x, int y);
void size_down_ico(int x, int y);
void flip_ico(int x, int y);
void mirror_ico(int x, int y);
void draw_button_border(int);
void undraw_button_border(int no);
void draw_color_button_border(int, int);
void start_up();

void check_if_exit();
int check_mouse_on(int, int, int, int);
int check_if_button_pressed();
int check_if_color();
int check_if_pattern();

void disp_filename();
void disp_coord();
void ShowStatus(char*);
void ClearStatus();
char* readline();

void showmouse();
void hidemouse();
void wheremouse(int*, int*);
int buttclicked();
void reset();
void getxy();
void startmouse(int, int);
void restrictmouse(int, int, int, int);

void Diagram();
void freehand();
void drawline();
void drawrectangle();
void erase();
void beep();
void drawtext();
void plotellipsepoints(int, int, int, int);
void algoellipse(int, int, float, float);
void algospiral(int, int, float, float);
void drawellipse();
void drawspiral();
void drawcircle();
void Bucket();
void Cube();
void sphere();
void insert(int, int);
void ffill(int, int, int, int);

void save();
void Load();

void mirror();
void flip();

void mark();
void unmark();
void delete ();
void translate();
void rotate();
void scale();
void clip();
/*
void title(int,int,int,int);
*/

void main()
{
    int i, j, gd = DETECT, gm = DETECT;
    initgraph(&gd, &gm, "c:\turboc2\include");
    if (graphresult()) {
        printf("n Could not initialise graphics n");
        exit(0);
    }

    /*
 cleardevice();
 setcolor(DARKGRAY);
 title(getmaxx()/2-180,getmaxy()/2-150,getmaxx()/2+180,getmaxy()/2+150);
 settextstyle(0,0,1);
 settextjustify(LEFT_TEXT,TOP_TEXT);
 setusercharsize(1,1,1,1);
 setcolor(WHITE);
 outtextxy(getmaxx()/2-150,getmaxy()/2-100,"Abhishek Dhingra's");
 setcolor(DARKGRAY);
 outtextxy(170,285,"for DOS environment");
 settextstyle(8,0,2);
 setusercharsize(3,2,5,1);
 setcolor(BLACK);
 for(i=0;i<=6;i++) outtextxy(getmaxx()/2-150+i,getmaxy()/2-150,"DOS Paint"); settextstyle(8,0,1); setusercharsize(1,1,1,1); setfillstyle(1,BLACK); rectangle(170,275,430,280); floodfill(175,277,BLACK); circle(429,186,5); settextstyle(2,0,4); outtextxy(427,180,"R"); settextstyle(6,0,1); outtextxy(150,355,"Version 1.0"); settextstyle(2,0,4); outtextxy(330,330,"This product is licensed to"); outtextxy(395,345,"R.V.C.E"); flushall(); getch(); flushall(); closegraph(); initgraph(&gd,&gm,"c:\turboc2\include"); if(graphresult()) { printf("n Could not initialise graphics n"); exit(0); } */ reset();
    start_up();
    showmouse();
    startmouse(300, 300);
    disp_filename(); /*setfillstyle(SOLID_FILL,LIGHTGRAY);*/ /*bar(8,25,78,270); */
    init();
    undraw_button_border(Current_Button);
    while (1) {
        getxy();
        disp_coord();
        if (LeftButtonPressed) {
            if (check_if_button_pressed() >= 0)
                ;
            else if (check_if_color())
                ClearStatus();
            else if (check_mouse_on(MIN_X + 2, MIN_Y + 2, MAX_X - 2, MAX_Y - 2)) {
                ClearStatus();
                saved = 0; /* file has been altered; */
                Diagram();
            }
            else
                check_if_exit();
        }
        else
            check_if_button_pressed();
    }
}

/*
void title(int x,int y,int x1,int y1)
{
 int pc;
 int i;
 hidemouse();
 setcolor(LIGHTGRAY);
 for(i=y;i<=y1;i++)
  line(x,i,x1,i);
 setcolor(WHITE);
 for(i=0;i<=5;i++)
 {
  line(x+i,y+i,x1-i,y+i);
  line(x+i,y+i,x+i,y1-i);
 }
 setcolor(BLACK);
 line(x1,y1,x1,y);
 line(x1,y1,x,y1);
 setcolor(DARKGRAY);
 for(i=1;i<=5;i++)
 {
  line(x1-i,y1-i,x+i,y1-i);
  line(x1-i,y1-i,x1-i,y+i);
 }
 showmouse();
}
*/
void init()
{
    int x1 = 10, y1 = 30, x2 = 44, y2 = MAX_Y + 28, ywidth = 30, xwidth = 30;
    int butt = 0, i, j;

    New_ico(x1, y1);
    init_button(butt, x1, y1, xwidth, ywidth, "New File");
    draw_button_border(butt);
    butt++;

    Line_ico(x2, y1);
    init_button(butt, x2, y1, xwidth, ywidth, "Line Drawing Tool");
    draw_button_border(butt);
    butt++;

    y1 = y1 + ywidth;
    Rectangle_ico(x1, y1);
    init_button(butt, x1, y1, xwidth, ywidth, "Rectangle Drawing Tool");
    draw_button_border(butt);
    butt++;

    Circle_ico(x2, y1);
    init_button(butt, x2, y1, xwidth, ywidth, "Circle Drawing Tool");
    draw_button_border(butt);
    butt++;

    y1 = y1 + ywidth;
    Ellipse_ico(x1, y1);
    init_button(butt, x1, y1, xwidth, ywidth, "Ellipse Drawing Tool");
    draw_button_border(butt);
    butt++;

    Spiral_ico(x2, y1);
    init_button(butt, x2, y1, xwidth, ywidth, "Spiral Drawing Tool");
    draw_button_border(butt);
    butt++;

    y1 = y1 + ywidth;
    Brush_ico(x1, y1);
    init_button(butt, x1, y1, xwidth, ywidth, "Free Hand");
    draw_button_border(butt);
    butt++;

    Erase_ico(x2, y1);
    init_button(butt, x2, y1, xwidth, ywidth, "Eraser");
    draw_button_border(butt);
    butt++;

    y1 = y1 + ywidth;
    Mark_ico(x1, y1);
    init_button(butt, x1, y1, xwidth, ywidth, "Marking Tool");
    draw_button_border(butt);
    butt++;

    Alphabet_ico(x2, y1);
    init_button(butt, x2, y1, xwidth, ywidth, "Text");
    draw_button_border(butt);
    butt++;

    y1 = y1 + ywidth;
    Clip_ico(x1, y1);
    init_button(butt, x1, y1, xwidth, ywidth, "Clipping (Works with Mark)");
    draw_button_border(butt);
    butt++;

    Translate_ico(x2, y1);
    init_button(butt, x2, y1, xwidth, ywidth, "Translate (Works with Mark)");
    draw_button_border(butt);
    butt++;

    y1 = y1 + ywidth;
    Rotate_ico(x1, y1);
    init_button(butt, x1, y1, xwidth, ywidth, "Rotate (Works with mark)");
    draw_button_border(butt);
    butt++;

    Del_ico(x2, y1);
    init_button(butt, x2, y1, xwidth, ywidth, "Delete (Works with mark)");
    draw_button_border(butt);
    butt++;

    y1 = y1 + ywidth;
    flip_ico(x1, y1);
    init_button(butt, x1, y1, xwidth, ywidth, "Flip Canvas");
    draw_button_border(butt);
    butt++;

    mirror_ico(x2, y1);
    init_button(butt, x2, y1, xwidth, ywidth, "Mirror Canvas");
    draw_button_border(butt);
    butt++;

    y1 = y1 + ywidth;
    Open_ico(x1, y1);
    init_button(butt, x1, y1, xwidth, ywidth, "Open File");
    draw_button_border(butt);
    butt++;

    Save_ico(x2, y1);
    init_button(butt, x2, y1, xwidth, ywidth, "Save File");
    draw_button_border(butt);
    butt++;

    y1 = y1 + ywidth;
    Scale_ico(x1, y1);
    init_button(butt, x1, y1, xwidth, ywidth, "Scaling (Works with Mark)");
    draw_button_border(butt);
    butt++;

    Bucket_ico(x2, y1);
    init_button(butt, x2, y1, xwidth, ywidth, "Bucket Fill");
    draw_button_border(butt);
    butt++;

    y1 = y1 + ywidth;
    Sphere_ico(x1, y1);
    init_button(butt, x1, y1, xwidth, ywidth, "3D Ellipse Drawing Tool");
    draw_button_border(butt);
    butt++;

    Cube_ico(x2, y1);
    init_button(butt, x2, y1, xwidth, ywidth, "Cuboid Drawing Tool");
    draw_button_border(butt);
    butt++;

    butt = 0;
    x1 = MIN_X + 8;
    y1 = MAX_Y + 9;
    xwidth = 19;
    ywidth = 15;
    for (i = 0; i < 8; i++) {
        init_color_button(butt, x1, y1, xwidth, ywidth, 1);
        draw_color_button_border(butt, 1);
        butt++;

        init_color_button(butt, x1, y2, xwidth, ywidth, 1);
        draw_color_button_border(butt, 1);
        butt++;

        x1 = x1 + xwidth;
    }

    butt = 0;
    x1 = x1 + 25;
    for (i = 0; i < 6; i++) {
        init_color_button(butt, x1, y1, xwidth, ywidth, 0);
        draw_color_button_border(butt, 0);
        butt++;

        init_color_button(butt, x1, y2, xwidth, ywidth, 0);
        draw_color_button_border(butt, 0);
        butt++;

        x1 = x1 + xwidth;
    }
    setfillstyle(Current_Pattern, Current_Color);
    bar(20, MAX_Y + 7, 65, MAX_Y + 7 + 35);
    setcolor(BLACK);
    rectangle(20, MAX_Y + 7, 65, MAX_Y + 7 + 35);
    setcolor(Current_Color);
}

void init_color_button(int color, int xmin, int ymin, int xwidth, int ywidth, int colflag)
{
    int xgap = 4;
    if (colflag) {
        colorbuttons[color].xmin = xmin;
        colorbuttons[color].xmax = xmin + xwidth - xgap;
        colorbuttons[color].ymin = ymin;
        colorbuttons[color].ymax = ymin + ywidth;
        colorbuttons[color].color = color;
        colorbuttons[color].colflag = colflag;
    }
    else {
        colorbuttons[color + 16].xmin = xmin;
        colorbuttons[color + 16].xmax = xmin + xwidth - xgap;
        colorbuttons[color + 16].ymin = ymin;
        colorbuttons[color + 16].ymax = ymin + ywidth;
        colorbuttons[color + 16].color = color;
        colorbuttons[color + 16].colflag = colflag;
    }
}

void init_button(int no, int xmin, int ymin, int xwidth, int ywidth, char* desc)
{
    int ygap = 4;
    buttons[no].xmin = xmin;
    buttons[no].ymin = ymin;
    buttons[no].xmax = xmin + xwidth;
    buttons[no].ymax = ymin + ywidth - ygap;
    buttons[no].desc = (char*)malloc(strlen(desc) + 1);
    if (buttons[no].desc == NULL) {
        cleardevice();
        printf("n No MEMORY ");
    }
    strcpy(buttons[no].desc, desc);
}

void draw_button_border(int no)
{
    int color = getcolor();
    hidemouse();
    setcolor(WHITE);
    line(buttons[no].xmin, buttons[no].ymin, buttons[no].xmax, buttons[no].ymin);
    line(buttons[no].xmin, buttons[no].ymin, buttons[no].xmin, buttons[no].ymax);
    setcolor(DARKGRAY);
    line(buttons[no].xmax, buttons[no].ymax, buttons[no].xmax, buttons[no].ymin);
    line(buttons[no].xmax, buttons[no].ymax, buttons[no].xmin, buttons[no].ymax);
    setcolor(color);
    showmouse();
}

void undraw_button_border(int no)
{
    int color = getcolor();
    hidemouse();
    setcolor(DARKGRAY);
    line(buttons[no].xmin, buttons[no].ymin, buttons[no].xmax, buttons[no].ymin);
    line(buttons[no].xmin, buttons[no].ymin, buttons[no].xmin, buttons[no].ymax);
    setcolor(WHITE);
    line(buttons[no].xmax, buttons[no].ymax, buttons[no].xmax, buttons[no].ymin);
    line(buttons[no].xmax, buttons[no].ymax, buttons[no].xmin, buttons[no].ymax);
    setcolor(color);
    showmouse();
}

void draw_color_button_border(int no, int colflag)
{
    int color = getcolor();
    setcolor(BLACK);
    if (colflag) {
        line(colorbuttons[no].xmin, colorbuttons[no].ymin, colorbuttons[no].xmax, colorbuttons[no].ymin);
        line(colorbuttons[no].xmin, colorbuttons[no].ymin, colorbuttons[no].xmin, colorbuttons[no].ymax);
        line(colorbuttons[no].xmax, colorbuttons[no].ymax, colorbuttons[no].xmax, colorbuttons[no].ymin);
        line(colorbuttons[no].xmax, colorbuttons[no].ymax, colorbuttons[no].xmin, colorbuttons[no].ymax);
        setfillstyle(1, no);
        floodfill(colorbuttons[no].xmin + 1, colorbuttons[no].ymin + 1, BLACK);
    }
    else {
        line(colorbuttons[no + 16].xmin, colorbuttons[no + 16].ymin, colorbuttons[no + 16].xmax, colorbuttons[no + 16].ymin);
        line(colorbuttons[no + 16].xmin, colorbuttons[no + 16].ymin, colorbuttons[no + 16].xmin, colorbuttons[no + 16].ymax);
        line(colorbuttons[no + 16].xmax, colorbuttons[no + 16].ymax, colorbuttons[no + 16].xmax, colorbuttons[no + 16].ymin);
        line(colorbuttons[no + 16].xmax, colorbuttons[no + 16].ymax, colorbuttons[no + 16].xmin, colorbuttons[no + 16].ymax);
        setfillstyle(no, LIGHTBLUE);
        floodfill(colorbuttons[no + 16].xmin + 1, colorbuttons[no + 16].ymin + 1, BLACK);
    }
    setcolor(color);
}

void New_ico(int x1, int y1)
{
    setlinestyle(0, 1, 1);
    setcolor(BLACK);
    line(9 + x1, 4 + y1, 9 + x1, 20 + y1);
    line(9 + x1, 20 + y1, 21 + x1, 20 + y1);
    line(21 + x1, 20 + y1, 21 + x1, 8 + y1);
    line(9 + x1, 4 + y1, 17 + x1, 4 + y1);
    line(17 + x1, 4 + y1, 17 + x1, 8 + y1);
    line(17 + x1, 8 + y1, 21 + x1, 8 + y1);
    line(21 + x1, 8 + y1, 17 + x1, 4 + y1);

    setfillstyle(1, WHITE);
    floodfill(10 + x1, 9 + y1, BLACK);
}

void Open_ico(int x1, int y1)
{
    setlinestyle(0, 1, 1);
    setcolor(BLACK);
    line(5 + x1, 20 + y1, 17 + x1, 20 + y1);
    line(17 + x1, 20 + y1, 24 + x1, 15 + y1);
    line(24 + x1, 15 + y1, 12 + x1, 15 + y1);
    line(12 + x1, 15 + y1, 5 + x1, 20 + y1);
    setfillstyle(1, DARKGRAY);
    floodfill(10 + x1, 18 + y1, BLACK);

    line(5 + x1, 20 + y1, 5 + x1, 10 + y1);
    line(5 + x1, 10 + y1, 6 + x1, 8 + y1);
    line(6 + x1, 8 + y1, 8 + x1, 8 + y1);
    line(8 + x1, 8 + y1, 9 + x1, 10 + y1);
    line(9 + x1, 10 + y1, 17 + x1, 10 + y1);
    line(17 + x1, 10 + y1, 17 + x1, 15 + y1);
    setfillstyle(1, YELLOW);
    floodfill(6 + x1, 12 + y1, BLACK);
    line(15 + x1, 7 + y1, 17 + x1, 5 + y1);
    line(17 + x1, 5 + y1, 22 + x1, 7 + y1);
    line(22 + x1, 7 + y1, 24 + x1, 12 + y1);
    line(24 + x1, 12 + y1, 20 + x1, 10 + y1);
    line(24 + x1, 12 + y1, 26 + x1, 9 + y1);
}

void Save_ico(int x1, int y1)
{
    setlinestyle(0, 1, 1);
    setcolor(BLACK);
    line(6 + x1, 4 + y1, 24 + x1, 4 + y1);
    line(24 + x1, 4 + y1, 24 + x1, 20 + y1);
    line(24 + x1, 20 + y1, 8 + x1, 20 + y1);
    line(8 + x1, 20 + y1, 6 + x1, 18 + y1);
    line(6 + x1, 18 + y1, 6 + x1, 4 + y1);

    line(9 + x1, 4 + y1, 9 + x1, 12 + y1);
    line(9 + x1, 12 + y1, 21 + x1, 12 + y1);
    line(21 + x1, 12 + y1, 21 + x1, 4 + y1);

    line(10 + x1, 20 + y1, 10 + x1, 15 + y1);
    line(10 + x1, 15 + y1, 20 + x1, 15 + y1);
    line(20 + x1, 15 + y1, 20 + x1, 20 + y1);

    line(17 + x1, 15 + y1, 17 + x1, 20 + y1);

    line(21 + x1, 7 + y1, 24 + x1, 7 + y1);

    setfillstyle(1, WHITE);
    floodfill(10 + x1, 5 + y1, BLACK);

    setfillstyle(1, LIGHTBLUE);
    floodfill(7 + x1, 5 + y1, BLACK);

    setfillstyle(1, DARKGRAY);
    floodfill(11 + x1, 19 + y1, BLACK);
}

void Line_ico(int x1, int y1)
{
    line(8 + x1, 5 + y1, 22 + x1, 19 + y1);
}

void Rectangle_ico(int x1, int y1)
{
    rectangle(8 + x1, 5 + y1, 22 + x1, 19 + y1);
}

void Circle_ico(int x1, int y1)
{
    circle(15 + x1, 12 + y1, 8);
}

void Spiral_ico(int x1, int y1)
{
    int xrad = 3, yrad = 1;
    int i;
    x1 = 15 + x1;
    y1 = 14 + y1;
    for (i = 1; i <= 4; ++i) {
        ellipse(x1, y1, 90, 270, xrad, yrad);
        xrad += 1;
        yrad += 1;
        y1 -= 1;
        ellipse(x1, y1, 270, 90, xrad, yrad);
        xrad += 1;
        yrad += 1;
        y1 += 1;
    }
}

void Ellipse_ico(int x1, int y1)
{
    ellipse(15 + x1, 13 + y1, 0, 360, 8, 6);
}

void Brush_ico(int x1, int y1)
{
    setcolor(BLACK);
    setlinestyle(0, 1, 3);
    line(19 + x1, 21 + y1, 10 + x1, 9 + y1);
    setlinestyle(0, 1, 1);
    line(11 + x1, 9 + y1, 11 + x1, 6 + y1);
    line(11 + x1, 6 + y1, 6 + x1, 4 + y1);
    line(6 + x1, 4 + y1, 7 + x1, 9 + y1);
    line(7 + x1, 9 + y1, 11 + x1, 9 + y1);
}

void Fill_ico(int x1, int y1)
{
    setlinestyle(0, 1, 1);
    setcolor(BLACK);
    line(10 + x1, 11 + y1, 16 + x1, 19 + y1);
    line(16 + x1, 19 + y1, 25 + x1, 12 + y1);
    line(25 + x1, 12 + y1, 20 + x1, 5 + y1);

    line(10 + x1, 11 + y1, 24 + x1, 11 + y1);
    setfillstyle(1, RED);
    floodfill(12 + x1, 12 + y1, BLACK);
    setcolor(RED);
    line(10 + x1, 11 + y1, 8 + x1, 14 + y1);
    line(8 + x1, 14 + y1, 8 + x1, 16 + y1);
}

void Cube_ico(int x, int y)
{
    rectangle(8 + x, 5 + y, 24 + x, 17 + y);
    rectangle(5 + x, 9 + y, 21 + x, 21 + y);
    line(5 + x, 9 + y, 8 + x, 5 + y);
    line(21 + x, 21 + y, 24 + x, 17 + y);
    line(21 + x, 9 + y, 24 + x, 5 + y);
    line(5 + x, 21 + y, 8 + x, 17 + y);
}

void Erase_ico(int x1, int y1)
{
    setlinestyle(0, 1, 1);
    setcolor(BLACK);
    line(14 + x1, 20 + y1, 25 + x1, 7 + y1);
    line(25 + x1, 7 + y1, 23 + x1, 4 + y1);
    line(23 + x1, 4 + y1, 12 + x1, 17 + y1);
    line(12 + x1, 17 + y1, 14 + x1, 20 + y1);

    line(14 + x1, 20 + y1, 5 + x1, 20 + y1);
    line(5 + x1, 20 + y1, 5 + x1, 17 + y1);
    line(5 + x1, 17 + y1, 12 + x1, 17 + y1);

    line(5 + x1, 17 + y1, 16 + x1, 4 + y1);
    line(16 + x1, 4 + y1, 23 + x1, 4 + y1);

    setfillstyle(1, DARKGRAY);
    floodfill(14 + x1, 18 + y1, BLACK);
    setfillstyle(1, WHITE);
    floodfill(16 + x1, 5 + y1, BLACK);
}

void Alphabet_ico(int x, int y)
{
    setcolor(BLACK);
    setlinestyle(0, 1, 3);
    line(8 + x, 20 + y, 18 + x, 4 + y);
    line(18 + x, 4 + y, 18 + x, 20 + y);
    setlinestyle(0, 1, 1);
    line(12 + x, 14 + y, 19 + x, 14 + y);
    line(6 + x, 20 + y, 12 + x, 20 + y);
    line(15 + x, 20 + y, 21 + x, 20 + y);
}

void Mark_ico(int x1, int y1)
{
    setlinestyle(0, 1, 1);
    setcolor(BLACK);
    setlinestyle(3, 1, 1);
    rectangle(5 + x1, 5 + y1, 25 + x1, 19 + y1);
    setlinestyle(0, 1, 1);
}

void Clip_ico(int x1, int y1)
{
    setlinestyle(0, 1, 1);
    setcolor(BLACK);
    rectangle(5 + x1, 5 + y1, 25 + x1, 19 + y1);
    setfillstyle(1, WHITE);
    floodfill(15 + x1, 12 + y1, BLACK);
    setfillstyle(1, BLACK);
    bar(12 + x1, 10 + y1, 23 + x1, 17 + y1);
}

void Translate_ico(int x, int y)
{
    setcolor(BLACK);
    line(6 + x, 3 + y, 20 + x, 3 + y);
    line(20 + x, 3 + y, 20 + x, 8 + y);
    line(6 + x, 3 + y, 6 + x, 16 + y);
    line(6 + x, 16 + y, 12 + x, 16 + y);

    line(25 + x, 8 + y, 12 + x, 8 + y);
    line(12 + x, 8 + y, 12 + x, 20 + y);
    line(12 + x, 20 + y, 25 + x, 20 + y);
    line(25 + x, 20 + y, 25 + x, 8 + y);
    setfillstyle(1, LIGHTRED);
    floodfill(8 + x, 5 + y, BLACK);
    floodfill(20 + x, 18 + y, BLACK);
}

void Rotate_ico(int x, int y)
{
    setcolor(BLACK);
    line(6 + x, 5 + y, 20 + x, 5 + y);
    line(20 + x, 5 + y, 20 + x, 8 + y);
    line(6 + x, 5 + y, 6 + x, 18 + y);
    line(6 + x, 18 + y, 12 + x, 18 + y);

    line(15 + x, 7 + y, 26 + x, 11 + y);
    line(26 + x, 11 + y, 21 + x, 20 + y);
    line(21 + x, 20 + y, 11 + x, 16 + y);
    line(11 + x, 16 + y, 15 + x, 7 + y);
    setfillstyle(1, LIGHTRED);
    floodfill(8 + x, 7 + y, BLACK);
    floodfill(20 + x, 18 + y, BLACK);
}

void Del_ico(int x, int y)
{
    setcolor(RED);
    setlinestyle(0, 1, 3);
    line(9 + x, 5 + y, 16 + x, 11 + y);
    line(16 + x, 11 + y, 21 + x, 18 + y);

    line(20 + x, 5 + y, 11 + x, 12 + y);
    line(11 + x, 12 + y, 8 + x, 19 + y);
    setcolor(BLACK);
    setlinestyle(0, 1, 1);
}

void color_ico(int x1, int y1, int c)
{
    setcolor(BLACK);
    rectangle(x1, y1, x1 + 9, y1 + 8);
    setfillstyle(1, c);
    floodfill(x1 + 1, y1 + 1, BLACK);
}

void size_up_ico(int x, int y)
{
    x -= 6;
    y -= 4;
    setcolor(BLACK);
    line(x + 10, y + 12, x + 22, y + 7);
    line(x + 22, y + 7, x + 34, y + 12);
    line(x + 10, y + 12, x + 34, y + 12);
    setfillstyle(1, BLACK);
    floodfill(x + 20, y + 10, BLACK);
}

void size_down_ico(int x, int y)
{
    x -= 6;
    y -= 3;
    setcolor(BLACK);
    line(x + 10, y + 7, x + 22, y + 12);
    line(x + 22, y + 12, x + 34, y + 7);
    line(x + 10, y + 7, x + 34, y + 7);
    setfillstyle(1, BLACK);
    putpixel(x + 20, y + 10, WHITE);
    floodfill(x + 20, y + 10, BLACK);
}

void Sphere_ico(int x1, int y1)
{
    setlinestyle(0, 1, 1);
    setcolor(BLACK);
    circle(x1 + 15, y1 + 13, 8);
    ellipse(x1 + 15, y1 + 13, 0, 360, 4, 8);
    ellipse(x1 + 15, y1 + 13, 0, 360, 8, 4);
}

void Bucket_ico(int x, int y)
{
    setlinestyle(0, 1, 1);
    setcolor(BLACK);
    line(7 + x, 8 + y, 11 + x, 20 + y);
    line(11 + x, 20 + y, 21 + x, 16 + y);
    line(21 + x, 16 + y, 17 + x, 4 + y);
    line(7 + x, 8 + y, 17 + x, 4 + y);
    line(17 + x, 4 + y, 7 + x, 8 + y);

    line(3 + x, 12 + y, 7 + x, 8 + y);
    line(3 + x, 12 + y, 5 + x, 15 + y);
    line(5 + x, 15 + y, 7 + x, 8 + y);

    setfillstyle(1, BLUE);
    floodfill(10 + x, 9 + y, BLACK);

    setfillstyle(1, YELLOW);
    floodfill(5 + x, 13 + y, BLACK);
}

void flip_ico(int x, int y)
{
    setcolor(BLACK);
    line(14 + x, 4 + y, 8 + x, 8 + y);
    line(8 + x, 8 + y, 12 + x, 8 + y);
    line(12 + x, 8 + y, 12 + x, 15 + y);
    line(12 + x, 15 + y, 8 + x, 15 + y);
    line(8 + x, 15 + y, 14 + x, 19 + y);
    line(14 + x, 19 + y, 20 + x, 15 + y);
    line(20 + x, 15 + y, 16 + x, 15 + y);
    line(16 + x, 15 + y, 16 + x, 8 + y);
    line(16 + x, 8 + y, 20 + x, 8 + y);
    line(20 + x, 8 + y, 14 + x, 4 + y);
    setfillstyle(1, CYAN);
    floodfill(14 + x, 10 + y, BLACK);
}

void mirror_ico(int x, int y)
{
    setcolor(BLACK);
    line(6 + x, 12 + y, 10 + x, 17 + y);
    line(11 + x, 18 + y, 11 + x, 15 + y);
    line(11 + x, 15 + y, 18 + x, 15 + y);
    line(18 + x, 15 + y, 18 + x, 18 + y);
    line(18 + x, 18 + y, 23 + x, 12 + y);
    line(23 + x, 12 + y, 18 + x, 6 + y);
    line(18 + x, 6 + y, 18 + x, 10 + y);
    line(18 + x, 10 + y, 11 + x, 10 + y);
    line(11 + x, 10 + y, 11 + x, 6 + y);
    line(11 + x, 6 + y, 6 + x, 12 + y);
    setfillstyle(1, CYAN);
    floodfill(9 + x, 12 + y, BLACK);
}

void Scale_ico(int x, int y)
{
    int i;
    setcolor(BLUE);
    line(x + 5, y + 5, x + 5, y + 20);
    line(x + 25, y + 5, x + 25, y + 20);
    setcolor(RED);
    for (i = y + 7; i < y + 19; i += 2)
        line(x + 7, i, x + 23, i);
}
void start_up()
{
    setfillstyle(1, LIGHTGRAY);
    floodfill(200, 200, 1); /* for MAIN WINDOW */
    setcolor(15);
    line(0, 0, 639, 0);
    line(0, 0 + 1, 639 - 1, 0 + 1);
    line(0, 0, 0, 479 - 1);
    line(0 + 1, 0, 0 + 1, 479 - 2);
    setcolor(8);
    line(639, 0 + 1, 639, 479);
    line(639 - 1, 0 + 2, 639 - 1, 479 - 1);
    line(639, 479, 0, 479);
    line(639, 479 - 1, 0 + 1, 479 - 1); /* for drawing window */
    setcolor(WHITE);
    rectangle(MIN_X, MIN_Y, MAX_X, MAX_Y);
    setfillstyle(1, WHITE);
    floodfill(300, 300, WHITE);
    setcolor(8);
    line(MIN_X, MIN_Y, MAX_X, MIN_Y);
    line(MIN_X, MIN_Y + 1, MAX_X - 1, MIN_Y + 1);
    line(MIN_X, MIN_Y, MIN_X, MAX_Y - 1);
    line(MIN_X + 1, MIN_Y, MIN_X + 1, MAX_Y - 2);
    setcolor(8);
    line(MAX_X, MIN_Y + 1, MAX_X, MAX_Y);
    line(MAX_X - 1, MIN_Y + 2, MAX_X - 1, MAX_Y - 1);
    line(MAX_X, MAX_Y, MIN_X, MAX_Y);
    line(MAX_X, MAX_Y - 1, MIN_X + 1, MAX_Y - 1); /* for status bar */
    setcolor(8);
    line(10, 460, 629, 460);
    line(10, 460, 10, 479 - 5 - 1);
    setcolor(15);
    line(629, 460, 629, 479 - 5);
    line(629, 479 - 5, 10, 479 - 5); /*/ for color*/
    setcolor(15);
    line(MIN_X, MAX_Y + 4, 251, MAX_Y + 4);
    line(MIN_X, MAX_Y + 4, MIN_X, MAX_Y + 47);
    setcolor(0);
    line(251, MAX_Y + 47, MIN_X, MAX_Y + 47);
    line(251, MAX_Y + 47, 251, MAX_Y + 4); /*/ for background */
    setcolor(15);
    line(258, MAX_Y + 4, 386, MAX_Y + 4);
    line(258, MAX_Y + 4, 258, MAX_Y + 47);
    setcolor(0);
    line(386, MAX_Y + 47, 258, MAX_Y + 47);
    line(386, MAX_Y + 47, 386, MAX_Y + 4); /* for Names */
    setcolor(15);
    line(8, 365, 76, 365);
    line(8, 365, 8, MAX_Y - 10);
    setcolor(0);
    line(76, MAX_Y - 10, 8, MAX_Y - 10);
    line(76, MAX_Y - 10, 76, 365);
    setcolor(BLUE);
    outtextxy(35, MAX_Y - 40, "By");
    outtextxy(12, MAX_Y - 30, "Abhishek");
    outtextxy(15, MAX_Y - 20, "Dhingra"); /* for college */
    setcolor(15);
    line(400, MAX_Y + 4, 630, MAX_Y + 4);
    line(400, MAX_Y + 4, 400, MAX_Y + 47);
    setcolor(0);
    line(630, MAX_Y + 47, 400, MAX_Y + 47);
    line(630, MAX_Y + 47, 630, MAX_Y + 4);
    setcolor(BLUE);
    outtextxy(410, MAX_Y + 15, "Developed At :");
    outtextxy(410, MAX_Y + 31, "R.V College of Engineering");
}
void disp_filename()
{
    char name[60];
    int xpos;
    setfillstyle(SOLID_FILL, BLUE);
    bar(10, 5, 629, 18);
    strcpy(name, "DOS Paint - ");
    strcat(name, FileName);
    xpos = (getmaxx() - textwidth(name)) / 2;
    setcolor(LIGHTRED);
    outtextxy(xpos, 8, name);
    setfillstyle(SOLID_FILL, BLUE);
    bar(614, 6, 628, 17);
    outtextxy(620, 8, "X");
}
void disp_coord()
{
    char xy[25];
    int color;
    if (prevx != mousex || prevy != mousey)
        if ((mousex > MIN_X + 1) && (mousex < max_X - 1) && (mousey > MIN_Y + 1) && (mousey < max_Y - 1)) {
            sprintf(xy, " x : %d  y : %d", mousex - MIN_X - 2, mousey - MIN_Y - 2);
            color = getcolor();
            setcolor(LIGHTGRAY);
            outtextxy(475, 464, "?????????????????"); /* ALT 219*/
            setcolor(BLACK);
            outtextxy(475, 464, xy);
            setcolor(color);
        }
}

void reset()
{
    union REGS regs;
    regs.x.ax = 0;
    int86(0x33, &regs, &regs);
    if (regs.x.ax == 0) {
        printf("n No Mouse Drivers ");
        exit(0);
    }
}

void showmouse()
{
    union REGS regs;
    regs.x.ax = 1;
    int86(0x33, &regs, &regs);
}

void hidemouse()
{
    union REGS regs;
    regs.x.ax = 2;
    int86(0x33, &regs, &regs);
}

int buttclicked()
{
    union REGS regs;
    regs.x.ax = 3;
    int86(0x33, &regs, &regs);

    return regs.x.bx;
}

void wheremouse(int* x, int* y)
{
    union REGS regs;
    regs.x.ax = 3;
    int86(0x33, &regs, &regs);
    *x = regs.x.cx;
    *y = regs.x.dx;
}

void getxy()
{
    union REGS regs;
    regs.x.ax = 3;
    int86(0x33, &regs, &regs);

    prevx = mousex;
    prevy = mousey;
    if (regs.x.bx & 1)
        LeftButtonPressed = 1;
    else
        LeftButtonPressed = 0;
    if (regs.x.bx & 2)
        RightButtonPressed = 1;
    else
        RightButtonPressed = 0;

    mousex = regs.x.cx;
    mousey = regs.x.dx;
}

void startmouse(int x, int y)
{
    union REGS regs;
    regs.x.ax = 4;
    regs.x.cx = x;
    regs.x.dx = y;
    int86(0x33, &regs, &regs);
}

void restrictmouse(int minx, int miny, int maxx, int maxy)
{
    union REGS regs;

    regs.x.cx = minx;
    regs.x.dx = maxx;
    regs.x.ax = 0x7;
    int86(0x33, &regs, &regs);
    regs.x.cx = miny;
    regs.x.dx = maxy;
    regs.x.ax = 0x8;
    int86(0x33, &regs, &regs);
}

int check_mouse_on(int minx, int miny, int maxx, int maxy)
{
    if (mousex < minx)
        return 0;
    if (mousex > maxx)
        return 0;
    if (mousey < miny)
        return 0;
    if (mousey > maxy)
        return 0;

    return 1;
}

void check_if_exit()
{
    if ((check_mouse_on(614, 6, 628, 17)) && LeftButtonPressed) {
        flushall();
        closegraph();
        exit(0);
    }
}

int check_if_button_pressed()
{
    int ret_value = -1;
    int i;
    char ch;

    for (i = 0; i < max_BUTTONS; ++i) {
        if (check_mouse_on(buttons[i].xmin, buttons[i].ymin, buttons[i].xmax, buttons[i].ymax)) {
            if (LeftButtonPressed && i != Current_Button) {
                ret_value = i;
                draw_button_border(Current_Button);
                Prev_Button = Current_Button;
                undraw_button_border(i);
                Current_Button = i;

                switch (Current_Button) {
                case CLEAR:
                    if (marked)
                        unmark();
                    hidemouse();
                    if (!saved) {
                        ShowStatus("Save Changes ? ");
                        ch = getch();
                        if (ch == 'y' || ch == 'Y')
                            save();
                    }
                    strcpy(FileName, "Untitled");
                    disp_filename();
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(MIN_X + 2, MIN_Y + 2, MAX_X - 2, MAX_Y - 2);
                    draw_button_border(Current_Button);
                    undraw_button_border(Prev_Button);
                    Current_Button = Prev_Button;
                    setfillstyle(Current_Pattern, Current_Color);
                    showmouse();
                    break;

                case LOAD_OP:
                    if (marked)
                        unmark();
                    hidemouse();
                    Load();
                    draw_button_border(Current_Button);
                    undraw_button_border(Prev_Button);
                    Current_Button = Prev_Button;
                    setfillstyle(Current_Pattern, Current_Color);
                    showmouse();
                    break;

                case SAVE_OP:
                    if (marked)
                        unmark();
                    hidemouse();
                    save();
                    draw_button_border(Current_Button);
                    undraw_button_border(Prev_Button);
                    Current_Button = Prev_Button;
                    setfillstyle(Current_Pattern, Current_Color);
                    showmouse();
                    break;

                case MIRROR:
                    if (marked)
                        unmark();
                    hidemouse();
                    mirror();
                    draw_button_border(Current_Button);
                    undraw_button_border(Prev_Button);
                    Current_Button = Prev_Button;
                    setfillstyle(Current_Pattern, Current_Color);
                    showmouse();
                    break;

                case FLIP:
                    if (marked)
                        unmark();
                    hidemouse();
                    flip();
                    draw_button_border(Current_Button);
                    undraw_button_border(Prev_Button);
                    Current_Button = Prev_Button;
                    setfillstyle(Current_Pattern, Current_Color);
                    showmouse();
                    break;

                case DELETE_OP:
                    hidemouse();
                    delete ();
                    draw_button_border(Current_Button);
                    undraw_button_border(Prev_Button);
                    Current_Button = Prev_Button;
                    setfillstyle(Current_Pattern, Current_Color);
                    showmouse();
                    break;

                case ROTATE_OP:
                    hidemouse();
                    rotate();
                    draw_button_border(Current_Button);
                    undraw_button_border(Prev_Button);
                    Current_Button = Prev_Button;
                    setfillstyle(Current_Pattern, Current_Color);
                    showmouse();
                    break;
                case CLIP_OP:
                    hidemouse();
                    clip();
                    draw_button_border(Current_Button);
                    undraw_button_border(Prev_Button);
                    Current_Button = Prev_Button;
                    setfillstyle(Current_Pattern, Current_Color);
                    showmouse();
                    break;
                case SCALE_OP:
                    hidemouse();
                    scale();
                    draw_button_border(Current_Button);
                    undraw_button_border(Prev_Button);
                    Current_Button = Prev_Button;
                    setfillstyle(Current_Pattern, Current_Color);
                    showmouse();
                    break;
                }
                if (Current_Button != MARK_OP && Current_Button != TRANS_OP) {
                    if (marked)
                        unmark();
                }
            }

            if (prevx != mousex || prevy != mousey)
                ShowStatus(buttons[i].desc);

            return ret_value;
        }
    }

    ClearStatus();
    return ret_value;
}

int check_if_color()
{
    int i = 0;
    for (i = 0; i < max_COLPAT; i++) {
        if (check_mouse_on(colorbuttons[i].xmin, colorbuttons[i].ymin, colorbuttons[i].xmax, colorbuttons[i].ymax)) {
            if (colorbuttons[i].colflag) {
                Current_Color = colorbuttons[i].color;
            }
            else
                Current_Pattern = colorbuttons[i].color;
            if (Current_Pattern == EMPTY_FILL)
                setfillstyle(SOLID_FILL, Current_Color);
            else
                setfillstyle(Current_Pattern, Current_Color);
            bar(20, MAX_Y + 7, 65, MAX_Y + 7 + 35);
            setcolor(BLACK);
            rectangle(20, MAX_Y + 7, 65, MAX_Y + 7 + 35);
            setcolor(Current_Color);
            return 1;
        }
    }
    return 0;
}

void ShowStatus(char* str)
{
    int color = getcolor();
    int i;

    ClearStatus();
    setcolor(BLACK);
    outtextxy(12, 464, str);
    setcolor(color);
}

void ClearStatus()
{

    static int first_time;
    static char text[59];
    int i;

    setcolor(LIGHTGRAY);
    if (!first_time) {
        strcpy(text, "");
        for (i = 0; i < 58; ++i)
            strcat(text, "?");
        text[58] = '�';
        first_time = 1;
    }
    outtextxy(12, 464, text);
}

void Diagram()
{
    restrictmouse(MIN_X + 2, MIN_Y + 2, MAX_X - 2, MAX_Y - 2);
    hidemouse();
    switch (Current_Button) {
    case 1:
        drawline();
        break;
    case 2:
        drawrectangle();
        break;
    case 3:
        drawcircle();
        break;
    case 4:
        drawellipse();
        break;
    case 5:
        drawspiral();
        break;
    case 6:
        freehand();
        break;
    case 7:
        erase();
        break;
    case MARK_OP:
        mark();
        break;
    case 9:
        drawtext();
        break;
    case TRANS_OP:
        translate();
        break;
    case 19:
        Bucket();
        break;
    case 20:
        sphere();
        break;
    case 21:
        Cube();
        break;
    }
    showmouse();
    restrictmouse(0, 0, 639, 479);
}

void freehand()
{
    setcolor(Current_Color);
    if (prevx < min_X + 2 || prevx > MAX_X - 2 || prevy > MAX_Y - 2 || prevy < min_Y + 2)
        return;

    while (LeftButtonPressed) {

        disp_coord();

        line(mousex, mousey, prevx, prevy);
        getxy();
    }
}

void drawline()
{
    int color = 15 - Current_Color;
    int x, y;
    setcolor(color);
    setwritemode(XOR_PUT);

    x = mousex;
    y = mousey;

    if (x < min_X + 2 || x > MAX_X - 2 || y > MAX_Y - 2 || y < min_Y + 2)
        return;

    while (LeftButtonPressed) {
        disp_coord();
        line(x, y, mousex, mousey);
        getxy();
        line(x, y, mousex, mousey);
    }
    setwritemode(COPY_PUT);
    setcolor(Current_Color);
    line(x, y, mousex, mousey);
}

void drawrectangle()
{
    int color = 15 - Current_Color;
    int x, y;
    setcolor(color);
    setwritemode(XOR_PUT);

    x = mousex;
    y = mousey;

    while (LeftButtonPressed) {
        disp_coord();
        rectangle(x, y, mousex, mousey);
        getxy();
        rectangle(x, y, mousex, mousey);
    }
    setwritemode(COPY_PUT);
    setcolor(Current_Color);
    if (Current_Pattern == EMPTY_FILL)
        rectangle(x, y, mousex, mousey);
    else {
        setfillstyle(Current_Pattern, Current_Color);
        bar(x, y, mousex, mousey);
    }
}

void erase()
{
    int i, j;
    while (LeftButtonPressed) {

        disp_coord();
        for (i = mousex; i < mousex + 10 && i <= MAX_X - 2; ++i)
            for (j = mousey; j < mousey + 10 && j <= MAX_Y - 2; ++j)
                putpixel(i, j, WHITE);
        getxy();
    }
}

void beep()
{
    sound(7);
    delay(1000);
    nosound();
}

void drawtext()
{
    int size = 0, max_char, i = 0;
    char ch;
    char str[68]; /*/ ( (MAX_X-2)-(MIN_X+2) )/8 ,8 being width & height of a char*/
    char blank[68]; /*/ to write blank*/

    max_char = (MAX_X - 2 - mousex) / 8;
    if ((MAX_Y - 2 - mousey < 9) || (max_char < 1)) {
        ShowStatus(" Not Enough Space to Write ");
        beep();
        ClearStatus();
        return;
    }

    ShowStatus("Press  or  to exit");
    fflush(stdin);
    str[0] = '�';

    ch = getch();

    while (ch != 13 && ch != 27) {
        if (ch == 8) {
            if (size < 1)
                beep();
            else {
                setcolor(WHITE);
                strcpy(blank, "");
                for (i = 0; i < size; ++i)
                    blank[i] = '?';
                blank[size] = '�';
                outtextxy(mousex, mousey, blank);

                setcolor(Current_Color);
                size--;
                str[size] = '�';
                outtextxy(mousex, mousey, str);
            }
        }
        else if (size == max_char) {
            beep();
        }
        else {
            size++;
            setcolor(WHITE);
            strcpy(blank, "");
            for (i = 0; i < size; ++i)
                blank[i] = '?';
            blank[size] = '�';
            outtextxy(mousex, mousey, blank);
            str[size - 1] = ch;
            setcolor(Current_Color);
            str[size] = '�';
            outtextxy(mousex, mousey, str);
        }
        ch = getch();
    }
    ClearStatus();
}
struct node1 {
    int x, y;
    struct node1* next;
};
struct node1 *last1, *root1, *p1;
void insert(int x, int y)
{
    struct node1* new1;
    new1 = (struct node1*)malloc(sizeof(struct node1));
    new1->x = x;
    new1->y = y;
    new1->next = NULL;
    last1->next = new1;
    last1 = new1;
    return;
}

void Bucket()
{
    int x, y, bgcolor;
    while (LeftButtonPressed) {
        disp_coord();
        getxy();
    }
    setwritemode(COPY_PUT);
    x = mousex;
    y = mousey;
    bgcolor = getpixel(x, y);
    ffill(x, y, bgcolor, Current_Color);
}

void ffill(int x, int y, int backColor, int fill_color)
{
    if (backColor == fill_color)
        return;
    last1 = root1 = (struct node1*)malloc(sizeof(struct node1));
    root1->x = x;
    root1->y = y;
    root1->next = NULL;
    while (root1 != NULL) {
        putpixel(x, y, fill_color);
        if (getpixel(x, y - 1) == backColor) {
            putpixel(x, y - 1, fill_color);
            insert(x, y - 1);
        }
        if (getpixel(x + 1, y) == backColor) {
            putpixel(x + 1, y, fill_color);
            insert(x + 1, y);
        }
        if (getpixel(x, y + 1) == backColor) {
            putpixel(x, y + 1, fill_color);
            insert(x, y + 1);
        }
        if (getpixel(x - 1, y) == backColor) {
            putpixel(x - 1, y, fill_color);
            insert(x - 1, y);
        }
        p1 = root1;
        root1 = root1->next;
        free(p1);
        x = root1->x;
        y = root1->y;
    }
}

void Cube()
{
    int color = 15 - Current_Color;
    int temp, x, y, mousex1, mousey1;
    restrictmouse((MIN_X + 5), (MIN_Y + 5), (MAX_X - 30), (MAX_Y - 30));
    setcolor(color);
    setwritemode(XOR_PUT);

    x = mousex;
    y = mousey;

    while (LeftButtonPressed) {
        disp_coord();
        /*  rectangle(x,y,mousex,mousey); */
        getxy();
        /*  rectangle(x,y,mousex,mousey); */
    }
    setwritemode(COPY_PUT);
    mousex1 = mousex;
    mousey1 = mousey;
    if (mousex11 && mousey1 - y > 1) {
        if (Current_Pattern == EMPTY_FILL) {
            setcolor(Current_Color);
            rectangle(x, y, mousex1, mousey1);
            rectangle(x + 25, y + 25, mousex1 + 25, mousey1 + 25);
            line(x, y, x + 25, y + 25);
            line(mousex1, mousey1, mousex1 + 25, mousey1 + 25);
            line(x, mousey1, x + 25, mousey1 + 25);
            line(mousex1, y, mousex1 + 25, y + 25);
        }
        else {
            setfillstyle(Current_Pattern, Current_Color);
            bar(x, y, mousex1, mousey1);
            bar(x + 25, y + 25, mousex1 + 25, mousey1 + 25);
            setcolor(BLACK);
            rectangle(x, y, mousex1, mousey1);
            rectangle(x + 25, y + 25, mousex1 + 25, mousey1 + 25);
            line(x, y, x + 25, y + 25);
            line(mousex1, mousey1, mousex1 + 25, mousey1 + 25);
            line(x, mousey1, x + 25, mousey1 + 25);
            line(mousex1, y, mousex1 + 25, y + 25);
            floodfill(mousex1 + 5, y + 10, BLACK);
            floodfill(x + 10, mousey1 + 5, BLACK);
            floodfill(mousex1 + 2, mousey1, BLACK);
        }
    }
    restrictmouse(0, 0, 640, 480);
}

void drawellipse()
{
    int x1, y1, x2, y2, color, xmid, ymid;
    float radx, rady;
    x1 = mousex;
    y1 = mousey;
    setwritemode(XOR_PUT);
    while (LeftButtonPressed) {
        disp_coord();
        x2 = mousex;
        y2 = mousey;
        xmid = (x1 + x2) / 2;
        ymid = (y1 + y2) / 2;
        radx = abs((x2 - x1) / 2);
        rady = abs((y2 - y1) / 2);
        if (radx < 1)
            radx = 1;
        if (rady < 1)
            rady = 1;
        color = 15 - Current_Color;
        setcolor(color);
        algoellipse(xmid, ymid, radx, rady);
        delay(20);
        getxy();
        algoellipse(xmid, ymid, radx, rady);
    }
    setwritemode(COPY_PUT);
    setcolor(Current_Color);
    x2 = mousex;
    y2 = mousey;
    xmid = (x1 + x2) / 2;
    ymid = (y1 + y2) / 2;
    radx = abs((x2 - x1) / 2);
    rady = abs((y2 - y1) / 2);
    if (Current_Pattern == EMPTY_FILL)
        algoellipse(xmid, ymid, radx, rady);
    else {
        setfillstyle(Current_Pattern, Current_Color);
        fillellipse(xmid, ymid, radx, rady);
    }
}

void algoellipse(int xcen, int ycen, float radx, float rady)
{
    float p, px, py, x, y, ry, rx, tworx, twory;
    ry = rady * rady;
    rx = radx * radx;
    twory = 2 * ry;
    tworx = 2 * rx;
    x = 0;
    y = rady;
    plotellipsepoints(xcen, ycen, x, y);
    p = (ry - rx * rady + (0.25 * rx));
    px = 0;
    py = tworx * y;
    while (px < py) {
        x++;
        px = px + twory;
        if (p >= 0) {
            y--;
            py = py - tworx;
        }
        if (p < 0)
            p = p + ry + px;
        else
            p = p + ry + px - py;
        plotellipsepoints(xcen, ycen, x, y);
    }
    p = (ry * (x + 0.5) * (x + 0.5) + rx * (y - 1) * (y - 1) - rx * ry);
    while (y > 0) {
        y--;
        py = py - tworx;
        if (p <= 0) {
            x++;
            px = px + twory;
        }
        if (p > 0)
            p = p + rx - py;
        else
            p = p + rx - py + px;
        plotellipsepoints(xcen, ycen, x, y);
    }
}

void plotellipsepoints(int xcen, int ycen, int x, int y)
{
    if (xcen + x >= MIN_X && xcen + x <= MAX_X && ycen + y >= MIN_Y && ycen + y <= MAX_Y)
        line(xcen + x, ycen + y, xcen + x, ycen + y);
    if (xcen - x >= MIN_X && xcen - x <= MAX_X && ycen + y >= MIN_Y && ycen + y <= MAX_Y)
        line(xcen - x, ycen + y, xcen - x, ycen + y);
    if (xcen + x >= MIN_X && xcen + x <= MAX_X && ycen - y >= MIN_Y && ycen - y <= MAX_Y)
        line(xcen + x, ycen - y, xcen + x, ycen - y);
    if (xcen - x >= MIN_X && xcen - x <= MAX_X && ycen - y >= MIN_Y && ycen - y <= MAX_Y)
        line(xcen - x, ycen - y, xcen - x, ycen - y);
}

/*
void algospiral(int xcen,int ycen,float radx,float rady)
{
 float rx=5,ry,ratio,ryold;
 int i;
 ratio=radx/rady;
 ryold=ry=rx/ratio;
 while(((xcen+rx)<=MAX_X) || ((ycen+ry)<=MAX_Y) || ((xcen-rx)>=MIN_X) || ((ycen-ry)>=MIN_Y))
 {
  ellipse( xcen, ycen, 90, 270, rx, ry );
  rx += 5;
  ry += rx/ratio;
  ycen -= ry-ryold;
  ryold=ry;
  ellipse( xcen, ycen, 270, 90, rx, ry );
  rx += 5;
  ry += rx/ratio;
  ycen += ry-ryold;
  ryold=ry;
 }
}
*/

void algospiral(int xcen, int ycen, float radx, float rady)
{
    float rx = 5, ry = 5;
    /* while(rx<=(MAX_X-xcen) || ry<=(MAX_Y-ycen) || rx<=(xcen-MIN_X) || ry<=(ycen-MIN_Y)) */
    while (rxMAX_X)
        radx = MAX_X - xmid;
    if ((xmid - radx) < min_X)
        radx = xmid - MIN_X;
    if ((ymid + rady) > MAX_Y)
        rady = MAX_Y - ymid;
    if ((ymid - rady) < min_Y)
        rady = ymid - MIN_Y;
    rectangle(xmid - radx, ymid - rady, xmid + radx, ymid + rady);
    getxy();
    if ((xmid + radx) > MAX_X)
        radx = MAX_X - xmid;
    if ((xmid - radx) < min_X)
        radx = xmid - MIN_X;
    if ((ymid + rady) > MAX_Y)
        rady = MAX_Y - ymid;
    if ((ymid - rady) < min_Y)
        rady = ymid - MIN_Y;
    rectangle(xmid - radx, ymid - rady, xmid + radx, ymid + rady);
}
setwritemode(COPY_PUT);
setcolor(Current_Color);
x2 = mousex;
y2 = mousey;
xmid = (x1 + x2) / 2;
ymid = (y1 + y2) / 2;
radx = abs((x2 - x1) / 2);
rady = abs((y2 - y1) / 2);
if ((xmid + radx) > MAX_X)
    radx = MAX_X - xmid;
if ((xmid - radx) < min_X)
    radx = xmid - MIN_X;
if ((ymid + rady) > MAX_Y)
    rady = MAX_Y - ymid;
if ((ymid - rady) < min_Y)
    rady = ymid - MIN_Y;
algospiral(xmid, ymid, radx, rady);
}
* /

    /* Problem Corrected in Algo below. Using Circle Drawing concept */
    void drawspiral()
{
    int x1, y1, x2, y2, color, xmid, ymid;
    float radx;
    x1 = mousex;
    y1 = mousey;
    setwritemode(XOR_PUT);
    while (LeftButtonPressed) {
        disp_coord();
        x2 = mousex;
        y2 = mousey;
        xmid = (x1 + x2) / 2;
        ymid = (y1 + y2) / 2;
        radx = abs((x2 - x1) / 2);
        if (radx < 1)
            radx = 1;
        color = 15 - Current_Color;
        setcolor(color);
        if ((xmid + radx) > (MAX_X - 2))
            radx = (MAX_X - 2) - xmid;
        if ((xmid - radx) < (MIN_X + 2))
            radx = xmid - (MIN_X + 2);
        if ((ymid + radx) > (MAX_Y - 2))
            radx = (MAX_Y - 2) - ymid;
        if ((ymid - radx) < (MIN_Y + 8))
            radx = ymid - (MIN_Y + 8);
        algoellipse(xmid, ymid, radx, radx); /* circle(xmid,ymid,radx); */
        delay(20);
        getxy();
        if ((xmid + radx) > (MAX_X - 2))
            radx = (MAX_X - 2) - xmid;
        if ((xmid - radx) < (MIN_X + 2))
            radx = xmid - (MIN_X + 2);
        if ((ymid + radx) > (MAX_Y - 2))
            radx = (MAX_Y - 2) - ymid;
        if ((ymid - radx) < (MIN_Y + 8))
            radx = ymid - (MIN_Y + 8);
        algoellipse(xmid, ymid, radx, radx);
    }
    setwritemode(COPY_PUT);
    setcolor(Current_Color);
    x2 = mousex;
    y2 = mousey;
    xmid = (x1 + x2) / 2;
    ymid = (y1 + y2) / 2;
    radx = abs((x2 - x1) / 2);
    if ((xmid + radx) > (MAX_X - 2))
        radx = (MAX_X - 2) - xmid;
    if ((xmid - radx) < (MIN_X + 2))
        radx = xmid - (MIN_X + 2);
    if ((ymid + radx) > (MAX_Y - 2))
        radx = (MAX_Y - 2) - ymid;
    if ((ymid - radx) < (MIN_Y + 8))
        radx = ymid - (MIN_Y + 8);
    /*circle(xmid,ymid,radx);*/
    algospiral(xmid, ymid, radx, radx);
}

void drawcircle()
{
    int x1, y1, x2, y2, color, xmid, ymid;
    float radx;
    x1 = mousex;
    y1 = mousey;
    setwritemode(XOR_PUT);
    while (LeftButtonPressed) {
        disp_coord();
        x2 = mousex;
        y2 = mousey;
        xmid = (x1 + x2) / 2;
        ymid = (y1 + y2) / 2;
        radx = abs((x2 - x1) / 2);
        if (radx < 1)
            radx = 1;
        color = 15 - Current_Color;
        setcolor(color);
        if ((xmid + radx) > (MAX_X - 2))
            radx = (MAX_X - 2) - xmid;
        if ((xmid - radx) < (MIN_X + 2))
            radx = xmid - (MIN_X + 2);
        if ((ymid + radx) > (MAX_Y - 2))
            radx = (MAX_Y - 2) - ymid;
        if ((ymid - radx) < (MIN_Y + 2))
            radx = ymid - (MIN_Y + 2);
        algoellipse(xmid, ymid, radx, radx); /* circle(xmid,ymid,radx); */
        delay(20);
        getxy();
        if ((xmid + radx) > (MAX_X - 2))
            radx = (MAX_X - 2) - xmid;
        if ((xmid - radx) < (MIN_X + 2))
            radx = xmid - (MIN_X + 2);
        if ((ymid + radx) > (MAX_Y - 2))
            radx = (MAX_Y - 2) - ymid;
        if ((ymid - radx) < (MIN_Y + 2))
            radx = ymid - (MIN_Y + 2);
        algoellipse(xmid, ymid, radx, radx); /* circle(xmid,ymid,radx); */
    }
    setwritemode(COPY_PUT);
    setcolor(Current_Color);
    x2 = mousex;
    y2 = mousey;
    xmid = (x1 + x2) / 2;
    ymid = (y1 + y2) / 2;
    radx = abs((x2 - x1) / 2);
    if (Current_Pattern == EMPTY_FILL) {
        if ((xmid + radx) > (MAX_X - 2))
            radx = (MAX_X - 2) - xmid;
        if ((xmid - radx) < (MIN_X + 2))
            radx = xmid - (MIN_X + 2);
        if ((ymid + radx) > (MAX_Y - 2))
            radx = (MAX_Y - 2) - ymid;
        if ((ymid - radx) < (MIN_Y + 2))
            radx = ymid - (MIN_Y + 2); /*circle(xmid,ymid,radx);*/
        algoellipse(xmid, ymid, radx, radx);
    }
    else {
        setfillstyle(Current_Pattern, Current_Color);
        if ((xmid + radx) > (MAX_X - 2))
            radx = (MAX_X - 2) - xmid;
        if ((xmid - radx) < (MIN_X + 2))
            radx = xmid - (MIN_X + 2);
        if ((ymid + radx) > (MAX_Y - 2))
            radx = (MAX_Y - 2) - ymid;
        if ((ymid - radx) < (MIN_Y + 2))
            radx = ymid - (MIN_Y + 2);
        fillellipse(xmid, ymid, radx, radx);
    }
}

void save()
{
    char* name;
    FILE* out;
    char ch;
    int row, col;
    int byte;

    if (strcmp(FileName, "Untitled") == 0) {
        name = readline("Save File As  : ");
        if (name == NULL)
            return;
    }
    else {
        name = malloc(strlen(FileName) + 1);
        strcpy(name, FileName);
    }

    out = fopen(name, "w");
    if (out == NULL) {
        ShowStatus(" Error Opening File !");
        delay(1000);
        ClearStatus();
        return;
    }

    ShowStatus(" Saving File (Please Wait) ");

    for (row = MIN_Y + 2; row <= MAX_Y - 2; ++row) {
        for (col = MIN_X + 2; col <= MAX_X - 2;) {
            byte = getpixel(col, row);
            byte = byte << 4;
            col++;
            byte += getpixel(col, row);
            col++;
            if (fputc(byte, out) == EOF) {
                ShowStatus("Error Writing FIle ! ");
                delay(1000);
                ClearStatus();
                free(name);
                fclose(out);
            }
        }
    }
    ClearStatus();
    strcpy(FileName, name);
    disp_filename();
    free(name);
    fclose(out);
    saved = 1;
}
char* readline(char* msg)
{
    char* Line;
    char temp[40];
    char Disp_Line[60];
    char ch;
    int i = 0, length = 0;
    int max = ((475 - 12) - strlen(msg) * 8) / 8; /*/ find maximum number of characters*/
    ClearStatus();
    setcolor(BLACK);
    outtextxy(12, 464, msg);
    strcpy(Disp_Line, msg);
    ch = getch();
    while ((ch != 27) && (ch != 13)) {
        switch (ch) {
        case 'b':
            if (i == 0)
                beep();
            else {
                i--;
                ClearStatus();
                length = strlen(Disp_Line);
                Disp_Line[length - 1] = '�';
                setcolor(BLACK);
                outtextxy(12, 464, Disp_Line);
            }
            break;
        default:
            if (i > max)
                beep();
            else {
                length = strlen(Disp_Line);
                Disp_Line[length] = ch;
                Disp_Line[length + 1] = '�';
                outtextxy(12, 464, Disp_Line);
                temp[i++] = ch;
            }
            break;
        }
        ch = getch();
    }

    temp[i] = '�';
    ClearStatus();
    if (ch == 27)
        return NULL;
    else {
        Line = malloc(strlen(temp) + 1);
        strcpy(Line, temp);
    }
    return Line;
}

void Load()
{
    FILE* in;
    char* name;
    char ch;
    int byte;
    int row, col;
    int temp;

    if (!saved) {
        ShowStatus(" Save Current File ? ");
        ch = getch();
        if (ch == 'y' || ch == 'Y') {
            save();
        }
    }

    name = readline(" Enter File To Load : ");
    if (name == NULL)
        return;

    in = fopen(name, "r");
    if (fopen == NULL) {
        ShowStatus(" Error Opening File ");
        delay(1000);
        ClearStatus();
        return;
    }

    byte = fgetc(in);
    /*if(byte==EOF)
 {
  ShowStatus(" Error Reading ");
  delay(1000);
  ClearStatus();
  free(name);
  fclose(in);
  return;
 }*/

    for (row = MIN_Y + 2; row <= MAX_Y - 2; row++) {
        for (col = MIN_X + 2; col <= MAX_X - 2;) {
            temp = (byte & 0xf0) >> 4;
            putpixel(col, row, temp);
            col++;
            temp = (byte & 0x0f);
            putpixel(col, row, temp);
            col++;
            byte = fgetc(in);
            if (byte == EOF) {
                /*ShowStatus(" Error Reading ");
    delay(1000);
    ClearStatus();
    free(name);
    fclose(in);*/
                return;
            }
        }
    }
    strcpy(FileName, name);
    disp_filename();
    free(name);
    fclose(in);
    saved = 1;
}

void mirror()
{
    int row;
    int x1, x2;
    int color1, color2;

    for (row = MIN_Y + 2; row <= MAX_Y - 2; ++row) {
        x1 = MIN_X + 2;
        x2 = MAX_X - 2;
        while (x1 < x2) {
            color1 = getpixel(x1, row);
            color2 = getpixel(x2, row);
            putpixel(x2, row, color1);
            putpixel(x1, row, color2);
            x1++;
            x2--;
        }
    }
}

void flip()
{
    int col;
    int y1, y2;
    int color1, color2;

    for (col = MIN_X + 2; col <= MAX_X - 2; ++col) {
        y1 = MIN_Y + 2;
        y2 = MAX_Y - 2;
        while (y1 < y2) {
            color1 = getpixel(col, y1);
            color2 = getpixel(col, y2);
            putpixel(col, y2, color1);
            putpixel(col, y1, color2);
            y1++;
            y2--;
        }
    }
}

void mark()
{
    int color = 15 - BLACK;
    int x, y;

    if (marked)
        unmark();

    setcolor(color);
    setwritemode(XOR_PUT);

    x = mousex;
    y = mousey;

    setlinestyle(DOTTED_LINE, 1, 1);
    while (LeftButtonPressed) {
        disp_coord();
        rectangle(x, y, mousex, mousey);
        getxy();
        rectangle(x, y, mousex, mousey);
    }
    setlinestyle(SOLID_LINE, 1, 1);

    if (x < mousex) {
        marker.left = x;
        marker.right = mousex;
        if (y < mousey) {
            marker.top = y;
            marker.bottom = mousey;
        }
        else {
            marker.top = mousey;
            marker.bottom = y;
        }
    }
    else {
        marker.left = mousex;
        marker.right = x;
        if (y < mousey) {
            marker.top = y;
            marker.bottom = mousey;
        }
        else {
            marker.top = mousey;
            marker.bottom = y;
        }
    }
    marked = 1;
    setwritemode(COPY_PUT);
}

void unmark()
{
    int color = 15 - BLACK;
    setcolor(color);
    setwritemode(XOR_PUT);
    setlinestyle(DOTTED_LINE, 1, 1);
    rectangle(marker.left, marker.top, marker.right, marker.bottom);
    setlinestyle(SOLID_LINE, 1, 1);
    setwritemode(COPY_PUT);
    marked = 0;
}

void delete ()
{
    if (marked) {
        unmark();
        setfillstyle(SOLID_FILL, WHITE);
        bar(marker.left, marker.top, marker.right, marker.bottom);
    }
}

void translate()
{
    int left, right, bottom, top;
    int diffx, diffy;
    int color = 15 - BLACK;
    char* image;
    int size;

    if (!marked)
        return;
    if (check_mouse_on(marker.left, marker.top, marker.right, marker.bottom)) {
        setwritemode(XOR_PUT);
        setcolor(color);
        setlinestyle(DOTTED_LINE, 1, 1);

        left = marker.left;
        right = marker.right;
        top = marker.top;
        bottom = marker.bottom;

        while (LeftButtonPressed) {
            rectangle(left, top, right, bottom);
            getxy();
            diffx = prevx - mousex;
            diffy = prevy - mousey;
            left = left - diffx;
            right = right - diffx;
            bottom = bottom - diffy;
            top = top - diffy;
            if ((left < min_X + 2) || (right > MAX_X - 2) || (top < min_Y + 2) || (bottom > MAX_Y - 2)) {
                left = left + diffx;
                right = right + diffx;
                bottom = bottom + diffy;
                top = top + diffy;
            }
            rectangle(left, top, right, bottom);
        }

        marked = 0;
        setwritemode(COPY_PUT);
        size = imagesize(marker.left, marker.top, marker.right, marker.bottom);
        if (size != -1) {
            image = malloc(size);
            if (image != NULL) {
                getimage(marker.left, marker.top, marker.right, marker.bottom, image);
                setfillstyle(SOLID_FILL, WHITE);
                bar(marker.left, marker.top, marker.right, marker.bottom);
                putimage(left, top, image, COPY_PUT);
                free(image);
            }
            else {
                ShowStatus(" No Memory! ");
                delay(1000);
                ClearStatus();
            }
        }
        else {
            ShowStatus(" No Memory! ");
            delay(1000);
            ClearStatus();
        }
        setlinestyle(SOLID_LINE, 1, 1);
    }
}

void rotate()
{
    char* charangle;
    int angle;
    float rad;
    int x, y;
    int xf = marker.left; /*/(marker.left-marker.right)/2+marker.left;*/
    int yf = marker.bottom; /*/(marker.bottom-marker.top)/2+marker.top;  */
    int row, col;
    int pixel;
    FILE* temp; /* added code*/

    if (!marked)
        return;

    charangle = readline(" Enter The Angle Of Rotation (?90,?180,?270) : ");
    if (charangle == NULL)
        return;
    angle = atoi(charangle);
    /* if(abs(angle)!=90&&abs(angle)!=180&&abs(angle)!=270)
 {
  ShowStatus(" Invalid Angle! ");
  delay(1000);
  ClearStatus();
  return;
 }
*/
    /*added code begins*/
    temp = fopen("work", "w");
    if (temp == NULL) {
        ShowStatus("Cannot Proceed!");
        delay(1000);
        ClearStatus();
        return;
    }

    for (row = marker.top + 1; row < marker.bottom; ++row) {
        for (col = marker.left + 1; col < marker.right; ++col) {
            pixel = getpixel(col, row);
            fputc(pixel, temp);
        }
    }
    fclose(temp);

    temp = fopen("work", "r");
    if (temp == NULL) {
        ShowStatus(" Cannot Proceed ! ");
        delay(1000);
        ClearStatus();
        return;
    }
    /*  added code ends */
    rad = angle * M_PI / 180.0;

    unmark();
    setwritemode(COPY_PUT);
    for (row = marker.top; row <= marker.bottom; ++row)
        for (col = marker.left; col <= marker.right; ++col)
            putpixel(col, row, WHITE);
    for (row = marker.top + 1; row < marker.bottom; ++row) {
        for (col = marker.left + 1; col < marker.right; ++col) { /* pixel=getpixel(col,row); */
            pixel = fgetc(temp);
            x = ceil((1 - cos(rad)) * (xf) + sin(rad) * (yf) + col * cos(rad) - row * sin(rad));
            y = ceil((1 - cos(rad)) * (yf)-sin(rad) * (xf) + col * sin(rad) + row * cos(rad)); /*x=(col-xf)*cos(rad)+(yf-row)*sin(rad)+xf;*/ /*y=(col-xf)*sin(rad)+(row-yf)*cos(rad)+yf;*/
            if (x >= MIN_X + 2 && x <= MAX_X - 2 && y >= MIN_Y + 2 && y <= MAX_Y - 2) {
                putpixel(x, y, pixel);
                putpixel(x + 1, y, pixel);
                putpixel(x, y + 1, pixel);
                putpixel(x, y - 1, pixel);
                putpixel(x - 1, y, pixel);
            }
        }
    }
}

void scale()
{
    int left, right, bottom, top;
    float x, y;
    float Sx, Sy;
    float i, j;
    int row, col;
    int pixel;
    int check_scale_done = 0;
    FILE* temp;

    if (!marked)
        return;

    while (1) {
        if (RightButtonPressed)
            return;
        else {
            showmouse();
            if (!check_mouse_on(marker.left, marker.top, marker.right, marker.bottom)) {
                startmouse(marker.right, marker.bottom);
                setcolor(15 - BLACK);
                setlinestyle(DOTTED_LINE, 1, 1);
                setwritemode(XOR_PUT);
            }
            left = marker.left;
            right = marker.right;
            top = marker.top;
            bottom = marker.bottom;
            restrictmouse(left, top, MAX_X - 2, MAX_Y - 2);
            delay(1000);
            while (LeftButtonPressed)
            /*  while(buttclicked()==1)  */
            {
                rectangle(left, top, right, bottom);
                getxy();
                right = mousex;
                bottom = mousey;
                rectangle(left, top, right, bottom);
                disp_coord();
            }
            rectangle(left, top, right, bottom);

            marked = 0;
            setlinestyle(SOLID_LINE, 1, 1);
            setwritemode(COPY_PUT);

            Sx = ((float)(right - left)) / (marker.right - marker.left);
            Sy = ((float)(bottom - top)) / (marker.bottom - marker.top);

            temp = fopen("work", "w");
            if (temp == NULL) {
                ShowStatus("Cannot Proceed!");
                delay(1000);
                ClearStatus();
                return;
            }

            for (row = marker.top; row <= marker.bottom; ++row) {
                for (col = marker.left; col <= marker.right; ++col) {
                    pixel = getpixel(col, row);
                    fputc(pixel, temp);
                }
            }
            fclose(temp);

            temp = fopen("work", "r");
            if (temp == NULL) {
                ShowStatus(" Cannot Proceed ! ");
                delay(1000);
                ClearStatus();
                return;
            }

            for (y = top; y <= bottom; y += Sy) {
                for (x = left; x <= right; x += Sx) {
                    pixel = fgetc(temp);
                    for (j = 0; j <= Sy; j++) {
                        for (i = 0; i <= Sx; i++) {
                            putpixel((int)(ceil(x + i)), (int)(ceil(y + j)), pixel);
                        }
                    }
                }
            }

            /*
  for(row=marker.top;row<=marker.bottom;++row)
  {
   for(col=marker.left;col<=marker.right;++col)
   {
    pixel=fgetc(temp);
    putpixel((int)(ceil(col+50)),(int)(ceil(row+50)),pixel);
   }
  }
  */

            check_scale_done = 1;
        } /* end of else*/
        if (check_scale_done == 1) {
            check_scale_done = 0;
            break;
        }
    }
    fclose(temp);
    restrictmouse(0, 0, 640, 480);
}

void clip()
{
    int i, j;
    if (!marked)
        return;

    unmark();
    for (j = MIN_Y + 2; j <= MAX_Y - 2; ++j) {
        for (i = MIN_X + 2; i <= MAX_X - 2; ++i) {
            if ((i >= marker.left && i <= marker.right) && (j >= marker.top && j <= marker.bottom)) {
            }
            else
                putpixel(i, j, WHITE);
        }
    }
}
int over(int x, int y, int w, int h)
{
    int x1, y1;
    x1 = x + w;
    y1 = y + h;
    wheremouse(&mousex, &mousey);
    if ((mousex > x) && (mousex < x1) && (mousey > y) && (mousey < y1))
        return 1;
    else
        return 0;
}

void sphere()
{
    int i, r;
    int px, py;
    int ex, ey;

    setcolor(Current_Color);

    if (over(40, 50, MAX_X - 60, MAX_Y - 65) == 0)
        return;
    {

        wheremouse(&mousex, &mousey);
        px = mousex;
        py = mousey;
        setwritemode(XOR_PUT);
        if (over(40, 50, MAX_X - 60, MAX_Y - 65) == 0)
            return;

        if (buttclicked() == 1)
            while (1) {

                hidemouse();
                line(px, py, px, mousey); /*    pxpy      mxpy */
                line(px, py, mousex, py); /*    pxmy      mxmy */
                line(mousex, mousey, px, mousey);
                line(mousex, mousey, mousex, py);
                showmouse();

                if (buttclicked() != 1)
                    break;
                wheremouse(&mousex, &mousey);
                if (over(40, 50, MAX_X - 60, MAX_Y - 65) == 0)
                    while (over(40, 50, MAX_X - 60, MAX_Y - 65) == 0)
                        ;
                if (buttclicked() != 1)
                    break;

                hidemouse();
                line(px, py, px, mousey);
                line(px, py, mousex, py);
                line(mousex, mousey, px, mousey);
                line(mousex, mousey, mousex, py);
                showmouse();
            }
        hidemouse();
        setcolor(WHITE);

        setwritemode(COPY_PUT);
        setcolor(Current_Color);
        ex = (px + mousex) / 2;
        ey = (py + mousey) / 2;
        ellipse(ex, ey, 0, 360, abs((px - mousex) / 2), abs((py - mousey) / 2));
        r = abs((py - mousey) / 2);
        for (i = 4; i <= r; i += 5) {
            ellipse(ex, ey, 0, 360, abs((px - mousex) / 2), i);
        }
        r = abs((px - mousex) / 2);
        for (i = 4; i <= r; i += 5) {
            ellipse(ex, ey, 0, 360, i, abs((py - mousey) / 2));
        }

        showmouse();
    }
}
