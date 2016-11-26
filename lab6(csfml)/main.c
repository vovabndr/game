//
//  main.c
//  lab6(csfml)
//
//  Created by Владимир Бондарь on 11/15/16.
//  Copyright © 2016 vbbv. All rights reserved.
//

#include <SFML/Graphics.h>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct
{
    int x;
    int y;
} Point;


int maxSum = -1;
int map[10][10];
Point* maxWay;
int sizeOfWay;


int rtrnX(int numb);
int rtrnY(int numb);
void Mdelay(unsigned int mseconds);

void findWay(int x, int y, int sum, Point* way, int counter);

void currentJSON();
void writeMap();
void readMap();

int main(int argc,char* argv[])
{
    
    sfVideoMode mode ={768,768,32};
    sfRenderWindow* window;
    
    sfTexture* blockTexture;
    sfTexture* grassTexture;
    sfTexture* boxTexture;
    sfTexture* heroTexture;
    sfTexture* goldTexture;
    sfTexture* goldIconTexture;
    sfTexture* doorTexture;
    sfTexture* stepsTexture;
    
    
    sfSprite* blockSprite[47];
    sfSprite* grassSprite[100];
    sfSprite* heroSprite[8];
    sfSprite* goldSprite[20];
    sfSprite* goldIconSprite;
    sfSprite* doorSprite;
    sfSprite* stepsSprite[10][10];
    
    sfVector2f sscale;
    sfVector2f textScale;
    sfVector2f currentScale;
    sfVector2f goldScale;
    
    sfColor textColor;
    
    sfEvent event;
    
    sfFont* font;
    
    sfText* text;
    sfText* goldText;
    sfText* goldIconText[20];
    sfText* fpsText;
    
    sfIntRect heroRect;
    
    sfClock *fpsClock;
    fpsClock = sfClock_create();

    
    int i,j,k,count=0,goldSpriteCount=0,gold=0,currentGoldCount=0,s=0,t=0,check,forS;
    int stepMap[10][10];
    char goldArr[4];
    heroRect.width=52;
    heroRect.height=76;
    
    srand((unsigned int)time(NULL));
    
    
    char blockAddress[]="/Users/adimirbondar/Documents/lab/lab6(csfml)/lab6(csfml)/Wall_DelbekeHannes copy.JPG";
    char grassAddress[]="/Users/adimirbondar/Documents/lab/lab6(csfml)/lab6(csfml)/rsz_so4m8w0.png";
    char boxAddress[]="/Users/adimirbondar/Documents/lab/lab6(csfml)/lab6(csfml)/rsz_box.png";
    char heroAddress[]="/Users/adimirbondar/Documents/lab/lab6(csfml)/lab6(csfml)/IMG_7392.PNG";
    char goldAddress[]="/Users/adimirbondar/Documents/lab/lab6(csfml)/lab6(csfml)/rsz_monetary_budget-512.png";
    char doorAddress[]="/Users/adimirbondar/Documents/lab/lab6(csfml)/lab6(csfml)/rsz_1475657141_thumb_100door.png";
    char textAddress[]="/Library/Fonts/Arial Black.ttf";
    char goldIconAddress[]="/Users/adimirbondar/Documents/lab/lab6(csfml)/lab6(csfml)/monetary_icon.png";
    char stepsAddress[]="/Users/adimirbondar/Documents/lab/lab6(csfml)/lab6(csfml)/steps.png";
    
    if (!fpsClock)
    {
        return 1;
    }
    
    window = sfRenderWindow_create(mode, "lab 6", sfResize | sfClose, NULL);
    if (!window)
        return 2;
    
    blockTexture = sfTexture_createFromFile(blockAddress, NULL);
    if (!blockTexture)
        return 3;
    
    grassTexture = sfTexture_createFromFile(grassAddress, NULL);
    if (!grassTexture)
        return 4;
    
    boxTexture = sfTexture_createFromFile(boxAddress, NULL);
    if (!boxTexture)
        return 5;
    
    heroTexture = sfTexture_createFromFile(heroAddress, NULL);
    if (!heroTexture)
        return 6;
    
    goldTexture = sfTexture_createFromFile(goldAddress, NULL);
    if (!goldTexture)
        return 7;
    
    doorTexture = sfTexture_createFromFile(doorAddress, NULL);
    if (!doorTexture)
        return 7;
    
    font = sfFont_createFromFile(textAddress);
    if (!font)
        return 8;
    
    goldIconTexture = sfTexture_createFromFile(goldIconAddress, NULL);
    if (!goldIconTexture)
        return 9;
    
    stepsTexture = sfTexture_createFromFile(stepsAddress, NULL);
    if (!stepsTexture)
        return 10;
    
    for(i=0;i<12;i++)
    {
        sscale.x=64*i;
        sscale.y=0;
        blockSprite[i]=sfSprite_create();
        sfSprite_setTexture(blockSprite[i],blockTexture, sfTrue);
        sfSprite_setPosition(blockSprite[i], sscale);
        
        sscale.x=64*i;
        sscale.y=704;
        blockSprite[i+12]=sfSprite_create();
        sfSprite_setTexture(blockSprite[i+12],blockTexture, sfTrue);
        sfSprite_setPosition(blockSprite[i+12], sscale);
        
        sscale.x=0;
        sscale.y=64*i;
        blockSprite[i+24]=sfSprite_create();
        sfSprite_setTexture(blockSprite[i+24],blockTexture, sfTrue);
        sfSprite_setPosition(blockSprite[i+24], sscale);
        
        sscale.x=704;
        sscale.y=64*i;
        blockSprite[i+36]=sfSprite_create();
        sfSprite_setTexture(blockSprite[i+36],blockTexture, sfTrue);
        sfSprite_setPosition(blockSprite[i+36], sscale);
    }
    

    
    Point* way = (Point*) malloc(sizeof(Point) * 100);
    
    
    while (maxSum==-1 )
    {
        goldSpriteCount=0;
        count=0;
        
        for(j=0;j<10;j++)
            for(k=0;k<10;k++)
            {
                sscale.x=64+64*j;
                sscale.y=64+64*k;
                
                grassSprite[count]=sfSprite_create();
                
                if(rand()%5==0 && (count!=0 && count!=99))
                {
                    sfSprite_setTexture(grassSprite[count],boxTexture, sfTrue);
                    map[rtrnX(count)][rtrnY(count)]=-1;
                    
                }
                else
                {
                    sfSprite_setTexture(grassSprite[count],grassTexture, sfTrue);
                    map[rtrnX(count)][rtrnY(count)]=0;
                    
                    if(rand()%3==0 && (count!=0 && count!=99))
                        if(goldSpriteCount<20)
                        {
                            goldSprite[goldSpriteCount]=sfSprite_create();
                            sfSprite_setTexture(goldSprite[goldSpriteCount],goldTexture, sfTrue);
                            sfSprite_setPosition(goldSprite[goldSpriteCount], sscale);
                            gold=(rand()%18)*5+10;
                            map[rtrnX(count)][rtrnY(count)]=gold;
                            
                            goldIconText[goldSpriteCount] = sfText_create();
                            textColor=sfBlack;
                            
                            goldScale.x=72+64*j;
                            goldScale.y=94+64*k;
                            sfText_setFont(goldIconText[goldSpriteCount], font);
                            sfText_setCharacterSize(goldIconText[goldSpriteCount], 11);
                            sfText_setColor(goldIconText[goldSpriteCount],textColor);
                            sfText_move(goldIconText[goldSpriteCount], goldScale);
                            
                            sprintf(goldArr, "%d",gold);
                            sfText_setString(goldIconText[goldSpriteCount], goldArr);
                            goldSpriteCount++;
                        }
                }
                sfSprite_setPosition(grassSprite[count], sscale);
                count++;
            }
        
        findWay(0, 0, 0, way, 0);
    }
    for(j=0;j<10;j++)
    {
        for(k=0;k<10;k++)
            printf("%2d   ",map[j][k]);
        printf("\n");
    }
    for(j=0;j<10;j++)
        for(k=0;k<10;k++)
            stepMap[j][k]=0;
    
    
    for(j=0;j<10;j++)
        for(k=0;k<10;k++)
        {
            sscale.x=64+64*j;
            sscale.y=64+64*k;
            stepsSprite[j][k] =sfSprite_create();
            sfSprite_setTexture(stepsSprite[j][k],stepsTexture, sfTrue);
            sfSprite_setPosition(stepsSprite[j][k], sscale);
            
        }
    //208x304
  for(i=0;i<4;i++)
    {  
    sscale.x=64;
    sscale.y=64;
    heroRect.left=52*i;
        
    heroRect.top=162;
    heroRect.width=52;
    heroRect.height=76;
    
   
    heroSprite[i]=sfSprite_create();
    sfSprite_setTexture(heroSprite[i],heroTexture, sfTrue);
    sfSprite_setTextureRect(heroSprite[i], heroRect);
    sfSprite_setPosition(heroSprite[i], sscale);
    
    }

    
    for(i=4;i<8;i++)
    {
        sscale.x=64;
        sscale.y=64;
        heroRect.left=52*(i-3)-52;
        heroRect.top=0;
        heroRect.width=52;
        heroRect.height=76;
        
        
        heroSprite[i]=sfSprite_create();
        sfSprite_setTexture(heroSprite[i],heroTexture, sfTrue);
        sfSprite_setTextureRect(heroSprite[i], heroRect);
        sfSprite_setPosition(heroSprite[i], sscale);
    }
    
    
    
    
    sscale.x=640;
    sscale.y=640;
    doorSprite=sfSprite_create();
    sfSprite_setTexture(doorSprite,doorTexture, sfTrue);
    sfSprite_setPosition(doorSprite, sscale);
    
    text = sfText_create();
    textColor=sfYellow;
    textScale.x=600;
    textScale.y=8;
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 32);
    sfText_setColor(text,textColor);
    sfText_move(text, textScale);
    sfText_setString(text, "Gold: ");
    
    goldText = sfText_create();
    textColor=sfYellow;
    textScale.x=690;
    textScale.y=10;
    sfText_setFont(goldText, font);
    sfText_setCharacterSize(text, 32);
    sfText_setColor(goldText,textColor);
    sfText_move(goldText, textScale);
    
    fpsText = sfText_create();
    textColor=sfYellow;
    textScale.x=400;
    textScale.y=8;
    sfText_setFont(fpsText, font);
    sfText_setCharacterSize(fpsText, 32);
    sfText_setColor(fpsText,textColor);
    sfText_move(fpsText, textScale);
    
    
    
    sscale.x=560;
    sscale.y=10;
    goldIconSprite=sfSprite_create();
    sfSprite_setTexture(goldIconSprite,goldIconTexture, sfTrue);
    sfSprite_setPosition(goldIconSprite, sscale);
    
    
    
    
    
    printf("%d\n", maxSum);
    
    for (i = 0; i < sizeOfWay; i++)
        printf("[%d]: %d %d    \n",i, maxWay[i].x, maxWay[i].y);
    
    printf("\n");
    i=0;
    
    int fps = 0;
    sfClock_restart(fpsClock);
    writeMap();
    
    ///////////////////////////////////////////////////////////////////////////
    while (sfRenderWindow_isOpen(window))
    {
        check=0;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        char buff[15];
        fps++;
        if (fmod(sfTime_asSeconds(sfClock_getElapsedTime(fpsClock)),0.25) < 0.001 && fps > 2)
        {
            sprintf(buff, "FPS: %d", (int)(fps*(1/ sfTime_asSeconds(sfClock_getElapsedTime(fpsClock)))));
            sfText_setString(fpsText, buff);
        }
        if (sfTime_asSeconds(sfClock_getElapsedTime(fpsClock)) >= 1)
        {
            fps = 0;
            sfClock_restart(fpsClock);
        }
        
        currentScale=sfSprite_getPosition(heroSprite[0]);
        
        if(s==128*2)
        {
            s=0;
            t++;
            currentGoldCount+=map[maxWay[t].x][maxWay[t].y];
            
        }
        for(i=0;i<8;i++){
        if(maxSum!=-1)
        {
            if (maxWay[t+1].x==maxWay[t].x)
            {
                if(currentScale.x<704)
                {
                sscale.x=0.25;
                sscale.y=0;
                sfSprite_move(heroSprite[i], sscale);
               if(i==0)
                    s++;
                }
            }
            else if (maxWay[t+1].y==maxWay[t].y)
            {
                if(currentScale.y<704)
                {
                sscale.x=0;
                sscale.y=0.25;
                sfSprite_move(heroSprite[i], sscale);
                    if(i==0)
                s++;
                    check=1;
                }
            }
        }
        
        }
        
        
        
        
        sprintf(goldArr, "%d",currentGoldCount);
        sfText_setString(goldText, goldArr);
        
        sfRenderWindow_clear(window, sfBlack);
        
        for (i=0;i<47;i++)
            sfRenderWindow_drawSprite(window, blockSprite[i], NULL);
        for(i=0;i<100;i++)
            sfRenderWindow_drawSprite(window, grassSprite[i], NULL);
        
        for(i=0;i<goldSpriteCount;i++)
        {
            sfRenderWindow_drawSprite(window, goldSprite[i], NULL);
            sfRenderWindow_drawText(window, goldIconText[i], NULL);
            
        }
        if(maxSum!=-1)
        {
            sfRenderWindow_drawSprite(window, stepsSprite[maxWay[0].y][maxWay[0].x], NULL);
            
            for(i=1;i<=t;i++)
                sfRenderWindow_drawSprite(window, stepsSprite[maxWay[i].y][maxWay[i].x], NULL);
        }
        sfRenderWindow_drawSprite(window, doorSprite, NULL);
        forS=s;
        if(check==0)
        {
            if(forS<=64 && forS>0)
                sfRenderWindow_drawSprite(window,heroSprite[0],NULL);
            if(forS<=128 && forS>64)
                sfRenderWindow_drawSprite(window,heroSprite[1],NULL);
            if(forS<=192 && forS>128)
                sfRenderWindow_drawSprite(window,heroSprite[2],NULL);
            if(forS<=256 && forS>192)
                sfRenderWindow_drawSprite(window,heroSprite[3],NULL);

        }
        else if (check==1)
        {
            if(forS<=64 && forS>0)
                sfRenderWindow_drawSprite(window,heroSprite[4],NULL);
            if(forS<=128 && forS>64)
                sfRenderWindow_drawSprite(window,heroSprite[5],NULL);
            if(forS<=192 && forS>128)
                sfRenderWindow_drawSprite(window,heroSprite[6],NULL);
            if(forS<=256 && forS>192)
                sfRenderWindow_drawSprite(window,heroSprite[7],NULL);
        }
        else
            sfRenderWindow_drawSprite(window,heroSprite[0],NULL);
 if(currentScale.x==704 && currentScale.y==704)
        sfRenderWindow_drawSprite(window,heroSprite[0],NULL);
        
        sfRenderWindow_drawText(window, text, NULL);
        sfRenderWindow_drawText(window, goldText, NULL);
        sfRenderWindow_drawText(window, fpsText, NULL);
        sfRenderWindow_drawSprite(window,goldIconSprite,NULL);
        
        sfRenderWindow_display(window);
    }
   
    
    sfTexture_destroy(blockTexture);
    sfTexture_destroy(grassTexture);
    sfTexture_destroy(goldTexture);
    sfTexture_destroy(heroTexture);
    sfTexture_destroy(doorTexture);
    sfText_destroy(goldText);
    sfText_destroy(text);
    sfText_destroy(fpsText);
    sfTexture_destroy(goldIconTexture);
    sfTexture_destroy(stepsTexture);
    
    sfRenderWindow_destroy(window);
    
    return 0;
}


