#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "Map.h"
#include <ctype.h>
#include <string.h>

typedef struct{
  char code[1000];
  char nombre[2000];
  char texto[1000000];
  int chars;
  int words;
}libro;

typedef struct{
  char palabra[200];
  int repite;
}palabras;


char * _strdup(const char * str) {
    char * aux = (char *)malloc(strlen(str) + 1);
    strcpy(aux, str);
    return aux;
}

int lower_than_string(void* key1, void* key2){
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)==0) return 1;
    return 0;
}


void interfaz();
void TextoReal(char*, int*);
void CargarDocumentos(List*, Map*);
void mostrarDocumentos(List*);


int main(void) {
  List* L= create_list();
  Map* M= createMap(lower_than_string);
  Map* Carritos= createMap(lower_than_string);
  int n;
  int cont=0;
  interfaz();
  printf("\n ¿Desea realizar alguna accion?\n");
  scanf ("%d", &n); 
  while (n!=0) {
      switch (n){

        case 1: CargarDocumentos(L, M); break;

        case 2: mostrarDocumentos(L); break;

        case 4:  break;

        case 5:  break;

        case 3:  break;

        case 6:  break;
        
        case 7:  break;

        default: printf("Opción incorrecta, por favor ingrese numero correcto\n"); break;
      }
      cont++;
      if (cont==3){
        interfaz();
        cont=0;
      }
      printf("\n¿Desea realizar otra accion?\n");
      scanf ("%d", &n);
    }
  clear(L); //Liberar el espacio usado
  printf("\n---------------------------------\n");
  printf("         Hasta la próxima       \n");
  printf("---------------------------------\n");
  return 0;
}

//FUNCION 1
void CargarDocumentos(List* L, Map* M){
  char txt[200];

  printf("\nIngrese las claves de libros que desees guardar\nen un archivo txt (Las claves deben tener .txt al final)\n");
  printf("\nIngrese nombre del txt a leer:");
  
  scanf("%s", txt);
  FILE *claves= fopen(txt, "r");

  if(claves==NULL){
    printf("\nError al abrir el archivo\n");
    return;
  }

  char lect[200], txt2[10000];
  char AUXclave[10], AUXnombre[30];
  int a, b, x, i=0;
  libro* guardo;

  
  while(fscanf(claves, "%199[^\n]s", lect)){
    guardo=(libro*) malloc(sizeof(libro));
    fgetc(claves);
    
    //limpieza
    for (a=0; a<10; a++)
      AUXclave[a]='\0';
    for(a=0; a<30; a++)
      AUXnombre[a]='\0';

    //Guardamos la clave
    for (a=0; lect[i]!=' '; a++, i++)
      AUXclave[a]=lect[i];
    i++;
    strcpy(guardo->code, AUXclave);
   

    //Trabajaremos con el achivo con la clave obtenida
    FILE *libros=fopen(AUXclave, "r");
    if(libros==NULL){
      printf("Error archivo ID:%s no se a encontrado\n", AUXclave);
      return;
    }
    fscanf(libros, "%9999[^\n]s", txt2);
     
    //Guardar los datos
    for(x=31, b=0; txt2[x]!='\n'; x++, b++){
      AUXnombre[b]=txt2[x];
    }

    char aux[10000];
    b=0;
    
    for(x=0; txt2[x]!='*'; x++){
        aux[x]=txt2[x];
    }
    while(txt2[x]!=EOF){
      aux[b]=txt2[x];
       b++;
       x++;
    }  
    if (txt2[x]=='*')
      break;
    
    
    //TextoReal(txt2, &x);
    
    strcpy(guardo->nombre, AUXnombre);
    strcpy(guardo->texto, txt2);
    guardo->chars=x;
    
    insertMap(M, guardo->nombre, guardo); //Guardamos los datos con el nombre como clave
    nextMap(M);
    push_back(L, guardo);    
    printf("Archivo ID:%s guardado\n", guardo->code);
    if(fclose(libros)==EOF) 
      printf("Error al cerrar el libro\n");
  }
 
  printf("\n----------------------------\n");
  printf("Archivo leído exitosamente\n");
  printf("----------------------------\n");

  //Para asegurar que se cerro el archivo...
  if(fclose(claves)==EOF) 
    printf("Error al cerrar el archivo\n");
}

//FUNCION 2
void mostrarDocumentos(List* L){
    libro* aux= first(L);
  
    if(aux==NULL){ // se valida si existen Productos para mostrar
      printf("-----------------------------\n");
      printf("No se han encontrado libros, vuelva a intentarlo\n");
      printf("-----------------------------\n");
    }else{
      while(aux){
        printf("ID:%s\nTitulo:%s\nCantidad de caracteres:%d\n", aux->code, aux->nombre, aux->chars);
        aux=next(L);
      }
    }

}


void TextoReal(char* txt2, int* x){
  char aux[50000];
  int i, j, y=0;
  for (i=0; txt2[i]!='*'; i++){
    aux[i]=txt2[i];
  }
  
  for(j=i+65; txt2[j]!='*'; j++, y++){
    aux[y]=txt2[j];
  }
  i=j-i;
  x=&i;
  for(i=0; txt2[i]!=EOF; i++)
    txt2[i]='\0';
  
  for(i=0; aux[i]!=EOF; i++)
    txt2[i]=aux[i];
}

void interfaz(){
  printf("________________________________\n");
  printf("    INDEXADOR DE LIBROS V1.1    \n");
  printf("________________________________\n");
  printf(" 1) Cargar Documentos           \n");
  printf(" 2) Mostar Documentos           \n");
  printf(" 3) Buscar por Titulo           \n");
  printf(" 4) Buscar Palabras Frecuentes  \n");
  printf(" 5) Palabras Más Relevantes     \n");
  printf(" 6) Buscar libro por Palabras   \n");
  printf(" 7) Buscar Contexto (Palabra)   \n");
  printf(" 0) Salir                       \n"); 
}