#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TRANSAKSI 10
#define JUMLAH_PERALATAN 5

// Array data peralatan
char namaPeralatan[JUMLAH_PERALATAN][50] = {
    "Tenda Kapasitas 4 Orang",
    "Sleeping Bag",
    "Kompor Portable",
    "Matras Camping",
    "Lampu Camping"
};

int hargaPeralatan[JUMLAH_PERALATAN] = {
    50000,
    15000,
    20000,
    10000,
    12000
};

// Array untuk riwayat transaksi
char namaPenyewa[MAX_TRANSAKSI][50];
char riwayatPeralatan[MAX_TRANSAKSI][50];
int riwayatJumlah[MAX_TRANSAKSI];
int riwayatLama[MAX_TRANSAKSI];
int riwayatTotal[MAX_TRANSAKSI];

int jumlahTransaksi = 0;

// Fungsi membersihkan input buffer
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fungsi menampilkan daftar peralatan
void tampilkanPeralatan() {
    printf("\n========================================\n");
    printf("       DAFTAR PERALATAN CAMPING\n");
    printf("========================================\n");

    for (int i = 0; i < JUMLAH_PERALATAN; i++) {
        printf("%d. %-25s Rp%d/hari\n",
               i + 1,
               namaPeralatan[i],
               hargaPeralatan[i]);
    }

    printf("========================================\n");
}

// Fungsi menentukan diskon
int hitungDiskon(int lama, int subtotal) {
    int persenDiskon;

    if (lama >= 5) {
        persenDiskon = 15;
    } else if (lama >= 3) {
        persenDiskon = 10;
    } else {
        persenDiskon = 0;
    }

    return subtotal * persenDiskon / 100;
}

// Fungsi menampilkan struk
void tampilkanStruk(
    char nama[],
    int pilihan,
    int jumlah,
    int lama,
    int subtotal,
    int diskon,
    int total
) {
    int persenDiskon;

    if (lama >= 5) {
        persenDiskon = 15;
    } else if (lama >= 3) {
        persenDiskon = 10;
    } else {
        persenDiskon = 0;
    }

    printf("\n========================================\n");
    printf("          ADVENTURE CAMP\n");
    printf("           STRUK PENYEWAAN\n");
    printf("========================================\n");
    printf("Nama Penyewa    : %s\n", nama);
    printf("Peralatan       : %s\n", namaPeralatan[pilihan]);
    printf("Harga per Hari  : Rp%d\n", hargaPeralatan[pilihan]);
    printf("Jumlah Unit     : %d\n", jumlah);
    printf("Lama Sewa       : %d hari\n", lama);
    printf("----------------------------------------\n");
    printf("Subtotal        : Rp%d\n", subtotal);
    printf("Diskon (%d%%)    : Rp%d\n", persenDiskon, diskon);
    printf("----------------------------------------\n");
    printf("TOTAL BAYAR     : Rp%d\n", total);
    printf("========================================\n");
    printf("Terima kasih telah menggunakan\n");
    printf("layanan Adventure Camp!\n");
    printf("========================================\n");
}

