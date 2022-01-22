target default:
	g++ main.cpp -o SpotGtk `pkg-config gtkmm-4.0 --cflags --libs`
clean:
	rm -f SpotGtk
debug:
	echo "This will create a binary with debugging symbols."
	g++ -g main.cpp -o SpotGtk `pkg-config gtkmm-4.0 --cflags --libs`
