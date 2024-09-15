#ifndef CL_MAPS_HEADER
#define CL_MAPS_HEADER
#include <cstdlib>
template <typename T1, typename T2>
// This class represents a single pair of values within a CL compatible map.
struct CL_Map_Pair {
    public:
        T1 val1;
        T2 val2;
        void CreateCL_Map_Pair(T1 val1, T2 val2) {
            this->val1 = val1;
            this->val2 = val2;
        }
};

// This class represents a map compatible with OpenCL, as std::map is not supported.
template <typename T1, typename T2>
struct CL_Map {
    CL_Map_Pair<T1,T2>* pairs;
    int sizeOfSinglePair;
    int pairsArraySize;
    int filledRange = 0;
    public:
        T1 getPairedValue(T2 val) {
            for (int i = 0; i <= filledRange; i++) {
                if (val == pairs[i].val2) return pairs[i].val1;
            }
            return (T1)-1;
        };
        T2 getPairedValue(T1 val) {
            for (int i = 0; i <= filledRange; i++) {
                if (val == pairs[i].val1) return pairs[i].val2;
            }
            return (T2)-1;  
        }
        int Insert(T1 val1, T2 val2) {
            if (filledRange < pairsArraySize/sizeOfSinglePair) {
                pairs[filledRange].CreateCL_Map_Pair(val1, val2);
                filledRange++;
            }
            else return 1;
        }
};

// Since this uses functions unsupported by OpenCL, it is not made a member function of CL_Map.
template <typename T1, typename T2>
CL_Map<T1,T2> CreateCL_Map(CL_Map<T1, T2>* map) {
    map->sizeOfSinglePair = sizeof(CL_Map<T1,T2>);
    map->pairsArraySize = map->sizeOfSinglePair*750;
    map->pairs = (CL_Map_Pair<T1,T2>*)malloc(map->pairsArraySize);
    return *map;
}

// Since this uses functions unsupported by OpenCL, it is not made a member function of CL_Map.
template <typename T1, typename T2>
void MapResize(CL_Map<T1,T2>* map, int lengthDelta) {
    CL_Map_Pair<T1,T2>* newPairs;
    int newSize = map->pairsArraySize - lengthDelta*map->sizeOfSinglePair;
    newPairs = (CL_Map_Pair<T1,T2>*)malloc(newSize);
    for (int i = 0; i < newSize/map->sizeOfSinglePair; i++) {
        newPairs[i] = map->pairs[i];
        map->pairs = newPairs;
        map->pairsArraySize = newSize;
        free(newPairs);
    }
}


#endif