// Fungsi melakukan penyewaan
void sewaPeralatan() {
    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        printf("\nMaaf, kapasitas transaksi sudah penuh.\n");
        printf("Tidak dapat menerima transaksi baru.\n");
        return;
    }

    char nama[50];
    int pilihan;
    int jumlah;
    int lama;
    int subtotal;
    int diskon;
    int total;
    char kembali;

    clearBuffer();

    printf("\n========================================\n");
    printf("          SEWA PERALATAN\n");
    printf("========================================\n");

    printf("Nama Penyewa : ");
    fgets(nama, sizeof(nama), stdin);

    // Menghapus newline dari fgets
    nama[strcspn(nama, "\n")] = '\0';

    // Validasi nama
    while (strlen(nama) == 0) {
        printf("Nama tidak boleh kosong.\n");
        printf("Nama Penyewa : ");
        fgets(nama, sizeof(nama), stdin);
        nama[strcspn(nama, "\n")] = '\0';
    }

    tampilkanPeralatan();

    // Validasi pilihan peralatan
    do {
        printf("Pilih peralatan [1-%d] : ", JUMLAH_PERALATAN);

        if (scanf("%d", &pilihan) != 1) {
            printf("Input harus berupa angka.\n");
            clearBuffer();
            pilihan = 0;
        } else if (pilihan < 1 || pilihan > JUMLAH_PERALATAN) {
            printf("Nomor peralatan tidak tersedia.\n");
        }

    } while (pilihan < 1 || pilihan > JUMLAH_PERALATAN);

    // Validasi jumlah unit
    do {
        printf("Jumlah unit : ");

        if (scanf("%d", &jumlah) != 1) {
            printf("Input harus berupa angka.\n");
            clearBuffer();
            jumlah = 0;
        } else if (jumlah < 1) {
            printf("Jumlah unit minimal 1.\n");
        }

    } while (jumlah < 1);

    // Validasi lama penyewaan
    do {
        printf("Lama penyewaan (hari) : ");

        if (scanf("%d", &lama) != 1) {
            printf("Input harus berupa angka.\n");
            clearBuffer();
            lama = 0;
        } else if (lama < 1) {
            printf("Lama penyewaan minimal 1 hari.\n");
        }

    } while (lama < 1);

    // Perhitungan
    subtotal = hargaPeralatan[pilihan - 1] * jumlah * lama;
    diskon = hitungDiskon(lama, subtotal);
    total = subtotal - diskon;

    // Simpan ke array riwayat
    strcpy(namaPenyewa[jumlahTransaksi], nama);
    strcpy(riwayatPeralatan[jumlahTransaksi],
           namaPeralatan[pilihan - 1]);

    riwayatJumlah[jumlahTransaksi] = jumlah;
    riwayatLama[jumlahTransaksi] = lama;
    riwayatTotal[jumlahTransaksi] = total;

    jumlahTransaksi++;

    // Tampilkan struk
    tampilkanStruk(
        nama,
        pilihan - 1,
        jumlah,
        lama,
        subtotal,
        diskon,
        total
    );

    // Konfirmasi kembali ke menu
    do {
        printf("\nKembali ke menu utama? (Y/T): ");
        scanf(" %c", &kembali);

        if (kembali != 'Y' && kembali != 'y' &&
            kembali != 'T' && kembali != 't') {
            printf("Input hanya boleh Y atau T.\n");
        }

    } while (kembali != 'Y' && kembali != 'y' &&
             kembali != 'T' && kembali != 't');

    if (kembali == 'T' || kembali == 't') {
        printf("\nTerima kasih telah menggunakan layanan Adventure Camp!\n");
        printf("Program selesai.\n");
        exit(0);
    }
}

// Fungsi menampilkan riwayat transaksi
void tampilkanRiwayat() {
    int totalPendapatan = 0;

    printf("\n========================================\n");
    printf("          RIWAYAT TRANSAKSI\n");
    printf("========================================\n");

    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        printf("========================================\n");
        return;
    }

    printf("%-3s %-15s %-25s %-12s\n",
           "No", "Nama", "Peralatan", "Total");
    printf("----------------------------------------\n");

    for (int i = 0; i < jumlahTransaksi; i++) {
        printf("%-3d %-15s %-25s Rp%-10d\n",
               i + 1,
               namaPenyewa[i],
               riwayatPeralatan[i],
               riwayatTotal[i]);

        totalPendapatan += riwayatTotal[i];
    }

    printf("----------------------------------------\n");
    printf("Jumlah Transaksi : %d\n", jumlahTransaksi);
    printf("Total Pendapatan : Rp%d\n", totalPendapatan);
    printf("========================================\n");
}

// Fungsi utama
int main() {
    int pilihan;

    do {
        printf("\n========================================\n");
        printf("           ADVENTURE CAMP\n");
        printf("     SISTEM PENYEWAAN PERALATAN\n");
        printf("========================================\n");
        printf("1. Lihat Daftar Peralatan\n");
        printf("2. Sewa Peralatan\n");
        printf("3. Lihat Riwayat Transaksi\n");
        printf("4. Keluar\n");
        printf("========================================\n");
        printf("Pilih menu [1-4]: ");

        if (scanf("%d", &pilihan) != 1) {
            printf("\nInput harus berupa angka.\n");
            clearBuffer();
            pilihan = 0;
            continue;
        }

        switch (pilihan) {
            case 1:
                tampilkanPeralatan();
                break;

            case 2:
                sewaPeralatan();
                break;

            case 3:
                tampilkanRiwayat();
                break;

            case 4:
                printf("\n========================================\n");
                printf("Terima kasih telah menggunakan\n");
                printf("layanan Adventure Camp!\n");
                printf("Program selesai.\n");
                printf("========================================\n");
                break;

            default:
                printf("\nPilihan menu tidak tersedia.\n");
                printf("Silakan pilih menu 1-4.\n");
        }

    } while (pilihan != 4);

    return 0;
}

