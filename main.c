#include <stdio.h>

#define MAX 10  // Maksimum jumlah simpul

// Fungsi untuk mengurutkan simpul berdasarkan derajatnya (dari terbesar ke terkecil)
void sortVerticesByDegree(int n, int degree[], int sorted[]) {
    int i, j, temp;

    // Inisialisasi array sorted dengan indeks vertex
    for (i = 1; i <= n; i++) {
        sorted[i] = i;
    }

    // Bubble Sort untuk mengurutkan berdasarkan derajat
    for (i = 1; i <= n - 1; i++) {
        for (j = i + 1; j <= n; j++) {
            if (degree[sorted[i]] < degree[sorted[j]]) {
                temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }

    printf("\nSetelah Sorting Berdasarkan Derajat (Descending):\n");
        printf("Urutan\tVertex\tDerajat\n");
        for (i = 1; i <= n; i++) {
            printf("%d\t%d\t%d\n", i, sorted[i], degree[sorted[i]]);
        }

}

// Fungsi untuk melakukan pewarnaan graf dengan Welch-Powell
void welchPowellColoring(int n, int graph[MAX][MAX]) {
    int degree[MAX] = {0};      // Menyimpan derajat setiap simpul
    int sorted[MAX];            // Menyimpan urutan simpul setelah diurutkan
    int color[MAX];             // Menyimpan warna yang diberikan untuk setiap simpul
    int usedColors = 0;         // Jumlah warna yang digunakan
    int i, j, k, colorUsed;

    // Hitung derajat setiap simpul
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (graph[i][j] == 1) {
                degree[i]++;
            }
        }
    }

    // Urutkan simpul berdasarkan derajatnya (descending)
    sortVerticesByDegree(n, degree, sorted);

    // Inisialisasi semua simpul dengan warna -1 (belum diwarnai)
    for (i = 1; i <= n; i++) {
        color[i] = -1;
    }

    // Pewarnaan graf dengan algoritma Welch-Powell
    for (i = 1; i <= n; i++) {
        int vertex = sorted[i];  // Ambil simpul dengan derajat tertinggi yang belum diwarnai
        if (color[vertex] == -1) {
            usedColors++;  // Gunakan warna baru
            color[vertex] = usedColors;

            // Warnai simpul lain yang tidak bertetangga dengan warna yang sama
            for (j = i + 1; j <= n; j++) {
                int neighbor = sorted[j];

                // Pastikan neighbor belum diwarnai dan tidak bertetangga dengan vertex yang sudah diwarnai
                if (color[neighbor] == -1) {
                    colorUsed = 1;

                    // Periksa apakah neighbor memiliki tetangga yang sudah memiliki warna yang sama
                    for (k = 1; k <= n; k++) {
                        if (graph[neighbor][k] == 1 && color[k] == usedColors) {
                            colorUsed = 0; // Tidak bisa diberi warna yang sama
                            break;
                        }
                    }

                    if (colorUsed) {
                        color[neighbor] = usedColors;
                    }
                }
            }
        }
    }

    // Output hasil pewarnaan
    printf("\nPewarnaan Vertex (Welch-Powell):\n");
    for (i = 1; i <= n; i++) {
        printf("Vertex %d -> Warna %d\n", i, color[i]);
    }
}

// **PROGRAM UTAMA**
int main() {
    int n, i, j;
    int graph[MAX][MAX];

    printf("Masukkan jumlah simpul: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            printf("Masukkan matriks ketetanggaan %d ke %d:\n",i ,j);
            scanf("%d", &graph[i][j]);
        }
    }

    welchPowellColoring(n, graph);

    return 0;
}

