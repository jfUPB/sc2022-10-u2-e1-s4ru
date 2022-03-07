#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef DOLOG
#define LOG(...) fprintf(log, __VA_ARGS__);
#else
#define LOG(...)
#endif

struct array
{
    int *pdata;
    int size;
};

void initArray(struct array *);
void getArray(struct array *);
void arrayCommon(struct array *, struct array *, struct array *);
void printArray(struct array *);
void freeMemory(struct array *, struct array *, struct array *);

void initArray(struct array *arr){
    arr->pdata = NULL;
    arr->size = -1;
}

void printArray(struct array *parr)
{
    for (int i = 0; i < parr->size; i++)
    {
        printf("%d ", parr->pdata[i]);
    }
    printf("\n");
}

void getArray(struct array *parr)
{
      char tam1[16]; //entrada del tamaño 
      char tam2[16]; //entrada de los numeros
    if(fgets(tam1,5,stdin) != NULL)
    {
        tam1[strlen(tam1)-1 =0];
    }
    int cambio1 = sscanf(tam1, "%d", &parr->size);

    parr->pdata = malloc(sizeof(int)*parr->size); 

    for(int k = 0; k < parr -> size;k++)
    {
    if (fgets(tam2,5,stdin) != NULL) //orden del teclado datos arreglo
    {
    int cambio2 = sscanf(tam2, "%d", parr->pdata+k); //cambio de caracter a integer
    }
    }
}

void arrayCommon(struct array *arregloIn1, struct array *arregloIn2, struct array *arregloOut)
{
    int size;
    arregloOut->size = 0; 


    if(arregloIn1->size>arregloIn2->size)
    {
        size = arregloIn1->size;
    }
    else if(arregloIn2->size>arregloIn1->size)
    {
        size = arregloIn2->size;
    }
    else if(arregloIn2->size == arregloIn1->size)
    {
        size = arregloIn2->size;
    }
     int cambio[size];

    for(int vari1 = 0; vari1<size; vari1++) 
    { 
        cambio[vari1]=-1;
    } 
int k=0;

    for(int vari1=0; vari1<arregloIn1->size;vari1++)
    {
        for(int vari2=0; vari2<arregloIn2->size;vari2++)
        {
            if(arregloIn1->pdata[vari1]==arregloIn2->pdata[vari2]) 
            {
                int condi = 0;
                for(int vari3=0; vari3<size; vari3++)
                {
                    if(arregloIn1->pdata[vari1]==cambio[vari3])
                    {
                        vari3 = size;
                        condi = 1;
                    }
                }
                if(condi==0)
                {
                    cambio[k] = arregloIn2->pdata[vari2];
                    k++;
                    arregloOut->size++;
                }
            }
        }
    }
        arregloOut->pdata = malloc(sizeof(int)*arregloOut->size);
    
    for(int vari1 = 0; vari1<arregloOut->size;vari1++)
    {
        *(arregloOut->pdata+vari1) = cambio[vari1];
    }
}


void freeMemory(struct array *arr1, struct array *arr2, struct array *arr3)
{
    free(arr1->pdata);
    free(arr1);

    free(arr2->pdata);
    free(arr2);

    free(arr3->pdata);
    free(arr3);
}

int main(void)
{

#ifdef DOLOG
    FILE *log = fopen("log", "w");
    if (log == NULL)
    {
        perror("log file creation fails: ");
        return EXIT_FAILURE;
    }
#endif

    char commandBuf[64];

    LOG("creating an object for each array\n");

    struct array *arr1 = malloc(sizeof(struct array) * 1);
    initArray(arr1);
    struct array *arr2 = malloc(sizeof(struct array) * 1);
    initArray(arr2);    
    struct array *arr3 = malloc(sizeof(struct array) * 1);
    initArray(arr3);


    LOG("Init command loop\n");

    while (fgets(commandBuf, sizeof(commandBuf), stdin) != NULL)
    {
        commandBuf[strlen(commandBuf) - 1] = 0;

        if (strncmp(commandBuf, "arr1", strlen("arr1")) == 0)
        {
            LOG("getting array1\n");
            getArray(arr1);
        }
        else if (strncmp(commandBuf, "arr2", strlen("arr2")) == 0)
        {
            LOG("getting array2\n");
            getArray(arr2);
        }
        else if (strncmp(commandBuf, "printArr1", strlen("printArr1")) == 0)
        {
            LOG("printing arr1\n");
            printArray(arr1);
        }
        else if (strncmp(commandBuf, "printArr2", strlen("printArr2")) == 0)
        {
            LOG("printing arr2\n");
            printArray(arr2);
        }
        else if (strncmp(commandBuf, "compare", strlen("compare")) == 0)
        {
            LOG("Compare arrays\n");
            arrayCommon(arr1, arr2, arr3);
        }
        else if (strncmp(commandBuf, "printResult", strlen("printResult")) == 0)
        {
            LOG("printing compare result\n");
            printf("%d\n", arr3->size);
            if (arr3->size != 0)
            {
                printArray(arr3);
            }
        }
        else if (strncmp(commandBuf, "exit", strlen("exit")) == 0)
        {
            LOG("running exit command\n");
            freeMemory(arr1,arr2,arr3);
            break;
        }
    }

    return EXIT_SUCCESS;
}
