#include "TXLib.h"


struct Mario
{
 int x;
 int y;
 int vy;
 HDC picture ;
 HDC right ;
 HDC left ;
 int floor;
};

struct Block
{
int x;
int y;
int w;
};

void drawblock(Block block)
{
    txSetColor(TX_ORANGE);
    txSetFillColor(TX_ORANGE);

    txRectangle(block.x,block.y,block.x+block.w,block.y+10);
}


int main()
    {
    txCreateWindow (1800, 900);
    txSetFillColor(TX_BLACK);
    txRectangle(0,0,1800,900);
    HDC marios = txLoadImage ("��������/�����/runMarioRight.bmp");
    HDC marioright = marios;
    HDC marioleft = txLoadImage ("��������/�����/runMarioLeft.bmp");
    Mario mario{350,750,0,marios,marioright,marioleft, 750};

    int Kolblock = 3;
    Block block[100];
    block[0] = {450, 550, 100};
    block[1] = {650, 550, 100};
    block[2] = {850, 400, 100};

    char strmario[100];

while(!GetAsyncKeyState(VK_ESCAPE))
{
    txClear();

    for(int i=0; i<Kolblock; i++)
    {
    drawblock(block[i]);
    }

    txSetFillColor(TX_BLACK);
    txTransparentBlt (txDC(), mario.x,mario.y,92,100,mario.picture,0,0, TX_WHITE);

    if(GetAsyncKeyState('D'))
    {
        mario.x=mario.x+10;
        mario.picture=mario.right;
    }


    if(GetAsyncKeyState('A'))
    {
        mario.x=mario.x-10;
        mario.picture=mario.left;
    }

    if(GetAsyncKeyState(VK_SPACE))
    {
        while(GetAsyncKeyState (VK_SPACE))
        txSleep(1);
        mario.vy=-30;
    }


    mario.y=mario.y+mario.vy;
    mario.vy=mario.vy+3;

    sprintf(strmario, "v mario = %d", mario.vy);
    txTextOut(50, 50, strmario);


    if(mario.y>mario.floor)
        mario.y=mario.floor;

    for(int x=mario.x; x<mario.x+92; x=x+5)
    {
        for(int y=mario.y; y<mario.y+100; y=y+5)
        {
            if(txGetPixel(x, y) == TX_ORANGE)
                mario.y = block[0].y+10;
        }
    }

    if((mario.x>block[0].x-block[0].w && mario.x<block[0].x+block[0].w) && mario.y<block[0].y)
        mario.floor = block[0].y-100;
    if((mario.x>block[1].x-block[1].w && mario.x<block[1].x+block[1].w) && mario.y<block[1].y)
        mario.floor = block[1].y-100;
    if((mario.x>block[2].x-block[2].w && mario.x<block[2].x+block[2].w) && mario.y<block[2].y)
        mario.floor = block[2].y-100;







    if(!(mario.x>block[0].x-block[0].w && mario.x<block[0].x+block[0].w) &&
       !(mario.x>block[1].x-block[1].w && mario.x<block[1].x+block[1].w) &&
       !(mario.x>block[2].x-block[2].w && mario.x<block[2].x+block[2].w))
        mario.floor = 750;




txSleep(10);
}


txDeleteDC(marioright);
txDeleteDC(marioleft);


    return 0;
    }
