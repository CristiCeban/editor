#include "events_handler.h"

void die(const char *s) {
  perror(s);
  exit(EXIT_FAILURE);
}