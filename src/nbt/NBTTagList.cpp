#include "NBTTagList.h"

NBTTagList::NBTTagList() : NBTTag(Type::LIST) {}

NBTTagList::NBTTagList(NBTTagList *tag) : NBTTag(tag) {
    for (auto child : tag->children)
        children.push_back(child->clone());
}

NBTTagList::~NBTTagList() {
    for (auto child : children)
        delete child;
}

void NBTTagList::read(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    NBTTag::Type type = (NBTTag::Type) *(data++);
    int_t size;
    *(((ubyte_t*) &size) + 3) = *(data++);
    *(((ubyte_t*) &size) + 2) = *(data++);
    *(((ubyte_t*) &size) + 1) = *(data++);
    *(((ubyte_t*) &size) + 0) = *(data++);
    for (int_t i = 0; i < size; i++)
        children.push_back(NBTTag::read(data, type, false));
}

void NBTTagList::write(ubyte_t *&data, bool header) {
    NBTTag::write(data, header);
    *(data++) = children.front()->type;
    int_t size = children.size();
    *(data++) = *(((ubyte_t*) &size) + 3);
    *(data++) = *(((ubyte_t*) &size) + 2);
    *(data++) = *(((ubyte_t*) &size) + 1);
    *(data++) = *(((ubyte_t*) &size) + 0);
    for (auto child : children)
        child->write(data, false);
}

void NBTTagList::print(int tab, bool header) {
    NBTTag::print(tab, header);
    std::cout << "TAG_List(" << (header ? ("'" + name + "'") : "None") << "):" << std::endl;
    NBTTag::print(tab, header);
    std::cout << "{" << std::endl;
    for (auto child : children)
        child->print(tab + 1, false);
    NBTTag::print(tab, header);
    std::cout << "}" << std::endl;
}

std::vector<NBTTag*>::iterator NBTTagList::begin() {
    return children.begin();
}

std::vector<NBTTag*>::iterator NBTTagList::end() {
    return children.end();
}

NBTTagList *NBTTagList::clone() {
    return new NBTTagList(this);
}
