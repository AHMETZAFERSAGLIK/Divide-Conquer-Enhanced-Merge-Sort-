#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void print_arr(vector<int>& arr, int first, int last)
{
	for (int i = first; i <= last; i++)
	{
		string if_eol = (i == last) ? "\n" : ", ";

		cout << arr[i] << if_eol;
	}
}

void merge(vector<int>& arr, int first, int mid, int last){ 

    int size1 = mid - first + 1; 
    int size2 = last - mid; 
  
    int left_part[size1];
	int right_part[size2]; 
  
    for (int i = 0; i < size1; i++) left_part[i] = arr[first + i]; 
    for (int i = 0; i < size2; i++) right_part[i] = arr[mid + 1 + i]; 
  
	int k = first;
	int i = 0;
	int j = 0;

    while( i < size1 && j < size2 ){ 
        if( left_part[i] <= right_part[j] ){ 
            arr[k] = left_part[i];
            i++;
        }
        else{
            arr[k] = right_part[j]; 
            j++;
        }
        k++; 
    } 
  
    while( i < size1 ){ 
        arr[k++] = left_part[i++]; 
    } 
    while( j < size2 ){ 
        arr[k++] = right_part[j++];
    } 
}



void func(vector<int>& arr, int first, int last){
	int m = 0;
	int k = first;

	while( k < last ){
		if( arr[k] > arr[k+1] ){
			int tmp = arr[k];
			arr[k] = arr[k+1];
			arr[k+1] = tmp;
		}
		k += 2;
	}

	k = first + 1;
	int A[last - first + 1];

	while( k <= last ){
		A[m] = arr[k];
		m+=1;
		k+=2;
	}

	int x = first;
	k = first;

	while( k <= last ){
		arr[x] = arr[k];
		x+=1;
		k+=2;
	}
	
	k = 0;

	while( k < m ){
		arr[x] = A[k];
		x+=1;
		k+=1;
	}
}

void sortt(vector<int>& arr, vector<int>& map, int lvl){
    int exit_flag = 1;

    int min_val = 999999;
    int min_idx = -1;

    int max_val = -1;
    int max_idx = -1;

    int map_idx1 = -1;
    int map_idx2 = -1;

    for(int i = 0; i < map.size(); i++){
        int idx = map[i];

        if( idx == -1 ) continue;
        else{
            exit_flag = 0;
        }

        if( arr[idx] <= min_val ){
            min_val = arr[idx];
            min_idx = idx;
            map_idx1 = i;
        }

        if( arr[idx] >= max_val ){
            max_val = arr[idx];
            max_idx = idx;
            map_idx2 = i;
        }

    }

    if( !exit_flag ){

        arr[min_idx] = arr[map[lvl]];
        arr[max_idx] = arr[map[map.size()-1-lvl]];
        arr[map[lvl]] = min_val;
        arr[map[map.size()-1-lvl]] = max_val;

        cout << "Min: " << min_val << " Max: " << max_val << endl;

        map[map_idx1] = -1;
        map[map_idx2] = -1;

        sortt(arr, map, lvl+1);
    }

}
  
void sort(vector<int>& arr, int first, int last)
{
	if( first < last ){

		print_arr(arr, first, last);

		func(arr, first, last);
		int m = first + ( last - first ) / 2;

        cout << "Min_max unsorted: "; print_arr(arr, first, m);
        vector<int> map;
        for(int i = first; i <= m; i++) map.push_back(i);
		sortt(arr, map, 0);
        cout << "Min_max sorted: "; print_arr(arr, first, m);
		sort(arr, m + 1, last);

		merge(arr, first, m, last);
	}
}

int main(int argc, char *argv[])
{

	vector<int> all_values;


	try {
		
		string filename = argv[1];

		ifstream myfile(filename);

		
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				int number = stoi(line);
				all_values.push_back(number);
			}

			sort(all_values, 0, all_values.size() - 1);

			print_arr(all_values, 0, all_values.size() - 1);
		}
		else
		{
			cout << "File is not available." << endl;
			throw;
		}

	}
	catch (const ifstream::failure& e)
	{
		cerr << "Exception opening the file!" << endl;
		return -1;
	}
	catch (...)
	{
		cerr << "Something's wrong!" << endl;
		return -1;
	}



	return 0;
}