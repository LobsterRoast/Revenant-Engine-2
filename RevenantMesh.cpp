#include "RevenantVectors.hpp"
#include "RevenantTris.hpp"
#include "RevenantMesh.hpp"
#include "SerializeString.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
        if (currentLineData.find("v ") == 0) {
            Vector3BytesToMalloc += bytesInVector3;
        }
        // in obj files, f stands for face. This engine does not support n-gons, so face is treated as synonymous with triangles and the same logic is applied here as is applied with individual vertices.
        else if (currentLineData.find("f ") == 0) {
            TriBytesToMalloc += bytesInTri;
        }
    }
    vertices = (Vector3*)malloc(Vector3BytesToMalloc); // Allocates enough memory to hold every vertex in the obj
    triangles = (Tri*)malloc(TriBytesToMalloc); // Allocates enough memory to hold every triangle in the obj
    triangleIndices = (Vector3*)malloc(sizeof(Vector3)*(TriBytesToMalloc/sizeof(Tri)));
    meshFile.close();
    meshFile.open(filePath);
    int vertexIndex = 0; // Index of the current vertex that is being written to in the vertices pointer
    int triIndex = 0; // Index of the current triangle that is being written to in the triangles pointer 
    while(std::getline(meshFile, currentLineData)) {
        if (this->currentLineData.find("v ") == 0) {
            std::vector<std::string> serializedLineData = SerializeString(currentLineData, " ");
            vertices[vertexIndex].x = std::stof(serializedLineData[1]);
            vertices[vertexIndex].y = std::stof(serializedLineData[2]);
            vertices[vertexIndex].z = std::stof(serializedLineData[3]);
            ++vertexIndex;

        }
        else if (this->currentLineData.find("f ") == 0) {
            std::vector<std::string> serializedLineData = SerializeString(currentLineData, " ");
            std::vector<std::string> serializedVertexData; // With the way faces are formatted in .obj files, it's necessary to make subtokens.
            serializedVertexData = SerializeString(serializedLineData[1], "/");
            triangles[triIndex].a = &vertices[std::stoi(serializedVertexData[0])-1];
            serializedVertexData = SerializeString(serializedLineData[2], "/");
            triangles[triIndex].b = &vertices[std::stoi(serializedVertexData[0])-1];
            serializedVertexData = SerializeString(serializedLineData[3], "/");
            triangles[triIndex].c = &vertices[std::stoi(serializedVertexData[0])-1];
            ++triIndex;
        }
    }
}