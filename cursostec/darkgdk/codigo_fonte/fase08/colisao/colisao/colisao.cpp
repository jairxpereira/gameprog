// colisao.cpp
// Esse programa demonstra colisão de sprites
#include "DarkGDK.h"

// Protótipo das funções
void initsys();					// inicializa o sistema
void load_imagens();			// Carrega as imagens
void load_efeitos_sonoros();	// Carrega os efeitos sonoros
void menu();					// Mostra um menu de opções na tela
void controle_principal();		// Controle principal do jogo
void atualiza_tiro();			// atualiza posição do tiro disparado
void atualiza_inimigo();		// atualiza posição do inimigo
void mostrar_info();			// Mostrar status na tela
void mudar_cor_difusa(void);	// Muda a cor difusa do inimigo

// Cores
const int nPreto	= 0;
const int nBranco	= 0xFFFFFF;
const int nAzul		= 0x0000FF;

// Atores do jogo
const int sprt_jogador	= 1;
const int sprt_inimigo	= 2;
const int sprt_tiro		= 3;

// Efeitos sonoros
const int som_tiro		= 1;
const int som_explodiu	= 2;

// Controle do tiro disparado
int tiro_disparado	= 0;
int tiro_viajando	= 0;

int terminar_app	= 0;

// Controle do inimigo
int inimigo_distancia	= 0;
int inimigo_velocidade	=  2;
int inimigo_energia		= 100;

// String para mostrar texto
char info[255];

// Estrutura para posicionar as sprites inicialmente
struct Posicao
{
int xpos;
int ypos;
};

Posicao sprt[4]; // Criando 4 (0-3) estruturas de Posição

// ----------------------------------------------------------------------------
void DarkGDK ( void ){
// Começo da aplicação DarkGdk
initsys();
// Carrega imagens e efeitos sonoros
load_imagens();
load_efeitos_sonoros();
menu(); dbSync();
dbWaitKey();

while ( LoopGDK ( ) ) {
controle_principal();
if (terminar_app == 1) return;
dbSync ( );
} // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys(){
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowSize(600,480);
dbSetWindowPosition(160,50);
dbSetWindowTitle("colisao.cpp");
dbHideMouse();
dbSetCurrentBitmap(0);
} // fim da função: initsys()


// ----------------------------------------------------------------------------
void menu(){

// Variáveis de trabalho para mostrar texto
int xpos				= 260;
int ypos				= 40;
int coluna				= xpos;
int linha				= ypos;
int ncx					= 0;
int espaco_entrelinhas	= 20;


// Nossa lista de opções
char *slista[] = {"Setas - mover",
"Espaco - Atirar", 
"q/botao direito - sair"};

dbCenterText (320,10, "Space Invader Gameprog");

// Mostre a lista
 for (ncx = 0; ncx < 3; ncx++) {
 linha = ypos + ( ncx * espaco_entrelinhas );
 dbText (coluna, linha, slista[ncx]);
 } // fim do for(ncx)

 dbCenterText (320,240, "Pressione <enter> para continuar");

 dbSync();
} // menu().end

// ----------------------------------------------------------------------------
void controle_principal(){

// Posição inicial do jogador na tela
sprt[sprt_jogador].xpos = 300; sprt[sprt_jogador].ypos = 420;

// Posição inicial do inimigo na tela
sprt[sprt_inimigo].xpos = 300; sprt[sprt_inimigo].ypos = 10;

// Posição inicial do tiro alinhado com o jogador
sprt[sprt_tiro].xpos = sprt[sprt_jogador].xpos + 45;
sprt[sprt_tiro].ypos = 396;

// Elabora as sprites a partir das imagens
dbSprite (1, sprt[sprt_jogador].xpos, sprt[sprt_jogador].ypos, 1);
dbSprite (2, sprt[sprt_inimigo].xpos, sprt[sprt_inimigo].ypos, 2);
dbSprite (3, sprt[sprt_tiro].xpos, sprt[sprt_tiro].ypos, 3);

// Esconde a imagem do tiro
dbHideSprite (sprt_tiro);

// Controla leitura do controle_principal
while (dbMouseClick() != 2) {

 char *tecla = dbInKey();

 if (!strcmp(tecla,"q")) {
 terminar_app = 1;
 break;
 } // endif

 // Controla movimentação da sprite(2) - nosso 'player'
 if (dbDownKey()==1) 
	 dbOffsetSprite (sprt_jogador, 
	 dbSpriteOffsetX(sprt_jogador), 
	 dbSpriteOffsetY(sprt_jogador)-2 );

 if (dbUpKey()==1) 
	 dbOffsetSprite (sprt_jogador,
	 dbSpriteOffsetX(sprt_jogador),
	 dbSpriteOffsetY(sprt_jogador)+2);

 if (dbRightKey()==1) 
	 dbOffsetSprite (sprt_jogador,
	 dbSpriteOffsetX(sprt_jogador)-2 ,
	 dbSpriteOffsetY(sprt_jogador));

 if (dbLeftKey()==1) 
	 dbOffsetSprite (sprt_jogador,
	 dbSpriteOffsetX(sprt_jogador)+2,
	 dbSpriteOffsetY(sprt_jogador));

 // O espaço dispara o tiro
 if (dbSpaceKey()==1)
 {
	 if (tiro_disparado == 0)
	 {
	 tiro_disparado = 1;
	 tiro_viajando = 1; 
	 dbShowSprite (sprt_tiro);

	 // Configura posição do tiro conforme posição do jogador
	 int dx, dy;
	 dx = dbSpriteOffsetX(sprt_jogador);
	 dy = dbSpriteOffsetY(sprt_jogador);
	 dbOffsetSprite(sprt_tiro, dx, dy);	
	
	 }// Só dispara um tiro por vez

 }// endif (espaço) (tiro)

 if (tiro_viajando == 1) atualiza_tiro();

 atualiza_inimigo();

 // Se o tiro acertou o inimigo, reduza a energia dele
 if (dbSpriteHit (sprt_tiro, sprt_inimigo) == 1)
 {
	 inimigo_energia = inimigo_energia - 10;
	 dbPlaySound (som_tiro);
	
 } // endif

  // Se o jogador se matou, termine o jogo...
 if (dbSpriteHit (sprt_jogador, sprt_inimigo) == 1)
 {
	 
	 dbPlaySound (som_explodiu);
	 terminar_app = 1;
	 break;
	
 } // endif


// Se o inimigo 'morrer' toque o efeito sonoro e troque a cor dele
 if (inimigo_energia <= 0)
 {
 dbPlaySound (som_explodiu);
 inimigo_energia = 100;
 mudar_cor_difusa();
 } // endif
 
 // menu();
 mostrar_info();
 dbSync();
} // endwhile (leitura do controle_principal)

// Vamos liberar a memória
for (int item=1; item <= 3; item++) {
if (dbImageExist(item)) dbDeleteImage (item);
if (dbSpriteExist(item)) dbDeleteSprite (item);
} // fim do if

dbCLS(0); 
dbShowMouse();
dbCenterText (320,240, "Pressione a tecla <ESC> para finalizar");
dbSync();
dbWaitKey();
} // endfunc: controle_principal


