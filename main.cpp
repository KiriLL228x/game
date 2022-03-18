#include "TXLib.h"
struct Key
{
int x;
int y;
HDC picture;
bool visible;
};
struct Spikes
{
int x;
int y;
HDC picture;

};
struct Moneta
{
int x;
int y;
HDC picture;
bool visible;
};

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

void drawKey(Key key)
{
if(key.visible)
    {
        txTransparentBlt (txDC(), key.x, key.y, 25, 25, key.picture, 0, 0, TX_WHITE);
    }
}

void drawSpikes(Spikes spikes)
{
    txTransparentBlt (txDC(), spikes.x, spikes.y, 100, 100, spikes.picture, 0, 0, TX_WHITE);
}

void drawMoneta(Moneta moneta)
{


if(moneta.visible)
    {
        txTransparentBlt (txDC(), moneta.x,moneta.y,31,29,moneta.picture,0,0,TX_WHITE);
    }
}


int main()
    {
    txCreateWindow (1800, 900);
    txSetFillColor(TX_BLACK);
    txRectangle(0,0,1800,900);
    HDC marios = txLoadImage ("��������/�����/runMarioRight.bmp");
    HDC marioright = marios;
    HDC marioleft = txLoadImage ("��������/�����/runMarioLeft.bmp");

    Mario mario = {350,750,0,marios,marioright,marioleft, 750};

    int kolm=0;

    int Kolblock = 3;
    Block block[100];
    block[0] = {450, 550, 200};
    block[1] = {650, 550, 100};
    block[2] = {850, 400, 100};
    char strmario[100];

    int Kolmoneta = 3;
    Moneta moneta[100];
    moneta[0] = {450, 750, txLoadImage ("��������/��������/moneta.bmp"), true};

    int kolkey = 1;
    Key key[100];
    key[0] = {650, 750, txLoadImage ("��������/��������/key.bmp"), true};

    int kolspikes = 3;
    Spikes spikes[100];
    spikes[0] = {450,450, txLoadImage ("��������/��������/Spikes.bmp")};
    spikes[1] = {1150,750, txLoadImage ("��������/��������/Spikes.bmp")};
    spikes[2] = {1350,750, txLoadImage ("��������/��������/Spikes.bmp")};

while(!GetAsyncKeyState(VK_ESCAPE))
{
    txClear();

    for(int i=0; i<Kolblock; i++)
    {
    drawblock(block[i]);
    }

    for(int i=0; i<Kolmoneta; i++)
    {
    drawMoneta(moneta[i]);
    }

    for(int i=0; i<kolkey; i++)
    {
    drawKey(key[i]);
    }

    for(int i=0; i<kolspikes; i++)
    {
    drawSpikes(spikes[i]);
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
        txSleep(50);
        mario.vy=-30;
    }


    mario.y=mario.y+mario.vy;
    mario.vy=mario.vy+3;

    sprintf(strmario, "����� = %d", kolm);
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


//������� �����
    for(int i=0; i<Kolmoneta; i++)
    {
        if(mario.x==moneta[i].x && mario.y==moneta[i].y && moneta[i].visible)
        {
            moneta[i].visible = false;
            kolm=kolm+1;
        }
    }

//�����
    for(int i=0; i<kolkey; i++)
    {
        if(mario.x==key[i].x && mario.y==key[i].y && key[i].visible)
        {
            key[i].visible = false;
        }
    }

//�������� �����
for(int i=0; i<kolspikes; i++)
    {
        if(mario.x==spikes[i].x && mario.y==spikes[i].y)
        {
        txTextOut(900, 450,"GAME OVER");
        }
    }

txSleep(15);
txEnd();
}


txDeleteDC(marioright);
txDeleteDC(marioleft);


    return 0;
    }

