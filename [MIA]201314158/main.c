#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "stdio.h"
#include <time.h>
#include "exec.h"
#define TRUE 1
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

        char *token =strtok(Comando," ");

        //TOKEN CONTIENE LA PRIMERA ORDEN

        //ACONTINUACION SE LLAMA A EL METODO SEGUN LA ORDEN

        if(strcmp(token,"mkdisk")==0){
         //   mkdisk();
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
            exec();
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
       leerComandos(cadena);
    }

       fclose(file1);

return 0;
}

//FIN METODOS FASE 1