void mostrar_info(void){
int dx, dy;
// Mostra posição do jogador
dx = dbSpriteOffsetX(sprt_jogador);
dy = dbSpriteOffsetY(sprt_jogador);
sprintf (info, "Jogador.pos: (%d, %d)",dx, dy);
dbText (10,60, info);

// Mostra posição do inimigo
dx = dbSpriteOffsetX(sprt_inimigo);
dy = dbSpriteOffsetY(sprt_inimigo);
sprintf (info, "Inimigo.pos: (%d, %d)", dx, dy);
dbText (10,80, info);

sprintf (info, "Inimigo.hp: %d", inimigo_energia);
dbText (10,100, info);

// Mostra a posição do mouse na janela
sprintf(info, "colisao.cpp - mouse: %d , %d",
dbMouseX(), dbMouseY());
dbSetWindowTitle (info);
} // mostrar_info()


void atualiza_tiro(void)
{
int dx = 0;
int dy = 0;

// Pega última posição da bala
dx = dbSpriteOffsetX(sprt_tiro);
dy = dbSpriteOffsetY(sprt_tiro);

// Avança bala pra frente
dbOffsetSprite (sprt_tiro, dx, dy + 2);

// Mostra posição do tiro na tela
sprintf(info, "tiro.pos: %d , %d", dx, dy+2);
dbText (320,400, info);

// Deleta tiro que sumiu da tela
if (dy > 400)
 {
 dbOffsetSprite (sprt_tiro, dx, 0);
 tiro_disparado = 0;
 tiro_viajando = 0;
 dbHideSprite(sprt_tiro);
 } // endif
	
} // atualiza_tiro()

void atualiza_inimigo(void)
{
int dx = 0;
int dy = 0;

// Faz contagem da distância
inimigo_distancia++;

// Pega posição do inimigo
dx = dbSpriteOffsetX(sprt_inimigo);
dy = dbSpriteOffsetY(sprt_inimigo);

// Inverte movimento nas fronteiras da tela
if (inimigo_distancia == 160)
 {
 inimigo_velocidade = inimigo_velocidade * -1;
 inimigo_distancia = -120;
 }

// Movimenta o inimigo na tela
dbOffsetSprite (sprt_inimigo, dx + inimigo_velocidade, dy);
} // atualiza_inimigo()


void mudar_cor_difusa(void){
int tr, tg, tb;
// Gera cor aleatória
tr = dbRnd(255); tg = dbRnd(255); tb = dbRnd(255);
// Configura individualmente cada canal de cor
dbSetSpriteDiffuse (sprt_inimigo,tr,tg,tb);
} // mudar_cor_difusa().fim

void load_imagens()
{
// As imagens tem um fundo preto
dbSetImageColorKey (0,0,0);
// Carrega as imagens
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\ship7.png", sprt_jogador);
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\alien3.png", sprt_inimigo);
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\bolt.png", sprt_tiro);
} // load_imagens()

void load_efeitos_sonoros()
{	
// Carrega os efeitos sonoros
dbLoadSound ("c:\\gameprog\\gdkmedia\\som\\shoot.wav",som_tiro);
dbLoadSound ("c:\\gameprog\\gdkmedia\\som\\explode.wav",som_explodiu);
} // load_efeitos_sonoros()
