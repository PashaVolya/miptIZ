/*
    Программа для иллюстрации работы двух нитей исполнения.
    Каждая нить исполнения просто увеличивает на 1
    разделяемую переменную а.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h> // sleep

int a = 0, j=0, n, i, N;

//pthread_mutex_t lock;

/* 
   Переменная а является глобальной статической для всей
   программы, поэтому будет разделяться обеими нитями
   исполнения 
*/

/*
    Ниже следует текст функции, которая будет ассоциирована
    со 2-м thread`oм
*/

void* mythread(void* dummy) {
/* 
    У функции должна быть такая сигнатура, и не важно
    что мы не используем входной параметр и возвращаемое
    значение
*/
    pthread_t mythid;

/*
    Переменная mythid является динамической локальной переменной
    функции my_thread(), т.е. помещается на стеке и, следовательно, не
    разделяется нитями исполнения.
*/

    mythid = pthread_self(); 
    for(j=j+1;j<=i*N/n;j++){
    	a=a+j;
    }

    printf("Thread %u, result = %d\n",(unsigned int)mythid , a);
    
    return NULL;
}


int main() {
    

    pthread_t thid , mythid;
    int result, n, i,j=0;
    /* 
        Пытаемся создать новую нить исполнения, ассоциированную
        с функцией my_thread(). Передаем ей в качестве параметра
        значение NULL. В случае удачи в переменную thread_id занесется
        id нового thread`a.
        В случае ошибки перекращаем работу.
    */
    //pthread_mutex_init(&lock, NULL);

    scanf("%d", &n);  //кол-во нитей
    scanf("%d", &N);
    for(i=1;i<n;i++){
    result = pthread_create(&thid , (pthread_attr_t *)NULL , mythread ,NULL);
    
    if (result!=0) {
        printf("Can`t create thread, returned value = %d\n" , result);
        exit(-1);
    }
    //printf("Thread was created, thid %d = %u\n" ,i, (unsigned int)thid);
    }
    
    
    mythid = pthread_self();
    for(j=j+1;j<=i*N/n;j++){
    	a=a+j;
    }
	printf("Сумма от 1 до n= %d\n", a);
   

    /*
        Ожидаем завершение порожденного thread`a, не интересуясь, какое значение он
        вернет. Если не выполнить вызов этой функции, то возможно ситуация, когда
        мы завершим функцию main() до того, как выполнится порожденный thread, что
        автоматически повлечет за собой его завершение, исказив результаты
    */

    //pthread_join(thid , (void **) NULL);

    

    //pthread_mutex_destroy(&lock);
    return 0;
}

