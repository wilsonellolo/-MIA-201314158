#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "stdio.h"
#include <time.h>
#include "exec.h"
#define TRUE 1

//STRUCTS
typedef struct{
    int  part_status;
    char part_type[100];
    char part_fit[100];
    int  part_start;
    int  part_size;
    char part_name[25];
}partition;

typedef struct{
    int mbr_tamanio;
    char mbr_fecha_creacion[128];
    int mbr_disk_signature;
    partition mbr_partition1;
    partition mbr_partition2;
    partition mbr_partition3;
    partition mbr_partition4;
}mbr;

typedef struct{
    int part_status;
    char part_fit[100];
    int part_start;
    int part_size;
    int part_next;
    char part_name[25];
}ebr;

char* comprobarcadena[200];
/*
FASE 1
La fase 1 se entregará el día viernes 12 de agosto antes de las 23:50 PM, al correo deben enviar el link
de su repositorio en github, para su descarga (tomen en cuenta que se ve la fecha de la última
modificación). Asunto: [MIA]Fase1_carné
Pares: 201212838@ingenieria.usac.edu.gt e Impares: Georgina.estrada78@gmail.com
1. Administración de disco
1.1. Mkdisk LISTO
1.2.Rmdisk LISTO
1.3. Fdisk
1.4.Mount
1.5.Umount
2. Reportes (Esenciales para calificación)
2.1. Mbr
2.2. Disk
2.3. Exec LISTO
*/
int main()
{
    char cadena[300];


    printf("Ingrese Orden\n");

    while(TRUE==1){

        fgets(cadena,300,stdin);

        char *quitarsalto=strtok(cadena,"\n\t");
        strcpy(cadena,quitarsalto);
        leerComandos(cadena);


    }

  return 0;
}




//METODOS FASE 1

int leerComandos(char *cadena[300]){
   char CadenaSalto[100];
    char Comando[300];
    strcpy(CadenaSalto,"");

if(strstr(cadena,"#")){
            return -1;
        }

        int HaySalto =0;

        while(strstr(cadena,"\\")){
            char *token =strtok(cadena,"\\\n\t");
            strcat(CadenaSalto,token);
            strcat(CadenaSalto," ");
            fgets(cadena,300,stdin);
            HaySalto=1;
        }

        if(HaySalto==1){
            strcpy(Comando,CadenaSalto);
            strcat(Comando," ");
            strcat(Comando,cadena);
        }else{
            strcpy(Comando,cadena);
        }

        strcpy(cadena,"");
        strcpy(CadenaSalto,"");

       //COMANDO YA TIENE LA CADENA COMPLETA;

       char *Minuscula;
       for(Minuscula = Comando; *Minuscula; Minuscula++){
            *Minuscula = tolower((unsigned char)*Minuscula);
            }


        // LA CADENA COMANDO YA ESTA TODA EN MINUSCULAS
        strcpy(comprobarcadena,Comando);
        char *token =strtok(Comando," ");

        //TOKEN CONTIENE LA PRIMERA ORDEN

        //ACONTINUACION SE LLAMA A EL METODO SEGUN LA ORDEN

        if(strcmp(token,"mkdisk")==0){
            mkdisk(token);
        }
        else if(strcmp(token,"rmdisk")==0){
            rmdisk(token);
        }
       /* else if(strcmp(token,"fdisk")==0){
            fdisk();
        }
        else if(strcmp(token,"mount")==0){
            mount();
        }
        else if(strcmp(token,"umount")==0){
            umount();
        }
        else if(strcmp(token,"rep")==0){
            rep();
        }*/
        else if(strcmp(token,"exec")==0){
            exec(token);
        } else if(strcmp(cadena,"\n")==0){ return 8;}

        return 0;
}

