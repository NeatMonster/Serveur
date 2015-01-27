#include "NBTTagCompound.h"

NBTTagCompound::NBTTagCompound() : NBTTag(Type::COMPOUND) {}

NBTTagCompound::NBTTagCompound(NBTTagCompound *tag) : NBTTag(tag) {
    for (auto child : tag->children)
        children[child.first] = child.second->clone();
}

void NBTTagCompound::read(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    std::shared_ptr<NBTTag> child;
    while ((child = NBTTag::read(data)) != nullptr)
        children.insert({child->name, child});
}

void NBTTagCompound::write(ubyte_t *&data, bool header) {
    NBTTag::write(data, header);
    for (auto child : children)
        child.second->write(data, true);
    *(data++) = Type::END;
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

std::shared_ptr<NBTTag> NBTTagCompound::get(string_t name) {
    return children[name];
}

void NBTTagCompound::set(string_t name, std::shared_ptr<NBTTag> child) {
    children[name] = child;
}

std::shared_ptr<NBTTag> NBTTagCompound::clone() {
    return std::make_shared<NBTTagCompound>(this);
}

bool NBTTagCompound::equals(std::shared_ptr<NBTTag> tag) {
    if (!tag->isCompound() || tag->getName() != name)
        return false;
    std::shared_ptr<NBTTagCompound> compound = tag->asCompound();
    if (children.size() != compound->children.size())
        return false;
    for (auto child : children) {
        auto compoundChild = compound->children.find(child.first);
        if (compoundChild == compound->children.end() || !compoundChild->second->equals(child.second))
            return false;
    }
    return true;
}
