#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

void print_prompt() {
  printf("%s", "minidb>> ");
}

int main(int argc, char *argv[])
{
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  while (true)
  {
    print_prompt();
    if ((nread = getline(&line, &len, stdin)) > 0)
    {
      // 末尾の改行を終端に変更
      char *p;
      p = strchr(line, '\n');
      if (p != NULL)
      {
        *p = '\0';
      }

      if (strcmp(line, ".exit") == 0)
      {
        exit(0);
      }
    }
  }
  return 0;
}
 