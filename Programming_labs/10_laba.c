#include <stdio.h>
#include <string.h>

int NOD(int, int);
int NOK(int, int);
void Array(int *, int);

int NOD(int a, int b) {
    while (a && b) {
        if (a >= b) {
            a %= b;
        }
        else{
            b %= a;
        }
    }
    return a | b;
}

int NOK(int a, int b) {
    return a * b / NOD(a, b);
}

void Array(int *arr, int n) {
    int i = 0;
    while (n > 0){
        arr[i++] = n % 10;
        n /= 10;
    }
    arr[i] = -1;
}

void foo(char *S){
    if ((S[0]==' ') && (S[1]==' ')) 
	{
            strncpy(&(S[0]),&(S[1]), strlen(S)-1);
            S[strlen(S)-1]='\0';
            foo(S);
    }
 
    if (S[0]) foo(&(S[1]));
}

int main(){

    // Task 2
    int arr[256];
    int n;
    scanf("%d", &n);

    Array(arr, n);

    for (int i = 0; arr[i] != -1; i++) {
        printf("%d %s", arr[i], "\n");
    }

    // Task 5
    char s[] = "Stroka    bez     lishnih     probelov    ";
    foo(s);
    printf("%s",s);

    return 0;
}




