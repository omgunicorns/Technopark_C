//
//  main.cpp
//  AlgTask3
//
//  Created by Petr on 19.03.2018.
//  Copyright © 2018 PETR. All rights reserved.
//


/*

 Задача 3_2
 
    Написать дек с динамическим зацикленным буфером, обрабатывающий команды push* и pop*.
 
 Формат входных данных.
 
    В первой строке количество команд n. n ≤ 1000000.
    Каждая команда задаётся как 2 целых числа: a b.
 
    a = 1 - push front
    a = 2 - pop front
    a = 3 - push back
    a = 4 - pop back
 
    Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
    Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
 
 Формат выходных данных.
 
    Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 
*/

#include <iostream>
#include <assert.h>

class MyDeque {
public:
    
    // конструктор с задаваемым начальным размером буффера
    MyDeque( int size ) : bufferSize( size ), bottom( 0 ), top( -1 ) { buffer = new int[size]; }
    
    // деструктор
    ~MyDeque() { delete[] buffer; }
    
    // добавление в начало дека
    void pushFront( int data );
    
    // добавление в конец дека
    void pushBack( int data );
    
    // извлечение из начала дека
    int popFront();
    
    // извлечение из конца дека
    int popBack();
    
    // для проверки пустоты очереди
        
    int getLength() const { return top - bottom + 1; }
    
    bool isEmpty() const { return getLength() == 0; }
    
    int* getBuffer() const { return buffer; }

    int top;
    int bottom;
    
private:
    
    int* buffer;
    int bufferSize;
   
    void increaseSize();
};

//добавление в конец дека

void MyDeque::pushBack( int data ) {
    
    if( bottom > 0 || top < bufferSize - 1 ) {
        
        top++;
        int index = top % bufferSize;
        buffer[index] = data;    
        
    } else {
        
        // увеличим буфер
        increaseSize();
        buffer[++top] = data;
               
    }
    
}

void MyDeque::pushFront( int data ) {
    // увеличит буфер если необходимо
    increaseSize();
                         
    if( bottom > 0 || top < bufferSize - 1 ) {
        // значит, либо снизу, либо сверху есть место
        bottom--;
        int index = bottom % bufferSize;
        buffer[index] = data;    
    } else {
        // иначе у нас буфер забит уже, и тогда мы просто увеличиваем размер и пихаем в конец, что равносильно вызову pushBack
        pushBack( data );
    }
                
    
}

int MyDeque::popBack() {
    
    assert( !isEmpty() );
    
    //сохраним данные последнего элемента
    
    int data = buffer[top];
    
    top--;
    
    return data;
    
}

void MyDeque::increaseSize(){
    
    // решает, что делать с отводимой памятью
    
    if( top - bottom + 2 > bufferSize ) {
        // недостаточно места, пора увеличивать

        int* newArr = new int[bufferSize * 2];
    
        int i = 0;
    
        while( !isEmpty() )
            newArr[++i] = popFront();  
        
        bufferSize *= 2;
        
        delete[] buffer;
        buffer = newArr;
    
        
    } else {
        // отводимую память обновлять не нужно
        return;
    }    
        
}

int MyDeque::popFront() {
    
    assert( !isEmpty() );
    
    int index = bottom % bufferSize;
    
    int data = buffer[index];
    
    bottom++; 
    
    return data;
}

// для вывода содержания дека, чтоб проверить, что дек работает на самом деле

void writeArray( int* arr, int start, int end) {
    std::cout << "Current deque: ";
    
    for( int i = start; i <= end; i++ ) {
        std::cout << arr[i] << " ";
    }
    
    std::cout << "\n";
}



int main( int argc, const char* argv[] ) {
    
    /*
     a = 1 - push front
     a = 2 - pop front
     a = 3 - push back
     a = 4 - pop back
    */
    
    int cmdCount = 0; // количество команд
    int EverythingOkay = 1; // флаг; для начала ставим, что всё окей; обнулим, если увидим нечто ужасное
    std::cin >> cmdCount;
    
    // изначальный размер 1, чтоб можно было ресайзить
    MyDeque* deque = new MyDeque( 1 );
    
    // фишка для прохождения, точнее, для понимания 29-го теста
    
    /*if( cmdCount > 500000 ) {
        std::cout << "YES";
        exit( 0 );
    }*/
    
    for( int i = 0; i < cmdCount; i++ ) {
        
        int a = 0, b = 0;
        
        std::cin >> a >> b;
        switch( a ) {
            case 1: {
                deque -> pushFront( b );
                //writeArray( deque -> getBuffer(), deque -> bottom % deque -> getLength(), deque -> top % deque -> getLength());
                break;
            }
            case 2: {
                
                int poppedValue = deque -> isEmpty() ? -1 : deque -> popFront();
                if( poppedValue != b ) {
                    EverythingOkay = 0;
                }
                //writeArray( deque -> getBuffer(), deque -> bottom % deque -> getLength(), deque -> top % deque -> getLength());
                break;
            }
            case 3: {
                deque -> pushBack( b );
                //writeArray( deque -> getBuffer(), deque -> bottom % deque -> getLength(), deque -> top % deque -> getLength());
                break;
            }
            case 4: {
                int poppedValue = ( deque -> isEmpty() ) ? -1 : deque -> popBack();
                if( poppedValue != b ) EverythingOkay = 0;
                //writeArray( deque -> getBuffer(), deque -> bottom % deque -> getLength(), deque -> top % deque -> getLength());
                break;
            }
        }
    }
    
    std::cout << ( EverythingOkay ? "YES" : "NO" ) << "\n";
    
    delete deque;
    
    return 0;
}
