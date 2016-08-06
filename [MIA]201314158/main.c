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


char* comprobarcadena[200];
/*
FASE 1
La fase 1 se entregará el día viernes 12 de agosto antes de las 23:50 PM, al correo deben enviar el link
de su repositorio en github, para su descarga (tomen en cuenta que se ve la fecha de la última
modificación). Asunto: [MIA]Fase1_carné
Pares: 201212838@ingenieria.usac.edu.gt e Impares: Georgina.estrada78@gmail.com
1. Administración de disco
1.1. Mkdisk
1.2.Rmdisk
1.3. Fdisk
1.4.Mount
1.5.Umount
2. Reportes (Esenciales para calificación)
2.1. Mbr
2.2. Disk
2.3. Exec*/
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
       /* else if(strcmp(token,"rmdisk")==0){
            rmdisk();
        }
        else if(strcmp(token,"fdisk")==0){
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
        }

        return 0;
}




//METODOS FASE 1

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
   /* mbr1->mbr_partition1 = (partition *)malloc(sizeof(partition));
    mbr1->mbr_partition2 = (partition *)malloc(sizeof(partition));
    mbr1->mbr_partition3 = (partition *)malloc(sizeof(partition));
    mbr1->mbr_partition4 = (partition *)malloc(sizeof(partition));*/

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


//FIN METODOS FASE 1


