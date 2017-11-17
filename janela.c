/** Módulo janela.
	Responsável por criar a janela do jogo e pela interação dos componentes do jogo.
*/

#include"SDL.h"/**Biblioteca SDL para desenvolvimento do jogo.*/
#include"SDL_ttf.h"/**Biblioteca para a utilização de textos na janela do jogo.*/
#include"SDL_image.h"/**Biblioteca para a utilização de imagens PNG na janela do jogo.*/
#include"janela.h"
#include"Falcon.h"
#include"Hiero.h"
#include"Obstaculo.h"
#include"Inimigo.h"
#include"Escrita.h"
#include<stdbool.h>


void construtor(int x, int y,int estado){
/** Função que constrói a janela do jogo e apresenta o menu.*/
	int z, w, ponto = 0;
	
	SDL_Window* window;/** Variável para janela do jogo.*/
	SDL_Renderer* renderer;/** Variável para renderização dentro da janela do jogo.*/
	SDL_Rect drect = {0, 0, 640, 480};/** Cria um retângulo para plano de fundo do menu.*/
	SDL_Event evento;/** Variável para reconhcer eventos do mouse ou teclado.*/
	IMG_Init(IMG_INIT_PNG);/** Inicia a apresentação de imagens PNG da biblioteca SDL_image.*/
	SDL_Init(SDL_INIT_EVERYTHING);/** Inicida as funções da bibloteca SDL responsável pela janela do jogo.*/
	TTF_Init();/** Inicia a apresentação de texto da biblioteca SDL_ttf.*/
	SDL_Surface* jogar = IMG_Load("jogar.png");/** Carrega uma imagen na janela do jogo.*/
	SDL_Surface* placar = IMG_Load("placar.png");/** Carrega uma imagen na janela do jogo.*/
	SDL_Surface* sair = IMG_Load("sair.png");/** Carrega uma imagen na janela do jogo.*/
	SDL_Rect rectJogar = {200, 80,jogar->w,jogar->h};/** Responsável pelo tamanho e posição de uma imagen na janela do jogo.*/
	SDL_Rect rectPlacar = {200, 200,placar->w,placar->h};/** Responsável pelo tamanho e posição de uma imagen na janela do jogo.*/
	SDL_Rect rectSair = {200, 310,sair->w,sair->h};/** Responsável pelo tamanho e posição de uma imagen na janela do jogo.*/
	SDL_Texture* textJogar; /** Variável para a criação da textura de uma imagen na janela do jogo.*/
	SDL_Texture* textPlacar;/** Variável para a criação da de uma imagen na janela do jogo.*/
	SDL_Texture* textSair;/** Variável para a criação da de uma imagen na janela do jogo.*/

	window = SDL_CreateWindow("Jogo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, 0);/** Cria a janela do jogo.*/
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);/** Cria o renderizador da janela.*/
	SDL_SetRenderDrawColor(renderer, 192, 159, 45, 255);/** Define a cor para renderizar*/
	SDL_RenderClear(renderer);/** Limpa o renderizador*/
	textJogar = SDL_CreateTextureFromSurface(renderer, jogar);/** Cria uma textura a partir de uma imagem.*/
	textPlacar = SDL_CreateTextureFromSurface(renderer, placar);/** Cria uma textura a partir de uma imagem.*/
	textSair = SDL_CreateTextureFromSurface(renderer, sair);/** Cria uma textura a partir de uma imagem.*/
				
	SDL_RenderCopy(renderer, textJogar, NULL, &rectJogar);/** Renderiza a textura.*/
	SDL_RenderCopy(renderer, textPlacar, NULL, &rectPlacar);/** Renderiza a textura.*/
	SDL_RenderCopy(renderer, textSair, NULL, &rectSair);/** Renderiza a textura.*/
	SDL_RenderPresent(renderer);/** Apresenta a renderização na janela do jogo.*/
	SDL_FreeSurface(jogar);
	SDL_FreeSurface(placar);
	SDL_FreeSurface(sair);
				
	while(SDL_WaitEvent(&evento)){
	/** Loop que espera o input do mouse de um usuário.*/
       	switch(evento.type){/** Switch para o input.*/
            case SDL_QUIT:/** Caso o jogador pressione o botão para fechar a janela.*/
				SDL_DestroyTexture(textJogar);
				SDL_DestroyTexture(textPlacar);
				SDL_DestroyTexture(textSair);
                destrutor(window, renderer);
                break;
            case SDL_MOUSEBUTTONDOWN:/** Caso o jogador de algum input de mouse na tela.*/
				z = evento.button.x;
				w = evento.button.y;
				if((z > 225) && (z < 417) && (w > 100) && (w < 190)){/** Condição quando o jogador clica em jogar.*/
					SDL_DestroyTexture(textJogar);
					SDL_DestroyTexture(textPlacar);
					SDL_DestroyTexture(textSair);
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderClear(renderer);
					ponto = update(window,renderer);/** Começa o jogo e retorna a pontuação depois que o jogo for terminado.*/
					InsereNome(ponto,window,renderer);
				}
				if((z > 225) && (z < 370) && (w > 325) && (w < 410)){/** Condição para quando o jogador clicar em sair.*/
					SDL_DestroyTexture(textJogar);
					SDL_DestroyTexture(textPlacar);
					SDL_DestroyTexture(textSair);
					destrutor(window, renderer);
				}
				break;
					
		}
	}

	destrutor(window, renderer);/* Destrói a janela do jogo.*/
}

