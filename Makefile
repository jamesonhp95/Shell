FLAGS= -g -c -m32

EXE = msshrc
MAIN = ./cscd340Lab6.c

HISTORY = ./history/history.o
ALIAS = ./alias/alias.o

UTILS= ./utils/myUtils.o ./utils/fileUtil.o
LINKEDLIST = ./linkedlist/linkedList.o ./linkedlist/listUtils.o 
TOKENIZE = ./tokenize/makeArgs.o
PROCESS = ./process/process.o
PIPES = ./pipes/pipes.o
REDIRECTS = ./redirects/redirects.o

${EXE}:  ${TOKENIZE} ${PIPES} ${REDIRECTS} ${PROCESS} ${UTILS} ${HISTORY} ${ALIAS} ${LINKEDLIST}  ${MAIN}
	gcc -o ${EXE} ${MAIN} ${TOKENIZE} ${PROCESS} ${PIPES} ${REDIRECTS} ${HISTORY} ${ALIAS} ${LINKEDLIST} ${UTILS}

#==============================================================================================================================

process.o: ./process/process.c ./process/process.h
	gcc -g -c ./process/process.c
   
pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

redirects.o: ./redirects/redirects.c ./redirects/redirects.h
	gcc -g -c ./redirects/redirects.c

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	gcc -g -c ./tokenize/makeArgs.c
   
#==============================================================================================================================

listUtils.o:	./linkedlist/listUtils.c listUtils.h
	gcc  ${FLAGS} ./linkedlist/listUtils.c
   

linkedList.o:	./linkedlist/linkedList.h ./linkedlist/linkedList.c ./linkedlist/requiredIncludes.h
	gcc ${FLAGS} ./linkedlist/linkedList.c

#==============================================================================================================================

myUtils.o:	./utils/myUtils.h ./utils/myUtils.c
	gcc ${FLAGS} ./utils/myUtils.c

fileUtil.o:	./utils/fileUtil.h ./utils/fileUtil.c
	gcc ${FLAGS} ./utils/fileUtil.c

#==============================================================================================================================

history.o:	./history/history.h ./history/history.c
	gcc ${FLAGS} ./history/history.c
alias.o: ./alias/alias.h ./alias/alias.c
	gcc ${FLAGS} ./alias/alias.c

clean:	
	rm ./pipes/*.o
	rm ./process/*.o
	rm ./tokenize/*.o
	rm ./history/*.o
	rm ./linkedlist/*.o
	rm ./utils/*.o
	rm ${EXE}