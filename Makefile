rev: SerializeString.hpp SerializeString.cpp main.cpp RevenantVectors.cpp RevenantVectors.hpp RevenantTris.cpp RevenantTris.hpp RevenantMesh.cpp RevenantMesh.hpp
	g++ SerializeString.cpp RevenantVectors.cpp RevenantTris.cpp RevenantMesh.cpp main.cpp -o rev `pkg-config --cflags --libs sdl2`
