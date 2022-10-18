#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

        int file1, file2;

        char buf[BUFSIZ];

        int read_cnt;
        file1 = open("file1.txt", O_RDONLY); //읽기 전용

        file2 = open("file2.txt", O_CREAT | O_WRONLY | O_TRUNC); //파일 생성, 쓰기전용, 내용이 있다면 내용 다 지우기

        if (file1 == -1 || file2 == -1) {
               puts("file open error");
               return -1;
        }

        while ((read_cnt = read(file1, buf, BUFSIZ)) != 0){
               write(file2, buf, read_cnt); //file1에서 읽어들여 file2에 복사
        }

        close(file1);
        close(file2);

        return 0;

}