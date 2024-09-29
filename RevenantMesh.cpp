#include "RevenantVectors.h"
#include "RevenantTris.h"
#include "RevenantMesh.hpp"
#include "SerializeString.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

LowDtlMesh Create_LowDtlMesh(std::string meshName) {
    std::cout << "Loading mesh: " + meshName + "..." << std::endl;
    LowDtlMesh newMesh;
    std::string currentLineData;
    std::ifstream meshFile;
    std::string directory = "./meshes/";
    std::string filePath = directory + meshName;
    std::strcpy(newMesh.name, meshName.substr(0,20).c_str());
    meshFile.open(filePath);
    while(std::getline(meshFile, currentLineData)) {
        // in obj files, v stands for vertex. This code will allocate as much memory to the vertices pointer in the parent object as is needed to store all vertices referenced in a given .obj file.
        if (currentLineData.find("v ") == 0) {
            newMesh.vertexCount++;
        }
        // in obj files, f stands for face. This engine does not support n-gons, so face is treated as synonymous with triangles and the same logic is applied here as is applied with individual vertices.
        else if (currentLineData.find("f ") == 0) {
            newMesh.triCount++;
        }
    }
    meshFile.close();
    meshFile.open(filePath);
    int vertexIndex = 0; // Index of the current vertex that is being written to in the vertices pointer
    int triIndex = 0; // Index of the current triangle that is being written to in the triangles pointer 
    while(std::getline(meshFile, currentLineData)) {
        if (currentLineData.find("v ") == 0) {
            std::vector<std::string> serializedLineData = SerializeString(currentLineData, " ");
            newMesh.vertices[vertexIndex].x = std::stof(serializedLineData[1]);
            newMesh.vertices[vertexIndex].y = std::stof(serializedLineData[2]);
            newMesh.vertices[vertexIndex].z = std::stof(serializedLineData[3]);
            vertexIndex++;

        }
        else if (currentLineData.find("f ") == 0) {
            int vertexIndex;
            std::vector<std::string> serializedLineData = SerializeString(currentLineData, " ");
            std::vector<std::string> serializedVertexData; // With the way faces are formatted in .obj files, it's necessary to make subtokens.
            
            serializedVertexData = SerializeString(serializedLineData[1], "/");
            vertexIndex = std::stoi(serializedVertexData[0])-1;
            newMesh.triangles[triIndex].vertex[0] = vertexIndex;

            serializedVertexData = SerializeString(serializedLineData[2], "/");
            vertexIndex = std::stoi(serializedVertexData[0])-1;
            newMesh.triangles[triIndex].vertex[1] = vertexIndex;

            serializedVertexData = SerializeString(serializedLineData[3], "/");
            vertexIndex = std::stoi(serializedVertexData[0])-1;
            newMesh.triangles[triIndex].vertex[2] = vertexIndex;
            ++triIndex;
        }
    }
    return newMesh;
}

