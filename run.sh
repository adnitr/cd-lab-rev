bison -d $2
flex $1
cc calb.tab.c lex.yy.c -lfl