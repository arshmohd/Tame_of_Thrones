all: Geektrust

Geektrust: geektrust.cpp golden_crown.cpp

	g++ geektrust.cpp golden_crown.cpp -o Geektrust -std=c++17

clean:
	rm Geektrust.exe