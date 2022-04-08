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
 HDC picture;
 int floor;
};

void drawMario(Mario mario)
{
    txTransparentBlt (txDC(), mario.x, mario.y, 92, 100, mario.picture, 0, 0, TX_WHITE);
}

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
        txTransparentBlt (txDC(), key.x, key.y, 43, 21, key.picture, 0, 0, TX_WHITE);
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
        txTransparentBlt (txDC(), moneta.x,moneta.y,31,30,moneta.picture,0,0,TX_WHITE);
    }
}


int main()
{
    txCreateWindow (1800, 900);

    txDisableAutoPause();

    HDC marioright = txLoadImage ("картинки/марио/runMarioRight.bmp");
    HDC marioleft = txLoadImage ("картинки/марио/runMarioLeft.bmp");

    HDC menufon = txLoadImage ("картинки/фон/menu.bmp");

    HDC gamefon1 = txLoadImage ("картинки/фон/game1.bmp");



    Mario mario = {350, 750, 0, marioright, 750};

    char strmario[100];

    string PAGE = "Меню";

    int level=1;
    int kolm=0;
    int spak=0;
    int kolk=0;

    int Kolblock = 3;
    Block block[100];
    block[0] = {450, 550, 200};
    block[1] = {650, 550, 100};
    block[2] = {850, 400, 100};


    int Kolmoneta = 3;
    Moneta moneta[100];
    moneta[0] = {450, 750, txLoadImage ("картинки/предметы/moneta.bmp"), true};

    int kolkey = 1;
    Key key[100];
    key[0] = {650, 750, txLoadImage ("картинки/предметы/key.bmp"), true};

    int kolspikes = 3;
    Spikes spikes[100];
    spikes[0] = {450,450, txLoadImage ("картинки/предметы/Spikes.bmp")};
    spikes[1] = {1150,750, spikes[0].picture};
    spikes[2] = {1350,750, spikes[0].picture};

    int ExitX = 800, ExitY = 700;



while(true)
{
    txClear();




    if(PAGE=="Меню")
    {

        txSetColor(TX_WHITE,3);
        txSetFillColor(TX_BLACK);
    txBitBlt(txDC(), 0, 0, 1800, 900, menufon);
        //кнопка для старта
        txRectangle(500,100,700,150);
        txDrawText(500,100,700,150, "START");
        //нажатие на кнопку старт
        if(txMouseX() >= 500 && txMouseY()>=100 &&
           txMouseX() <= 700 && txMouseY()<=150 &&
            txMouseButtons() == 1)
        {
            PAGE="Игра";
        }

        //кнопка ПОМОЩЬ
        txRectangle(500,200,700,250);
        txDrawText(500,200,700,250, "HELP");
        //нажатие на кнопку старт
        if(txMouseX() >= 500 && txMouseY()>=200 &&
        txMouseX() <= 700 && txMouseY()<=250 &&
        txMouseButtons() == 1)
        {
            PAGE="help";
        }

        //кнопка Exit
        txRectangle(500,500,700,550);
        txDrawText(500,500,700,550, "EXIT");
        //нажатие на кнопку выхода
        if(txMouseX() >= 500 && txMouseY()>=500 &&
        txMouseX() <= 700 && txMouseY()<=550 &&
        txMouseButtons() == 1)
        {
            return 0;
        }

    }

    if(PAGE=="help")
    {
        txSetColor(TX_WHITE,3);
        txSetFillColor(TX_BLACK);

        txRectangle(100,200,300,250);
        txDrawText(100,200,300,250, "BACK");
        //нажатие на кнопку старт
        if(txMouseX() >= 100 && txMouseY()>=200 &&
        txMouseX() <= 300 && txMouseY()<=250 &&
        txMouseButtons() == 1)
        {
            PAGE="Меню";
        }

        txSelectFont("Arial",25);
        txDrawText(300,100,900,600,"Управление:\n"
                                "D-идти вправо S-идти влево SPACE прыжок"
        );
    }



    if(PAGE=="Игра")
    {
        txBegin();

        txBitBlt(txDC(), 0, 0, 1800, 900, gamefon1);




        if(GetAsyncKeyState (VK_ESCAPE))
        {
            PAGE="Меню";
        }

        txSetColor(TX_GREEN);
        txSetFillColor(TX_GREEN);
        txRectangle(ExitX,ExitY,ExitX+50,ExitY+50);
        txSetFillColor(TX_BLACK);

        drawMario(mario);



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

        if(GetAsyncKeyState('D'))
        {
            mario.x=mario.x+10;
            mario.picture=marioright;
        }
        if(GetAsyncKeyState('A'))
        {
            mario.x=mario.x-10;
            mario.picture=marioleft;
        }
        if(GetAsyncKeyState(VK_SPACE))
        {
            while(GetAsyncKeyState (VK_SPACE))
            txSleep(50);
            mario.vy=-30;
            spak=spak+1;

        }

        mario.y=mario.y+mario.vy;
        mario.vy=mario.vy+3;

        txSetColor(TX_RED);
        sprintf(strmario, "Монет = %d", kolm);
        txTextOut(900, 25, strmario);
        sprintf(strmario, "Ключ = %d", kolk);
        txTextOut(900, 75, strmario);
        sprintf(strmario, "Уровень = %d", level);
        txTextOut(900, 50, strmario);





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



    //система монет
        for(int i=0; i<Kolmoneta; i++)
        {
            if(mario.x==moneta[i].x && mario.y==moneta[i].y && moneta[i].visible)
            {
                moneta[i].visible = false;
                kolm=kolm+1;
            }
        }

    //ключи
        for(int i=0; i<kolkey; i++)
        {
            if(mario.x==key[i].x && mario.y==key[i].y && key[i].visible)
            {
                key[i].visible = false;
                kolk=kolk+1;
            }
        }

    //механика шипов
    for(int i=0; i<kolspikes; i++)
        {
            if(mario.x+20 > spikes[i].x && mario.x+70 < spikes[i].x+100 &&
               mario.y+20 > spikes[i].y && mario.y+80 < spikes[i].y+100)
            {
                txTextOut(900, 450,"GAME OVER");
            }
        }



        if (txGetPixel(mario.x+40, mario.y) == TX_GREEN)
        {
            txSetColor(TX_ORANGE,3);
            txSelectFont("Time", 50);
            txTextOut(50, 50, "Уровень пройден!");
            txSleep(5000);
            ExitX = 1200;
            ExitY = 500;
            level++;
        }



        if(level==2 && txGetPixel(mario.x,mario.y) == TX_GREEN && kolk==1)
        {
            mario.x=100;
            mario.y=750;
            block[0] = {150, 550, 200};
            block[1] = {950, 550, 100};
            block[2] = {450, 400, 100};
            spikes[0] = {1150,750, spikes[0].picture};
            spikes[1] = {11,750, spikes[0].picture};
            spikes[2] = {150,750, spikes[0].picture};
        }


        txEnd();


   }
    txSleep(20);

}
txDeleteDC(marioright);
txDeleteDC(marioleft);



return 0;
}
