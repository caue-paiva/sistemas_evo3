#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <string.h>

#define TAM_POP 10
#define DELTA 1
#define VAR_MUT_ARR_SIZE 7
#define OG_MUT 5.0
#define maxx 1000
const float arr_mut_changes[] = {0.1,0.1,1000,10,10,10,1};

float MaxMut = OG_MUT;
float last_best_fit;

float max_fit = 0.0;
float media = 0.0;

int i, maxi = 0;  //maxi é o index do melhor de todos
int gen = 0;

void avalia(float* indi, float*fit){
 float x;
 printf(" generation %d \n", gen);

 for (i = 1; i <= TAM_POP; i++)
 {
    x = indi[i]; 
    float y = 5 * (2*cos(0.039*x) + 5*sin(0.05*x) + 0.5*cos(0.01*x) + 10*sin(0.07*x) + 5*sin(0.1*x) + 5*sin(0.035*x))*10+500;
    
    fit[i] = y;
   // printf("\tFitness %d (%f)= %f\n",i,indi[i],fit[i]);
 }

}
 
float* init_pop(void){
 float* indi = (float*) malloc(sizeof(float) * TAM_POP+1);
   if(!indi){exit(1);}

 for (i = 1; i <= TAM_POP; i++)
 {
    indi[i] = (float) (rand() % maxx);
 }
  return indi;
}

void Sele_natu(float* indi, float* fit){
 
 max_fit = fit[1];
 maxi = 1 ; //indv mais adaptado é o index 1 do array 
 
 for (i = 2; i <= TAM_POP; i++){
    if (fit[i]> max_fit){
        max_fit = fit[i];
        maxi=i; //MUDA O INDEX DO MAXI
    }
 }

 for (i = 1; i <= TAM_POP; i++){

    if (i==maxi){
        continue;
    }

    indi[i] = (indi[i]+ indi[maxi])/2.0;  //transa com o melhor

    indi[i] = indi[i] + ((float)   (rand()%maxx)-maxx/2)*MaxMut/100.0f;                     
      
    if(indi[i]>maxx)
			indi[i]=maxx;
	if(indi[i]<0)
			indi[i]=indi[i]*-1.0;

      } 
      
     // printf(" indv mais adaptado: %f \n", indi[maxi]);
  } 

bool mut_calculation(){
    static int number_gen;
    static int mut_arr_index;

    if(fabs(max_fit - last_best_fit) < DELTA){
        number_gen++;
    }else{
        number_gen = 0;
    }

    if (number_gen > 5){
        printf("MUTATION TIME \n");
        if(mut_arr_index == VAR_MUT_ARR_SIZE-1){
           MaxMut = OG_MUT;
           return true;
         //  keep_best_genocide();
        }else{
        MaxMut = MaxMut* arr_mut_changes[mut_arr_index];
        }
        mut_arr_index = (mut_arr_index + 1) % (VAR_MUT_ARR_SIZE);
        number_gen = 0;
    }

    return false;
}

/*void keep_best_genocide(){
    for (i = 1; i <= TAM_POP; i++){
        if (i != maxi){  //mata todos menos o melhor de todos 
            indi[i] = (float) (rand() % maxx);
        }
    }
}*/

void kill_them_all(float* indi){
    printf("beat beat beat kill kill kill stomp them raw \n");
    for (i = 1; i <= TAM_POP; i++){
        indi[i] = (float) (rand() % maxx);
    }
    printf("beat beat beat kill kill kill stomp them raw \n");
}

void torneio(float* fit, float*indi, float* temp_indi){

    int a, b, pai1, pai2;
    max_fit= fit[1];
    maxi=1;

    for (i=2;i<=TAM_POP;i++){   // Busca pelo melhor individuo para protege-lo
        if (fit[i]>max_fit)
        {
            max_fit = fit[i];
            maxi = i;
        }
    }

    for (i=1;i<=TAM_POP;i++){  //copia o array indi para temp_indi
        temp_indi[i] = indi[i];
    }

for ( i = 1; i<=TAM_POP; i++){ //torneio
    
    if (i ==maxi)
        continue;
    

    a = (rand()%TAM_POP) +1;
    b = (rand()%TAM_POP) +1;

    if (fit[a]> fit[b]){
        pai1=a;
    } else {
        pai1=b;
    }

    a = (rand()%TAM_POP) +1;
    b = (rand()%TAM_POP) +1;

    if (fit[a]> fit[b]){
        pai2=a;
    } else {
        pai2=b;
    }

    indi[i] = (temp_indi[pai1] + temp_indi[pai2])/ 2.0;

    indi[i] = indi[i] + (double) (((rand() %maxx - (maxx/2.0))/100.0) * MaxMut);
    }
     printf(" novo max_fit %f \n\n", max_fit);
     if(mut_calculation()){
         kill_them_all(indi);
     }  
}

void ag(float* indi, float*fit, float* temp_indi){
 Sele_natu(indi,fit);
 avalia(indi,fit);
 torneio(fit,indi,temp_indi);
 last_best_fit = max_fit;  //pega o ultimo melhor fitness antes da seleção, antes de aplicar sele nat e torneio
 printf(" last best fit %f \n", last_best_fit);
 gen++;

}

int main(){
  srand(time(NULL));
  float* individuals =  init_pop();

  float* fitness = (float*) calloc(TAM_POP+1, sizeof(float));
       if(!fitness){exit(1);}
  float* temp_indi = (float*) calloc(TAM_POP+1, sizeof(float));
       if(!fitness){exit(1);}

   for (int i = 0; i < 100; i++) {  // Run the AG for 100 generations
     ag(individuals,fitness, temp_indi);
   }
    free(individuals);
    free(fitness);
    free(temp_indi);
    return 0;
}

