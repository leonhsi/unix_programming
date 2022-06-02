#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <fcntl.h>

int fd = 2;
int hasInit = 0;

void init_fd(){
	char *output_file = getenv("OUTPUT_FILE");

	int (*open_func)(const char *pathname, int flags, mode_t mode);
	open_func = (void *)dlsym(RTLD_NEXT, "open");

	if(strcmp(output_file, "stderr") == 0){
		fd = dup(2);
	}
	else{
		fd = open_func(output_file, O_APPEND | O_CREAT | O_RDWR, 0644);
	}

	hasInit = 1;
}

void print(char *str){
	ssize_t (*write_func)(int fd, const void *buf, size_t count);
	write_func = (void *)dlsym(RTLD_NEXT, "write");

	write_func(fd, str, strlen(str));
}


int chmod(const char *pathname, mode_t mode){
	if(!hasInit) init_fd();

	int (*func)(const char *pathname, mode_t mode);
	func = (void *)dlsym(RTLD_NEXT, "chmod");
	int res = func(pathname, mode);

	//handle log
	char buf[PATH_MAX];
	char *path;
	char *ret = realpath(pathname, buf);
	if(ret)
		path = buf;
	else
		path = (char *)pathname;

	char log[256];
	sprintf(log, "[logger] chmod (\"%s\", %o) = %d\n", path, mode, res);
	print(log);

	return res;
}

int chown(const char *pathname, uid_t owner, uid_t group){
	if(!hasInit) init_fd();

	int (*func)(const char *pathname, uid_t owner, uid_t group);
	func = (void *)dlsym(RTLD_NEXT, "chown");
	int res = func(pathname, owner, group);

	//handle log
	char buf[PATH_MAX];
	char *path;
	char *ret = realpath(pathname, buf);
	if(ret)
		path = buf;
	else
		path = (char *)pathname;

	char log[256];
	sprintf(log, "[logger] chown (\"%s\", %d, %d) = %d\n", path, owner, group, res);
	print(log);

	return res;
}

int close(int fd){
	int (*func)(int fd);
	func = (void *)dlsym(RTLD_NEXT, "close");
	int res = func(fd);

	//handle log
	char *path;
	char pathname[PATH_MAX];
	strcpy(pathname, "/proc/self/fd/");
	char fd_c = fd + '0';
	char cToStr[2];
	cToStr[1] = '\0';
	cToStr[0] = fd_c;
	strcat(pathname, cToStr);

	char buf[PATH_MAX];
	int ret = readlink(pathname, buf, PATH_MAX-1);
	if(ret){
		path = buf;
	}
	else
		path = (char *)pathname;

	char log[256];
	sprintf(log, "[logger] close (\"%s\") = %d\n", path, res);
	print(log);

	return res;
}

int creat(const char *pathname, mode_t mode){
	if(!hasInit) init_fd();

	int (*func)(const char *pathname, mode_t mode);
	func = (void *)dlsym(RTLD_NEXT, "creat");
	int res = func(pathname, mode);

	//handle log
	char buf[PATH_MAX];
	char *path;
	char *ret = realpath(pathname, buf);
	if(ret)
		path = buf;
	else
		path = (char *)pathname;

	char log[256];
	sprintf(log, "[logger] creat (\"%s\", %o) = %d\n", path, mode, res);
	print(log);

	return res;
}

int creat64(const char *pathname, mode_t mode){
	if(!hasInit) init_fd();

	int (*func)(const char *pathname, mode_t mode);
	func = (void *)dlsym(RTLD_NEXT, "creat64");
	int res = func(pathname, mode);

	//handle log
	char buf[PATH_MAX];
	char *path;
	char *ret = realpath(pathname, buf);
	if(ret)
		path = buf;
	else
		path = (char *)pathname;

	char log[256];
	sprintf(log, "[logger] creat64 (\"%s\", %o) = %d\n", path, mode, res);
	print(log);

	return res;
}

int fclose(FILE *stream){
	if(!hasInit) init_fd();

	int (*func)(FILE *stream);
	func = (void*)dlsym(RTLD_NEXT, "fclose");
	int res = func(stream);

	//handle log
	char fd_c = fileno(stream) + '0';
	char *path = "";
	char pathname[PATH_MAX];
	strcpy(pathname, "/proc/self/fd/");
	char cToStr[2];
	cToStr[1] = '\0';
	cToStr[0] = fd_c;
	strcat(pathname, cToStr);

	char buf[PATH_MAX];
	int ret = readlink(pathname, buf, PATH_MAX-1);
	if(ret){
		path = buf;
	}

	char log[256];
	sprintf(log, "[logger] fclose(\"%s\") = %d\n", path, res);
	print(log);

	return res;
}