int exec (char *token){

    char path[150]="";
    int veces=0;

    while(token!=NULL){
        token=strtok(NULL," :\"\n");

        if(token==NULL){
            break;
        }
        strcpy(path,token);
        veces++;

    }

     FILE *file1;

    char *c1;
    char cadena[100]="";


    file1=fopen(path,"r");

    if(file1 ==NULL){
        printf("\nArchivo de Script inexistente\n");
        return -1;
    }

    while(c1=fgets(cadena,200,file1)){
       printf("%s\n",cadena);
       char *quitarsalto=strtok(cadena,"\n\t");
        strcpy(cadena,quitarsalto);
       leerComandos(cadena);
    }

       fclose(file1);

return 0;
}

int mkdisk(char*token){

char size[20]="-size";
char unit[20]="+unit";
char path[20]="-path";
char name[20]="-name";

//COMPROBANDO QUE TIENE LOS PARAMETROS OBLIGATORIOS
if(strstr(comprobarcadena,size) &&strstr(comprobarcadena,name)&& strstr(comprobarcadena,path)){
}else{
printf("\nComando No cuenta con parametros minimos\n");
return -1;
}


char comillas[2]="\"";
int control=0;
int tamanioDeDisco;
char unitletra[5]="m";
char Nombre[200];
char direccionPath[200];
char direccionPath2[200];
char direccionPath3[200];
while(token !=NULL){

    token = strtok(NULL," ::");
    if(token==NULL) break;

    char *estaSize;
    char *estaUnit;
    char *estaPath;
    char *estaName;

    estaSize = strstr(token,size);
    estaUnit = strstr(token,unit);
    estaPath = strstr(token,path);
    estaName = strstr(token,name);

    if(estaSize) control=1;
    if(estaUnit) control=2;
    if(estaPath) control=3;
    if(estaName) control=4;

    switch(control){
    case 1:
        token = strtok(NULL," :");
        tamanioDeDisco=atoi(token);
        if(tamanioDeDisco <=0){
            printf("\nTamaño De Disco Invalido\n");
         return -1;
        }
        break;
     case 2:
        token= strtok(NULL," ::");
        strcpy(unitletra,token);
        if((strcmp(unitletra,"m") == 0) || (strcmp(unitletra,"k") == 0)){
        }else{
            printf("\nUnidad Invalida.\n");
            return -1;
        }
        break;
     case 3:

        token = strtok(NULL," ::");

        if(strstr(token,comillas)){

            token=strtok(NULL,"\"");
            strcpy(direccionPath,token);
            strcpy(direccionPath2,direccionPath);
            strcpy(direccionPath3,direccionPath);
        }else{
            strcpy(direccionPath,token);
            strcpy(direccionPath2,token);
            strcpy(direccionPath3,token);
        }

        break;


    case 4:
        token = strtok(NULL," ::");

        if(strstr(token,comillas)){
            token=strtok(NULL,"\"");
            strcpy(Nombre,token);

        }else{
            strcpy(Nombre,token);
        }

        if(strstr(Nombre,".dsk")){
        printf("\nNombre verificado\n");
        }else{
        printf("\nExtension de nombre invalida\n");
       return -1;
        }


        break;

      default:
        printf("\nAccion invalida o Inexistente.\n");

        return -1;

        break;
    }
}
    //SE CREA EL PATH

    strcat(direccionPath,Nombre);
    strcat(direccionPath2,Nombre);
    strcat(direccionPath3,Nombre);
    int numPalabras =1;
    char *tem;
    tem =strtok(direccionPath,"/");

    while(tem!=NULL){
        tem =strtok(NULL,"/");
        if(tem==NULL) break;
        numPalabras++;
    }

    char pathReal[200]="/";
    char*aux11;
    aux11= strtok(direccionPath2,"/");
    strcat(pathReal,aux11);
    strcat(pathReal,"/");
    while(numPalabras > 2)
    {
        aux11 = strtok(NULL,"/");
        strcat(pathReal,aux11);
        strcat(pathReal,"/");
        mkdir(pathReal ,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        numPalabras--;
    }

    aux11 = strtok(NULL,"/");

    mbr *mbr1 =(mbr*)malloc(sizeof(mbr));
    FILE *archivo = fopen(direccionPath3,"wb");

    //obteniendo fecha del sistema
    timer_t tiempo = time(0);
    struct tm *tlocal=localtime(&tiempo);
    char output[128];
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);

    strcpy(mbr1->mbr_fecha_creacion,output);

    int random = rand();
    mbr1->mbr_disk_signature=random;


    mbr1->mbr_partition1.part_size =0;
    mbr1->mbr_partition2.part_size =0;
    mbr1->mbr_partition3.part_size =0;
    mbr1->mbr_partition4.part_size =0;
    mbr1->mbr_partition1.part_start=0;
    mbr1->mbr_partition2.part_start=0;
    mbr1->mbr_partition3.part_start=0;
    mbr1->mbr_partition4.part_start=0;

    strcpy(mbr1->mbr_partition1.part_type,"x");
    strcpy(mbr1->mbr_partition2.part_type,"x");
    strcpy(mbr1->mbr_partition3.part_type,"x");
    strcpy(mbr1->mbr_partition4.part_type,"x");



    if(strcmp(unitletra, "k")==0){
       mbr1->mbr_tamanio= tamanioDeDisco*1024;
       //fseek(archivo,0,SEEK_SET);
       fwrite(mbr1,sizeof(mbr),1,archivo);
       int h =0;
       for(h; h<320*tamanioDeDisco;h++){
           fputs("\\0",archivo);
       }
    }else if(strcmp(unitletra,"m") == 0){
           mbr1->mbr_tamanio=tamanioDeDisco*1024*1024;
           //fseek(archivo,0,SEEK_SET);
           fwrite(mbr1,sizeof(mbr),1,archivo);
           int i=0;
           for(i;i< 2*(500*tamanioDeDisco*500);i++){
               fputs("\\0",archivo);
           }

}
    printf("\nDisco creado Con exito\n");
fclose(archivo);
/**************************/

mbr *mbrLeido=(mbr*)malloc(sizeof(mbr));
FILE *archivo1 =fopen(direccionPath3,"rb");
fread(mbrLeido,sizeof(mbr),1,archivo1);
int t= sizeof(mbrLeido);
printf("\ntamannio: %d\n", mbrLeido->mbr_tamanio);

fclose(archivo1);
return 1;
/**************************/


}

