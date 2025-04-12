//*********************************************************
//
// classe para fazer o carregamento de arquivos no formato BMP
// Autor: Cesar Tadeu Pozzer
//        pozzer@inf.ufsm.br
//
//  Referencia:  http://astronomy.swin.edu.au/~pbourke/dataformats/bmp/
//  Versao 09/2010
//
//**********************************************************

#ifndef ___BMP__H___
#define ___BMP__H___

#include <stdio.h>
#include <stdlib.h>


#include "gl_canvas2d.h"

#define HEADER_SIZE      14 //sizeof(HEADER) vai dar 16 devido ao alinhamento de bytes
#define INFOHEADER_SIZE  40 //sizeof(INFOHEADER) da 40 e esta correto.
#define uchar unsigned char

typedef struct {
   unsigned short int type;                 /* Magic identifier            */
   unsigned int size;                       /* File size in bytes          */
   unsigned short int reserved1, reserved2;
   unsigned int offset;                     /* Offset to image data em bytes*/
} HEADER;


typedef struct {
   unsigned int size;               /* Header size in bytes      */
   int width,height;                /* Width and height of image */
   unsigned short int planes;       /* Number of colour planes   */
   unsigned short int bits;         /* Bits per pixel            */
   unsigned int compression;        /* Compression type          */
   unsigned int imagesize;          /* Image size in bytes       */
   int xresolution,yresolution;     /* Pixels per meter          */
   unsigned int ncolours;           /* Number of colours         */
   unsigned int impcolours;         /* Important colours         */
} INFOHEADER;


class Bmp
{
private:


public:
 int imagesize, bytesPerLine, bits;
   unsigned char *data;

   float brilho;

   HEADER     header;
   INFOHEADER info;

   void load(const char *fileName);
   int width, height;
   Bmp(const char *fileName);
   uchar* getImage();
   int    getWidth(void);
   int    getHeight(void);
   void   convertBGRtoRGB(void);
   void render();

   void renderFlippedH();
   void renderFlippedV();
   void renderFlippedHV();

   int positionX;
   int positionY;

};

class Botao{
  float altura, largura, x, y;
  char label[100];

public:
  Botao(float _x, float _y, float _larg, float _alt, char *_label)
  {
     altura  = _alt;
     largura = _larg;
     x = _x;
     y = _y;
     strcpy(label, _label);
  }

  void render()
  {
      CV::color(0, 0, 1);
      CV::rectFill(x, y, x + largura, y + altura);
      CV::color(0, 0, 0);
      CV::text(x+5, y+altura/2, label); //escreve o label do botao mais ou menos ao centro.
  }

  //recebe as coordenadas do mouse para tratar clique ou detectar quando o mouse esta em cima do botao
  bool Colidiu(int mx, int my)
  {
      if( mx >= x && mx <= (x + largura) && my >= y && my <= (y + altura) )
      {
          return true;
      }
      return false;
  }

};

class CheckBox{
  float lado, x, y;  //CheckBox será quadrada


public:

    bool ativa;
  CheckBox(float _x, float _y, float _lado)
  {
     lado  = _lado;
     x = _x;
     y = _y;
  }

   void toggle(CheckBox *cb);

  void render()
  {
      CV::color(0, 0, 1);
      CV::rectFill(x, y, x + lado, y + lado);

      //Controla o display de estado
      if(ativa == true){
      CV::color(1, 0.647, 0);
            CV::rectFill(x+(lado*0.1), y+(lado*0.1), x + lado - (lado*0.1), y + lado - (lado*0.1));
                CV::color(0, 0, 0);}
      else
        {
         CV::color(1, 1, 1);
            CV::rectFill(x+(lado*0.1), y+(lado*0.1), x + lado - (lado*0.1), y + lado - (lado*0.1));
                }
}


  //recebe as coordenadas do mouse para tratar clique ou detectar quando o mouse esta em cima do botao
  bool Colidiu(int mx, int my)
  {
      if( mx >= x && mx <= (x + lado) && my >= y && my <= (y + lado) )
      {
          return true;
      }
      return false;
  }


};

class PainelDeCamadas
{
public:
    int x, y, largura, altura, nmrCamadas;


    PainelDeCamadas(int _x, int _y, int _largura, int _altura, int _nmrCamadas)
  {
     x =  _x;
     y =  _y;



     largura = _largura;
     altura = _altura;

     nmrCamadas = _nmrCamadas;

  }

  void renderizaCamada(int x1, int y1, int x2, int y2, int c)
  {
            char temp[8] = "Camada ";
            temp[7] = 48 + (nmrCamadas - c);
            CV::color(0, 0, 0);
            if(nmrCamadas-c == 1)
                {
                     CV::color(1, 0, 0);
                     CV::rectFill(x1, y1, x2, y2);
                     CV::color(0, 0, 0);
                }
            CV::rect(x1, y1, x2, y2);
            CV::text(x1+(x2-x1)*0.1, y1+(y2-y1)*0.4, temp);



  }

    void render()
    {

       CV::color(0, 0, 0);
       CV::rect(x, y, x + largura, y + altura); //fundo do painel

       //renderiza o painel de camadas com base no numero de camadas
       for(int i = 0; i<nmrCamadas; i++)
        {

          renderizaCamada(x, y+altura*1/nmrCamadas*i, x + largura, y + altura*1/nmrCamadas*(i+1), i);

        }


    }


};

#endif