FILE *fopen(const char *restrict pathname, const char *restrict mode){
	if(!hasInit) init_fd();

	FILE* (*func)(const char *restrict pathname, const char *restrict mode);
	func = (void*)dlsym(RTLD_NEXT, "fopen");
	FILE* res = func(pathname, mode);

	//handle log
	char buf[PATH_MAX];
	char *path;
	char *ret = realpath(pathname, buf);
	if(ret)
		path = buf;
	else
		path = (char *)pathname;

	char log[256];
	sprintf(log, "[logger] fopen(\"%s\", \"%s\") = %p\n", path, mode, res);
	print(log);

	return res;
}

FILE *fopen64(const char *restrict pathname, const char *restrict mode){
	if(!hasInit) init_fd();

	FILE* (*func)(const char *restrict pathname, const char *restrict mode);
	func = (void*)dlsym(RTLD_NEXT, "fopen64");
	FILE* res = func(pathname, mode);

	//handle log
	char buf[PATH_MAX];
	char *path;
	char *ret = realpath(pathname, buf);
	if(ret)
		path = buf;
	else
		path = (char *)pathname;
	
	char log[256];
	sprintf(log, "[logger] fopen64(\"%s\", \"%s\") = %p\n", path, mode, res);
	print(log);

	return res;
}

size_t fread(void *restrict ptr, size_t size, size_t nmemb, FILE *restrict stream){
	if(!hasInit) init_fd();

	size_t (*func)(void *restrict ptr, size_t size, size_t nmemb, FILE *restrict stream);
	func = (void *)dlsym(RTLD_NEXT, "fread");
	size_t res = func(ptr, size, nmemb, stream);

	//handle log
	char print_buf[32];
	for(int i=0; i<32; i++){
		if(*((char*)ptr+i) == '\0'){
			print_buf[i] = '\0';
			break;
		}
		if(isprint(*((char*)ptr+i))){
			print_buf[i] = *((char*)ptr+i);
		}
		else{
			print_buf[i] = '.';
		}
	}

	char fd_c = fileno(stream) + '0';
	char *path;
	char pathname[PATH_MAX];
	strcpy(pathname, "/proc/self/fd/");
	char cToStr[2];
	cToStr[1] = '\0';
	cToStr[0] = fd_c;
	strcat(pathname, cToStr);

	char buf[PATH_MAX];
	int ret = readlink(pathname, buf, PATH_MAX-1);
	if(ret){
		path = buf;
	}
	else
		path = (char *)pathname;

	char log[256];
	sprintf(log, "[logger] fread (\"%s\", %ld, %ld, \"%s\") = %ld\n", print_buf, size, nmemb, path, res);
	print(log);

	return res;
}

size_t fwrite(const void *restrict ptr, size_t size, size_t nmemb, FILE *restrict stream){
	if(!hasInit) init_fd();

	size_t (*func)(const void *restrict ptr, size_t size, size_t nmemb, FILE *restrict stream);
	func = (void *)dlsym(RTLD_NEXT, "fwrite");
	size_t res = func(ptr, size, nmemb, stream);

	//handle log
	char print_buf[32];
	for(int i=0; i<32; i++){
		if(*((char*)ptr+i) == '\0'){
			print_buf[i] = '\0';
			break;
		}
		if(isprint(*((char*)ptr+i))){
			print_buf[i] = *((char*)ptr+i);
		}
		else{
			print_buf[i] = '.';
		}
	}

	char fd_c = fileno(stream) + '0';
	char *path;
	char pathname[PATH_MAX];
	strcpy(pathname, "/proc/self/fd/");
	char cToStr[2];
	cToStr[1] = '\0';
	cToStr[0] = fd_c;
	strcat(pathname, cToStr);

	char buf[PATH_MAX];
	int ret = readlink(pathname, buf, PATH_MAX-1);
	if(ret){
		path = buf;
	}
	else
		path = (char *)pathname;

	char log[256];
	sprintf(log, "[logger] fwrite (\"%s\", %ld, %ld, \"%s\") = %ld\n", print_buf, size, nmemb, path, res);
	print(log);

	return res;
}

int open(const char *pathname, int flags, ...){
	if(!hasInit) init_fd();

	va_list args;
	va_start(args, flags);
	mode_t mode = va_arg(args, mode_t);

	int (*func)(const char *pathname, int flags, mode_t mode);
	func = (void *)dlsym(RTLD_NEXT, "open");
	int res = func(pathname, flags, mode);

	//handle log
	char buf[PATH_MAX];
	char *path;
	char *ret = realpath(pathname, buf);
	if(ret)
		path = buf;
	else
		path = (char *)pathname;

	char log[256];
	if(mode){
		sprintf(log, "[logger] open (\"%s\", %o, %o) = %d\n", path, flags, mode, res);
	}
	else{
		sprintf(log, "[logger] open (\"%s\", %o) = %d\n", path, flags, res);
	}
	print(log);

	return res;
}

