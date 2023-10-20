#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <string.h>
#define DELTA 0.00001
#define VAR_MUT_ARR_SIZE 7
#define OG_MUT 5.0

const float arr_mut_changes = {0.1,0.1,1000,10,10,10,1};
float MaxMut = OG_MUT;
float last_best_fit;
float indi[TamPop+1];
float temp_indi[TamPop+1];
float fit[TamPop+1];

float max_fit=0.0;
float media = 0.0;

int i, maxi = 0;  //maxi é o index do melhor de todos
int gen = 0;

void avalia(){
 float x;
 printf("generation %d \n", gen);

 for (i = 1; i <= TamPop; i++)
 {
    x = indi[i];
    float y =x;
    if (x >500){
        y = 1000-x;
    }

    fit[i] = y;
     //printf("\tFitness %d (%f)= %f\n",i,indi[i],fit[i]);
 }

}
 
void init_pop(){

 for (i = 1; i <= TamPop; i++)
 {
    indi[i] = (float) (rand() % maxx);
 }
 
}

void Sele_natu(){
 
 max_fit = fit[1];
 maxi = 1 ; //indv mais adaptado é o index 1 do array 
 last_best_fit = fit[1];
 for (i = 2; i <= TamPop; i++){
    if (fit[i]> max_fit){
        max_fit = fit[i];
        maxi=i; //MUDA O INDEX DO MAXI
    }
 }

 for (i = 1; i <= TamPop; i++){

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

      printf(" indv mais adaptado: %f", indi[maxi]);
  } 

void mut_calculation(){
    static int number_gen;
    static int mut_arr_index;

    if(fabs(max_fit - last_best_fit) < DELTA){
        number_gen++;
    }else{
        number_gen = 0;
    }

    if (number_gen > 10){
        if(mut_arr_index = VAR_MUT_ARR_SIZE-1){
           MaxMut = OG_MUT;
           keep_best_genocide();
        }else{
        MaxMut = MaxMut* arr_mut_changes[mut_arr_index];
        }
        mut_arr_index = (mut_arr_index++)%(VAR_MUT_ARR_SIZE);
        number_gen = 0;
    }
}

void keep_best_genocide(){
    for (i = 1; i <= TamPop; i++){
        if (i != maxi){  //mata todos menos o melhor de todos 
            indi[i] = (float) (rand() % maxx);
        }
    }
}

void kill_them_all(){
    for (i = 1; i <= TamPop; i++){
        indi[i] = (float) (rand() % maxx);
    }
}

void torneio(){

int a, b, pai1, pai2;

max_fit= fit[1];
maxi=1;

for (i=2;i<=TamPop;i++){   // Busca pelo melhor individuo para protege-lo

        if (fit[i]>max_fit)
        {
            max_fit = fit[i];
            maxi = i;
        }
    }

for (i=1;i<=TamPop;i++){
       temp_indi[i] = indi[i];
}

for ( i = 1; i<=TamPop; i++){ //torneio
    
    if (i ==maxi){
        continue;
    }

    a = (rand()%TamPop) +1;
    b = (rand()%TamPop) +1;

    if (fit[a]> fit[b]){
        pai1=a;
    } else {
        pai1=b;
    }

    a = (rand()%TamPop) +1;
    b = (rand()%TamPop) +1;

    if (fit[a]> fit[b]){
        pai2=a;
    } else {
        pai2=b;
    }

    indi[i] = (temp_indi[pai1] + temp_indi[pai2])/ 2.0;

    indi[i] = indi[i] + (double) (((rand() %maxx - (maxx/2.0))/100.0) * MaxMut);
    }

}

void ag(){
 Sele_natu();
 avalia();
 torneio();

 gen++;

}

int main(){
 srand(time(NULL));

 init_pop();

  for (int i = 0; i < 100; i++) {  // Run the AG for 100 generations
     ag();
 }

return 0;
}