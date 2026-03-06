#include <iostream>
#include <clocale>
#include <cstdlib>
using namespace std;
//Функция меню
void menu() {
	cout<< "1. Ввести матрицу" << endl
		<< "2. Метод Гаусса" << endl
		<< "3. Проверка" << endl
		<< "4. Вывод текущей матрицы" << endl
		<< "5. Вывод исходной матрицы" << endl
		<< "6. Выход из программы" << endl;
}

void input_matrix(int n, double** arr, double* barr) {
	//Заполнение массива данными
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			double A;
			cin >> A;
			arr[i][j] = A;
		}
	}
	//столбец b
	cout << "Введите столбец свободных членов:" << endl;
	for (int i = 0; i < n; i++) {
		double b;
		cin >> b;
		barr[i] = b;
	}
}
void output_matrix(int n, double**arr, double*barr) {
	cout << "Массив элементов матрицы" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
	//вывод массива b
	cout << "Массив свободных членов b" << endl;
	for (int i = 0; i < n; i++) {
		cout << barr[i] << endl;
	}
}
void output_copy_matrix(int n, double** copy_arr, double* copy_barr) {
	cout << "Массив элементов матрицы" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << copy_arr[i][j] << "\t";
		}
		cout << endl;
	}
	//вывод массива b
	cout << "Массив свободных членов b" << endl;
	for (int i = 0; i < n; i++) {
		cout << copy_barr[i] << endl;
	}
}
//метод Гаусса
void method_Gauss(int n, double** arr, double* barr) {
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			double alpha = arr[j][i] / arr[i][i];
			for (int k = i; k < n; k++) {
				arr[j][k] -= alpha * arr[i][k];
			}
			barr[j] -= alpha * barr[i];
		}
	}

}
//функция с выводом Гаусса построчно
void method_Gauss_str(int n, double** arr, double* barr) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			double alpha = arr[j][i] / arr[i][i];
			for (int k = i; k < n; k++) {
				arr[j][k] -= alpha * arr[i][k];
			}
			//
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					cout << arr[i][j] << "\t";
				}
				cout << endl;
			}
			//вывод массива b
			cout << "Массив свободных членов b" << endl;
			for (int i = 0; i < n; i++) {
				cout << barr[i] << endl;
			}
			cout << "---------------------"<<endl;
			barr[j] -= alpha * barr[i];
		}
	}

}
//функция, меняющая местами строки
void swap_str(int n, double** arr, double* barr) {
	double* temp;
	double temp_b;
	for (int i = 0; i < n; i++) {
		if (arr[i][0] == 0) {
			for (int j = i+1; j < n; j++) {
				if (arr[j][0] != 0) {
					temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;

					temp_b = barr[i];
					barr[i] = barr[j];
					barr[j] = temp_b;
					break;
				}
			}
		}
	}
}
//поиск x
void found_x(int n, double** arr, double* barr, double* x) {
	for (int i = n - 1; i >= 0; i--) {
		x[i] = barr[i] / arr[i][i];
		for (int j = i - 1; j >= 0; j--) {
			barr[j] -= arr[j][i] * x[i];
		}
	}
}


//вывод вектора 
void output_x(int n, double* x) {
	for (int i = 0; i < n; i++) {
		cout << x[i] << endl;
	}
}
//проверка матрицы на количество решений или их отсутствие
// 0 - нет решений
// 1 - единственное решение
// 2 - множество решений
int check_matrix(int n, double** arr, double* barr) {
	int flag;
	int count_zero_str = 0;
	for (int i = 0; i < n; i++) {
		flag = 1;
		for (int j = 0; j < n; j++) {
			if (arr[i][j] != 0) {
				flag = 0;
				break;
			}
		}
		if (flag == 1) {
			if (barr[i] != 0) {
				return 0;
			}
			else {
				count_zero_str+=1;
			}
		}
	}
	if (count_zero_str > 0) {
		return 2;
	}
	return 1;
}

