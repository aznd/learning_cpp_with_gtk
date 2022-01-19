target default:
	g++ main.cpp -o SpotGtk `pkg-config gtkmm-4.0 --cflags --libs`
clean:
	rm -f SpotGtk