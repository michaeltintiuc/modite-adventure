#include <stdarg.h>
#include <stdio.h>

// The bundled libxmp declares these wrappers on Windows.
int libxmp_vsnprintf(char *buffer, size_t size, const char *format, va_list args) {
  return vsnprintf(buffer, size, format, args);
}

int libxmp_snprintf(char *buffer, size_t size, const char *format, ...) {
  va_list args;
  va_start(args, format);
  const int result = libxmp_vsnprintf(buffer, size, format, args);
  va_end(args);
  return result;
}
