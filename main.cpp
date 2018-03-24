//
//  main.cpp
//  AlgTask1
//
//  Created by Petr on 18.03.2018.
//  Copyright © 2018 PETR. All rights reserved.
//

/*
 
 Задача 1_1
 
 Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
 Необходимо найти первую пару индексов i0 и j0,
 такую что A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.
 Время работы - O(n). n ≤ 100000.
 
 ПРИМЕР
 
 Ввод
 
 4
 4 -8 6 0
 -10 3 1 1
 
 Вывод
 
 0 1
 
*/


#include <iostream>


void readArray( int* arr, int size ) {
    for( int i = 0; i < size; i++ ) {
        std::cin >> arr[i];
    }
}

void findMaximums( int* arr, int* maximums, int size ) {
    
    // составляет массив из индексов масксимума
    // то есть i-й элемент новобранного массива содержит индекс маскимального элемента подмассива [0, i]
    
    int max = 0;
    
    for( int i = 0; i < size; i++) {
        if( arr[i] > arr[max] ) {
            max=i;
        }
        maximums[i]=max;
    }
}

int findMaxInArraysSum( int* arr1, int* arr2, int* maximums, int size ) {
    
    // пользуясь подсказочным массивом, полученным в findMaximums, просто суммирует попарно, находит индекс маскимума во втором массиве.
    //В первом массиве индекс может быть получен как maximums[max], где maximums - результат работы findMaximums
    
    int max = 0;
    for( int i = 0; i < size; i++ ) {
        if( arr1[maximums[i]] + arr2[i] > arr1[maximums[max]] + arr2[max] ) {
            max=i;
        }
    }
    return max;
}

int main( int argc, const char* argv[] ) {

    int arrayLength = 0;
    
    std::cin >> arrayLength;
    if( arrayLength < 1 ) {
        return 0;
    }
    
    int* firstArray = new int[arrayLength];
    int* secondArray = new int[arrayLength];
    int* firstMaximums = new int[arrayLength];
    
    readArray( firstArray, arrayLength );
    readArray( secondArray, arrayLength );
    
    //массив из индексов максимумов массива firstArray
    findMaximums( firstArray, firstMaximums, arrayLength );
    //индекс элемента во втором массиве, вместе с которым будет максимальная сумма
    int max = findMaxInArraysSum( firstArray, secondArray, firstMaximums, arrayLength );
    
    std::cout << firstMaximums[max] << " " << max << "\n";
    
    delete [] firstArray;
    delete [] secondArray;
    delete [] firstMaximums;
    
    return 0;
}

