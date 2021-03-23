CFLAGS  = -g
BIN1= bbb
BIN2 = xx  

all :$(BIN1) $(BIN2)   clean
		
$(BIN1) :ddd.c   
		gcc $^ -o $@ $(CFLAGS)
$(BIN2):main.c
		gcc $^ -o $@ 


#clean :
#		rm -r  $(BIN1) $(BIN2)

