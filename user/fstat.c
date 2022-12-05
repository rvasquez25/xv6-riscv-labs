#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void
fstatfunc(char *path)
{
  char buf[512], *p;
  int fd;
  //struct dirent de; de not needed here
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    // adjusted ls command from t_file to output required data
    printf("name: %s \ntype: regular file \ninode number: %d \nsize: %l \nlinks: %d\n", path, st.ino, st.size, st.nlink);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
     //removed while loop to only output directory and data required
     printf("name: %s \ntype: directory \ninode number: %d \nsize: %l \nlinks: %d\n", path, st.ino, st.size, st.nlink);
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    fstatfunc(".");
    exit(0);
  }
  for(i=1; i<argc; i++)
    fstatfunc(argv[i]);
  exit(0);
}
