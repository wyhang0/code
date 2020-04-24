#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(int *array, int length);
void quick_sort(int *array, int start, int end);
void shell_sort(int *array, int length);
void merge_sort(int *array, int length);

int main(int argc, char* argv[]){
	if(argc != 3){
		fprintf(stderr, "usage %s seed array_length\n", argv[0]);
		return -1;
	}

	unsigned int seed = atol(argv[1]);
	int length = atol(argv[2]);

	if(length <= 0){
		fprintf(stderr, "lenght less zero\n");
		return -1;
	}

	srand(seed);
	int *array = (int*)malloc(length*sizeof(int));
	if(array == NULL){
		fprintf(stderr, "malloc error\n");
		return -1;
	}
	bzero(array, length*sizeof(int));

	for(int i=0; i<length; i++){
		array[i] = rand()%50;
	}

	print_array(array, length);
//	quick_sort(array, 0, length-1);
//	shell_sort(array, length);
	merge_sort(array, length);
	print_array(array, length);

	free(array);
	return 0;
}

void print_array(int *array, int length){
	for(int i=0; i<length; i++){
		printf("%5d", array[i]);
	}
	printf("\n");
}
void quick_sort(int *array, int start, int end){
	if(start >= end)
		return;
	int i = start;
	int j = end;
	int flag = array[i];

	while(i < j){
		while(i < j && flag <= array[j]){
			j--;
		}
		array[i] = array[j];
		while(i < j && flag >= array[i]){
			i++;
		}
		array[j] = array[i];
	}
	array[i] = flag;

	quick_sort(array, start, i-1);
	quick_sort(array, i+1, end);
}
void shell_sort(int *array, int length){
	int tmp,i,j,dt;
	for(dt = length>>1; dt >= 1; dt >>= 1){
		for(i=dt; i<length; i++){
			tmp = array[i];
			for(j=i-dt; j>=0 && array[j]>tmp; j-=dt){
			       array[j+dt] = array[j];
			}
	 		array[j+dt] = tmp;
		}
	}
}

void merge(int *array, int *tmp, int start, int middle, int end){
	int i=start, j=middle+1, k=start;
	while(i<=middle && j<=end){
		if(array[i]>array[j]){
			tmp[k++] = array[j++];
		}else{
			tmp[k++] = array[i++];
		}
	}
	while(i<=middle){
		tmp[k++] = array[i++];
	}
	while(j<=end){
		tmp[k++] = array[j++];
	}
	memcpy(array+start, tmp+start, (end-start+1)*sizeof(int));
}
void merge_sort(int *array, int *tmp,  int start, int end){
	if(start >= end)
		return;
	int middle = start + ((end-start)>>1);
	merge_sort(array, tmp, start, middle);
	merge_sort(array, tmp, middle+1, end);
	merge(array, tmp, start, middle, end);
}
void merge_sort(int *array, int length){
	int *tmp = (int*)malloc(length*sizeof(int));
	if(tmp == NULL){
		return;
	}

	merge_sort(array, tmp, 0, length-1);
	free(tmp);
}