//проверка, когда единственное решение
void control(int n, double** copy_arr, double* copy_barr, double* x) {
	double* cntr = new double[n];
	for (int i = 0; i < n; i++) {
		double sumn = 0.0;
		for (int j = 0; j < n; j++) {
			sumn += copy_arr[i][j] * x[j];
		}
		cntr[i] = sumn;
	}
	cout << "Ax = " << endl;
	output_x(n, cntr);
	for (int i = 0; i < n; i++) {
		cntr[i] -= copy_barr[i];
	}
	cout << "Ax - b = " << endl;
	output_x(n, cntr);
	delete[]cntr;
}
//функция для проверки столбца нулей
int control_stlb(int n, double** arr, double* barr) {
	int flag;
	int count_zero_stlb = 0;
	for (int j = 0; j < n; j++) {
		flag = 1;
		for (int i = 0; i < n; i++) {
			if (arr[i][j] != 0) {
				flag = 0;
				break;
			}
		}
		if (flag == 1) {
			count_zero_stlb += 1;
		}
	}
	if (count_zero_stlb > 0) {
		return 0;
	}
	return 1;
}
//пропуск нулевого столбца
void control_null(int n, double** arr, double* barr) {
	int zero_stlb = -1;  
	for (int j = 0; j < n; j++) {
		bool zero_column = true;
		for (int i = 0; i < n; i++) {
			if (arr[i][j] != 0) {
				zero_column = false;
				break;
			}
		}
		if (zero_column) {
			zero_stlb = j;  
			break;
		}
	}
	if (zero_stlb != -1) {
		// Сохраняем нулевой столбец во временный массив
		double* temp_zero_column = new double[n];
		for (int i = 0; i < n; i++) {
			temp_zero_column[i] = arr[i][zero_stlb];
		}
		// Заменяем нулевой столбец на массив b
		for (int i = 0; i < n; i++) {
			arr[i][zero_stlb] = barr[i];
		}
		for (int i = 0; i < n; i++) {
			barr[i] = temp_zero_column[i];
		}
		delete[] temp_zero_column;
	}
}

