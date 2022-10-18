#include <stdio.h>

int main(void) {

    char buf[BUFSIZ];
    int read_cnt;
    FILE *file1 = fopen("file1.txt", "rb"); //읽기전용
    FILE *file2 = fopen("file2.txt", "wb"); //쓰기전용

    if (file1 == NULL || file2 == NULL) {
        puts("file open error");
        return -1;
    }

    while (1) {
        read_cnt = fread((void *)buf, 1, BUFSIZ, file1); //읽어오고
        if (read_cnt < BUFSIZ) {
            if (feof(file1) != 0) //파일의 끝이 아니라면 복사 {
                fwrite((void *)buf, 1, read_cnt, file2);
                break;
            }
            else
                puts("copy error");
            break;
        }
    fclose(file1);
    fclose(file2);
    return 0;
}