#include <stdio.h>
#include <stdlib.h>

void print_array(int *array, int length);
void heap_sort(int *array, int length);

int main(int argc, char* argv[]){
	if(argc != 3){
		fprintf(stderr, "usage %s seed array_length\n", argv[0]);
		return -1;
	}
	unsigned int seed = atol(argv[1]);
	int length = atoi(argv[2]);
	if(length <= 0){
		fprintf(stderr, "length error\n");
		return -1;
	}
	srand(seed);

	int *array = (int*)malloc(length*sizeof(int));
	if(array == NULL){
		fprintf(stderr, "malloc error\n");
		return -1;
	}
	for(int i = 0; i<length; i++){
		array[i] = rand()%20;
	}
	print_array(array, length);
	heap_sort(array, length);
	print_array(array, length);

	return 0;
}

void print_array(int *array, int length){
	for(int i = 0; i<length; i++){
		printf("%5d", array[i]);
	}
	printf("\n");
}
void heap_sort(int *array, int length){
	for(int end = length-1; end > 0; end--){
		int lastParentIndex = (end-1)>>1;
		int leftChildIndex, rightChildIndex, maxIndex;
		for(int i = lastParentIndex; i>=0; i--){
			leftChildIndex = (i<<1)+1;
			rightChildIndex = (i<<1)+2;
			maxIndex = i;
			if(rightChildIndex <= end && array[rightChildIndex] > array[maxIndex]){
				maxIndex = rightChildIndex;
			}
			if(array[leftChildIndex] > array[maxIndex]){
				maxIndex = leftChildIndex;
			}
			
			if(maxIndex != i){
				int tmp = array[i];
				array[i] = array[maxIndex];
				array[maxIndex] = tmp;
			}
		}
		int tmp = array[end];
		array[end] = array[0];
		array[0] = tmp; 
	}	
	
}
