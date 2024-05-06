#include <iostream>
#include <fstream>
#include <string>
#include <list>

int main()
{
    //get_data();

    std::ifstream file("data.txt");
    if (!file.is_open()) {
		std::cerr << "Failed to open file. Aborting ;((" << std::endl;
		return 1;
	}
    int n;
	std::string line;
	file >> line;
	std::string TargetLine = "data.10:";
	while (line != TargetLine){
		file >> line;
	}

	file >> n;

	int* tablica = new int[n];

	int* p = new int[n];
	int* w = new int[n];
	int* d = new int[n];

    for (int i = 0; i < n; i++) {
		file >> p[i] >> w[i] >> d[i];
	}

	file.close();

	int N = 1 << n;

	int* F = new int[N];
	F[0] = 0;
	std::list<int> permutation;
	std::list<int> task;
	int time = 0;




	for (int kombinacja = 1; kombinacja < N; kombinacja++) {
		time = 0;
		for (int i = 0; i < n; i++) {
			if (kombinacja & (1 << i)) {
				permutation.push_back(kombinacja ^ (1 << i));
				task.push_back(i);
				time += p[i];
			}
		}
		F[kombinacja] = INT_MAX;
		while (!task.empty()) {
			int i = task.front();
			int node = permutation.front();
			F[kombinacja] = std::min(F[kombinacja], F[node] + w[i] * std::max(0, time - d[i]));
			task.pop_front();
			permutation.pop_front();
		}
	}


	std::cout << "Cmax: " << F[N - 1] << std::endl;

	int sekwencja = N - 1;
	//std::list<int> kolejnosc;
	int* kolejnosc = new int[n];
	int najlepsza_podsekwencja = sekwencja;


	//for (int element = 0; element < n; element++) {
	//	najlepsza_podsekwencja = sekwencja;
	//	for (int nr_podsekwencji = 0; nr_podsekwencji < n; nr_podsekwencji++) {
	//		if (!(sekwencja & (1 << nr_podsekwencji))) {
	//			continue;
	//		}
	//		int sprawdzana_podsekwencja = sekwencja ^ (1 << nr_podsekwencji);
	//		if (F[najlepsza_podsekwencja] > F[sprawdzana_podsekwencja]) {
	//			najlepsza_podsekwencja = sprawdzana_podsekwencja;

	//			kolejnosc[element] = nr_podsekwencji;
	//		}
	//	}
	//	std::cout << kolejnosc[element] << std::endl;
	//}


	//while(najlepsza_podsekwencja){
	for (int kombinacja = 0; kombinacja < n; kombinacja++) {
		for (int i = 0; i < n; i++) {
			if (najlepsza_podsekwencja & (1 << i)) {
				permutation.push_back(najlepsza_podsekwencja ^ (1 << i));
				task.push_back(i);
				time += p[i];
			}
		}
		int temp = INT_MAX;
		while (!task.empty()) {
			int i = task.front();
			int node = permutation.front();
			if (temp > (F[node] + w[i] * std::max(0, time - d[i]))){
				temp = F[node] + w[i] * std::max(0, time - d[i]);
				kolejnosc[kombinacja] = i;
				najlepsza_podsekwencja = node;
			}
			task.pop_front();
			permutation.pop_front();
		}
		std::cout << kolejnosc[kombinacja] + 1 << std::endl;
	}



	delete[] p;
	delete[] w;
	delete[] d;
}

void get_data() {
	std::string url = "http://mariusz.makuchowski.staff.iiar.pwr.wroc.pl/download/courses/sterowanie.procesami.dyskretnymi/lab.instrukcje/lab02.witi/witi.data.txt";
	std::string command = "curl " + url + " > buffer.txt";
	int result = system(command.c_str());
	system("cls");
	if (result != 0) {
		std::cerr << "Failed to fetch website content. Working on saved data:" << std::endl;
	}
	else
	{
		std::cout << "Data fetched successfully. Working on data from website:" << std::endl;
		std::ifstream  src("buffer.txt", std::ios::binary);
		std::ofstream  dst("data.txt", std::ios::binary);
		dst << src.rdbuf();
		src.close();
		dst.close();
		system("del buffer.txt");
	}
}









// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