MedDtlMesh Create_MedDtlMesh(std::string meshName) {
    std::cout << "Loading mesh: " + meshName + "..." << std::endl;
    MedDtlMesh newMesh;
    std::string currentLineData;
    std::ifstream meshFile;
    std::string directory = "./meshes/";
    std::string filePath = directory + meshName;
    std::strcpy(newMesh.name, meshName.substr(0,20).c_str());
    meshFile.open(filePath);
    while(std::getline(meshFile, currentLineData)) {
        // in obj files, v stands for vertex. This code will allocate as much memory to the vertices pointer in the parent object as is needed to store all vertices referenced in a given .obj file.
        if (currentLineData.find("v ") == 0) {
            newMesh.vertexCount++;
        }
        // in obj files, f stands for face. This engine does not support n-gons, so face is treated as synonymous with triangles and the same logic is applied here as is applied with individual vertices.
        else if (currentLineData.find("f ") == 0) {
            newMesh.triCount++;
        }
    }
    meshFile.close();
    meshFile.open(filePath);
    int vertexIndex = 0; // Index of the current vertex that is being written to in the vertices pointer
    int triIndex = 0; // Index of the current triangle that is being written to in the triangles pointer 
    while(std::getline(meshFile, currentLineData)) {
        if (currentLineData.find("v ") == 0) {
            std::vector<std::string> serializedLineData = SerializeString(currentLineData, " ");
            newMesh.vertices[vertexIndex].x = std::stof(serializedLineData[1]);
            newMesh.vertices[vertexIndex].y = std::stof(serializedLineData[2]);
            newMesh.vertices[vertexIndex].z = std::stof(serializedLineData[3]);
            vertexIndex++;

        }
        else if (currentLineData.find("f ") == 0) {
            int vertexIndex;
            std::vector<std::string> serializedLineData = SerializeString(currentLineData, " ");
            std::vector<std::string> serializedVertexData; // With the way faces are formatted in .obj files, it's necessary to make subtokens.
            
            serializedVertexData = SerializeString(serializedLineData[1], "/");
            vertexIndex = std::stoi(serializedVertexData[0])-1;
            newMesh.triangles[triIndex].vertex[0] = vertexIndex;

            serializedVertexData = SerializeString(serializedLineData[2], "/");
            vertexIndex = std::stoi(serializedVertexData[0])-1;
            newMesh.triangles[triIndex].vertex[1] = vertexIndex;

            serializedVertexData = SerializeString(serializedLineData[3], "/");
            vertexIndex = std::stoi(serializedVertexData[0])-1;
            newMesh.triangles[triIndex].vertex[2] = vertexIndex;
            ++triIndex;
        }
    }
    return newMesh;
}

HighDtlMesh Create_HighDtlMesh(std::string meshName) {
    std::cout << "Loading mesh: " + meshName + "..." << std::endl;
    HighDtlMesh newMesh;
    std::string currentLineData;
    std::ifstream meshFile;
    std::string directory = "./meshes/";
    std::string filePath = directory + meshName;
    std::strcpy(newMesh.name, meshName.substr(0,20).c_str());
    meshFile.open(filePath);
    while(std::getline(meshFile, currentLineData)) {
        // in obj files, v stands for vertex. This code will allocate as much memory to the vertices pointer in the parent object as is needed to store all vertices referenced in a given .obj file.
        if (currentLineData.find("v ") == 0) {
            newMesh.vertexCount++;
        }
        // in obj files, f stands for face. This engine does not support n-gons, so face is treated as synonymous with triangles and the same logic is applied here as is applied with individual vertices.
        else if (currentLineData.find("f ") == 0) {
            newMesh.triCount++;
        }
    }
    meshFile.close();
    meshFile.open(filePath);
    int vertexIndex = 0; // Index of the current vertex that is being written to in the vertices pointer
    int triIndex = 0; // Index of the current triangle that is being written to in the triangles pointer 
    while(std::getline(meshFile, currentLineData)) {
        if (currentLineData.find("v ") == 0) {
            std::vector<std::string> serializedLineData = SerializeString(currentLineData, " ");
            newMesh.vertices[vertexIndex].x = std::stof(serializedLineData[1]);
            newMesh.vertices[vertexIndex].y = std::stof(serializedLineData[2]);
            newMesh.vertices[vertexIndex].z = std::stof(serializedLineData[3]);
            vertexIndex++;

        }
        else if (currentLineData.find("f ") == 0) {
            int vertexIndex;
            std::vector<std::string> serializedLineData = SerializeString(currentLineData, " ");
            std::vector<std::string> serializedVertexData; // With the way faces are formatted in .obj files, it's necessary to make subtokens.
            
            serializedVertexData = SerializeString(serializedLineData[1], "/");
            vertexIndex = std::stoi(serializedVertexData[0])-1;
            newMesh.triangles[triIndex].vertex[0] = vertexIndex;

            serializedVertexData = SerializeString(serializedLineData[2], "/");
            vertexIndex = std::stoi(serializedVertexData[0])-1;
            newMesh.triangles[triIndex].vertex[1] = vertexIndex;

            serializedVertexData = SerializeString(serializedLineData[3], "/");
            vertexIndex = std::stoi(serializedVertexData[0])-1;
            newMesh.triangles[triIndex].vertex[2] = vertexIndex;
            ++triIndex;
        }
    }
    return newMesh;
}