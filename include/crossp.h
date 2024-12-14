#ifndef CROSSP_H
#define CROSSP_H

#include <stdint.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define pthread_mutex_t         HANDLE
#define pthread_t               HANDLE
#define pthread_mutex_lock(ptr) WaitForSingleObject(*(ptr), INFINITE)
#define pthread_mutex_unlock(ptr)
#define pthread_mutex_init(ptr, reserved) \
	(!(*(ptr) = CreateMutex(NULL, FALSE, reserved)))
#define pthread_mutex_destroy(ptr) CloseHandle(*(ptr))
#define PTHREAD_MUTEX_INITIALIZER  NULL
#define pthread_create(id, attr, func, args) \
	(!(*(id) = CreateThread(attr, 0, (LPTHREAD_START_ROUTINE)func, args, 0, NULL)))
#define pthread_join(id, retval) WaitForSingleObject(id, INFINITE)
#define pthread_detach(id)       CloseHandle(id)

typedef size_t ssize_t;
#endif

int strincmp(const char *a, const char *b, uint64_t maxLen);
char *strtok_r(char *str, const char *delim, char **saveptr);

#endif // CROSSP_H