int rmdisk(char *token){
    token = strtok(NULL," :");
char* path[200];

if(strstr(token,"-path")){

}
else{
    printf("\nComando de path invalido\n");
    return -1;
}

token =strtok(NULL,":");
strcpy(path,token);

if(strstr(token,"\"")){

  token=strtok(token,"\"");

  strcpy(path,token);

}


FILE* ArchivoBorrar =fopen(path,"r");
printf(path);
if(ArchivoBorrar){
    printf("\nSeguro que desea eliminar disco (escriba si o no):\n");
    char *confirmacion[10];
    fgets(confirmacion,10,stdin);
    char *quitarsalto=strtok(confirmacion,"\n");
    strcpy(confirmacion,quitarsalto);

    if(strcmp(confirmacion,"si")==0){
        remove(path);
        printf("\nDisco eliminado\n");

    }else if(strcmp(confirmacion,"no")==0){
       printf("\nDisco No eliminado\n");
       fclose(ArchivoBorrar);
    }else{
        printf("\nRespuesta invalida, no se ejecuto ninguna accion.\n");
        fclose(ArchivoBorrar);
    }

}else{
    printf("\nArchivo a Borrar No Existe\n");
}

return 1;

}

int fdisk(char *token){

    int    op = 0;
    int    size1=0;
    char*  unit1[5];
    char*  path1[200];
    char*  type1[5];
    char*  fit1[5];
    char*  delete1[20];
    char*  name1[50];
    int    add1=0;
    char*  add11[20];
    int  Menos=0;
    int delete11=0;

    //aca se mira si hay comandos incompatibles
    if(strstr(comprobarcadena,"add") && strstr(comprobarcadena,"delete") || strstr(comprobarcadena,"add") && strstr(comprobarcadena,"size") || strstr(comprobarcadena,"size") && strstr(comprobarcadena,"delete")){
   printf("\nError comandos Incompatibles\n");
   return -1;
   }
   //SE VERIFICA QUE ESTE TODA LA INFORMACION DE SIZE
    if(strstr(comprobarcadena,"-size")){

       if(strstr(comprobarcadena,"-path") && strstr(comprobarcadena,"-name")){

       }else{
           printf("\nFalta Informacion\n");
           return -1;
       }
   }
   //SE VERIFICA QUE ESTE TODA LA INFORMACION DEL DELETE
    if(strstr(comprobarcadena,"+delete")){


       if(strstr(comprobarcadena,"-path") && strstr(comprobarcadena,"-name")){

       }else{
           printf("\nFalta Informacion\n");
       return -1;
       }
   }
    //SE VERIFICA QUE ESTE TODA LA INFORMACIOND EL ADD
    if(strstr(comprobarcadena,"+add")){
      if(strstr(comprobarcadena,"-path") && strstr(comprobarcadena,"-name")){

       }else{
           printf("\nFalta Informacion\n");
       return -1;
       }

   }
    //SE COLOCAN LOS VALORES POR DEFECTO

    strcpy(fit1,"wf");
    strcpy(unit1,"k");
    strcpy(type1,"p");


    //SE ANALIZA LA CADENA A EJECUTAR
     while(token !=NULL){
        token=strtok(NULL," :");
        if(token==NULL) break;
        if(strstr(token,"-size"))    op=1;
        if(strstr(token,"+unit"))    op=2;
        if(strstr(token,"-path"))    op=3;
        if(strstr(token,"+type"))    op=4;
        if(strstr(token,"+fit"))     op=5;
        if(strstr(token,"+delete"))  op=6;
        if(strstr(token,"-name"))    op=7;
        if(strstr(token,"+add"))     op=8;
     switch(op){
      case 1:
        token=strtok(NULL," :");
        size1=atoi(token);
        if(token==NULL){
        printf("\nComando invalido o mal escrito\n");
        return -1;
        }else if(size1 <=0){
            printf("\nTama;o de particion invalido\n");
            return -1;
        }
          break;
      case 2:
        token=strtok(NULL," :");
        strcpy(unit1,token);
        if(token==NULL){
        printf("\nComando invalido o mal escrito\n");
        return -1;
        }else if(strcmp(unit1,"m")!=0 && strcmp(unit1,"k")!=0 && strcmp(unit1,"b")!=0){

            printf("\nUnidad  invalida.\n");
            return -1;
        }
        break;
      case 3:
          token = strtok(NULL,": ");
      char *tok;
      if(strstr(token,"\"")){
        tok=strtok(token,"\"");
        strcpy(path1,tok);
      }else{
          strcpy(path1,token);
      }
      FILE* comprobar =fopen(path1,"r");
      if(comprobar){
      fclose(comprobar);
      }else{
      printf("\nArchivo Inexistente\n");
      return -1;
      }

          break;
      case 4:
          token=strtok(NULL," :");
          strcpy(type1,token);
          if(strcmp(type1,"p")!=0 && strcmp(type1,"e")!=0 && strcmp(type1,"l")!=0){
              printf("\nTipo de particion invalida\n");
              return -1;
          }
          break;
      case 5:
          token =strtok(NULL," :");
          strcpy(fit1,token);
          if(strcmp(fit1,"bf")!=0 && strcmp(fit1,"ff")!=0 && strcmp(fit1,"wf")!=0){
              printf("\nAjuste de particion invalido\n");
              return -1;
          }
          break;
      case 6:
          token =strtok(NULL," :");
          strcpy(delete1,token);
          delete11=1;
          if(strcmp(delete1,"full")!=0 && strcmp(delete1,"fast")!=0){
              printf("\nTipo de eliminacion invalido\n");
              return -1;
          }
          break;

      case 7:
          token =strtok(NULL," :");
          strcpy(name1,token);
          if(name1==NULL){
              printf("\nNombre invalido\n");
              return -1;
          }
          break;
      case 8:
          token =strtok(NULL," :");
          strcpy(add11,token);
          if(add11!=NULL){
          if(strstr(add11,"-")){
           Menos = 1;
           char* tok1;
           tok1 = strtok(add11,"- :");
           strcpy(add11,tok1);
           add1 =atoi(add11);
          }else{
              add1=atoi(add11);
          }
          }else{
              printf("\nvalor de add incorrecto o inexistente.\n");
          return -1;
          }
          break;
      default:
          printf("\ncomandos invalidos\n");
          return -1;
          break;

        }

    }

    mbr* mbraux=(mbr*)malloc(sizeof(mbr));
    FILE* file = fopen(path1,"r+b");
    fseek(file,0,SEEK_SET);
    fread(mbraux,sizeof(mbr),1,file);
    fclose(file);

    if(strcmp(unit1,"b")==0){
        size1= size1;
        add1 = add1;
    }else if(strcmp(unit1,"k")==0){
        size1=size1*1024;
        add1 =add1 *1024;
    }else if(strcmp(unit1, "m")==0){
        size1=size1*1024*1024;
        add1 =add1 *1024*1024;
    }
    //comprobando que hay suficiente espacio en el disco
    int EspacioLibreEnDisco;
       EspacioLibreEnDisco=mbraux->mbr_tamanio-mbraux->mbr_partition1.part_size-mbraux->mbr_partition2.part_size-mbraux->mbr_partition3.part_size-mbraux->mbr_partition4.part_size;
    int cabeParticion;

    cabeParticion=EspacioLibreEnDisco-size1;
    //SI LA PARTICION A CREAR CABE EN EL DISCO ENTONCES CabeParticion SERA 1 en otro caso sera -1
    if(cabeParticion>0){
    cabeParticion=1;
    }else{
    cabeParticion=-1;
    }

    //COMPROVANO RESTRICCIONES POR TEORIA DE PARTICIONES

    mbr *mbr01=(mbr*)malloc(sizeof(mbr));
    FILE *partc =fopen(path1,"r+b");

    fseek(partc,0,SEEK_SET);
    fread(mbr01,sizeof(mbr),1,partc);
    fclose(partc);

   if(strstr(comprobarcadena,"type")){


       if(strcmp(type1,"e")==0){
            if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){printf("\nYa existe una particion Extendida\n"); return -1;}
            if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){printf("\nYa existe una particion Extendida\n"); return -1;}
            if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){printf("\nYa existe una particion Extendida\n"); return -1;}
            if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){printf("\nYa existe una particion Extendida\n"); return -1;}
        }
        if(strcmp(type1,"l")==0){
        if(strcmp(mbr01->mbr_partition1.part_type,"e")!=0 && strcmp(mbr01->mbr_partition2.part_type,"e")!=0 && strcmp(mbr01->mbr_partition3.part_type,"e")!=0 && strcmp(mbr01->mbr_partition4.part_type,"e")!=0)
        {
            printf("\nNO existe una particion Extendida\n");
               return -1;
        }
        }
        if(strcmp(type1,"l")!=0 && mbr01->mbr_partition1.part_size>0 && mbr01->mbr_partition2.part_size>0 && mbr01->mbr_partition3.part_size>0 && mbr01->mbr_partition4.part_size>0){
           printf("\nNo hay espacio para otra particion\n");
           return -1;
        }
    }


    //SI SE CREA UNA NUEVA PARTICION
    if(size1>0){
    if(strcmp(mbraux->mbr_partition1.part_name,name1)==0 && strcmp(mbraux->mbr_partition2.part_name,name1)==0 && strcmp(mbraux->mbr_partition3.part_name,name1)==0 && strcmp(mbraux->mbr_partition4.part_name,name1)==0){
          printf("/nnombre de particion ya existe/n");
          return -1;
       }

      if(mbr01->mbr_partition1.part_size==0){

        int inicio=0;


        inicio=IniciarParticion(mbraux->mbr_partition2.part_start,mbraux->mbr_partition2.part_size,mbraux->mbr_partition3.part_start,mbraux->mbr_partition3.part_size,mbraux->mbr_partition4.part_start,mbraux->mbr_partition4.part_size,size1,mbraux->mbr_tamanio);

        if(inicio<0){
        return -1;
        }



    strcpy(mbr01->mbr_partition1.part_fit,fit1);
    strcpy(mbr01->mbr_partition1.part_name,name1);
    strcpy(mbr01->mbr_partition1.part_type,type1);
    mbr01->mbr_partition1.part_size    =size1;
    mbr01->mbr_partition1.part_start   =inicio;
    mbr01->mbr_partition1.part_status  =1;

    FILE *partc11 =fopen(path1,"rb+");
    fseek(partc11,0,SEEK_SET);
    fwrite(mbr01,sizeof(mbr),1,partc11);
    fclose(partc11);

    if(strcmp(type1,"e")==0){
        ebr *ebr1 =(ebr*)malloc(sizeof(ebr));
        ebr1->part_status=1;
        FILE* amigo=fopen(path1,"rb+");
        fseek(amigo,0,SEEK_SET);
        mbr* auxiliar=(mbr*)malloc(sizeof(mbr));
        fread(auxiliar,sizeof(mbr),1,amigo);
        fseek(amigo,inicio,SEEK_CUR);
        strcpy(ebr1->part_fit,"");
        ebr1->part_status=0;
        ebr1->part_start=-1;
        ebr1->part_size=0;
        ebr1->part_next=-1;
        strcpy(ebr1->part_name,"");
        fwrite(ebr1,sizeof(ebr),1,amigo);

        fclose(amigo);

    }




   }

    }

    return 1;
}

