CPPFLAGS = -std=c++14 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g

all: dataOrganizer.cpp  
	g++ -std=c++14 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g dataOrganizer.cpp fileReader.cpp fileWriter.cpp -o dataOrganizer