#include "RevenantVectors.hpp"
#include "RevenantTris.hpp"
#include "RevenantMesh.hpp"
#include <iostream>
#include <fstream>

Mesh::Mesh(std::string meshName) {
    std::ifstream meshFile;
    size_t bytesInVector3 = sizeof(Vector3); // Number of bytes in each Vector3
    size_t Vector3BytesToMalloc = 0; // Number of bytes to be allocated to the vertices pointer
    size_t bytesInTri = sizeof(Tri); // Number of bytes in each Tri
    size_t TriBytesToMalloc = 0; // Number of bytes to be allocated to the triangles pointer
    std::string filePath = "./meshes/" + meshName;
    meshFile.open(filePath);
    while(std::getline(meshFile, this->currentLineData)) {
        // in obj files, v stands for vertex. This code will allocate as much memory to the vertices pointer in the parent object as is needed to store all vertices referenced in a given .obj file.
        if (this->currentLineData.find("v ") == 0) {
            Vector3BytesToMalloc += bytesInVector3;
        }
        // in obj files, f stands for face. This engine does not support n-gons, so face is treated as synonymous with triangles and the same logic is applied here as is applied with individual vertices.
        else if (this->currentLineData.find("f ") == 0) {
            TriBytesToMalloc += bytesInTri;
        }
    }
    this->vertices = (Vector3*)malloc(Vector3BytesToMalloc); // Allocates enough memory to hold every vertex in the obj
    this->triangles = (Tri*)malloc(TriBytesToMalloc); // Allocates enough memory to hold every triangle in the obj
    this->triangleIndices = (Vector3*)malloc(sizeof(Vector3)*(TriBytesToMalloc/sizeof(Tri)));\
    meshFile.close();
    meshFile.open(filePath);
    int vertexIndex = 0; // Index of the current vertex that is being written to in the vertices pointer
    int triIndex = 0; // Index of the current triangle that is being written to in the triangles pointer 
    while(std::getline(meshFile, this->currentLineData)) {
        if (this->currentLineData.find("v ") == 0) {
            this->currentLineData = this->currentLineData.substr(2, this->currentLineData.length() - 2);
            float vertexCoordinate = std::stof(this->currentLineData.substr(0, this->currentLineData.find(' '))); // Sets vertexCoordinate to the first value in the substring (representing x)
            this->vertices[vertexIndex].x = vertexCoordinate;
            this->currentLineData = this->currentLineData.substr(this->currentLineData.find(' ') + 1, this->currentLineData.length()); // Removes the x value from the substring
            vertexCoordinate = std::stof(this->currentLineData.substr(0, this->currentLineData.find(' '))); // Sets vertexCoordinate to the second value in the substring (representing x)
            this->vertices[vertexIndex].y = vertexCoordinate;
            this->currentLineData = this->currentLineData.substr(this->currentLineData.find(' ') + 1, this->currentLineData.length()); // Removes the y value from the substring
            vertexCoordinate = std::stof(this->currentLineData.substr(0, this->currentLineData.find(' '))); // Sets vertexCoordinate to the third value in the substring (representing x)
            this->vertices[vertexIndex].z = vertexCoordinate;
            ++vertexIndex;

        }
        else if (this->currentLineData.find("f ") == 0) {
            this->currentLineData = this->currentLineData.substr(2, this->currentLineData.length() - 2);
            int triVertexIndex = stoi(this->currentLineData.substr(0, this->currentLineData.find('/'))); // This sets vertexIndex to the index of the first vertex that the current Tri should point to.
            triVertexIndex--; // The vertex indices in .obj files start at 1 (rather than 0), so 1 is subtracted from the index number here.
            //std::cout << triVertexIndex << '\n';
            this->triangles[triIndex].a = &this->vertices[triVertexIndex];
            std::cout << this->currentLineData << std::endl;
            this->currentLineData = this->currentLineData.substr(this->currentLineData.find('/'), this->currentLineData.length()); // Removes the first vertex index from the current line data
            //triVertexIndex = stoi(this->currentLineData.substr(0, this->currentLineData.find('/')));
            triVertexIndex--;
            //std::cout << triVertexIndex << '\n';
            this->triangles[triIndex].b = &this->vertices[triVertexIndex];
            this->currentLineData = this->currentLineData.substr(this->currentLineData.find('/'), this->currentLineData.length());
            /*triVertexIndex = stoi(this->currentLineData.substr(0, this->currentLineData.find('/')));
            triVertexIndex--;
            std::cout << triVertexIndex << std::endl;
            this->triangles[triIndex].c = &this->vertices[triVertexIndex];
            ++triIndex;*/
        }
    }
}