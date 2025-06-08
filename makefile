# 컴파일러 설정
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

# 헤더파일
HEADERS = christo.h utils.h

# 소스파일과 오브젝트파일
SRCS = main.cpp \
       christo.cpp \
	   fread.cpp \
       mst.cpp \
       perfectmatching.cpp \
       hamilton.cpp\
	   utils.cpp\
	   myalgo.cpp\
	   heldkarp.cpp

OBJS = $(SRCS:.cpp=.o)

# 최종 실행 파일 이름
TARGET = main

# 빌드 규칙
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# 정리
clean:
	rm -f $(OBJS) $(TARGET)