int main() {
	setlocale(LC_ALL, "Rus");
	int flag = 1, chek, chek_1, number, n, flag_1 = 0;
	do {
		cout << "Введите размер квадратной матрицы: ";
		cin >> n;
	} while (n <= 0);
	//выделение динамической памяти и создание двумерного массива и массива b
	double** arr = new double* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new double[n];
	}
	double** copy_arr = new double* [n];
	double* copy_barr = new double[n];
	double* barr = new double[n];
	double* x_stlb = new double[n];
	//меню
	while (flag) {
		menu();
		cout << "Введите нужный пункт меню: ";
		cin >> number;
		switch (number)
		{
		case 1:
			flag_1 = 1;
			input_matrix(n, arr, barr);
			//заполнение копии массива
			for (int i = 0; i < n; i++) {
				copy_arr[i] = new double[n];
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					copy_arr[i][j] = arr[i][j];
				}
			}
			//заполнение копии для массива b
			for (int i = 0; i < n; i++) {
				copy_barr[i] = barr[i];
			}
			cout << "-------------------------------------------------------------------" << endl;
			break;
		case 2:
			if (flag_1 == 0) {
				flag_1 = 1;
				input_matrix(n, arr, barr);
				//заполнение копии массива
				for (int i = 0; i < n; i++) {
					copy_arr[i] = new double[n];
				}
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						copy_arr[i][j] = arr[i][j];
					}
				}
				//заполнение копии для массива b
				for (int i = 0; i < n; i++) {
					copy_barr[i] = barr[i];
				}
				cout << "-------------------------------------------------------------------" << endl;
				swap_str(n, arr, barr);
				method_Gauss_str(n, arr, barr);
				//method_Gauss(n, arr, barr);
				chek = check_matrix(n, arr, barr);
				if (chek == 1) {
					output_matrix(n, arr, barr);
					cout << "Решение:" << endl;
					found_x(n, arr, barr, x_stlb);
					output_x(n, x_stlb);
				}
				else if (chek == 2) {
					output_matrix(n, arr, barr);
					cout << "Данная матрица имеет множество решений" << endl;
				}
				else if (chek == 0) {
					output_matrix(n, arr, barr);
					cout << "Нет решений" << endl;
				}
				cout << "-------------------------------------------------------------------" << endl;
			}
			swap_str(n, arr, barr);
			chek_1 = control_stlb(n, arr, barr);
			if (chek_1 == 0) {
				control_null(n, arr, barr);
				method_Gauss(n, arr, barr);
				chek = check_matrix(n, arr, barr);
				if (chek == 2) {
					output_copy_matrix(n, copy_arr, copy_barr);
					cout << "Данная матрица имеет множество решений" << endl;
				}
				else {
					output_copy_matrix(n, copy_arr, copy_barr);
					cout << "Нет решений" << endl;
				}
				break;
			}
			else {
				method_Gauss_str(n, arr, barr);
				chek = check_matrix(n, arr, barr);
				if (chek == 1) {
					output_matrix(n, arr, barr);
					cout << "Решение:" << endl;
					found_x(n, arr, barr, x_stlb);
					output_x(n, x_stlb);
				}
				else if (chek == 2) {
					output_matrix(n, arr, barr);
					cout << "Данная матрица имеет множество решений" << endl;
				}
				else if (chek == 0) {
					output_matrix(n, arr, barr);
					cout << "Нет решений" << endl;
				}
				cout << "-------------------------------------------------------------------" << endl;
			}
			break;
		case 3:
			if (flag_1 == 0) {
				flag_1 = 1;
				input_matrix(n, arr, barr);
				//заполнение копии массива
				for (int i = 0; i < n; i++) {
					copy_arr[i] = new double[n];
				}
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						copy_arr[i][j] = arr[i][j];
					}
				}
				//заполнение копии для массива b
				for (int i = 0; i < n; i++) {
					copy_barr[i] = barr[i];
				}
				cout << "-------------------------------------------------------------------" << endl;
				control(n, copy_arr, copy_barr, x_stlb);
				cout << "-------------------------------------------------------------------" << endl;
			}
			control(n, copy_arr, copy_barr, x_stlb);
			cout << "-------------------------------------------------------------------" << endl;
			break;
		case 4:
			if (flag_1 == 0) {
				flag_1 = 1;
				input_matrix(n, arr, barr);
				//заполнение копии массива
				for (int i = 0; i < n; i++) {
					copy_arr[i] = new double[n];
				}
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						copy_arr[i][j] = arr[i][j];
					}
				}
				//заполнение копии для массива b
				for (int i = 0; i < n; i++) {
					copy_barr[i] = barr[i];
				}
				output_matrix(n, arr, barr);
				cout << "-------------------------------------------------------------------" << endl;
			}
			output_matrix(n, arr, barr);
			cout << "-------------------------------------------------------------------" << endl;
			break;
		case 5:
			if (flag_1 == 0) {
				flag_1 = 1;
				input_matrix(n, arr, barr);
				//заполнение копии массива
				for (int i = 0; i < n; i++) {
					copy_arr[i] = new double[n];
				}
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						copy_arr[i][j] = arr[i][j];
					}
				}
				//заполнение копии для массива b
				for (int i = 0; i < n; i++) {
					copy_barr[i] = barr[i];
				}
				output_copy_matrix(n, copy_arr, copy_barr);
				cout << "-------------------------------------------------------------------" << endl;
			}
			output_copy_matrix(n, copy_arr, copy_barr);
			cout << "-------------------------------------------------------------------" << endl;
			break;
		case 6:
			if (flag_1 == 0) {
				flag_1 = 1;
				input_matrix(n, arr, barr);
				//заполнение копии массива
				for (int i = 0; i < n; i++) {
					copy_arr[i] = new double[n];
				}
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						copy_arr[i][j] = arr[i][j];
					}
				}
				//заполнение копии для массива b
				for (int i = 0; i < n; i++) {
					copy_barr[i] = barr[i];
				}
				flag = 0;
				exit(1);
			}
			flag = 0;
			exit(1);
		default:
			cout << "Неверный пункт меню! Повторите попытку! " << endl;
		}
	};
	//очистка 
	for (int i = 0; i < n; i++) {
		delete[]arr[i];
		delete[] copy_arr[i];
	}
	delete[]arr;
	delete[]copy_arr;
	delete[]barr;
	delete[]copy_barr;
	delete[]x_stlb;

}