int update(SDL_Window* window,SDL_Renderer* renderer){
/** Função responsável por todo o funcionamento do jogo.*/
	int alt=0 ,x = 50, y = 49, y1 = 49, altura = 1, k = -10, m = 0, k1 = -20, m1 = 0, k2 = -20, m2 = 0, flag = 0, flag1 = 0, flag2 = 0,flag3 =0;
	int score = 0, temp, running = 1;
	char pontos[12];
	char aux[8];
	int* j = &k;
	int* j1 = &k1;
	int* j2 = &k2;
	int* l = &m;
	int* l1 = &m1;
	int* l2 = &m2;
	SDL_Color amarelo = {203,211,0};
	SDL_Surface* surfScore;/** Superfície para o score do jogo.*/
	SDL_Texture* textScore;/** Textura para o score do jogo.*/
	SDL_Rect posScore = {40,430 , 0, 0};
	SDL_Event event;
	TTF_Font* sans = TTF_OpenFont("Sans.ttf", 24); /** Cria a fonte para escrita na tela do jogo.*/
	
	while(event.type!= SDL_QUIT){/** Enquanto o jogador não clicar no botão de sair, o jogo continua rodando.*/
		SDL_PollEvent(&event);
        if (flag == 0){
			m = (rand() % 640) + 360;
		}
		if (flag1 == 0){
			m1 = (rand() % 640) + 60;
		}
		if (flag2 ==  0){
			m2 = (rand() % 640) + 160;
		}
		if (flag3 == 0){
			alt = (rand() % 3);
		}
		temp = render(alt, x, y, y1, j, l, j1, l1, j2, l2, altura, renderer);
		if (temp == 10){
			SDL_FreeSurface(surfScore);
			SDL_DestroyTexture(textScore);
			return score;

		}
		score  = score + temp;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer,&posScore);
		strcpy(pontos,  "SCORE: ");
		sprintf(aux, "%d", score);
		strcat(pontos, aux);
		surfScore = TTF_RenderText_Solid(sans, pontos, amarelo);
		textScore = SDL_CreateTextureFromSurface(renderer, surfScore);
		posScore.w = surfScore->w;
		posScore.h = surfScore->h;
		SDL_FreeSurface(surfScore);
		SDL_RenderCopy(renderer, textScore, NULL, &posScore);
		SDL_RenderPresent(renderer);
		SDL_DestroyTexture(textScore);
		SDL_Delay(5);
		flag = 1;
		flag1 = 1;
		flag2 = 1;
		flag3 = 1;
		switch(event.type){/** Switch para input do usuário durante o jogo.*/
            case SDL_KEYDOWN:/** Case para a tecla pressionada pelo usuário.*/
                switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                    	if((x > 0) && (y > 0)){
                        	x -= 2;
							y -= 2;
							y1 -= 2;
                        }
                        break;
                    case SDLK_RIGHT:
                    	if((x < 630) && (y < 320)){
                        	x += 2;
							y += 2;
							y1 += 2;
                        }
                        break;
                    case SDLK_UP:
                    	if((altura < 2) && (y > 10)){
                        	y -= 15;
                        	altura++;
                    	}
                        break;
                    case SDLK_DOWN:
                    	if((altura > 0) && (y < 316)){
                        	y += 15;
                        	altura--;
                        }
                        break;
                    default:
                        break;
            }
        }
		if((k2 < 325) && (m2 < 550)){
			k2 = k2 + 2; 
			m2 = m2 - 2;
		}else{
			k2 = -20, m2 = 0,flag2 = 0;
		}
		
		if((k1 < 325) && (m1 < 550)){
			k1++, m1--;
		}else{
			k1 = -20, m1 = 0,flag1 = 0;
		}

		if((k < 350) && (m < 550)){
			k++, m--;
		}else{
			k = -20, m = 0,flag = 0;
		}

		SDL_Delay(5);
	}
	
	destrutor(window, renderer);
}

int render(int alt, int x, int y, int y1, int* j, int* l, int* j1, int* l1 ,int* j2, int* l2, int altura, SDL_Renderer* renderer){
/** Função para renderizar todos os componentes do jogo.*/
	int ponto = 0;
	SDL_Rect drect = {0, 0, 640, 380};
	SDL_SetRenderDrawColor(renderer, 255, 255, 140, 255);
	SDL_RenderFillRect(renderer, &drect);/** Plano de fundo durante o jogo.*/
	
	SDL_Texture* Hiero = ConstroiHiero(j,l, renderer);/** Constrói o componente Hiero.*/
	SDL_Texture* Obstaculo = ConstroiObstaculo(j1, l1, renderer);/** Constrói o componente Obstáculo.*/
	SDL_Texture* Inimigo = ConstroiInimigo( j2, l2, renderer);/** Constrói o componente Inimigo.*/
    SDL_Texture* Falcon = ConstroiFalcon(x, y, renderer, altura);/** Constrói o componente Falcon.*/
	
		
    if ((ChecaColisao(Falcon, Hiero, x, y, j,l)== true) && altura==0){/** Checa a colisão entre o falcon e o hiero.*/
		*j=0;
		*l = (rand() % 640) + 360;
		ponto += 1;
        DestroiHiero(Hiero);
    }
	else if((ChecaColisao(Falcon, Obstaculo, x, y, j1,l1)== true) && altura==0){/** Checa a colisão entre o falcon e o obstáculo.*/
		DestroiObstaculo(Obstaculo); 
		DestroiFalcon(Falcon);
		return 10;

	}
	else if((ChecaColisao(Falcon, Inimigo, x, y, j2,l2)== true) && altura==alt){/** Checa a colisão entre o falcon e o inimigo.*/
		DestroiObstaculo(Inimigo); 
		DestroiFalcon(Falcon);
		
		return 10;

	}
	return ponto;
}

void destrutor(SDL_Window* window, SDL_Renderer* renderer){
/** Função para destruir a janela do jogo.*/

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}