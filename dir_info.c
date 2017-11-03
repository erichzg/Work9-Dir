#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int dir_dirs(char * directory) {
  DIR * direct;
  direct = opendir(directory);

  struct dirent * dir_entry;
  dir_entry = readdir(direct);
  printf("Directories: \n");
  while (dir_entry) {
    if (dir_entry -> d_type == DT_DIR) {
      printf("\t%s\n", dir_entry -> d_name);
    }
    dir_entry = readdir(direct);
  }
  closedir(direct);
  return 0;
}

int dir_files(char * directory) {
  DIR * direct;
  direct = opendir(directory);

  struct dirent * dir_entry;
  dir_entry = readdir(direct);
  printf("Regular files: \n");
  char path_name[256];
  int total_size = 0;
  struct stat sb;
  while (dir_entry) {
    if (dir_entry -> d_type == DT_REG) {
      printf("\t%s\n", dir_entry -> d_name);
      strcpy(path_name, directory);
      strcat(path_name, dir_entry -> d_name);
      stat(path_name, &sb);
      total_size += sb.st_size;
    }
    dir_entry = readdir(direct);
  }
  closedir(direct);
  return total_size;
}

int main() {
  char dir_name[] = "./";
  printf("Statistics for directory: %s\n", dir_name);
  dir_dirs(dir_name);
  printf("\nTotal directory size: %d\n", dir_files(dir_name));
  return 0;
}
