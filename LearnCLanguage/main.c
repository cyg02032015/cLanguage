//
//  main.c
//  LearnCLanguage
//
//  Created by Youngkook on 16/8/12.
//  Copyright © 2016年 youngkook. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <curses.h>
#include <ncurses.h>
#include <time.h>
#include <termios.h>
#include <string.h>

int cc_getch(void);
int getche(void);

int cc_getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void timeTicToc(); // C语言函数需要先声明才能调用
/*
 1
 22
 333
 4444
 55555
 
 1
 23
 456
 78910
 101112131415
 */
void printfNum();
void printfSpaceH();

void printfSpaceH() {
    for (int i = 0; i < 10; i++) {
        system("clear");
        fflush(stdout);
        sleep(1);
        for (int j = 0; j < i; j++) {
            printf(" ");
        }
        printf("H");
    }
}

void forloopCount();
void forloopCount() {
    int i,j, sum = 0;
    i = 1;
    while (i<=11) {
        j=1;
        while (j<=i) {
            sum = sum + 1;
            printf("OK%d\n",sum);
            j++;
        }
        i++;
    }
}

void printfNum() {
    for (int row = 1; row <= 5; row++) {
        for (int col = 1; col <= row; col++) {
            printf("%d", row);
        }
        printf("\n");
    }
    
    printf("\n\n");
    int sum = 0;
    for (int row = 1; row <= 5; row++) {
        for (int col = 0; col < row; col++) {
            sum = sum + 1;
            printf("%d", sum);
        }
        printf("\n");
    }
}

void timeTicToc() {
    int s = 0, m = 0, h = 0, t; // a is seconds;
    
    while (t >= 0) {
        system("clear");
        if (t >= 3600) {
            h = t / 3600;
            m = (t - h * 3600) / 60;
            s = t - h * 3600 - m * 60;
            printf("%d:%d:%d\n", h, m, s);
        } else if (t >= 60) {
            m = t / 60;
            s = t - m * 60;
            printf("00:%d:%d\n", m, s);
        } else {
            s = t;
            if (s > 9) {
                printf("00:00:%d\n", s);
            } else {
                printf("00:00:0%d\n", s);
            }
        }
        fflush(stdout);
        sleep(1);
        t--;
    }
}

void lengxing();
void lengxing(int line, int mid) {
    for (int i = 0; i<line; i++) {
        if (i<mid) {
            for (int j = line/2; j>i; j--) {
                printf(" ");
            }
            for (int xing = 0; xing<=i; xing++) {
                printf("*");
            }
            for (int xing = 1; xing<=i; xing++) {
                printf("*");
            }
        } else { // i > 5
            for (int j = mid; j<=i; j++) {
                printf(" ");
            }
            for (int xing = line; xing>i; xing--) {
                printf("*");
            }
            for (int xing = line - 1; xing>i; xing--) {
                printf("*");
            }
        }
        printf("\n");
    }
}

void test();
void test() {
    srand((unsigned)time(NULL));
    int a = rand()%10000000, b;
    printf("%d", a);
    scanf("%d", &b);
    while (1) {
        if (b==a) {
            printf("正确");
            break;
        } else if (b > a) {
            printf("数字大了");
            scanf("%d", &b);
        } else {
            printf("数字小了");
            scanf("%d", &b);
        }
    }
}

/**
 *  选择排序
 */
void selectSort();
void selectSort() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i<n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = i + 1; j<n; j++) {
            if (a[i] < a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
    for (int i = 0; i<n; i++) {
        printf("---%d\n", a[i]);
    }
}

/**
 *  走迷宫
 */
void migong();
void migong() {
    char a[50][50] = {
        "######",
        "#o #  ",
        "# ## #",
        "#  # #",
        "##   #",
        "######"
    };
    char ch;
    // p,q表示出口
    // x,y表示人
    int i,x=1,y=1,p=1,q=5;
    for (i = 0; i <= 5; i++) {
        puts(a[i]);
    }
    while (x != p || y != q) {
        ch = cc_getch();
        if (ch == 's') { // 向下走
            if (a[x+1][y] != '#') {
                a[x][y] = ' ';
                x++;
                a[x][y] = 'o';
            }
        }
        
        if (ch == 'w') { // 向上走
            if (a[x-1][y] != '#') {
                a[x][y] = ' ';
                x--;
                a[x][y] = 'o';
            }
        }
        
        if (ch == 'a') {
            if (a[x][y-1] != '#') {
                a[x][y] = ' ';
                y--;
                a[x][y] = 'o';
            }
        }
        
        if (ch == 'd') {
            if (a[x][y+1] != '#') {
                a[x][y] = ' ';
                y++;
                a[x][y] = 'o';
            }
        }
        system("clear");
        for (int i=0; i<=5; i++) {
            puts(a[i]);
        }
    }
    printf("恭喜成功");
}

int main(int argc, const char * argv[]) {
    migong();
    return 0;
}