int open64(const char *pathname, int flags, ...){
	if(!hasInit) init_fd();

	va_list args;
	va_start(args, flags);
	mode_t mode = va_arg(args, mode_t);

	int (*func)(const char *pathname, int flags, mode_t mode);
	func = (void *)dlsym(RTLD_NEXT, "open64");
	int res = func(pathname, flags, mode);

	//handle log
	char buf[PATH_MAX];
	char *path;
	char *ret = realpath(pathname, buf);
	if(ret)
		path = buf;
	else
		path = (char *)pathname;

	char log[256];
	if(mode){
		sprintf(log, "[logger] open64 (\"%s\", %o, %o) = %d\n", path, flags, mode, res);
	}
	else{
		sprintf(log, "[logger] open64 (\"%s\", %o) = %d\n", path, flags, res);
	}

	return res;
}

ssize_t read(int fd, void *buf, size_t count){
	if(!hasInit) init_fd();

	ssize_t (*func)(int fd, void *buf, size_t count);
	func = (void *)dlsym(RTLD_NEXT, "read");
	ssize_t res = func(fd, buf, count);

	//handle log
	char *path;
	char pathname[PATH_MAX];
	strcpy(pathname, "/proc/self/fd/");
	char fd_c = fd + '0';
	char cToStr[2];
	cToStr[1] = '\0';
	cToStr[0] = fd_c;
	strcat(pathname, cToStr);

	char path_buf[PATH_MAX];
	int ret = readlink(pathname, path_buf, PATH_MAX-1);
	if(ret){
		path = path_buf;
	}
	else
		path = (char *)pathname;

	char print_buf[32];
	for(int i=0; i<32; i++){
		if(*((char*)buf+i) == '\0'){
			print_buf[i] = '\0';
			break;
		}
		if(isprint(*((char*)buf+i))){
			print_buf[i] = *((char*)buf+i);
		}
		else{
			print_buf[i] = '.';
		}
	}

	char log[256];
	sprintf(log, "[logger] read (\"%s\",  \"%s\", %ld) = %ld\n", print_buf, path, count, res);

	return res;
}

int remove(const char *pathname){
	if(!hasInit) init_fd();

	int (*func)(const char *pathname);
	func = (void *)dlsym(RTLD_NEXT, "remove");
	int res = func(pathname);

	//handle log
	char buf[PATH_MAX];
	char *path;
	char *ret = realpath(pathname, buf);
	if(ret)
		path = buf;
	else
		path = (char *)pathname;

	char log[256];
	sprintf(log, "[logger] remove (\"%s\") = %d\n", path, res);

	return res;
}

int rename(const char *oldpath, const char *newpath){
	if(!hasInit) init_fd();

	int (*func)(const char *oldpath, const char *newpath);
	func = (void *)dlsym(RTLD_NEXT, "rename");
	int res = func(oldpath, newpath);

	char log[256];
	sprintf(log, "[logger] rename (\"%s\", \"%s\") = %d\n", oldpath, newpath, res);
	print(log);

	return res;
}

FILE *tmpfile(void){
	if(!hasInit) init_fd();

	FILE* (*func)();
	func = (void *)dlsym(RTLD_NEXT, "tmpfile");
	FILE *res = func();

	char log[256];
	sprintf(log, "[logger] tmpfile() = %p\n", res);
	print(log);

	return res;
}

FILE *tmpfile64(void){
	if(!hasInit) init_fd();

	FILE* (*func)();
	func = (void *)dlsym(RTLD_NEXT, "tmpfile64");
	FILE *res = func();

	char log[256];
	sprintf(log, "[logger] tmpfile64() = %p\n", res);
	print(log);

	return res;
}

ssize_t write(int fd, const void *buf, size_t count){
	if(!hasInit) init_fd();

	ssize_t (*func)(int fd, const void *buf, size_t count);
	func = (void *)dlsym(RTLD_NEXT, "write");
	ssize_t res = func(fd, buf, count);

	//handle log
	char *path;
	char pathname[PATH_MAX];
	strcpy(pathname, "/proc/self/fd/");
	char fd_c = fd + '0';
	char cToStr[2];
	cToStr[1] = '\0';
	cToStr[0] = fd_c;
	strcat(pathname, cToStr);

	char path_buf[PATH_MAX];
	int ret = readlink(pathname, path_buf, PATH_MAX-1);
	if(ret){
		path = path_buf;
	}
	else
		path = (char *)pathname;

	char print_buf[32];
	for(int i=0; i<32; i++){
		if(*((char*)buf+i) == '\0'){
			print_buf[i] = '\0';
			break;
		}
		if(isprint(*((char*)buf+i))){
			print_buf[i] = *((char*)buf+i);
		}
		else{
			print_buf[i] = '.';
		}
	}
	
	char log[256];
	sprintf(log, "[logger] write (\"%s\", \"%s\", %ld) = %ld\n", path, print_buf, count, res);
	print(log);

	return res;
}
