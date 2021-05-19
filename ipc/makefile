all:mkfifo1  mkfifo2  pipe1  shm1  shm2

shm1:shm1.c
	gcc $^ -o $@  -std=gnu99
shm2:shm2.c
	gcc $^ -o $@  -std=gnu99
mkfifo1:mkfifo1.c
	gcc $^ -o $@ -g 
mkfifo2:mkfifo2.c
	gcc $^ -o $@ -g 
pipe1:pipe1.c
	gcc $^ -o $@ -g 