//a1, b1 ,c1 son los inicios de las particiones, y a2, b2, c2 son el size de cada particion
int IniciarParticion(int a1,int a2, int b1, int b2, int c1, int c2, int size, int sizedisco){
    int aux1;
    int ref=-10;

    int cero   =-1;
    int uno    =-1;
    int dos    =-1;
    int tres   =-1;
    int cuatro =-1;
    int cinco  =-1;
    int seis   =-1;
    int siete  =-1;
    int nueve  =-1;
    int diez   =-1;
    int once   =-1;
    int doce   =-1;

    int arr[15];
    arr[1]=cero;
    arr[2]=uno;
    arr[3]=dos;
    arr[4]=tres;
    arr[5]=cuatro;
    arr[6]=cinco;
    arr[7]=seis;
    arr[8]=siete;
    arr[9]=nueve;
    arr[10]=diez;
    arr[11]=once;
    arr[12]=doce;
    //printf("\nvalor a2: %d\n",a2);
    if(a2==0 && b2==0 && c2==0){
          return 0;
      }
    if((a1<=b1 || b2<1) && (a1<=c1|| c2<1) && a2>0){
        /**************PARA A MENOR***********************************/
        ref=1;
        if(size<=a1){
            cero =0;
            arr[1]=a1;
        }
        if(size<=a1){
            return 0;
        }
        if((b1<c1 ||c2<=0) && b2>0){//MODIFIQUE PUSE LOS IGUALES

            /***********************************************/

            aux1=b1-(a1+a2);
            if(size<=aux1 ){
                uno= a1+a2;
                arr[2]=aux1;
            }

            if(c2<=0){
             aux1=sizedisco-(b1+b2);
             if(size<=aux1){
                 arr[3]=aux1;
                dos =b1+b2;
             }

            }else{
                aux1=c1-(b1+b2);
                if(size<=aux1){
                    tres =b1+b2;
                    arr[4]=aux1;
                }else if((sizedisco-c1-c2)>=size){
                    tres =c1+c2;
                    arr[4]=sizedisco-c1-c2;
                }

            }

            /**************************************/


        }
        if((c1<b1 || b2<=0) && c2>0){

            /*************************************/
            aux1=c1-(a1+a2);
            if(size<=aux1 ){
                cuatro= a1+a2;
                arr[5]=aux1;
            }

            if(b2<=0){
             aux1=sizedisco-(c1+c2);
             if(size<=aux1){
                cinco =c1+c2;
                arr[6]=aux1;
             }

            }else{
                aux1=b1-(c1+c2);
                if(size<=aux1){
                    seis =c1+c2;
                    arr[7]=aux1;
                }else if((sizedisco-b1-b2)>=size){
                    seis =b1+b2;
                    arr[7]=sizedisco-b1-b2;
                }
            }


            /************************************/


        }
        if(c2>0 && b2<=0){

            /*************************************/
            aux1=c1-(a1+a2);
            if(size<=aux1 ){
                nueve= a1+a2;//crear variable int nueve;
                arr[9]=aux1;
            }

             aux1=sizedisco-(c1+c2);
             if(size<=aux1){
                diez =c1+c2;//crear variable int diez
                arr[10]=aux1;
             }

            /************************************/
            }
        if(b2>0 && c2<=0){

                    /*************************************/
                    aux1=b1-(a1+a2);
                    if(size<=aux1 ){
                        once= a1+a2;//crear variable int once;
                        arr[11]=aux1;
                    }

                     aux1=sizedisco-(b1+b2);
                     if(size<=aux1){
                        doce =b1+b2;//crear variable int doce
                        arr[12]=aux1;
                     }

                    /************************************/
                    }
         aux1= sizedisco-(a1+a2);
        if(size<=aux1 && b2<=0 && c2<=0){
                siete =a1+a2;
                arr[8]=aux1;
            }

        /**************FIN A MENOR***********************************/
    }
    else if((b1<=a1|| a2<1) && (b1<=c1 || c2<1) && b2>0){
        /**************PARA B MENOR***********************************/
        ref=1;
        if(size<=b1){
                cero=0;
               arr[1]=b1;
        }
        if(size<=b1 ){
            return 0;
        }
        if((a1<c1 || c2<=0) && a2>0){

            /***********************************************/

            aux1=(a1)-(b1+b2);
            if(size<=aux1 ){
                uno= b1+b2;
                arr[2]=aux1;
            }

            if(c2<=0){
             aux1=sizedisco-(a1+a2);
             if(size<=aux1){
                dos =a1+a2;
                arr[3]=aux1;
             }

            }else{
                aux1=c1-(a1+a2);
                if(size<=aux1){
                    tres =a1+a2;
                    arr[4]=aux1;
                }else if((sizedisco-c1-c2)>=size){
                    tres =c1+c2;
                    arr[4]=sizedisco-c1-c2;
                }

            }

            /**************************************/


        }
        if((c1<a1 || a2<=0)&& c2>0){

            /*************************************/
            aux1=(c1)-(b1+b2);
            if(size<=aux1 ){
                cuatro= b1+b2;
                arr[5]=aux1;
            }

            if(a2<=0){
             aux1=sizedisco-(c1+c2);
             if(size<=aux1){
                cinco =c1+c2;
                arr[6]=aux1;
             }

            }else{
                aux1=a1-(c1+c2);
                if(size<=aux1){
                    seis =c1+c2;
                    arr[7]=aux1;
                }else if((sizedisco-a1-a2)>=size){
                    seis =a1+a2;
                    arr[4]=sizedisco-a1-a2;
                }

               }

            /************************************/


        }
        if(c2>0 && a2<=0){

            /*************************************/
            aux1=c1-(b1+b2);
            if(size<=aux1 ){
                nueve= b1+b2;//crear variable int nueve;
                arr[9]=aux1;
            }

             aux1=sizedisco-(c1+c2);
             if(size<=aux1){
                diez =c1+c2;//crear variable int diez
                arr[10]=aux1;
             }

            /************************************/
            }
        if(a2>0 && c2<=0){

                    /*************************************/
                    aux1=a1-(b1+b2);
                    if(size<=aux1 ){
                        once= a1+a2;//crear variable int once;
                        arr[11]=aux1;
                    }

                     aux1=sizedisco-(a1+a2);
                     if(size<=aux1){
                        doce =a1+a2;//crear variable int doce
                        arr[12]=aux1;
                     }

                    /************************************/
                    }
        aux1= sizedisco-(b1+b2);
        if(size<=aux1 && a2<=0 && c2<=0){
                siete =b1+b2;
                arr[8]=aux1;
            }



        /**************FIN B MENOR***********************************/

    }
    else if((c1<=a1|| a2<1) && (c1<=b1|| b2<1) && c2>0){

        /**************PARA C MENOR***********************************/
        ref=1;
        if(size<=c1){
                cero=0;
                arr[1]=aux1;
        }
        if(size<=c1 ){
            return 0;
        }
        if((a1<b1 || b2<=0) && a2>0){

            /***********************************************/

            aux1=(a1)-(c1+c2);
            if(size<=aux1 ){
                uno= c1+c2;
                arr[2]=aux1;
            }

            if(b2<=0){
             aux1=sizedisco-(a1+a2);
             if(size<=aux1){
                dos =a1+a2;
                arr[3]=aux1;
             }

            }else{
                aux1=b1-(a1+a2);
                if(size<=aux1){
                    tres =a1+a2;
                    arr[4]=aux1;
                }else if((sizedisco-b1-b2)>=size){
                    tres =b1+b2;
                    arr[4]=sizedisco-b1-b2;
                }
            }


            /**************************************/


        }
        if((b1<a1 || a2<=0)&& b2>0){

            /*************************************/
            aux1=(b1)-(c1+c2);
            if(size<=aux1 ){
                cuatro= c1+c2;
                arr[5]=aux1;
            }

            if(a2<=0){
             aux1=sizedisco-(b1+b2);
             if(size<=aux1){
                cinco =b1+b2;
                arr[6]=aux1;
             }

            }else{
                aux1=a1-(b1+b2);
                if(size<=aux1){
                    seis =b1+b2;
                    arr[7]=aux1;
                }else if((sizedisco-a1-a2)>=size){
                    seis =a1+a2;
                    arr[4]=sizedisco-a1-a2;
                }

            }

            /************************************/


        }
        if(b2>0 && a2<=0){

                    /*************************************/
                    aux1=b1-(c1+c2);
                    if(size<=aux1 ){
                        nueve= c1+c2;//crear variable int nueve;
                        arr[9]=aux1;
                    }

                     aux1=sizedisco-(b1+b2);
                     if(size<=aux1){
                        diez =b1+b2;//crear variable int diez
                        arr[10]=aux1;
                     }

                    /************************************/
                    }
        if(a2>0 && b2<=0){

                            /*************************************/
                            aux1=a1-(c1+c2);
                            if(size<=aux1 ){
                                once= a1+a2;//crear variable int once;
                                arr[11]=aux1;
                            }

                             aux1=sizedisco-(a1+a2);
                             if(size<=aux1){
                                doce =a1+a2;//crear variable int doce
                                arr[12]=aux1;
                             }

                            /************************************/
                            }
        aux1= (c1+c2)-sizedisco;
        if(size<=aux1 && a2<=0 && b2<=0){
                siete =c1+c2;
                arr[8]=aux1;
            }



        /**************FIN C MENOR***********************************/
    }
    else{
        printf("\nError al crear el disco\n");
        return -1;
    }
     int u[15];
     u[1]=cero;
     u[2]=uno;
     u[3]=dos;
     u[4]=tres;
     u[5]=cuatro;
     u[6]=cinco;
     u[7]=seis;
     u[8]=siete;
     u[9]=nueve;
     u[10]=diez;
     u[11]=once;
     u[12]=doce;
     int l=1;
     for(l;l<13;l++){
         //printf("\n--------------------------------------------------valor de espacio: %d  valor de l: %d\n",arr[l],l);
     }
    // printf("\n-----------------------------------------------------------valor de size: %d\n",size);



                int n=1;
                int auxiliar =-1;
                int auxiliar2=-1;
                int auxiliar3=-1;
                int auxiliar4=-1;

                for(n;n<=11;n++){

                    if(size<=arr[n] && arr[n]!=-1){
                       auxiliar4=auxiliar3;
                       auxiliar3=u[n];
                       if(auxiliar3<auxiliar4 || auxiliar4==-1){
                           auxiliar =arr[n];
                           auxiliar2=u[n];
                       }else{
                           auxiliar =1;
                           auxiliar2=auxiliar4;
                       }

                    }
                }

                if(auxiliar!=-1){
                 return auxiliar2;
                }else{printf("\nEspacio fragmentado insuficiente para contener esta particion.\n"); return -1;}


}






//FIN METODOS FASE 1































