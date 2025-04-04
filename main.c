#include <stdio.h>
#include <stdlib.h>

#define MAX 10  // Maksimum jumlah simpul

// Fungsi untuk mengurutkan simpul berdasarkan derajatnya (dari terbesar ke terkecil)
void bubbleSort(int n, int derajat[], int urutan[]) {
    int i, j, sementara;

    // Inisialisasi array urutan dengan indeks vertex
    for (i = 1; i <= n; i++) {
        urutan[i] = i;
    }

    // Bubble Sort untuk mengurutkan berdasarkan derajat
    for (i = 1; i <= n - 1; i++) {
        for (j = i + 1; j <= n; j++) {
            if (derajat[urutan[i]] < derajat[urutan[j]]) {
                sementara = urutan[i];
                urutan[i] = urutan[j];
                urutan[j] = sementara;
            }
        }
    }

    printf("\nSetelah Sorting Berdasarkan Derajat (Descending):\n");
        printf("Urutan\tVertex\tDerajat\n");
        for (i = 1; i <= n; i++) {
            printf("%d\t%d\t%d\n", i, urutan[i], derajat[urutan[i]]);
        }

}

// Fungsi untuk melakukan pewarnaan graf dengan Welch-Powell
void pewarnaanWelchPowell(int n, int graph[MAX][MAX]) {
    int derajat[MAX] = {0};      // Menyimpan derajat setiap simpul
    int urutan[MAX];            // Menyimpan urutan simpul setelah diurutkan
    int warna[MAX];             // Menyimpan warna yang diberikan untuk setiap simpul
    int jumlahWarna = 0;         // Jumlah warna yang digunakan
    int i, j, k, bolehDiwarnai;

    // Hitung derajat setiap simpul
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (graph[i][j] == 1) {
                derajat[i]++;
            }
        }
    }

    // Urutkan simpul berdasarkan derajatnya (descending)
    urutkanSimpulBerdasarkanDerajat(n, derajat, urutan);

    // Inisialisasi semua simpul dengan warna -1 (belum diwarnai)
    for (i = 1; i <= n; i++) {
        warna[i] = -1;
    }

    // Pewarnaan graf dengan algoritma Welch-Powell
    for (i = 1; i <= n; i++) {
        int vertex = urutan[i];  // Ambil simpul dengan derajat tertinggi yang belum diwarnai
        if (warna[vertex] == -1) {
            jumlahWarna++;  // Gunakan warna baru
            warna[vertex] = jumlahWarna;

            // Warnai simpul lain yang tidak bertetangga dengan warna yang sama
            for (j = i + 1; j <= n; j++) {
                int tetangga = urutan[j];

                // Pastikan tetangga belum diwarnai dan tidak bertetangga dengan vertex yang sudah diwarnai
                if (warna[tetangga] == -1) {
                    bolehDiwarnai = 1;

                    // Periksa apakah tetangga memiliki tetangga yang sudah memiliki warna yang sama
                    for (k = 1; k <= n; k++) {
                        if (graph[tetangga][k] == 1 && warna[k] == jumlahWarna) {
                            bolehDiwarnai = 0; // Tidak bisa diberi warna yang sama
                            break;
                        }
                    }

                    if (bolehDiwarnai) {
                        warna[tetangga] = jumlahWarna;
                    }
                }
            }
        }
    }

    // Output hasil pewarnaan
    printf("\nPewarnaan Vertex (Welch-Powell):\n");
    for (i = 1; i <= n; i++) {
        printf("Vertex %d -> Warna %d\n", i, warna[i]);
    }
}

// **PROGRAM UTAMA**
int main() {
    system("cls");

    int n, i, j;
    int graph[MAX][MAX];

    printf("Masukkan jumlah simpul: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            printf("Masukkan matriks ketetanggaan %d ke %d: ",i ,j);
            scanf("%d", &graph[i][j]);
        }
    }

    // Tampilkan matriks ketetanggaan
    printf("\nMatriks Ketetanggaan:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    pewarnaanWelchPowell(n, graph);

    return 0;
}