void findWay(int x, int y, int sum, Point* way, int counter)
{
    int i = 0;
    
    way[counter].x = x;
    way[counter].y = y;
    
    if (x == 9 && y == 9)
    {
        if (sum > maxSum)
        {
            maxSum = sum;
            
            maxWay = (Point*) malloc(sizeof(Point) * counter + 1);
            
            for (i = 0; i < counter + 1; i++)
                maxWay[i] = way[i];
            
            sizeOfWay = counter + 1;
        }
    }
    else
    {
        if (x < 9 && map[x + 1][y] != -1)
            findWay(x + 1, y, sum + map[x + 1][y], way, counter + 1);
        
        if (y < 9 && map[x][y + 1] != -1)
            findWay(x, y + 1, sum + map[x][y + 1], way, counter + 1);
    }
}


int rtrnX(int numb)
{
    int tmp=numb;
    
    if (numb<10)
        return numb;
    else
    {
        numb/=10;
        numb*=10;
        tmp-=numb;
        return tmp;
    }
}


int rtrnY(int numb)
{
    if(numb<10)
        return 0;
    else
        return numb/10;
}

void Mdelay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void currentJSON()
{
    FILE* mapJson=fopen("/Users/adimirbondar/Documents/lab/lab6(csfml)/lab6(csfml)/map.json", "w");
    int i,j;
    fprintf(mapJson,"[\n");
    for(i=0;i<10;i++)
    {
        fprintf(mapJson,"\t");
        for(j=0;j<10;j++)
        {
            if(j!=9)
            fprintf(mapJson, "[%2d], ",map[i][j]);
            else
                fprintf(mapJson, "[%2d]",map[i][j]);

        }
        fprintf(mapJson,"\n");
    }
    fprintf(mapJson,"]");
    fclose(mapJson);
    
}

void writeMap()
{
    
    FILE* mapJson=fopen("/Users/adimirbondar/Documents/lab/map.json", "w");
    int i,j;
    for(i=0;i<10;i++)
        for(j=0;j<10;j++)
                fprintf(mapJson, "%d ",map[i][j]);
    fclose(mapJson);
}

void readMap()
{
    FILE* mapJson=fopen("/Users/adimirbondar/Documents/lab/map.json", "r");
    int i,j;
    for(i=0;i<10;i++)
        for(j=0;j<10;j++)
            fscanf(mapJson,"%d",&map[i][j]);
    fclose(mapJson);
    
}

