#include "NBTTagCompound.h"

NBTTagCompound::NBTTagCompound() : NBTTag(Type::COMPOUND) {}

NBTTagCompound::NBTTagCompound(NBTTagCompound *tag) : NBTTag(tag) {
    for (auto child : tag->children)
        children[child.first] = child.second->clone();
}

NBTTagCompound::~NBTTagCompound() {
    for (auto child : children)
        delete child.second;
}

void NBTTagCompound::read(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    NBTTag *child;
    while ((child = NBTTag::read(data)) != nullptr)
        children.insert({child->name, child});
}

void NBTTagCompound::write(ubyte_t *&data, bool header) {
    NBTTag::write(data, header);
    for (auto child : children)
        child.second->write(data, true);
}

void NBTTagCompound::print(int tab, bool header) {
    NBTTag::print(tab, header);
    std::cout << "TAG_Compound(" << (header ? ("'" + name + "'") : "None") << ")" << std::endl;
    NBTTag::print(tab, header);
    std::cout << "{" << std::endl;
    for (auto child : children)
        child.second->print(tab + 1, true);
    NBTTag::print(tab, header);
    std::cout << "}" << std::endl;
}

NBTTag *&NBTTagCompound::get(string_t name) {
    return children[name];
}

void NBTTagCompound::set(string_t name, NBTTag *&child) {
    children[name] = child;
}

NBTTagCompound *NBTTagCompound::clone() {
    return new NBTTagCompound(this);
}
