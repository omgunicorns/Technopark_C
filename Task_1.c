
//LEBEDEV Petr 15.03.2018

#include <stdio.h>
#include <stdlib.h>

int getMaxConsequentSection(int *a, int N, int *b){
// N1 - длина первого найдённого подотрезка, N2 - длина второго найдённого подотрезка (если такой найдётся)
  // b - указатель на подотрезок (он только один, так как понадобится указатель только для большего найдённого подотрезка)
  
  int N1=1, N2=0;

 int prev=0;
  
    for(int i=0;i<N;prev=a[i],i++){
        
        if(i>0){if(a[i]-prev==1){
            if(N2)N2++; else N1++; //если N2>0, то N2 увеличиваем на 1. Иначе N2 не трогаем, а N1 увеличиваем на 1.
            //это потому что если N2!=0, значит N1 уже найденный отрезок, и в дальнейшем его нужно менять только если найдём больший отрезок N2, и менять мы будем ниже.
        } else {
            //эта ветка выполняется тогда, когда отрезок ПРЕРВАЛСЯ.
            //(ну или i=0, но это начальный случай, который сюда отведится, чтоб не возникло исключения при попытке получить a[i-1] в условии выше)
            
            
            if(N2==0){ //если ко второму отрезку мы не притрагивались ещё, то и хорошо, рассматриваем первый отрезок.
                if(N1>1) {
                    //то есть, прервавшись, у нас первый отрезок уже как минимум длины 2
                    b=&a[i-N1]; //запишем указатель на него, "откатившись" к началу отрезка.
                    N2=1; //и теперь можно приступать к поискам другого отрезка (с целью найти отрезок побольше).
                }
            } else {
                //значит, ко второму отрезку мы уже притронулись
                if(N2>N1) {
                    //второй найдённый отрезок больше, чем первый найдённый отрезок! Запишем второй отрезок в первый отрезок и попытаемся найти ещё больший отрезок.
                    b=&a[i-N2]; // запишем указатель на него, "откатившись" к началу отрезка.
                    N1=N2;
                }
                //а иначе оставляем первый отрезок без изменений.
                
                N2=1; //в любом случае, начинаем второй отрезок искать заново.
            }
        }}
        
     }
  
  //в конце имеем два отрезка, один из который непременно является наибольшим подотрезком, то есть решением.
  
  //Проверим, какой из отрезков больше. Снова заметим, что второй отрезок будет больше только в том случае, если он так и не прервался до конца массива.
  if(N2>N1){
      b=&a[N-N2]; //запишем указатель на наш дорогой отрезок.
      N1=N2; //чтоб больше не проверять условие N2>N1 при выводе, запишем N2 в N1
  } else {
      if(N2==0) b=&a[N-N1];
  }
  // а иначе нам делать ничего не надо, указатель на первый отрезок уже записан в цикле.
  
  //Всё, имеем N1 - длина наибольшего найдённого подотрезка и b - указатель на него.
  
  if(N1<2) {
      b=NULL;
      return 0;
  } else return N1;
}

int main()
{
  
int N;

  scanf("%d",&N);
  if(N<0||!N){
      printf("[error]");
      return 0;

  }
 int *a=malloc((N+1)*sizeof(int));
   for(int i=0;i<N;i++)
        if(!scanf("%d",&a[i])){
			free(a);
			printf("[error]");
			return 0;
		}
  int *b=NULL;
  int ans=getMaxConsequentSection(a, N, b);
  printf("%d\n",ans);

  if(ans>1) for(int i=0;i<ans;i++) printf("%d ",b[i]);

  free(a);
  free(b);

  return 0;
}



