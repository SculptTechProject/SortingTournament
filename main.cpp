#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>

// Deklaracje funkcji sortujących
void bubbleSort(std::vector<int>& n);
void insertionSort(std::vector<int>& arr);
void quickSort(std::vector<int>& arr, int start, int end);
int partition(std::vector<int>& arr, int start, int end);
void mergeSort(std::vector<int>& arr, int left, int right);
void merge(std::vector<int>& arr, int left, int mid, int right);

// Funkcja do ładowania danych z pliku
std::vector<int> loadDataFromFile(const std::string& filePath) {
    std::ifstream inputFile(filePath);
    std::vector<int> data;
    int number;

    //
    if (!inputFile.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku: " << filePath << std::endl;
        return data;
    }

    while (inputFile >> number) {
        data.push_back(number);
    }

    inputFile.close();
    return data;
}

int main() {
    // Ścieżka do pliku
    std::string filePath = "../pliki_LAB08/pes_2000liczb.txt";

    // Wczytywanie danych
    std::vector<int> numbers = loadDataFromFile(filePath);

    if (numbers.empty()) {
        std::cerr << "Brak danych do sortowania." << std::endl;
        return 1;
    }

    // Tworzenie kopii danych dla każdego algorytmu sortowania
    std::vector<int> numbersBubble = numbers;
    std::vector<int> numbersInsertion = numbers;
    std::vector<int> numbersQuick = numbers;
    std::vector<int> numbersMerge = numbers;

    // Pomiar czasu dla Bubble Sort
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(numbersBubble);
    auto end = std::chrono::high_resolution_clock::now();
    auto durationBubble = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Czas wykonania Bubble Sort: " << durationBubble << " mikrosekund" << std::endl;

    // Pomiar czasu dla Insertion Sort
    start = std::chrono::high_resolution_clock::now();
    insertionSort(numbersInsertion);
    end = std::chrono::high_resolution_clock::now();
    auto durationInsertion = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Czas wykonania Insertion Sort: " << durationInsertion << " mikrosekund" << std::endl;

    // Pomiar czasu dla Quick Sort
    start = std::chrono::high_resolution_clock::now();
    quickSort(numbersQuick, 0, numbersQuick.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    auto durationQuick = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Czas wykonania Quick Sort: " << durationQuick << " mikrosekund" << std::endl;

    // Pomiar czasu dla Merge Sort
    start = std::chrono::high_resolution_clock::now();
    mergeSort(numbersMerge, 0, numbersMerge.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    auto durationMerge = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Czas wykonania Merge Sort: " << durationMerge << " mikrosekund" << std::endl;

    // Wyświetlanie posortowanych danych
    std::cout << "\nPosortowane liczby (Bubble Sort): ";
    for (const auto& num : numbersBubble) {
        std::cout << num << " ";
    }
    std::cout << "\nPosortowane liczby (Insertion Sort): ";
    for (const auto& num : numbersInsertion) {
        std::cout << num << " ";
    }
    std::cout << "\nPosortowane liczby (Quick Sort): ";
    for (const auto& num : numbersQuick) {
        std::cout << num << " ";
    }
    std::cout << "\nPosortowane liczby (Merge Sort): ";
    for (const auto& num : numbersMerge) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Funkcja do sortowania bąbelkowego
void bubbleSort(std::vector<int>& n) {
    int size = n.size();
    for (int j = 0; j < size - 1; j++) {
        for (int i = 0; i < size - j - 1; i++) {
            if (n[i] > n[i + 1]) {
                std::swap(n[i], n[i + 1]);
            }
        }
    }
}

// Funkcja do sortowania przez wstawianie
void insertionSort(std::vector<int>& arr) {
    int size = arr.size();
    for (int i = 1; i < size; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Funkcja implementująca algorytm QuickSort
void quickSort(std::vector<int>& arr, int start, int end) {
    if (end <= start) return;
    int pivot = partition(arr, start, end);
    quickSort(arr, start, pivot - 1);
    quickSort(arr, pivot + 1, end);
}

// Funkcja dzieląca tablicę na części w oparciu o pivot
int partition(std::vector<int>& arr, int start, int end) {
    int pivot = arr[end];
    int i = start - 1;
    for (int j = start; j <= end - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[end]);
    return i + 1;
}

// Funkcja implementująca algorytm MergeSort
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Funkcja łącząca podzielone tablice dla MergeSort
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Tworzenie tymczasowych tablic
    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    // Kopiowanie danych do tymczasowych tablic
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Łączenie tymczasowych tablic z powrotem do arr[left..right]
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Kopiowanie pozostałych elementów leftArr[], jeśli są
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Kopiowanie pozostałych elementów rightArr[], jeśli są
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}