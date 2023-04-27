//Файл array.h
#pragma once

#include <memory>
#include <cstddef>

//Класс для работы с массивом
class Array{
   std::shared_ptr<int[]> array_;//сам массив
   size_t n_;//количество элементов
   
   //Сортировка слиянием(без многопоточности)
   void mergeSort(size_t l, size_t r);

   //Сортировка слиянием(с многопоточностью)
   void mergeSortWith(size_t l, size_t r);

   //Слияние 
   void merge(size_t l, size_t m, size_t r);
public:
   //Конструктор по умолчанию
   Array() : array_(nullptr), n_(0){}

   //Конструктор с параметрами
   explicit Array(size_t n);

   //Конструктор копирования
   Array(const Array &other);

   //Деструктор
   ~Array() = default;

   //Оператор присваивания копирования
   Array& operator = (const Array &other);

   //Показать массив
   void show() const;
   
   //Получить массив
   std::shared_ptr<int[]> getArray() const;

   //Получить n
   size_t getN() const;
   
   //Сделать сортировку слиянием(без многопоточности)
   void doMergeSortWithout();

   //Сделать сортировку слиянием(с многопоточностью)
   void doMergeSortWith();

   //Проверка на правильность сортировки
   bool checkSort();
};

