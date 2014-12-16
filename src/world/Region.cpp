#include "Region.h"

#include "Compression.h"
#include "NBTTag.h"
#include "NBTTagByte.h"
#include "NBTTagByteArray.h"
#include "NBTTagCompound.h"
#include "NBTTagIntArray.h"
#include "NBTTagList.h"
#include "Section.h"

#include <arpa/inet.h>

Region::Region(string_t worldName, int_t x, int_t z) {
    file.open(worldName + "/region/r." + std::to_string(x) + "." + std::to_string(z) + ".mca",
              std::fstream::in | std::fstream::out | std::ios::binary);
    file.seekg(0, file.end);
    int_t length = file.tellg();
    file.seekg(0, file.beg);
    if (length > 0) {
        file.read((char*) locations, 4096);
        file.read((char*) timestamps, 4096);
        for (int_t &i : locations)
            i = ntohl(i);
        for (int_t &i : timestamps)
            i = ntohl(i);
    } else
        for (int i = 0; i < 1024; i++)
            locations[i] = timestamps[i] = 0;
}

Region::~Region() {
    file.close();
}

bool Region::getChunk(Chunk *chunk) {
    int_t offset = locations[mod(chunk->getX(), 32) + 32 * mod(chunk->getZ(), 32)] >> 8;
    if (offset == 0)
        return false;
    file.seekg(offset * 4096);
    int_t length;
    file.read((char*) &length, 4);
    length = ntohl(length);
    ubytes_t data(length);
    file.read((char*) data.data(), length);
    ubyte_t *plain = Compression::inflateZlib(data.data() + 1, length).first;
    ubyte_t *copy = (ubyte_t*) plain;
    NBTTag *root = NBTTag::read(copy);
    NBTTagCompound *level = root->asCompound()->get("Level")->asCompound();
    level->get("HeightMap")->asIntArray()->get(chunk->heightMap);
    for (NBTTag *&sectionTag : *(level->get("Sections")->asList())) {
        NBTTagCompound *sectionCmpd = sectionTag->asCompound();
        byte_t y = sectionCmpd->get("Y")->asByte()->get();
        Section *section = chunk->sections[y];
        section->initialize(false);
        ushort blockCount = 0;
        ushort_t *blockTypeData = new ushort_t[4096];
        ubyte_t blockType[4096];
        sectionCmpd->get("Blocks")->asByteArray()->get(blockType);
        ubyte_t blockData[2048];
        sectionCmpd->get("Data")->asByteArray()->get(blockData);
        for (int i = 0; i < 4096; i++) {
            if (blockType[i] > 0)
                blockCount++;
            if (i % 2 == 0)
                blockTypeData[i] = ((blockType[i] & 0xff) << 4) | (blockData[i / 2] & 0xf);
            else
                blockTypeData[i] = ((blockType[i] & 0xff) << 4) | ((blockData[i / 2] >> 4) & 0xf);
        }
        section->blockCount = blockCount;
        section->blockData = blockTypeData;
        sectionCmpd->get("BlockLight")->asByteArray()->get(section->blockLight);
        sectionCmpd->get("SkyLight")->asByteArray()->get(section->skyLight);
        section->initialized = true;
    }
    level->get("Biomes")->asByteArray()->get(chunk->biomes);
    delete root;
    std::free(plain);
    return true;
}
