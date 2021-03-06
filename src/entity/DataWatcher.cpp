#include "DataWatcher.h"

#include "PacketBuffer.h"

DataWatcher::DataWatcher() : changed(false) {
    for (size_t i = 0; i < 23; ++i) {
        data[i] = nullptr;
        type[i] = NONE;
    }
}

DataWatcher::~DataWatcher() {
    for (size_t i = 0; i < 23; ++i)
        switch (type[i]) {
            case BYTE:
                delete (byte_t*) data[i];
                break;
            case SHORT:
                delete (short_t*) data[i];
                break;
            case INT:
                delete (int_t*) data[i];
                break;
            case FLOAT:
                delete (float_t*) data[i];
                break;
            case STRING:
                delete (string_t*) data[i];
                break;
            case ITEMSTACK:
                delete (ItemStack*) data[i];
                break;
        }
}

byte_t DataWatcher::getByte(size_t index) {
    return *((byte_t*) data[index]);
}

void DataWatcher::setByte(size_t index, byte_t b) {
    changed = true;
    if(data[index] != nullptr)
        delete (byte_t*) data[index];
    data[index] = new byte_t(b);
    type[index] = BYTE;
}

short_t DataWatcher::getShort(size_t index) {
    return *((short_t*) data[index]);
}

void DataWatcher::setShort(size_t index, short_t s) {
    changed = true;
    if(data[index] != nullptr)
        delete (short_t*) data[index];
    data[index] = new short_t(s);
    type[index] = SHORT;
}

int_t DataWatcher::getInt(size_t index) {
    return *((int_t*) data[index]);
}

void DataWatcher::setInt(size_t index, int_t i) {
    changed = true;
    if(data[index] != nullptr)
        delete (int_t*) data[index];
    data[index] = new int_t(i);
    type[index] = INT;
}

float_t DataWatcher::getFloat(size_t index) {
    return *((float_t*) data[index]);
}

void DataWatcher::setFloat(size_t index, float_t f) {
    changed = true;
    if(data[index] != nullptr)
        delete (float_t*) data[index];
    data[index] = new float_t(f);
    type[index] = FLOAT;
}

string_t DataWatcher::getString(size_t index) {
    return *((string_t*) data[index]);
}

void DataWatcher::setString(size_t index, string_t str) {
    changed = true;
    if(data[index] != nullptr)
        delete (string_t*) data[index];
    data[index] = new string_t(str);
    type[index] = STRING;
}

std::shared_ptr<ItemStack> DataWatcher::getItemStack(size_t index) {
    return std::make_shared<ItemStack>((ItemStack*) data[index]);
}

void DataWatcher::setItemStack(size_t index, std::shared_ptr<ItemStack> stack) {
    changed = true;
    if(data[index] != nullptr)
        delete (ItemStack*) data[index];
    data[index] = stack == nullptr ? nullptr : new ItemStack(stack.get());
    type[index] = ITEMSTACK;
}

void DataWatcher::read(PacketBuffer &buffer) {
    byte_t item, index;
    do {
        buffer.getByte(item);
        if (item == 0x7f)
            break;
        index = item & 0x1f;
        switch (item >> 5) {
            case BYTE: {
                byte_t b;
                buffer.getByte(b);
                setByte(index, b);
                break;
            } case SHORT: {
                short_t s;
                buffer.getShort(s);
                setShort(index, s);
                break;
            } case INT: {
                int_t i;
                buffer.getInt(i);
                setInt(index, i);
                break;
            } case FLOAT: {
                float_t f;
                buffer.getFloat(f);
                setFloat(index, f);
                break;
            } case STRING: {
                string_t str;
                buffer.getString(str);
                setString(index, str);
                break;
            } case ITEMSTACK: {
                std::shared_ptr<ItemStack> stack;
                buffer.getItemStack(stack);
                setItemStack(index, stack);
                break;
            }
        }
    } while (true);
}

void DataWatcher::write(PacketBuffer &buffer) {
    for (byte_t index = 0; index < 23; ++index) {
        if (type[index] == NONE)
            continue;
        buffer.putByte(type[index] << 5 | (index & 0x1f));
        switch (type[index]) {
            case BYTE:
                buffer.putByte(getByte(index));
                break;
            case SHORT:
                buffer.putShort(getShort(index));
                break;
            case INT:
                buffer.putInt(getInt(index));
                break;
            case FLOAT:
                buffer.putFloat(getFloat(index));
                break;
            case STRING:
                buffer.putString(getString(index));
                break;
            case ITEMSTACK:
                buffer.putItemStack(getItemStack(index));
                break;
        }
    }
    buffer.putByte(0x7f);
}

bool DataWatcher::hasChanged() {
    bool changed_ = changed;
    changed = false;
    return changed_;
}
