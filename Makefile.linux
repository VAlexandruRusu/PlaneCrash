LIBDIRS= -L/usr/X11R6/lib
LDLIBS = -lglut -lGL -lGLU -lX11 -lm -lGLU

CPPFLAGS= -O3 
LDFLAGS= $(CPPFLAGS) $(LIBDIRS)

TARGETS = Planes

SRCS = Planes.cpp GlobalVariables.cpp GameLogic.cpp Graphics.cpp Interactive.cpp Playerbullet.cpp Enemyplane.cpp

OBJS =  $(SRCS:.cpp=.o)

CXX = g++
#added flags: c++11 compatibility, threading compatibility
CXXFLAGS=-g -std=c++11 -pthread
#linker flags for threads added
LDFLAGS = -pthread

default: $(TARGETS)
