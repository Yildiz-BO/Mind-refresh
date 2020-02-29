#include <stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdbool.h>
char* DIRECT_IMAGE="image/";
char* DIRECT_SON="sound/";
char* DIRECT_DATA="data/";
typedef struct nomJ nomJ;
struct nomJ
    {
    	char nom1[100];int indice1;//longchar
    	char nom2[100];int indice2;
    	char nom3[100];int indice3;
    	char nom4[100];int indice4;
    };
char* getNameFile(char* debut,char* fin){
	char* copie=NULL;int num=1;
    copie=malloc((strlen(debut)+strlen(fin))*sizeof(char));
    strcpy(copie,debut);
    strcat(copie,fin);
	return copie;
}
bool setImage(float posX,float posY,char* img,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
	positionMenu.x=posX;
	positionMenu.y=posY;
	menu = IMG_Load(getNameFile(DIRECT_IMAGE,img));
	SDL_BlitSurface(menu,NULL,SDL_GetWindowSurface( window ),&positionMenu);
    SDL_UpdateWindowSurface( window );
    return true;
}
int ifMin(char* type,float* joueurCase,int longArr,float max){
	int indice=0;
	float min=900;
	for(int i=0;i<longArr;i=i+2){
		if(joueurCase[i+1]<max&&strstr(type,"min")!=NULL){
			max=joueurCase[i+1];indice=i+1;i=longArr;
		}
		else if(joueurCase[i+1]>max&&joueurCase[i+1]<min&&strstr(type,"max")!=NULL){
			min=joueurCase[i+1];indice=i+1;
		}
	}
	if(indice==0){
		for(int i=0;i<longArr;i=i+2){
			if(joueurCase[i+1]<max&&strstr(type,"max")!=NULL){
				max=joueurCase[i+1];indice=i+1;
			}
			else if(joueurCase[i+1]>max&&strstr(type,"min")!=NULL){
				max=joueurCase[i+1];indice=i+1;
			}
		}
	}
	return indice;
}
int getMinRight(float *Tab,float colone,int nb,char* move){
	float min;
	if(strstr(move,"right")!=NULL||strstr(move,"down")!=NULL) min=1000;
	else if(strstr(move,"left")!=NULL||strstr(move,"up")!=NULL) min=0;
	int indice=0;
	for(int i=0;i<nb;i=i+2){if(Tab[i]!=-100){
		if(Tab[i]<min&&colone==Tab[i+1]&&strstr(move,"right")!=NULL){min=Tab[i];indice=i;}
		else if(Tab[i]>min&&colone==Tab[i+1]&&strstr(move,"left")!=NULL){min=Tab[i];indice=i;}
		else if(Tab[i+1]<min&&colone==Tab[i]&&strstr(move,"down")!=NULL){min=Tab[i+1];indice=i+1;}
		else if(Tab[i+1]>min&&colone==Tab[i]&&strstr(move,"up")!=NULL){min=Tab[i+1];indice=i+1;}}
	}	return indice;
}
int getMax(float *Tab,float cases,float col,float colone,int nb,char* move){
	float min,max;
	if(strstr(move,"down")!=NULL||strstr(move,"right")!=NULL) {min=1000;max=0;}
	else if(strstr(move,"up")!=NULL||strstr(move,"left")!=NULL) {min =0;max=0;}
	int indice=0;
	for(int i=0;i<nb;i=i+2){
		if(Tab[i+1]<cases&&strstr(move,"up")!=NULL){if(Tab[i+1]>min&&max<Tab[i+1]&&colone==Tab[i]){min=Tab[i+1];max=Tab[i+1];indice=i+1;}}
		else if(Tab[i+1]>cases&&strstr(move,"down")!=NULL){if(Tab[i+1]<min&&max>Tab[i+1]&&colone==Tab[i]){max=Tab[i+1];min=Tab[i+1];indice=i+1;}}
		if(Tab[i]>cases&&strstr(move,"right")!=NULL){if(Tab[i]<min&&colone==Tab[i+1]){ min=Tab[i];indice=i;}}
		else if(Tab[i]<cases&&strstr(move,"left")!=NULL){if(Tab[i]>min&&colone==Tab[i+1]){ min=Tab[i];indice=i;}}
	}
	if(min==1000||min==0){
		if(strstr(move,"down")!=NULL&&ifMin("max",Tab,nb,cases)){indice=ifMin("max",Tab,nb,cases);}
		else if(strstr(move,"up")!=NULL&&ifMin("min",Tab,nb,cases)){indice=ifMin("min",Tab,nb,cases);}
		else {indice = getMinRight(Tab,colone,nb,move);}
	}
	return indice;
}
int tryMove(int i,int pos,int* Dame,char* move,int longArr,float *joueurCase,float *lastMove,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
	int cases=3,indice=0;
	if(pos==2) cases=5;
	if(strstr(move,"up")!=NULL||strstr(move,"down")!=NULL){
		indice=getMax(joueurCase,lastMove[1],lastMove[0]-35,joueurCase[i],longArr,move);
		lastMove[0]=joueurCase[indice-1]+35;
		lastMove[1]=joueurCase[indice];
	}else if(strstr(move,"left")!=NULL||strstr(move,"right")!=NULL){
		indice=getMax(joueurCase,lastMove[0]-35,lastMove[1],joueurCase[i],longArr,move);
		lastMove[0]=joueurCase[indice]+35;
		lastMove[1]=joueurCase[i];
	}
		setImage(lastMove[0]-35,lastMove[1]+35,"moveDame.png",window,menu,positionMenu);
 	return longArr;
}
int moveDame(int pos,int* Dame,char* move,int longArr,float *joueurCase,float *lastMove,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
	int foundPlace=0;
	if(strstr(move,"left")!=NULL||strstr(move,"right")!=NULL){
		for(int i=1;i<longArr;i=i+2){
			if(lastMove[1]==joueurCase[i]&&lastMove[0]-35==joueurCase[i-1]){foundPlace++;i=tryMove(i,pos,Dame,move,longArr,joueurCase,lastMove,window,menu,positionMenu);}
			else if(strstr(move,"left")!=NULL&&lastMove[1]==joueurCase[i]&&(lastMove[0]-35==joueurCase[i-1]+50||lastMove[0]-35==joueurCase[i-1]+(50*2))){
				foundPlace++;i=tryMove(i,pos,Dame,move,longArr,joueurCase,lastMove,window,menu,positionMenu);}
			else if(strstr(move,"right")!=NULL&&lastMove[1]==joueurCase[i]&&(lastMove[0]-35==joueurCase[i-1]-50||lastMove[0]-35==joueurCase[i-1]-(50*2))){
				foundPlace++;i=tryMove(i,pos,Dame,move,longArr,joueurCase,lastMove,window,menu,positionMenu);}
			else if(lastMove[1]==joueurCase[i]){foundPlace++;i=tryMove(i,pos,Dame,move,longArr,joueurCase,lastMove,window,menu,positionMenu);}
			else if(foundPlace==0&&i==(longArr-1)) i=tryMove(i,pos,Dame,move,longArr,joueurCase,lastMove,window,menu,positionMenu);
		}
	}
	if(strstr(move,"down")!=NULL||strstr(move,"up")!=NULL){
		for(int i=0;i<=longArr;i=i+2){
			if(lastMove[0]-35==joueurCase[i]){i=tryMove(i,pos,Dame,move,longArr,joueurCase,lastMove,window,menu,positionMenu);}
			else if(longArr<=12){if(lastMove[0]-35==joueurCase[i]-(50*2)||lastMove[0]-35==joueurCase[i]+(50*2)||lastMove[0]-35==joueurCase[i]-50){i=tryMove(i,pos,Dame,move,longArr,joueurCase,lastMove,window,menu,positionMenu);}
			else if(lastMove[0]-35==joueurCase[i]+50){i=tryMove(i,pos,Dame,move,longArr,joueurCase,lastMove,window,menu,positionMenu);}}
		}
	}
	return 0;
}
int emptyPlace(int longArr,float *lastMove,float* joueurCase,int i,int j){
    for(int r=0;r<longArr;r=r+2){
        if(lastMove[1]+(39*i)==joueurCase[r+1]&&lastMove[0]-35+(50*j)==joueurCase[r]){return 0;}
    }
    return 1;
}
SDL_Rect setPositionMenu(float* emptyCase1,int *count,float xx,float yy,SDL_Rect positionMenu){
	if(yy>=18.0&&yy<=468){
     	if(xx>=18.0&&xx<=369){
			if(emptyCase1!=NULL){
				emptyCase1[*count]=yy;
        		emptyCase1[*count+1]=xx;
        		*count=*count+2;
			}
			positionMenu.y=xx+35;
    		positionMenu.x=yy;
    	}
    }return positionMenu;
}
int findEmptyCase(int* longeur,float* lastMove,int longAllCases,float* allCases,float* emptyCase1,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
    int count=0;
    float place[2];
    *longeur=0;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if(lastMove[1]!=lastMove[1]+(39*i)||lastMove[0]!=lastMove[0]+(50*j)){
                place[0]=lastMove[0]+(50*(j));
                place[1]=lastMove[1]+(39*(i));
                if(lastMove[0]+(50*j)-35>=18&&lastMove[0]+(50*j)-35<=468){
                    if(lastMove[1]+(39*i)>=18&&lastMove[1]+(39*i)<=369){
                        	if(emptyPlace(longAllCases,lastMove,allCases,i,j)){
                        		positionMenu=setPositionMenu(emptyCase1,&count,lastMove[1]+(39*i),lastMove[0]-35+(50*j),positionMenu);
                        		setImage(positionMenu.x,positionMenu.y,"moveDame1.png",window,menu,positionMenu);
                        	}else if(emptyPlace(longAllCases,place,allCases,i,j)){
                        		if(place[0]+(50*j)-35>=18.0&&place[0]+(50*j)-35<=468){
                        			if(place[1]+(39*i)>=18.0&&place[1]+(39*i)<=369){
                        				if(lastMove[0]!=lastMove[0]+(50*j)&&lastMove[1]!=lastMove[1]+(39*i)){
                        					if(lastMove[0]<lastMove[0]-35+(50*j)&&lastMove[1]<lastMove[1]+(39*i)){
                        						positionMenu=setPositionMenu(emptyCase1,&count,lastMove[1]+(39*(i+1)),lastMove[0]-35+(50*(j+1)),positionMenu);
                            				}else if(lastMove[0]>lastMove[0]-35+(50*j)&&lastMove[1]>lastMove[1]+(39*i)){
                            					positionMenu=setPositionMenu(emptyCase1,&count,lastMove[1]+(39*(i-1)),lastMove[0]-35+(50*(j-1)),positionMenu);
                            				}else if(lastMove[0]<lastMove[0]-35+(50*j)&&lastMove[1]>lastMove[1]+(39*i)){
                            					positionMenu=setPositionMenu(emptyCase1,&count,lastMove[1]+(39*(i-1)),lastMove[0]-35+(50*(j+1)),positionMenu);
                            				}else if(lastMove[0]>lastMove[0]-35+(50*j)&&lastMove[1]<lastMove[1]+(39*i)){
                            					positionMenu=setPositionMenu(emptyCase1,&count,lastMove[1]+(39*(i+1)),lastMove[0]-35+(50*(j-1)),positionMenu);
                            				}

                        				}
                        				else if(lastMove[0]==lastMove[0]+(50*j)&&lastMove[1]!=lastMove[1]+(39*i)){
                        					if(lastMove[0]==lastMove[0]+(50*j)&&lastMove[1]>lastMove[1]+(39*i)){
                        						positionMenu=setPositionMenu(emptyCase1,&count,lastMove[1]-(39*2)+(39*(i+1)),lastMove[0]-35+(50*(j)),positionMenu);
                            				}else if(lastMove[0]==lastMove[0]+(50*j)&&lastMove[1]<lastMove[1]+(39*i)){
                            					positionMenu=setPositionMenu(emptyCase1,&count,lastMove[1]+(39*(i+1)),lastMove[0]-35+(50*(j)),positionMenu);
                            				}
                        				}
                        				else if(lastMove[0]!=lastMove[0]-35+(50*j)&&lastMove[1]==lastMove[1]+(39*i)){
                       		 			if(lastMove[0]<lastMove[0]-35+(50*j)&&lastMove[1]==lastMove[1]+(39*i)){
                    		    				positionMenu=setPositionMenu(emptyCase1,&count,lastMove[1]+(39*(i)),lastMove[0]-35+(50*(j+1)),positionMenu);
                          		  		}else if(lastMove[0]>lastMove[0]-35+(50*j)&&lastMove[1]==lastMove[1]+(39*i)){
                       		     			positionMenu=setPositionMenu(emptyCase1,&count,lastMove[1]+(39*(i)),lastMove[0]-35+(50*(j-1)),positionMenu);
                       		     		}
                   		     		}
                        			setImage(positionMenu.x,positionMenu.y,"moveDame1.png",window,menu,positionMenu);
                    			}
                        	}
                   		}
                    }
                }
            }
        }
    setImage(lastMove[0]-35,lastMove[1]+35,"moveDame.png",window,menu,positionMenu);
    }

    return count;
}
void moveCase(float *joueurCase,int longArr,float recentY,float recentX,float newX,float newY){
	for(int i=0;i<longArr;i=i+1){
		if((recentY==joueurCase[i])&&(recentX==joueurCase[i+1])){
			joueurCase[i+1]=newX;
			joueurCase[i]=newY;
			i=longArr;
		}
	}
}
int getLongInt(int num){
	int i=0;
	do{ num=num/10;i++; }while(num/10!=0);
	return i;
}
char* convertName(char* debut,int i,char* fin){
	char* copie=NULL;int num=1;
    copie=malloc((strlen(debut)+strlen(fin)+getLongInt(i))*sizeof(char));
    char convert[10];
    sprintf(convert,"%d",i);
    strcpy(copie,debut);
    strcat(copie,convert);
    strcat(copie,fin);
	return copie;
}
void reloadDame(float *joueurCase,int longArr,int Dame,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
	for(int i=0;i<longArr;i=i+2){
		setImage(joueurCase[i],joueurCase[i+1],convertName("myIcone",Dame,".png"),window,menu,positionMenu);
	}
}
int addTabDame(float *joueurCase,int numBulle,float y,float x,float pasY,float pasX){
	int z=0;
	float posx=0,posy=0;
	if(numBulle==5)numBulle=0;
	else numBulle=2;
	posy=y;
	for (int i = 1; i < 4+numBulle; i++)
	{
		posx=x;
		for(int j=1;j<5+numBulle-i;j++){
			joueurCase[z]=posx;
			joueurCase[z+1]=posy;
			z=z+2;
			posx=posx+pasX;
			}
		posy=posy+pasY;
	}
	return z;
}
int finalGame(float *joueurCase,int numBulle,float y,float x,float pasY,float pasX){
	float Tab[100];
	int nb=0,xx=0;
	nb=addTabDame(Tab,numBulle,y,x,pasY,pasX);
	for (int i = 0; i < nb; i=i+2)
	{
		for (int j = 0; j < nb; j=j+2){
			if(joueurCase[i]==Tab[j]&&joueurCase[i+1]==Tab[j+1])xx++;
		}
	}
	return xx;
}
int caseInAll(float *joueurCase,int myCase,int cases){
	int score[4];
	if(myCase!=1)score[0]=finalGame(joueurCase,cases,18,468,39,-50);else score[0]=2;
	if(myCase!=2)score[1]=finalGame(joueurCase,cases,369,18,-39,50);else score[1]=2;
	if(myCase!=3)score[2]=finalGame(joueurCase,cases,18,18,39,50);else score[2]=2;
	if(myCase!=4)score[3]=finalGame(joueurCase,cases,369,468,-39,-50);else score[3]=2;
	return score[0]+score[1]+score[2]+score[3]-2;
}
int killer(float* joueurActuel,float *joueurCase,int numBulle,float y,float x,float pasY,float pasX){
	float Tab[100];
	float cases[100];
	int yy=0,xx=0,nb=0,nb2=0,empty=0;
	nb=addTabDame(Tab,numBulle,y,x,pasY,pasX);
	for (int i = 0; i < nb; i=i+2)
	{
		for (int j = 0; j < nb; j=j+2){
			empty=0;
			if(joueurCase[i]==Tab[j]&&joueurCase[i+1]==Tab[j+1])xx++;
			if(joueurCase[i]+pasX==joueurActuel[j]&&joueurCase[i+1]==joueurActuel[j+1]){
				nb2=nb2+2;
				for (int m = 0; m < nb2;m=m+2)
				{
					if(joueurActuel[j]==cases[m]&&joueurActuel[j+1]==cases[m+1]) empty=1;
				}
				if(!empty){
					cases[nb2-2]=joueurActuel[j];cases[nb2-1]=joueurActuel[j+1];yy++;
				}else nb2=nb2-2;
			}
			else if(joueurCase[i]==joueurActuel[j]&&joueurCase[i+1]+pasY==joueurActuel[j+1]){
				nb2=nb2+2;
				for (int m = 0; m < nb2;m=m+2)
				{
					if(joueurActuel[j]==cases[m]&&joueurActuel[j+1]==cases[m+1]) empty=1;
				}
				if(!empty){
					cases[nb2-2]=joueurActuel[j];cases[nb2-1]=joueurActuel[j+1];yy++;
				}else nb2=nb2-2;
			}
		}
	}
	if(xx==15&&yy==((nb/2)/3)+1||xx==6&&yy==((nb/2)/3)+2) return 1;
	return 0;

}
int caseInAll2(int myCase,float *joueurCase,float *joueurCase1,float *joueurCase2,float *joueurCase3,float *joueurCase4,int cases,float y,float x,float pasY,float pasX){
	int score[4];
	if(myCase!=4)score[0]=killer(joueurCase4,joueurCase,cases,y,x,pasY,pasX);else score[0]=2;
	if(myCase!=3)score[1]=killer(joueurCase3,joueurCase,cases,y,x,pasY,pasX);else score[1]=2;
	if(myCase!=1)score[2]=killer(joueurCase1,joueurCase,cases,y,x,pasY,pasX);else score[2]=2;
	if(myCase!=2)score[3]=killer(joueurCase2,joueurCase,cases,y,x,pasY,pasX);else score[3]=2;
	return score[0]+score[1]+score[2]+score[3]-2;
}
int getIndexMax(int* score,int longeur){
	int max=0,indice=0;
	for (int i = 1; i < longeur; i++)
	{
		if(score[i]>max){
			max=score[i];
			indice=i;
		}
	}
	return indice;
}
int gameover3(int* score,float *joueurCase1,float *joueurCase2,float *joueurCase3,float *joueurCase4,int pos){
	int cases=3;
	if(pos==2){
		cases=5;
		score[1] = caseInAll2(2,joueurCase2,joueurCase1,joueurCase2,joueurCase3,joueurCase4,cases,369,468,-39,-50);
		score[2] = caseInAll2(1,joueurCase1,joueurCase1,joueurCase2,joueurCase3,joueurCase4,cases,18,18,39,50);
		score[3] = caseInAll2(3,joueurCase3,joueurCase1,joueurCase2,joueurCase3,joueurCase4,cases,18,468,39,-50);
		score[4] = caseInAll2(4,joueurCase4,joueurCase1,joueurCase2,joueurCase3,joueurCase4,cases,369,18,-39,50);
		if(score[1]!=0||score[2]!=0||score[3]!=0||score[4]!=0)return getIndexMax(score,5);
		else{
			score[1]=caseInAll(joueurCase1,3,cases);
			score[2]=caseInAll(joueurCase2,4,cases);
			score[3]=caseInAll(joueurCase3,1,cases);
			score[4]=caseInAll(joueurCase4,2,cases);
			if(score[1]>=6||score[2]>=6||score[3]>=6||score[4]>=6)return getIndexMax(score,5);
		}
	}else if(pos==1){
	score[2]=finalGame(joueurCase2,cases,18,18,39,50);
	score[1]=finalGame(joueurCase1,cases,369,468,-39,-50);
	if(score[1]>=10||score[2]>=10)return getIndexMax(score,3);
	else{
		if(killer(joueurCase1,joueurCase2,cases,369,468,-39,-50))return 1;
		else if(killer(joueurCase2,joueurCase1,cases,18,18,39,50))return 2;
	}
	}
	return 0;
}
int addDame(float *joueurCase,int numBulle,float y,float x,float pasY,float pasX,int Dame,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
	int nb=0;
	nb=addTabDame(joueurCase,numBulle,y,x,pasY,pasX);
	reloadDame(joueurCase,nb,Dame,window,menu,positionMenu);
	return nb;
}
int setAllCases(int longArr,float* allCases,float* Tab1,float* Tab2,float* Tab3,float* Tab4,int joueur){
	for(int i=0;i<longArr*(2*joueur);i++){
		if(i<longArr)allCases[i]=Tab1[i];
		else if(i<longArr*2)allCases[i]=Tab2[i-longArr];
		else if(i<longArr*3)allCases[i]=Tab3[i-(longArr*2)];
		else if(i<longArr*4)allCases[i]=Tab4[i-(longArr*3)];
	}
	return longArr*(2*joueur);
}
int setDame(float* allCases,float *joueurCase1,float *joueurCase2,float *joueurCase3,float *joueurCase4,int pos,int* Dame,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
	int longArr=0;
	int cases=3;
	if(pos==2){
		cases=5;
		addDame(joueurCase3,cases,18,468,39,-50,Dame[3],window,menu,positionMenu);
		addDame(joueurCase4,cases,369,18,-39,50,Dame[4],window,menu,positionMenu);
	}
	addDame(joueurCase1,cases,18,18,39,50,Dame[1],window,menu,positionMenu);
	longArr=addDame(joueurCase2,cases,369,468,-39,-50,Dame[2],window,menu,positionMenu);
	setAllCases(longArr,allCases,joueurCase1,joueurCase2,joueurCase1,joueurCase1,pos);
	return longArr;
}
int getMinCase(float* joueurCase,int longArr){
	float min2=joueurCase[1];
	int indice=0;
	for (int i = 0; i < longArr; i=i+2)
	{
		if(joueurCase[i+1]<min2){
			min2=joueurCase[i+1];
			indice=i;
		}

	}
	return indice;
}
int getMaxCase(float* joueurCase,int longArr){
	float min2=joueurCase[1];
	int indice=0;
	for (int i = 0; i < longArr; i=i+2)
	{
		if(joueurCase[i+1]>min2){
			min2=joueurCase[i+1];
			indice=i;
		}
	}
	return indice;
}
void setJoueur(float* lastMove,float* joueurCase1,float* joueurCase2,float* joueurCase3,float* joueurCase4,int longArr,int joueur,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
	setImage(lastMove[0]-35,lastMove[1]+35,"moveDame.png",window,menu,positionMenu);
}
int setText(int step,int indice,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
	SDL_Surface* menu4= NULL;
	SDL_Rect positionMenu2;
	positionMenu2.y=positionMenu.y+20;
	positionMenu2.x=positionMenu.x-10;
	if(step==1){
	setImage(positionMenu.x-25,positionMenu.y+10,"zone.png",window,menu4,positionMenu) ;}
    SDL_BlitSurface(menu, NULL, SDL_GetWindowSurface( window ), &positionMenu2);
    SDL_UpdateWindowSurface( window );
    printf("%d\n",indice );
    return ++indice;
}
void loadScore(int nbJoueur,int* score,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
	for(int i=0;i<nbJoueur*2;i++){
		setImage(540,60+(70*(1+i)),convertName("score/",score[i+1]*100,".png"),window,menu,positionMenu);
    }
}
char* getNomJoueur(nomJ* nomJoueur,int joueur){
	if(joueur==1)return nomJoueur->nom1;
	if(joueur==2)return nomJoueur->nom2;
	if(joueur==3)return nomJoueur->nom3;
	if(joueur==4||joueur==0)return nomJoueur->nom4;
}
void loadScoreJoueur(nomJ* nomJoueur,int nbJoueur,SDL_Window *window,SDL_Surface* menu,TTF_Font *police,SDL_Color colore){
	SDL_Rect positionMenu;
    positionMenu.x=550;
	for(int i=0;i<nbJoueur*2;i++){
		positionMenu.y=90+(70*(i));
		setText(0,0,window,TTF_RenderText_Blended(police,getNomJoueur(nomJoueur,i+1),colore),positionMenu);
    }
}
void gameOver(float *joueurCase1,float *joueurCase2,float *joueurCase3,float *joueurCase4,int longArr,int nbJoueur,int* score,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
		setImage(0,0,"gameover.png",window,menu,positionMenu);
		int i=gameover3(score,joueurCase1,joueurCase2,joueurCase3,joueurCase4,nbJoueur);
    	setImage(200,280,convertName("score/scorej",i,".png"),window,menu,positionMenu) ;
    	setImage(350,260,convertName("score/",score[i],".png"),window,menu,positionMenu);
}
void loadJoueur(nomJ* nomJoueur,int nbJoueur,int* score,int joueur,int posDame[],SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
	TTF_Font *police = NULL;
    SDL_Color colore={70,130,180};
    police = TTF_OpenFont("fon.ttf", 20);
    positionMenu.x=590;
    positionMenu.y=40;
    setText(0,10,window,TTF_RenderText_Blended(police,getNomJoueur(nomJoueur,joueur),colore),positionMenu);
    if(joueur==0)posDame[0]=posDame[4];
    setImage(530,50,convertName("myIcone",posDame[joueur],".png"),window,menu,positionMenu);
    loadScore(nbJoueur,score,window,menu,positionMenu);
	loadScoreJoueur(nomJoueur,nbJoueur,window,menu,police,colore);

}
bool initSound(int ActuelVolume,SDL_Rect positionMenu){
	Mix_VolumeMusic(7*(ActuelVolume+1));
	return true;
}
void menuSon(int ActuelVolume,int max,char* text1,char* text2,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
    if(positionMenu.y==80) initSound(ActuelVolume,positionMenu);
    for (int i = 0; i < max; i++)
    {
        if(i>=ActuelVolume+1)setImage(350+12*i,positionMenu.y,text1,window,menu,positionMenu);
    	else setImage(350+12*i,positionMenu.y,text2,window,menu,positionMenu);
    }
}
void menuVertical(int max,char* text1,char* text2,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
    for (int i = 1; i < max; ++i)
    {
        if(i>1)setImage(250+80*i,positionMenu.y,convertName(text1,i,".png"),window,menu,positionMenu);
    	else setImage(250+80*i,positionMenu.y,text2,window,menu,positionMenu);
    }
}
void initMenu(char* type,int* volumeActuel,int vertical,int max,char* text1,char* text2,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
	int depart=1;positionMenu.y=0;int posX=positionMenu.x-25;
	if(max==100){depart=0;max=4;}
    for (int i = depart; i < max; ++i)
    {
        if(i>depart){
        menu = IMG_Load(getNameFile(DIRECT_IMAGE,convertName(text1,i,".png")));
    }else menu = IMG_Load(getNameFile(DIRECT_IMAGE,text2));
        positionMenu.y=positionMenu.y+80;
        if(vertical&&strstr(type,"start")!=NULL){
            positionMenu.x=10;
            menuVertical(5,"icon","iconHover1.png",window,menu,positionMenu);
        }
        if(vertical&&strstr(type,"name")!=NULL){
        	setImage(posX,positionMenu.y+10,"zone.png",window,menu,positionMenu) ;
            positionMenu.x=10;
        }
        if(vertical&&i<max-1&&strstr(type,"son")!=NULL){
            positionMenu.x=10;
            menuSon(volumeActuel[i],20,"volume.png","volumeHover.png",window,menu,positionMenu);
        }
        SDL_BlitSurface(menu,NULL,SDL_GetWindowSurface( window ),&positionMenu);
        SDL_UpdateWindowSurface( window );
    }
}
void initWindow(char* title,char* bg,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
    SDL_SetWindowTitle(window,title);
    setImage(0,0,bg,window,menu,positionMenu);
}
int menuLeftSon(Mix_Chunk *son,int type,char* move,int posY,int pos,int max,char* text1,char* text2,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
	if(strstr(move,"left")!=NULL&&pos!=-1){ pos--;}
    else if(strstr(move,"right")!=NULL&&pos!=max-1){pos++;}
    positionMenu.y=posY;
    for (int i = 0; i < max; i++)
    {
    	positionMenu.x=350+12*i;
    	if(i==pos-1||i==pos||i==pos+1){
        if(pos<i)menu = IMG_Load(getNameFile(DIRECT_IMAGE,text1));
        else menu = IMG_Load(getNameFile(DIRECT_IMAGE,text2));
        SDL_BlitSurface(menu,NULL,SDL_GetWindowSurface( window ),&positionMenu);
        SDL_UpdateWindowSurface( window );}
    }
    if(type==1)Mix_VolumeMusic(7*(pos+1));//change Volume
    if(type==2)Mix_VolumeChunk(son,7*(pos+1));
    return pos;
}
int menuUp(char* move,int vertical,int posY,int pos,int depart,int max,char* text1,char* text2,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
    if(strstr(move,"up")!=NULL){pos--;if(depart==1&&pos<=0||depart==0&&pos<0) pos=max-1;positionMenu.y=0;}
    else if(strstr(move,"down")!=NULL){pos++;if(depart==1&&pos>=max) pos=1;if(depart==0&&pos>=max) pos=0;positionMenu.y=0;}
    else if(strstr(move,"left")!=NULL){ pos--;if(pos<=0) pos=max-1;positionMenu.y=posY;}
    else if(strstr(move,"right")!=NULL){pos++;if(pos>=max) pos=1;positionMenu.y=posY;}
    for (int i = depart; i < max; i++)
    {
		if(pos!=i) menu = IMG_Load(getNameFile(DIRECT_IMAGE,convertName(text1,i,".png")));
        else menu = IMG_Load(getNameFile(DIRECT_IMAGE,convertName(text2,i,".png")));
        if(strstr(move,"up")!=NULL||strstr(move,"down")!=NULL) positionMenu.y=positionMenu.y+80;
        else positionMenu.x=250+80*i;
		if(vertical) positionMenu.x=10;
        SDL_BlitSurface(menu,NULL,SDL_GetWindowSurface( window ),&positionMenu);
        SDL_UpdateWindowSurface( window );
    }
    return pos;
}
void reloadGame(int posM2,float* joueurCase1,float* joueurCase2,float* joueurCase3,float* joueurCase4,int longArr,int* posDame,SDL_Window *window,SDL_Surface* menu,SDL_Rect positionMenu){
    if(posM2==1)
    initWindow("Mind Refresh","testBack.png",window,menu,positionMenu);
    else initWindow("Mind Refresh","testBack2.png",window,menu,positionMenu);
    reloadDame(joueurCase1,longArr,posDame[1],window,menu,positionMenu);
    reloadDame(joueurCase2,longArr,posDame[2],window,menu,positionMenu);
    if(posM2==2){
       	reloadDame(joueurCase3,longArr,posDame[3],window,menu,positionMenu);
       	reloadDame(joueurCase4,longArr,posDame[4],window,menu,positionMenu);
    }
}
void moveSelectDame(int joueur,int posM2,int* posDame,char* move,int longArr,float* joueurCase1,float* joueurCase2,float* joueurCase3,float* joueurCase4,float* lastMove,SDL_Window *window,SDL_Surface* menu2,SDL_Rect positionMenu2){
   	if (joueur%4==1)moveDame(posM2,posDame,move,longArr,joueurCase1,lastMove,window,menu2,positionMenu2);
      	if (joueur%4==2)moveDame(posM2,posDame,move,longArr,joueurCase2,lastMove,window,menu2,positionMenu2);
      	if(posM2==2){
          	if (joueur%4==3)moveDame(posM2,posDame,move,longArr,joueurCase3,lastMove,window,menu2,positionMenu2);
          	if (joueur%4==0)moveDame(posM2,posDame,move,longArr,joueurCase4,lastMove,window,menu2,positionMenu2);
      	}
   }
