CXXFLAGS = -g -Wall
CXX = g++
OBJECTS = tauler.o candy.o partida.o

secondapp: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) main2.cpp -o app
	rm -rf *.o

app: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) main.cpp -o app
	rm -rf *.o

partida.o: partida.cpp partida.h tauler.h
	$(CXX) $(CXXFLAGS) -c partida.cpp

tauler.o: tauler.cpp tauler.h definicions.h candy.h posicio.h
	$(CXX) $(CXXFLAGS) -c tauler.cpp

candy.o: candy.cpp candy.h definicions.h
	$(CXX) $(CXXFLAGS) -c candy.cpp

clean:
	rm -rf *.o app.exe