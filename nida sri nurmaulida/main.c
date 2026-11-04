#include

int main() {
    int nilai[5] = {10, 20, 30, 40, 50};
    int indeks = 3;
    int nilaiBaru = 99;

    nilai[indeks] = nilaiBaru;

    printf("Array setelah update:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", nilai[i]);
    }

    return 0;
}
