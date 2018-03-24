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

#define SHRINK -1
#define GROW    1

class MyDeque {
public:
    
    // конструктор с задаваемым начальным размером буффера
    MyDeque( int size ) : bufferSize( size ), top( -1 ) { buffer = new int[size]; }
    
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
    
    bool isEmpty() const { return top == -1; }
    
    int getLength() const { return top + 1; }
    
    int* getBuffer() const { return buffer; }

    
private:
    
    int* buffer;
    int bufferSize;
    int top;
    
    void resize( int newTop );
    void determineResizing( int how );
};

//добавление в конец дека

void MyDeque::pushBack(int data) {
    // увеличим буфер
    
    determineResizing( GROW );
    
    buffer[++top] = data;
}

void MyDeque::pushFront(int data) {
    
    determineResizing( GROW );
    
    top++;
    
    //сдвигаем вперед все данные
    
    for( int i = top; i > 0; i-- ) {
        buffer[i] = buffer[i - 1];
    }
    
    // ставим в начало новое число
    buffer[0] = data;
}

int MyDeque::popBack() {
    
    assert( !isEmpty() );
    
    //сохраним данные последнего элемента
    
    int data = buffer[top];
    
    determineResizing( SHRINK );
    
    top--;
    
    return data;
    
}

void MyDeque::determineResizing(int how){
    
    assert( bufferSize >= 0 );
    
    // решает, что делать с отводимой памятью
    
    if( ( top + how ) * 2 < bufferSize ) {
        // слишком велик размер, пора уменьшать, но только если он не есть 1
        if(bufferSize > 1) {
            bufferSize /= 2;
        } else {
            // если размер уже 1, то уменьшать дальше не стоит, чтоб не потерять возможность увеличивать
            return;
        }
    } else if( top + how > bufferSize ) {
        // недостаточно места, пора увеличивать
        bufferSize *= 2;
    } else {
        // отводимую память обновлять не нужно
        return;
    }
    
    // изменение отведенной на массив памяти
    
    int* newArr = new int[bufferSize];
    
    for( int i = 0; i < top + 1; i++ ) {
        newArr[i] = buffer[i];
    }
    
    delete[] buffer;
    buffer = newArr;
    
}



int MyDeque::popFront() {
    
    assert( !isEmpty() );
    
    int data = buffer[0];
    
    //принимает решение, нужно ли изменить размер массива
    determineResizing( SHRINK );
    
    //обрезает массив снизу
    for( int i = 1; i < top + 1; i++ )
        buffer[i - 1] = buffer[i];
    
    top--;
    
    return data;
}

// для вывода содержания дека, чтоб проверить, что дек работает на самом деле

void writeArray( int* arr, int N ) {
    std::cout << "Current deque: ";
    
    for( int i = 0; i < N; i++ ) {
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
                //writeArray( deque -> getBuffer(), deque -> getLength() );
                break;
            }
            case 2: {
                
                int poppedValue = deque -> isEmpty() ? -1 : deque -> popFront();
                if( poppedValue != b ) {
                    EverythingOkay = 0;
                }
                //writeArray( deque -> getBuffer(), deque -> getLength() );
                break;
            }
            case 3: {
                deque -> pushBack( b );
                //writeArray( deque -> getBuffer(), deque -> getLength() );
                break;
            }
            case 4: {
                int poppedValue = ( deque -> isEmpty() ) ? -1 : deque -> popBack();
                if( poppedValue != b ) EverythingOkay = 0;
                //writeArray( deque -> getBuffer(), deque -> getLength() );
                break;
            }
        }
    }
    
    std::cout << ( EverythingOkay ? "YES" : "NO" ) << "\n";
    
    delete deque;
    
    return 0;
}