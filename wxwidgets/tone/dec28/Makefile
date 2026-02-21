CXX = g++
STDCXXFLAG = -std=c++17 -Wall
WXGUIFLAG = wx-config --cxxflags --libs

build-%: %.cpp
	$(CXX) $(STDCXXFLAG) $< -o $*.exe
	./$*.exe


guibuild-%: %.cpp
	$(CXX) $< `$(WXGUIFLAG)` -o $*.exe
	./$*.exe

