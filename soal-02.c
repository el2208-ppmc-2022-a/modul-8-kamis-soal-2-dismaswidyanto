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

#define MAX_STRING 255

void print_papan_catur(int dim, char **matrix){
	// Fungsi digunakan untuk menampilkan papan catur ke layar
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			printf("%c ",matrix[i][j]);
		}
		printf("\n");
	}
}

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

void salin_papan_catur(int dim, char **matrix, char** matrix_new){
	// Fungsi digunakan untuk menyalin papan catur ke variabel lain
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			matrix_new[i][j] = matrix[i][j];
		}
	}
	// printf("Salin papan catur berhasil\n");
	return;
}

int taruh_ratu(char** chess, int dim, int row, int column){
	// Cek apakah ada kuda/ratu di kolom/baris bersangkutan
	for(int i=0;i<dim; i++){
		if(chess[i][column]!='X'||chess[row][i]!='X'){
			return 0;
		}
	}
	// Cek apakah ada kuda/ratu di diagonal kiri bawah
	for(int i=row, j=column;i < dim && j>=0;i++,j--){
		if(chess[i][j]!='X'){
			return 0;
		}
	}
	// Cek apakah ada kuda/ratu di diagonal kiri atas
	for(int i=row, j=column;i>=0 && j>=0;i--,j--){
		if(chess[i][j]!='X'){
			return 0;
		}
	}
	// Cek apakah ada kuda/ratu di diagonal kanan bawah
	for(int i=row, j=column;i < dim && j < dim;i++,j++){
		if(chess[i][j]!='X'){
			return 0;
		}
	}
	// Cek apakah ada kuda/ratu di diagonal kanan atas
	for(int i=row, j=column;i>=0 && j < dim;i--,j++){
		if(chess[i][j]!='X'){
			return 0;
		}
	}

	// Cek apakah ada kuda di sisi atas
	if(row-2>=0){
		if(column+1<dim){
			if(chess[row-2][column+1]=='K'){
				return 0;
			}
		}
		if(column-1>=0){
			if(chess[row-2][column-1]=='K'){
				return 0;
			}
		}
	}

	// Cek apakah ada kuda di sisi kanan
	if(column+2 < dim){
		if(row+1<dim){
			if(chess[row+1][column+2]=='K'){
				return 0;
			}
		}
		if(row-1>=0){
			if(chess[row-1][column+2]=='K'){
				return 0;
			}
		}
	}

	// Cek apakah ada kuda di sisi kiri
	if(column-2 >= 0){
		// printf("row %d, Column %d\n",row,column);
		if(row+1<dim){
			if(chess[row+1][column-2]=='K'){
				return 0;
			}
			// printf("No horse\n");
		}
		if(row-1>=0){
			// printf("Masuk sini\n");
			if(chess[row-1][column-2]=='K'){
				return 0;
			}
		}
	}
	// 3,4 2,2
	// Cek apakah ada kuda di sisi bawah
	if(row+2 < dim){
		if(column+1<dim){
			if(chess[row+2][column+1]=='K'){
				return 0;
			}
		}
		if(column-1>=0){
			if(chess[row+2][column-1]=='K'){
				return 0;
			}
		}
	}
	return 1;
}

int isi_papan_catur(char** catur, int dim, int row, int* total_ratu, int max_ratu){
	// Kasus basis, seluruh ratu telah diletakkan
	if(*total_ratu == max_ratu){
		return 1;
	}
	else if(row==dim){
		if(*total_ratu!=max_ratu){
			return 0;
		}
	}
	// Letakkan ratu satu per satu pada setiap kolom
	for(int i=0;i<dim;i++){
		// Periksa apakah ratu bisa diletakkan di papan
		if(taruh_ratu(catur,dim,row,i)){
			catur[row][i]='Q';
			*total_ratu+=1;
			// Periksa apakah ratu bisa diletakkan di kolom selanjutnya
			if(isi_papan_catur(catur,dim,row+1,total_ratu,max_ratu)){
				return 1;
			}
			// Backtrack apabila ratu tidak bisa diletakkan di kolom bersangkutan
			catur[row][i]='X';
			*total_ratu-=1;
		}
	}
	// Apabila ratu tidak bisa diletakkan di semua kolom pada baris bersangkutan, maka return false
	if(max_ratu==dim){
		return 0;   
	}
	else{
		isi_papan_catur(catur,dim,row+1,total_ratu,max_ratu);
	}
}

int hitung_maks_ratu(char** catur, int n_catur, int* n_ratu, char** final_catur){
	int ratu_final = 0;
	// Salin dulu untuk kasus apabila tidak ditemukan solusi
	salin_papan_catur(n_catur,catur,final_catur);
	for(int i=1;i<=n_catur;i++){
		reset_papan_catur(n_catur,catur);
		if (isi_papan_catur(catur,n_catur,0,n_ratu,i)){
			ratu_final = *n_ratu;
			*n_ratu=0;
			salin_papan_catur(n_catur,catur,final_catur);
		}
	}
	return ratu_final;
}

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
	print_papan_catur(n_catur,catur); // Print untuk debugging

	char** final_catur = (char**) malloc (n_catur*sizeof(char*));
	for(int i=0;i<n_catur;i++){
		final_catur[i] = (char*) malloc (n_catur*sizeof(char));
	}

	int ratu_max = hitung_maks_ratu(catur,n_catur,&n_ratu,final_catur);
	printf("Jumlah pion ratu terbanyak yang dapat diletakkan di papan catur adalah %d ratu.\n",ratu_max);
	printf("Susunan akhir papan catur adalah:\n");
	print_papan_catur(n_catur,final_catur);
	return 0;
	free(catur);
	free(final_catur);
}
