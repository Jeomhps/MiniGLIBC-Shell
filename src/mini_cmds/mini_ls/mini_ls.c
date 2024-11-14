#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include "../../mini_glibc/mini_lib.h"

#define MAX_BUF 256

void construct_path(char *dest, const char *path, const char *filename) {
  int i = 0;
  while (path[i] != '\0') {
    dest[i] = path[i];
    i++;
  }

  if (i > 0 && path[i - 1] != '/') {
    dest[i] = '/';
    i++;
  }

  int j = 0;
  while (filename[j] != '\0') {
    dest[i] = filename[j];
    i++;
    j++;
  }

  dest[i] = '\0';
}

void print_permissions(mode_t mode) {
  char perms[11] = "----------";
  if (S_ISDIR(mode))
    perms[0] = 'd'; // Directory
  if (mode & S_IRUSR)
    perms[1] = 'r'; // Owner read
  if (mode & S_IWUSR)
    perms[2] = 'w'; // Owner write
  if (mode & S_IXUSR)
    perms[3] = 'x'; // Owner execute
  if (mode & S_IRGRP)
    perms[4] = 'r'; // Group read
  if (mode & S_IWGRP)
    perms[5] = 'w'; // Group write
  if (mode & S_IXGRP)
    perms[6] = 'x'; // Group execute
  if (mode & S_IROTH)
    perms[7] = 'r'; // Others read
  if (mode & S_IWOTH)
    perms[8] = 'w'; // Others write
  if (mode & S_IXOTH)
    perms[9] = 'x'; // Others execute
  mini_printf(perms);
}

void pad_and_print(char *str, int width, int right_align) {
  char buffer[MAX_BUF];
  int len = mini_strlen(str);
  int padding = width - len;

  if (padding < 0)
    padding = 0;

  if (right_align) {
    for (int i = 0; i < padding; i++)
      buffer[i] = ' ';
    mini_strcpy(buffer + padding, (char *)str);
  } else {
    mini_strcpy(buffer, (char *)str);
    for (int i = len; i < width; i++)
      buffer[i] = ' ';
  }

  buffer[width] = '\0';
  mini_printf(buffer);
}

void mini_ls(const char *path) {
  DIR *dir;
  struct dirent *entry;
  struct stat file_stat;

  dir = opendir(path);
  if (dir == NULL) {
    mini_perror("Error opening directory");
    return;
  }

  while ((entry = readdir(dir)) != NULL) {

    char full_path[1024]; // Adjust size as needed
    construct_path(full_path, path, entry->d_name);
    if (stat(full_path, &file_stat) == -1) {
      mini_perror("Error reading file metadata");
      continue;
    }

    print_permissions(file_stat.st_mode);
    mini_printf(" ");

    char link_count_str[20];
    mini_itoa((int)file_stat.st_nlink, link_count_str);
    pad_and_print(link_count_str, 4, 1);
    mini_printf(" ");

    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    pad_and_print(pw ? pw->pw_name : "UNKNOWN", 10, 0);
    mini_printf(" ");
    pad_and_print(gr ? gr->gr_name : "UNKNOWN", 10, 0);
    mini_printf(" ");

    char size_str[20];
    mini_itoa((int)file_stat.st_size, size_str);
    pad_and_print(size_str, 8, 1);
    mini_printf(" ");

    char time_str[20];
    struct tm *tm_info = localtime(&file_stat.st_mtime);
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", tm_info);
    pad_and_print(time_str, 12, 0);
    mini_printf(" ");

    mini_printf(entry->d_name);
    mini_printf("\n");
  }

  closedir(dir);
}

int main(int argc, char *argv[]) {
  const char *path;

  if (argc > 1) {
    path = argv[1];
  } else {
    path = ".";
  }

  mini_ls(path);
  return 0;
}