bool isFileVide(FILE* fichier){
	int caractereActuel = 0,nbLigne=0;
	if(fichier!=NULL){
    	do{
        	nbLigne++;
            caractereActuel = caractereActuel = fgetc(fichier);;
        } while (caractereActuel != EOF);
    	if(nbLigne<=1)return true;
    	return false;
    }else{
    	printf("%s\n","file not found" );
    	return true;
    }
}
bool saveData(nomJ* nomJoueur,FILE* fichier,int posM2,int longArr,float* joueurCase1,float* joueurCase2,float* joueurCase3,float* joueurCase4,int* score,int* posDame,int joueur){
	fichier = fopen("test.txt", "w");
	fprintf(fichier, "%d\n", posM2);
	fprintf(fichier, "%d\n", longArr);
	fprintf(fichier, "%d\n", joueur);
	fprintf(fichier, "%s\n", nomJoueur->nom1);
	fprintf(fichier, "%s\n", nomJoueur->nom2);
	fprintf(fichier, "%d\n", nomJoueur->indice1);
	fprintf(fichier, "%d\n", nomJoueur->indice2);
	if(posM2==2){
		fprintf(fichier, "%s\n", nomJoueur->nom3);
		fprintf(fichier, "%s\n", nomJoueur->nom4);
		fprintf(fichier, "%d\n", nomJoueur->indice3);
		fprintf(fichier, "%d\n", nomJoueur->indice4);
		for (int i = 0; i < longArr; i++)fprintf(fichier, "%f\n",joueurCase3[i] );
		for (int i = 0; i < longArr; i++)fprintf(fichier, "%f\n",joueurCase4[i] );
	}
	for (int i = 0; i < longArr; i++)fprintf(fichier, "%f\n",joueurCase1[i] );
	for (int i = 0; i < longArr; i++)fprintf(fichier, "%f\n",joueurCase2[i] );
	for (int i = 1; i < 5; i++)fprintf(fichier, "%d\n",score[i] );
	for (int i = 0; i < 5; i++)fprintf(fichier, "%d\n",posDame[i] );
		fclose(fichier);
		return true;
}
bool readData(nomJ* nomJoueur,FILE* fichier,int* posM2,int* longArr,float* joueurCase1,float* joueurCase2,float* joueurCase3,float* joueurCase4,int* score,int* posDame,int* joueur){
	fichier = fopen("test.txt", "r");
	fscanf(fichier, "%d", posM2);
	fscanf(fichier, "%d", longArr);
	fscanf(fichier, "%d", joueur);
	fscanf(fichier, "%s", &nomJoueur->nom1);
	fscanf(fichier, "%s", &nomJoueur->nom2);
	fscanf(fichier, "%d", &nomJoueur->indice1);
	fscanf(fichier, "%d", &nomJoueur->indice2);
	if(*posM2==2){
		fscanf(fichier, "%s", &nomJoueur->nom3);
		fscanf(fichier, "%s", &nomJoueur->nom4);
		fscanf(fichier, "%d", &nomJoueur->indice3);
		fscanf(fichier, "%d", &nomJoueur->indice4);
		for (int i = 0; i < *longArr; i++) fscanf(fichier, "%f", &joueurCase3[i]);
		for (int i = 0; i < *longArr; i++) fscanf(fichier, "%f", &joueurCase4[i]);
	}
	for (int i = 0; i < *longArr; i++)fscanf(fichier, "%f", &joueurCase1[i]);
	for (int i = 0; i < *longArr; i++)fscanf(fichier, "%f", &joueurCase2[i]);
	for (int i = 1; i < 5; i++)fscanf(fichier, "%d", &score[i]);
	for (int i = 0; i < 5; i++)fscanf(fichier, "%d", &posDame[i]);
	fclose(fichier);
	return true;
}
bool initWAV(Mix_Chunk *son,int ActuelVolume,SDL_Rect positionMenu){
	Mix_VolumeChunk(son,7*(ActuelVolume+1));
	return true;
}
void setLastMove(float* lastMove,int joueur,int posM2,float* joueurCase1,float* joueurCase2,float* joueurCase3,float* joueurCase4,int longArr){
	if(posM2==2){
        if(joueur%4==3){lastMove[0]=joueurCase3[getMinCase(joueurCase3,longArr)]+35;lastMove[1]=joueurCase3[getMinCase(joueurCase3,longArr)+1];}
        if(joueur%4==0){lastMove[0]=joueurCase4[getMaxCase(joueurCase4,longArr)]+35;lastMove[1]=joueurCase4[getMaxCase(joueurCase4,longArr)+1];}
    }
    if(joueur%4==1){lastMove[0]=joueurCase1[getMinCase(joueurCase1,longArr)]+35;lastMove[1]=joueurCase1[getMinCase(joueurCase1,longArr)+1];}
    if(joueur%4==2){lastMove[0]=joueurCase2[getMaxCase(joueurCase2,longArr)]+35;lastMove[1]=joueurCase2[getMaxCase(joueurCase2,longArr)+1];}
}
