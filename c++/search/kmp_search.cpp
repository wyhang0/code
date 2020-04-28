#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int normal_search(char *mainString, char *patternString);
int kmp_search(char *mainString, char *patternString);

int main(int argc, char* argv[]){
	if(argc != 3){
		perror("parameter error\n");
		return -1;
	}

	printf("normal search:%s %s %d\n", argv[1], argv[2], normal_search(argv[1], argv[2]));
	printf("kmp search:%s %s %d\n", argv[1], argv[2], kmp_search(argv[1], argv[2]));
	
	return 0;
}

int normal_search(char *mainString, char *patternString){
	int mainStringLen = strlen(mainString);
	int patternStringLen = strlen(patternString);
	for(int i=0; i<mainStringLen; i++){
		for(int j=i,k=0; j<mainStringLen && k<patternStringLen; j++,k++){
			if(mainString[j] == patternString[k] && k==patternStringLen-1){
				return i;
			}
			if(mainString[j] != patternString[k]){
				break;
			}
		}
	}
	return -1;
}
void init_next(char *patternString, int *next){
	int patternStringLen = strlen(patternString);
	next[0] = -1;//next[m]=n;字符串下标为m的最长可以匹配前缀子串的下表为n
	int k = -1;//-1不存在最长可匹配前缀子串
	for(int i=1; i<patternStringLen-1; i++){
		//在坏字符i的 好前缀字符串的 可匹配前缀子串中 找到最长的可匹配前缀子串的下一个字符与坏字符相等的子串末尾字符下标k或者找不到k为-1
		while(k != -1 && patternString[k+1] != patternString[i]){
			k = next[k];
		}
		//k的下一个字符与i的字符相等 则next[i] = k+1
		if(patternString[k+1] == patternString[i]){
			k++;
		}
		next[i] = k;
	}
}
int kmp_search(char *mainString, char *patternString){
	int mainStringLen = strlen(mainString);
	int patternStringLen = strlen(patternString);
	int index = -1;
	
	int *next = (int*)malloc(patternStringLen*sizeof(int));
	if(next == NULL){
		perror("malloc error\n");
		return -1;
	}
	init_next(patternString, next);

	int j=0;
	for(int i=0; i<mainStringLen; i++){
		//找到下标j使模式串该位置的字符与主串i位置的字符相等 或者 找不到模式串从0开始
		while(j>0 && mainString[i]!=patternString[j]){
			j = next[j-1] + 1;
		}
		//如果找到则模式串往后移一位 或者 找不到模式串从0开始
		if(mainString[i] == patternString[j]){
			j++;
		}
		if(j == patternStringLen){
			index = i-j+1;
			break;
		}
	}
	free(next);
	return index;
}

