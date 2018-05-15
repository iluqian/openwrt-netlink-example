#IPC(进程间通信)
##管道
pipe 无名管道; 半双工,有血缘关系
##fifo
有名管道;磁盘文件p开头;伪文件,大小0;在内核中有一个对应的缓冲区
没有血缘关系的进程间通信   man 3 mkfifo
int mkfifo(const char * pathname, mode_t mode) the permissions of the created file are (mode & ~umask).
