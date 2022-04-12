/*EL2208 Praktikum Pemecahan Masalah dengan C 2021/2022
*Modul            : 8 - Advanced Algorithms
*Percobaan        : -
*Hari dan Tanggal : Kamis, 14 April 2022
*Nama (NIM)       : -
*Asisten (NIM)    : -
*Nama File        : soal-02.c
*Deskripsi        : -
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_STRING 255

// Silahkan tambahkan fungsi sesuai kebutuhan
// Apabila menggunakan VS Code, tahan tombol Ctrl lalu arahkan ke fungsi untuk melihat deskripsi fungsi

/** @brief fungsi digunakan untuk menampilkan papan catur ke layar 
 * @param dim dimensi dari papan catur
 * @param matrix pointer to pointer of char dari papan catur
**/
void print_papan_catur(int dim, char **matrix){
	// Fungsi digunakan untuk menampilkan papan catur ke layar
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			printf("%c ",matrix[i][j]);
		}
		printf("\n");
	}
}

/** @brief fungsi digunakan untuk mengatur ulang papan catur menjadi sesuai bacaan awal dari file eksternal
 * @param dim dimensi dari papan catur
 * @param matrix pointer to pointer of char dari papan catur
**/
void reset_papan_catur(int dim, char **matrix){
	// Fungsi digunakan untuk menghapus ratu yang telah diletakkan di papan catur
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			if(matrix[i][j]=='Q'){
				matrix[i][j]='X';
			}
		}
	}
}

/** @brief fungsi digunakan untuk menyalin papan catur ke sebuah variabel lain
 * @param dim dimensi dari papan catur
 * @param matrix pointer to pointer of char dari papan catur
 * @param matrix_new pointer to pointer of char dari variabel baru yang akan menjadi tujuan
**/
void salin_papan_catur(int dim, char **matrix, char** matrix_new){
	// Fungsi digunakan untuk menyalin papan catur ke variabel lain
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			matrix_new[i][j] = matrix[i][j];
		}
	}
	return;
}

/** @brief fungsi digunakan untuk membuat papan catur berdasarkan file eksternal
 * @param n_catur pointer to integer dari dimensi dari papan catur
 * @param n_kuda pointer to integer dari jumlah kuda
 * @return pointer to pointer of char dari papan catur
**/
char** buat_papan_catur(int* n_catur, int* n_kuda){
	// Deklarasi variabel
	char file_name[MAX_STRING];
	char each_line[MAX_STRING];
	char temp[MAX_STRING];
	char *token;
	int count = 0;

	// Input nama file
	printf("Masukkan nama file data papan catur: ");
	scanf("%s", file_name);

	// Buka File Eksternal
	FILE* file_catur = fopen(file_name, "r") ;
	// printf("Nama File: %s\n",file_name); // Untuk Debugging

	// Validasi File 
	if(file_catur == NULL){
		printf("File tidak dapat dibuka. Program Berakhir.\n");
		fclose(file_catur);
		exit(1);
	}

	// Baca ukuran papan catur
	fgets(each_line,MAX_STRING,file_catur);
	*n_catur = atoi(each_line);

	// Buat bidak catur
	char** catur = (char**) malloc ((*n_catur)*sizeof(char*));
	for(int i=0;i<*n_catur;i++){
		catur[i] = (char*) malloc ((*n_catur)*sizeof(char));
		for(int j=0;j<*n_catur;j++){
			catur[i][j] = 'X';
		}
	}
	// Baca Banyak Kuda
	fgets(each_line,MAX_STRING,file_catur);
	*n_kuda = atoi(each_line);

	// Baca Koordinat Kuda
	while(fgets(each_line,MAX_STRING,file_catur)){
		strcpy(temp,each_line);
		int column = 0,row_temp = 0;
		token = strtok(temp,",");
		while(token!=NULL){
			if(column == 0){
				row_temp = atoi(token);
			}
			else{
				catur[row_temp][atoi(token)] = 'K';
			}
			column += 1;
			token = strtok(NULL,",");
		}
	}
	return catur;
}

int main(){
	int n_catur, n_kuda, n_ratu;
	char** catur;
	n_ratu = 0;

	catur = buat_papan_catur(&n_catur,&n_kuda);
	printf("Konfigurasi papan catur yang diberikan oleh Fei adalah:\n");
	print_papan_catur(n_catur,catur);

	printf("Jumlah pion ratu terbanyak yang dapat diletakkan di papan catur adalah %d ratu.\n",...);
	printf("Susunan akhir papan catur adalah:\n");
	print_papan_catur(...);
	
	free(catur);
	
	return 0;
}
