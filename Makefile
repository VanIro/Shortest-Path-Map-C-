all: compile link

includePath = "D:\Documents\Codeblocks\Maps\include"
linkPath = "D:\Documents\Codeblocks\Maps\lib"

compile:
	g++ -c *.cpp -I$(includePath)

link:
	g++ main.o search.o button.o scrollList.o ops.o map.o khojiRukh.o graph.o batoRukh.o nodes.o queue_lst.o list.o element.o  -o main -L$(linkPath) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	del -f main *.o