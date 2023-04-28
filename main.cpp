//Файл main.cpp
#include <iostream>
#include "array.h"

int main(){
   //Создаем два массива
   Array array1(100000);
   Array array2(array1);
   
   //Сортируем без многопоточности
   array1.doMergeSortWithout();

   //Проверяем корректность сортировки
   std::cout << "Sorting without: ";
   if(array1.checkSort()){
      std::cout << "Correct sorting!" << std::endl;
   }
   else{
      std::cout << "Incorrect sorting" << std::endl; 
   }
   
   //Сортируем с многопоточностью
   array2.doMergeSortWith();

   //Проверяем корректность сортировки
   std::cout << "Sorting with: ";
   if(array2.checkSort()){
      std::cout << "Correct sorting!" << std::endl;
   }
   else{
      std::cout << "Incorrect sorting" << std::endl; 
   }

   return 0;
}
