#include <stdio.h>
#include <stdlib.h>

int main() {
    int nilai[6] = {10, 20, 30, 40, 50};
    int n = 5; // jumlah elemen saat ini
    int posisi = 2; // posisi untuk menyisipkan (indeks dimulai dari 0)
    int dataBaru = 25;

    // Geser elemen ke kanan
    for (int i = n; i > posisi; i--) {
        nilai[i] = nilai[i - 1];
    }

    // Sisipkan data baru
    nilai[posisi] = dataBaru;
    n++;

    printf("Array setelah insert:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", nilai[i]);
    }

    return 0;
}
