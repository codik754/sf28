//Файл array.cpp
#include "array.h"
#include <ctime>
#include <iostream>
#include <future>

//Конструктор с параметрами
Array::Array(size_t n) : n_(n){
   //Создаем массив
   array_ = std::shared_ptr<int[]>(new int[n_], std::default_delete<int[]>());
   
   //Заполняем значениями
   //Устанавливаем точку, с которой начинается генерация
   srand(time(NULL));
   //Проходим по всему массиву и заполняем значениями
   for(size_t i = 0; i < n_;  ++i){
      array_[i] = rand() % 800 - 200;
   }
}

//Конструктор копирования
Array::Array(const Array &other) : n_(other.n_){
   //Создаем массив
   array_ = std::shared_ptr<int[]>(new int[n_], std::default_delete<int[]>());

   //Копируем значения
   for(size_t i = 0; i < n_;  ++i){
      array_[i] = other.array_[i];
   }
}

//Оператор присваивания копирования
Array& Array::operator = (const Array &other){
   //Проверка на самоприсваивание
   if(&other == this){
      return *this;
   }

   n_ = other.n_;
   
   //Если в массиве уже есть элементы
   if(array_ != nullptr){
      array_.reset();      
   }

   //Создаем массив
   array_ = std::shared_ptr<int[]>(new int[n_], std::default_delete<int[]>());

   //Копируем значения
   for(size_t i = 0; i < n_;  ++i){
      array_[i] = other.array_[i];
   }

   return *this;
}

//Показать массив
void Array::show() const{
   for(size_t i = 0; i < n_; ++i){
      std::cout << array_[i] << " ";
   }
   std::cout << std::endl;
}

//Получить массив
std::shared_ptr<int[]> Array::getArray() const{
   return array_;
}

//Получить n
size_t Array::getN() const{
   return n_;
}

//Сортировка слиянием(без многопоточности)
void Array::mergeSort(size_t l, size_t r){
   if(l >= r){
      return;
   }

   size_t m = (l + r - 1) / 2;
   
   mergeSort(l, m);
   mergeSort(m + 1, r);
   merge(l, m, r);
}

//Слияние
void Array::merge(size_t l, size_t m, size_t r){
   size_t nl = m - l + 1;
   size_t nr = r - m;

   
   //Создаем временные массивы
   std::unique_ptr<int[]> left = std::unique_ptr<int[]>(new int[nl]);
   std::unique_ptr<int[]> right = std::unique_ptr<int[]>(new int[nr]);

   //Копируем данные во временные массивы
   for (size_t i = 0; i < nl; i++){
       left[i] = array_[l + i];
   }
   for (size_t j = 0; j < nr; j++){
       right[j] = array_[m + 1 + j];
   }

   size_t i = 0;
   size_t j = 0;
   size_t k = l;//начало левой части

   while (i < nl && j < nr) {
       //Записываем минимальные элементы обратно во входной массив
       if (left[i] <= right[j]) {
           array_[k] = left[i];
           i++;
       }
       else {
           array_[k] = right[j];
           j++;
       }
       k++;
   }

   //Записываем оставшиеся элементы левой части
   while (i < nl) {
       array_[k] = left[i];
       i++;
       k++;
   }

   //Записываем оставшиеся элементы правой части
   while (j < nr) {
       array_[k] = right[j];
       j++;
       k++;
   }
}

//Сделать сортировку слиянием(без многопоточности)
void Array::doMergeSortWithout(){
   mergeSort(0, n_ - 1);
}

//Сортировка слиянием(с многопоточностью)
void Array::mergeSortWith(size_t l, size_t r){
   if(l >= r){
      return;
   }

   size_t m = (l + r - 1) / 2;
   
   //Если размер массива больше 100
   if(r - l > 100){
      //Делаем сортировку в многопоточном варианте
      //Создаем фьючерс
      auto f1 = std::async(std::launch::async, [&](){
         mergeSortWith(l, m);
      });
      mergeSortWith(m + 1, r);
      //Ждем завершения
      f1.get();
      //Делаем слияние
      merge(l, m, r);
   }
   else{
      //Делаем сортировку в однопоточном варианте
      mergeSort(l, m);
      mergeSort(m + 1, r);
      merge(l, m, r);
   }
}

//Сделать сортировку слиянием(с многопоточностью)
void Array::doMergeSortWith(){
   mergeSortWith(0, n_ - 1);
}

//Проверка на правильность сортировки
bool Array::checkSort(){
   for(size_t i = 0; i < n_ - 1; ++i){
      if(array_[i] > array_[i + 1]){
         return false;
      }
   }

   return true;
}
