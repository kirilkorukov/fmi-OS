/*
    Реализирайте команда swap, разменяща съдържанието на два файла, подадени като
    входни параметри. Приемаме, че двата файла имат еднакъв брой символи. Може да
    модифицирате решението, да работи и когато нямат еднакъв брой символи.
*/

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[]){

    if(argc != 3){
        errx(1, "We need 2 arguments");
    }

    int fd1;
    if((fd1 = open(argv[1], O_RDWR)) == -1)
    {
        err(2, "Error opening %s", argv[1]);
    }
    int fd2;
    if((fd2 = open(argv[2], O_RDWR)) == -1){
        const int olderrno = errno;
        close(fd1);
        errno = olderrno;
        err(3, "Error opening %s" , argv[2]);
    }

    int fd3;
    if((fd3 = open("my_temp_file.txt", O_CREAT | O_TRUNC |  O_RDWR, S_IRWXU)) == -1)
    {
        const int olderrno = errno;
        close(fd1);
        close(fd2);
        errno = olderrno;
        err(4, "Error opening my_temp_file.txt");
    }

    char buf[4096];
    ssize_t read_size; 

    // 1 -> 3
    while(1)
    {
        read_size = read(fd1, &buf, sizeof(buf));
        if(read_size == 0){
            // end of file
            break;
        }
        if(read_size == -1)
        {   
            const int olderrno = errno;
            close(fd1); close(fd2); close(fd3);
            errno = olderrno;
            err(5, "Error reading 1");
        }
        if(write(fd3, &buf, read_size) != read_size)
        {
            const int olderrno = errno;
            close(fd1); close(fd2); close(fd3);
            errno = olderrno;
            err(6, "error writing 1");
        }
    }
    if(lseek(fd1, 0, SEEK_SET) == -1)
    {
        const int olderrno = errno;
        close(fd1); close(fd2); close(fd3);
        errno = olderrno;
        err(1, "Error moving marker 1");
    }

    // 2 -> 1
    while(1)
      {
          read_size = read(fd2, &buf, sizeof(buf));
          if(read_size == 0){
              // end of file
              break;
          }
          if(read_size == -1)
          {
             const int olderrno = errno;
              close(fd1); close(fd2); close(fd3);
              errno = olderrno;
              err(7, "Error reading 2");
          }
          if(write(fd1, &buf, read_size) != read_size)
          {
              const int olderrno = errno;
              close(fd1); close(fd2); close(fd3);
              errno = olderrno;
              err(8, "error writing 2");
          }
      }
    if(lseek(fd2, 0, SEEK_SET) == -1)
    {
        const int olderrno = errno;
        close(fd1); close(fd2); close(fd3);
        errno = olderrno;
        err(1, "error moving marker 2");
    }
    lseek(fd3, 0, SEEK_SET);

    // 3 -> 2
    while(1)
    {
        read_size = read(fd3, &buf, sizeof(buf));
        if(read_size == 0)
        {
            break;
        }
        if(read_size == -1)
        {
            const int olderrno = errno;
            close(fd1); close(fd2); close(fd3);
            errno = olderrno;
            err(9, "error reading 3");
        }
        if((write(fd2, &buf, read_size)) != read_size)
        {
            const int olderrno = errno;
            close(fd1); close(fd2); close(fd3);
            errno = olderrno;
            err(10, "error writing 3");
        }
    }
    close(fd1);
    close(fd2);
    close(fd3);

    return 42;
}

