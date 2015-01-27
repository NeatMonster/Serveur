#include "NBTTagList.h"

NBTTagList::NBTTagList() : NBTTag(Type::LIST) {}

NBTTagList::NBTTagList(NBTTagList *tag) : NBTTag(tag) {
    for (auto child : tag->children)
        children.push_back(child->clone());
}

void NBTTagList::read(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    NBTTag::Type type = (NBTTag::Type) *(data++);
    int_t size;
    *(((ubyte_t*) &size) + 3) = *(data++);
    *(((ubyte_t*) &size) + 2) = *(data++);
    *(((ubyte_t*) &size) + 1) = *(data++);
    *(((ubyte_t*) &size) + 0) = *(data++);
    for (size_t i = 0; i < size; i++)
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

std::vector<std::shared_ptr<NBTTag>>::iterator NBTTagList::begin() {
    return children.begin();
}

std::vector<std::shared_ptr<NBTTag>>::iterator NBTTagList::end() {
    return children.end();
}

std::shared_ptr<NBTTag> NBTTagList::clone() {
    return std::make_shared<NBTTagList>(this);
}

bool NBTTagList::equals(std::shared_ptr<NBTTag> tag) {
    if (!tag->isList() || tag->getName() != name)
        return false;
    std::shared_ptr<NBTTagList> list = tag->asList();
    if (children.size() != list->children.size())
        return false;
    for (size_t i = 0; i < children.size(); i++)
        if (!children[i]->equals(list->children[i]))
            return false;
    return true;
}
