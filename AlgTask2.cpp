//
//  main.cpp
//  AlgTask2
//
//  Created by Petr on 18.03.2018.
//  Copyright © 2018 PETR. All rights reserved.
//

/*

 Задача 2_2
 
 Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают. Найти m за O(log m).
 2 ≤ n ≤ 10000.
 
 Пример
 
 Ввод
 
 10
 1 2 3 4 5 6 7 6 5 4
 
 Вывод
 
 6
 
*/

#include <iostream>

void readArray( int* arr, int size ) {
    for( int i = 0; i < size; i++ ) {
        std::cin >> arr[i];
    }
}

int binaryPeak( int*  arr, int start, int end ) {
    
    // запомним конец
    static int end_0 = end;
    
    //пусть пик у нас в середине
    int peak = (start + end) / 2;
    
    // теперь будем двигать пик в зависимости от его боковых значений
    
    if( arr[peak] < arr[peak - 1] ) {
        end = peak - 2;
    } else if ( arr[peak] < arr[peak + 1] ) {
        start = peak + 2;
        
        //если у нас начало уже сжатого массива оказывается больше, чем изначальный конец, то последовательность строго возрастает и пиком будет последний элемент
        if(start > end_0) {
            return end_0;
        }
    } else {
        
        // сюда попадаем в том случае, если пик больше соседних элементов (то есть он в самом деле является пиком)
        // и тогда наш поиск закончен
        
        return peak;
    }
    
    return binaryPeak( arr, start, end );
}

int localizeInterval( int* arr, int size ) {
    
    int num = 1;
    for( ; num < size; num *= 2 ) {
        if( arr[num] < arr[num - 1] ) {
            break;
        }
    }
    return num;
}


int main( int argc, const char* argv[] ) {
    
    int arrayLength = 0;
    
    std::cin >> arrayLength;
    
    int* array = new int[arrayLength];
    
    readArray( array, arrayLength );
    
    // определим конец интервала
    int intervalEnd = localizeInterval( array, arrayLength ) - 1;
    
    // начало, соответсвенно
    int intervalStart = intervalEnd / 2;
    
    // обрежем интервал сверху, если он ушел за пределы массива
    if( intervalEnd >= arrayLength - 1 ) {
        intervalEnd = arrayLength - 1;
    }
    
    // выполним бинарный поиск пикового значения в пределах локализированного интервала
    
    int max = binaryPeak( array, intervalStart, intervalEnd );
    
    std::cout << max << "\n";
    
    delete [] array;
    
    return 0;
}
