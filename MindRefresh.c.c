#include <stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdbool.h>
#include "move.h"
int main(int args,char *argv[]){
    SDL_Window *window=NULL;
    SDL_Surface* menu= NULL;
    SDL_Surface* menu2= NULL;
    SDL_Surface* menu3= NULL;
    SDL_Surface* menu4= NULL;
    SDL_Event event;
    SDL_Rect positionMenu2;
    SDL_Rect positionMenu3;
    SDL_Rect positionMenu4;
    SDL_Rect positionMenu;
    int longArr=0,count=0,longAllCases=10,longeur=0;
    int step=0,done = 0,pos=0,option=0,posM2=1,posJ=1,joueur=1,depart=1;
    int posDame[5]={1,1,1,1,1},score[5]={0,0,0,0,0},posOption[3]={0,9,9};
    float joueurCase1[100],joueurCase2[100],joueurCase3[100],joueurCase4[100],allCases[200], lastMove[2],lastSelect[2];
    float emptyCase1[100];
    FILE* fichier = NULL;
    FILE* fichierMusic = NULL;
    fichierMusic = fopen(getNameFile(DIRECT_DATA,"option.txt"), "r");
    if(!isFileVide(fichierMusic)){
        fclose(fichierMusic);
        fichierMusic = fopen(getNameFile(DIRECT_DATA,"option.txt"), "r");
        fscanf(fichierMusic, "%d", &posOption[1]);
        fscanf(fichierMusic, "%d", &posOption[2]);
        fclose(fichierMusic);
    }
    positionMenu2.x=400;
    positionMenu3.x=400;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    Mix_Music *music=Mix_LoadMUS(getNameFile(DIRECT_SON,"102.mp3"));
    Mix_Chunk *son=Mix_LoadWAV(getNameFile(DIRECT_SON,"2003.wav"));
    Mix_PlayMusic(music,-1);
    window = SDL_CreateWindow("SDL2",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,680,450,SDL_WINDOW_SHOWN);
    initWindow("Mind refresh","BACKGROUND.png",window,menu,positionMenu);
    initSound(posOption[1],positionMenu);
    initWAV(son,posOption[2],positionMenu);
    fichier = fopen(getNameFile(DIRECT_DATA,"test.txt"), "r");
    if(!isFileVide(fichier)){fclose(fichier);
    depart=0;pos=0;
    initMenu("start",posOption,0,100,"menu","menuHover0.png",window,menu2,positionMenu2);}
    else {pos=1;initMenu("start",posOption,0,4,"menu","menuHover1.png",window,menu2,positionMenu2);}
    SDL_Surface *texte = NULL;
    TTF_Init();
    TTF_Font *police = NULL;
    SDL_Color noire={139, 108, 66};
    police = TTF_OpenFont("fon.ttf", 25);
    SDL_StartTextInput();
    int postext=1;
    struct nomJ nomJoueur={"",0,"",0,"",0,"",0};
    while (done==0)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_TEXTINPUT:
                if(step==22){
                    if(postext==1&&nomJoueur.indice1<=7){
                        texte=TTF_RenderText_Blended(police,strcat(nomJoueur.nom1,event.text.text),noire);
                        nomJoueur.indice1=setText(1,nomJoueur.indice1,window,texte,positionMenu3);
                    }if(postext==2&&nomJoueur.indice2<=7){
                        texte=TTF_RenderText_Blended(police,strcat(nomJoueur.nom2,event.text.text),noire);
                        nomJoueur.indice2=setText(1,nomJoueur.indice2,window,texte,positionMenu3);
                    }if(postext==3&&nomJoueur.indice3<=7){
                        texte=TTF_RenderText_Blended(police,strcat(nomJoueur.nom3,event.text.text),noire);
                        nomJoueur.indice3=setText(1,nomJoueur.indice3,window,texte,positionMenu3);
                    }if(postext==4&&nomJoueur.indice4<=7){
                        texte=TTF_RenderText_Blended(police,strcat(nomJoueur.nom4,event.text.text),noire);
                        nomJoueur.indice4=setText(1,nomJoueur.indice4,window,texte,positionMenu3);
                    }
                }
                break;
                case SDL_QUIT:
                    done = 1;
                    break;
                case SDL_KEYDOWN:
                    {
                        if(event.key.keysym.sym == SDLK_BACKSPACE){
                            if(step==22){
                            if(postext==1&&nomJoueur.indice1>0){
                                nomJoueur.nom1[nomJoueur.indice1-1]='\0';
                                texte=TTF_RenderText_Blended(police,nomJoueur.nom1,noire);
                                nomJoueur.indice1=nomJoueur.indice1-1;
                                setText(1,nomJoueur.indice1,window,texte,positionMenu3);
                            }if(postext==2&&nomJoueur.indice2<=15){
                                nomJoueur.nom2[nomJoueur.indice2-1]='\0';
                                texte=TTF_RenderText_Blended(police,nomJoueur.nom2,noire);
                                nomJoueur.indice2=nomJoueur.indice2-1;
                                setText(1,nomJoueur.indice2,window,texte,positionMenu3);
                            }if(postext==3&&nomJoueur.indice3<=15){
                                nomJoueur.nom3[nomJoueur.indice3-1]='\0';
                                texte=TTF_RenderText_Blended(police,nomJoueur.nom3,noire);
                                nomJoueur.indice3=nomJoueur.indice3-1;
                                setText(1,nomJoueur.indice3-1,window,texte,positionMenu3);
                            }if(postext==4&&nomJoueur.indice4<=15){
                                nomJoueur.nom4[nomJoueur.indice4-1]='\0';
                                texte=TTF_RenderText_Blended(police,nomJoueur.nom4,noire);
                                nomJoueur.indice4=nomJoueur.indice4-1;
                                setText(1,nomJoueur.indice4-1,window,texte,positionMenu3);
                            }
                        }
                        }
                        longAllCases=setAllCases(longArr,allCases,joueurCase1,joueurCase2,joueurCase3,joueurCase4,posM2);
                        if (event.key.keysym.sym == SDLK_LEFT||event.key.keysym.sym == SDLK_RIGHT){
                            if(step==2||step==3||step==4||step==5)
                            Mix_PlayChannel(1,son,0);
                            char move[6]="left";
                            if(event.key.keysym.sym == SDLK_RIGHT)strcpy(move,"right");
                            if (step==2){
                                posDame[positionMenu.y/80]=menuUp(move,0,positionMenu.y,posDame[positionMenu.y/80],1,5,"icon","iconHover",window,menu2,positionMenu2);
                            }
                            if (step==3){
                                reloadGame(posM2,joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr,posDame,window,menu,positionMenu);
                                moveSelectDame(joueur,posM2,posDame,move,longArr,joueurCase1,joueurCase2,joueurCase3,joueurCase4,lastMove,window,menu2,positionMenu2);
                            }
                            if (step==4){
                                reloadGame(posM2,joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr,posDame,window,menu,positionMenu);
                                moveDame(posM2,posDame,move,count,emptyCase1,lastMove,window,menu2,positionMenu2);
                            }
                            if(step==5&&option!=3){
                                if(positionMenu4.y<80)positionMenu4.y=80;
                                posOption[positionMenu4.y/80]=menuLeftSon(son,option,move,positionMenu4.y,posOption[positionMenu4.y/80],20,"volume.png","volumeHover.png",window,menu4,positionMenu4);
                                fichierMusic = fopen(getNameFile(DIRECT_DATA,"option.txt"), "w");
                                fprintf(fichierMusic, "%d\n", posOption[1]);
                                fprintf(fichierMusic, "%d\n", posOption[2]);
                                fclose(fichierMusic);
                            }if(step==3||step==4){
                                loadJoueur(&nomJoueur,posM2,score,joueur%4,posDame,window,menu,positionMenu);
                            }
                        }
                        else if (event.key.keysym.sym == SDLK_UP||event.key.keysym.sym == SDLK_DOWN){
                            if(step==0||step==1||step==2||step==3||step==4||step==5)
                            Mix_PlayChannel(1,son,0);
                            char move[6]="up";
                            if (event.key.keysym.sym == SDLK_DOWN)strcpy(move,"down");
                            if(step==0)pos=menuUp(move,0,0,pos,depart,4,"menu","menuHover",window,menu2,positionMenu2);
                            else if(step==1)posM2=menuUp(move,0,0,posM2,1,3,"joueurs","joueursHover",window,menu3,positionMenu3);
                            if(step==22){
                                if(positionMenu3.y<80)positionMenu3.y=80;
                                if (event.key.keysym.sym == SDLK_UP){
                                    if(positionMenu3.y<=80) positionMenu3.y=80*posM2*2;
                                    else positionMenu3.y=positionMenu3.y-80;
                                }else{
                                    if(positionMenu3.y>=80*posM2*2) positionMenu3.y=80;
                                    else positionMenu3.y=positionMenu3.y+80;
                                }
                                postext=menuUp(move,1,0,postext,1,posM2*2+1,"joueur","joueurHover",window,menu3,positionMenu3);

                            }
                            else if(step==2){
                                if (event.key.keysym.sym == SDLK_UP){
                                    if(positionMenu.y<=80) positionMenu.y=80*posM2*2;
                                    else positionMenu.y=positionMenu.y-80;
                                }else{
                                    if(positionMenu.y>=80*posM2*2) positionMenu.y=80;
                                    else positionMenu.y=positionMenu.y+80;
                                }
                                posJ=menuUp(move,1,0,posJ,1,posM2*2+1,"joueur","joueurHover",window,menu3,positionMenu3);
                            }
                            if (step==3){
                                reloadGame(posM2,joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr,posDame,window,menu,positionMenu);
                                moveSelectDame(joueur,posM2,posDame,move,longArr,joueurCase1,joueurCase2,joueurCase3,joueurCase4,lastMove,window,menu2,positionMenu2);
                            }
                            if (step==4){
                                reloadGame(posM2,joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr,posDame,window,menu,positionMenu);
                                moveDame(posM2,posDame,move,count,emptyCase1,lastMove,window,menu2,positionMenu2);
                            }if(step==5){
                                if(positionMenu4.y<80)positionMenu4.y=80;
                                if (event.key.keysym.sym == SDLK_UP){
                                    if(positionMenu4.y<=80) positionMenu4.y=80*3;
                                    else positionMenu4.y=positionMenu4.y-80;
                                }else if (event.key.keysym.sym == SDLK_DOWN){
                                    if(positionMenu4.y>=80*3) positionMenu4.y=80;
                                    else positionMenu4.y=positionMenu4.y+80;
                                }
                                option=menuUp(move,1,0,option,1,4,"option","optionHover",window,menu4,positionMenu4);
                            }if(step==3||step==4){
                                loadJoueur(&nomJoueur,posM2,score,joueur%4,posDame,window,menu,positionMenu);
                            }

                        }else if(event.key.keysym.sym ==SDLK_KP_ENTER){
                            Mix_PlayChannel(1,son,0);
                            int continu=0;
                            if(pos==0){
                                    step=22;pos=1;continu=1;
                                    readData(&nomJoueur,fichier,&posM2,&longArr,joueurCase1,joueurCase2,joueurCase3,joueurCase4,score,posDame,&joueur);
                                    reloadGame(posM2,joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr,posDame,window,menu,positionMenu);
                                    longAllCases=setAllCases(longArr,allCases,joueurCase1,joueurCase2,joueurCase3,joueurCase4,posM2);
                                    setLastMove(lastMove,joueur,posM2,joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr);
                                    loadJoueur(&nomJoueur,posM2,score,joueur%4,posDame,window,menu,positionMenu);
                                    setJoueur(lastMove,joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr,joueur,window,menu,positionMenu);

                            }if(pos==1){
                                if(step==0){
                                    step=1;
                                    initWindow("Mind refresh","BACKGROUND.png",window,menu,positionMenu);
                                    positionMenu.y=80;
                                    initMenu("start",posOption,0,3,"joueurs","joueursHover1.png",window,menu3,positionMenu3);
                                }else if(step==1){
                                    step=2;
                                    initWindow("Mind refresh","BACKGROUND2.png",window,menu,positionMenu);
                                    initMenu("start",posOption,1,(posM2*2)+1,"joueur","joueurHover1.png",window,menu3,positionMenu3);
                                }else if(step==2){
                                    step=22;
                                    initWindow("Mind refresh","BACKGROUND2.png",window,menu,positionMenu);
                                    initMenu("name",posOption,1,(posM2*2)+1,"joueur","joueurHover1.png",window,menu3,positionMenu3);
                                    positionMenu3.y=80;
                                }else if(step==22){
                                    step=3;
                                    if(continu!=1){
                                        joueur=1;
                                        if(posM2==1){
                                        initWindow("Mind refresh","testBack.png",window,menu,positionMenu);}
                                        else if (posM2==2){initWindow("Mind refresh","testBack2.png",window,menu,positionMenu);}

                                        longArr = setDame(allCases,joueurCase1,joueurCase2,joueurCase3,joueurCase4,posM2,posDame,window,menu,positionMenu);
                                        loadJoueur(&nomJoueur,posM2,score,1,posDame,window,menu,positionMenu);
                                        lastMove[0]=18+35;lastMove[1]=18;
                                    }
                                    setJoueur(lastMove,joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr,1,window,menu,positionMenu);

                                }
                                else if(step==3){
                                    lastSelect[0]=lastMove[0];
                                    lastSelect[1]=lastMove[1];
                                    reloadGame(posM2,joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr,posDame,window,menu,positionMenu);
                                    loadJoueur(&nomJoueur,posM2,score,joueur%4,posDame,window,menu,positionMenu);
                                    count=findEmptyCase(&longeur,lastMove,longAllCases,allCases,emptyCase1,window,menu,positionMenu);
                                    step=4;
                                }
                                else if(step==4){
                                    if(joueur==1) moveCase(joueurCase1,longArr,lastSelect[0]-35,lastSelect[1],lastMove[1],lastMove[0]-35);
                                    if(joueur==2) moveCase(joueurCase2,longArr,lastSelect[0]-35,lastSelect[1],lastMove[1],lastMove[0]-35);
                                    if(posM2==2){
                                        if(joueur==3) moveCase(joueurCase3,longArr,lastSelect[0]-35,lastSelect[1],lastMove[1],lastMove[0]-35);
                                        if(joueur==4) moveCase(joueurCase4,longArr,lastSelect[0]-35,lastSelect[1],lastMove[1],lastMove[0]-35);
                                    }
                                    if(posM2==1)
                                        initWindow("Mind refresh","testBack.png",window,menu,positionMenu);
                                        else if (posM2==2) initWindow("Mind refresh","testBack2.png",window,menu,positionMenu);

                                    reloadGame(posM2,joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr,posDame,window,menu,positionMenu);
                                    joueur++;
                                    if(posM2==2){if(joueur==5)joueur=1;}
                                    else if(joueur==3) joueur=1;
                                    setLastMove(lastMove,joueur,posM2,joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr);

                                    if(gameover3(score,joueurCase1,joueurCase2,joueurCase3,joueurCase4,posM2)!=0){

                                        gameOver(joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr,posM2,score,window,menu,positionMenu);
                                        system("del data/test.txt");
                                        step=10;
                                    }else{
                                        gameover3(score,joueurCase1,joueurCase2,joueurCase3,joueurCase4,posM2);
                                        saveData(&nomJoueur,fichier,posM2,longArr,joueurCase1,joueurCase2,joueurCase3,joueurCase4,score,posDame,joueur);
                                        step=3;
                                        setJoueur(lastMove,joueurCase1,joueurCase2,joueurCase3,joueurCase4,longArr,joueur,window,menu,positionMenu);
                                    }
                                    loadJoueur(&nomJoueur,posM2,score,joueur%4,posDame,window,menu,positionMenu);
                                }
                            }
                            else if(pos==2){
                                if(option==0){
                                step=5;option=1;
                                positionMenu4.x=0;
                                positionMenu4.y=0;
                                initWindow("Mind refresh","BACKGROUND2.png",window,menu4,positionMenu4);
                                initMenu("son",posOption,1,4,"option","optionHover1.png",window,menu4,positionMenu4);
                                }
                                if(option==3){
                                    system("del data/test.txt");
                                }
                            }
                            else if(pos==3){
                                done = 1;
                            }
                        }else if(event.key.keysym.sym ==SDLK_ESCAPE){
                            Mix_PlayChannel(1,son,0);
                            if(step!=4){
                            for (int i = 0; i <=nomJoueur.indice1 ; i++)nomJoueur.nom1[i]='\0';
                            for (int i = 0; i <=nomJoueur.indice2 ; i++)nomJoueur.nom2[i]='\0';
                            for (int i = 0; i <=nomJoueur.indice3 ; i++)nomJoueur.nom3[i]='\0';
                            for (int i = 0; i <=nomJoueur.indice4 ; i++)nomJoueur.nom4[i]='\0';
                            nomJoueur.indice1=0,nomJoueur.indice2=0,nomJoueur.indice3=0,nomJoueur.indice4=0;
                            postext=1;
                            step=0,pos=0,posM2=1,posJ=1,depart=1;done = 0;option=0;
                            fichier = fopen(getNameFile(DIRECT_DATA,"test.txt"), "r");
                            initWindow("Mind refresh","BACKGROUND.png",window,menu,positionMenu);
                            if(!isFileVide(fichier)){depart=0;pos=0; initMenu("start",posOption,0,100,"menu","menuHover0.png",window,menu2,positionMenu2);}
                            else {pos=1;initMenu("start",posOption,0,4,"menu","menuHover1.png",window,menu2,positionMenu2);}
                            for (int i = 0; i < 5; i++)
                            {
                                posDame[i]=1;
                            }
                            }else{
                                step=3;
                            }
                        }
                        break;
                    }
                }
            }
        }
    SDL_DestroyWindow(window);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Quit: SDL_Quit();
}
