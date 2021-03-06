// HanoiTowers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h> 
#include <ctime> 

using namespace std;

int SI[100];
int SC[100];
int n, m, count_limit;

void initial_state() {
	SI[0] = n;
	for (int i = 1; i <= m; i++) {
		SI[i] = 1;
	}
}

void copy_state(int st1[], int st2[]) {
	for (int i = 0; i <= m; i++)
		st1[i] = st2[i];
}

void print_state(int stare[]) {
	cout << "[";
	for (int i = 0; i <= m - 1; i++)
		cout << stare[i] << ", ";
	cout << stare[m] << "]\n";
}

bool final_state(int stare[]) {
	for (int i = 0; i <= m; i++)
		if (stare[i] != n) return false;
	return true;
}

bool valid(int x, int y, int stare[]) {
	if (stare[x] == y) return false;
	if (x <= 0 || y <= 0 || x > m || y > n) return false;
	for (int i = 1; i < x; i++) {
		if (stare[i] == y) return false;
		if (stare[i] == stare[x]) return false;
	}
	return true;
}
void transition_state(int x, int y, int stare[]) {
	stare[x] = y;
}

void random_strategy() {
	copy_state(SC, SI);
	int count = 0, count2 = 0;
	int x, y;
	while (final_state(SC) != 1) {
		x = rand() % m + 1;
		y = rand() % n + 1;
		if (valid(x, y, SC)) {
			transition_state(x, y, SC);
			print_state(SC);
			count++;
			count2++;
		}
		if (count > count_limit) {
			copy_state(SC, SI);
			count = 0;
		}
	}

	cout << "Iteratii:" << count2 << " (" << count << ")\n";

}

int count_score(int stare[]) {
	return stare[m];
}

void hill_climbing()
{
	copy_state(SC, SI);
	int count = 0, count2 = 0;
	int x, y;
	int AUX[100];
	while (final_state(SC) != 1) {
		x = rand() % m + 1;
		y = rand() % n + 1;
		if (valid(x, y, SC)) {
			copy_state(AUX, SC);
			transition_state(x, y, SC); // SC devine starea urmatoare si AUX e starea curenta
			if (count_score(SC) >= count_score(AUX)) {
				print_state(SC);
				count++;
				count2++;
			}
			else {
				copy_state(SC, AUX); // SC revine la loc
			}

		}
		if (count > count_limit) {
			copy_state(SC, SI);
			count = 0;
		}
	}
	cout << "Iteratii:" << count2 << " (" << count << ")\n";
}

void add_in_list(int a[1000][100], int b[], int c) {
	for (int i = 0; i <= m; i++)
		a[c][i] = b[i];
}


int to_number(int stare[]) {
	int number = 0;
	for (int i = 0; i <= m; i++)
		number = number * 10 + stare[i];
	return number;
}

bool is_visited(long stari_vizitate[], int stare[], int limit) {
	int number = to_number(stare);
	for (int i = 1; i <= limit; i++) {
		if (stari_vizitate[i] == number) return true;
	}
	return false;
}

void bkt(int n, int m) {
	copy_state(SC, SI);
	int AUX[100];
	int lista_stari[1000][100];
	long stari_vizitate[10000];
	stari_vizitate[1] = to_number(SI);
	int count1 = 1; int count2 = 1;
	add_in_list(lista_stari, SI, 1);
	int ok = 0;
	while (final_state(SC) != 1) {
		for (int i = 1; i <= m; i++) {
			if (ok == 0)
				for (int j = n; j >= 1; j--) {
					if (valid(i, j, SC) && ok == 0) {
						copy_state(AUX, SC);
						transition_state(i, j, AUX);
						if (is_visited(stari_vizitate, AUX, count2) == 0) {
							copy_state(SC, AUX);
							ok = 1;
							count1++;
							add_in_list(lista_stari, SC, count1);
							count2++;
							stari_vizitate[count2] = to_number(SC);

						}

					}
				}
		}
		if (ok == 0) {
			count1--;
			copy_state(SC, lista_stari[count1]);
		}
		ok = 0;
	}
	for (int i = 1; i <= count1; i++)
		print_state(lista_stari[i]);
	cout << "Iteratii:" << count1 << endl;
}

int main()
{
	srand(time(NULL));
	cout << "nr turnuri = "; cin >> n;
	cout << "nr piese = "; cin >> m;

	count_limit = m * n * 10;

	initial_state();

	/* Random strategy*/

	cout << "Random Strategy:\n";
	//copy_state(SC, SI);
	clock_t begin = clock();
	random_strategy();
	clock_t end = clock();
	printf("Timp: %.2fs\n", (double)(end - begin) / CLOCKS_PER_SEC);
	cout << endl; 

		/* Hill Climbing */
		cout << "Hill Climbing:\n";
	//copy_state(SC, SI);
	begin = clock();
	hill_climbing();
	end = clock();
	printf("Timp: %.2fs\n", (double)(end - begin) / CLOCKS_PER_SEC);

	/*BKT*/
	cout << "BKT:\n";
	copy_state(SC, SI);
	bkt(n, m);
	return 0;
}