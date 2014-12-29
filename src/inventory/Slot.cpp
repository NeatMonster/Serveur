#include "Slot.h"

Slot::Slot() : m_stack(nullptr) {}

Slot::~Slot()
{
    delete m_stack;
}

ItemStack *Slot::getStack() {
    return m_stack;
}

void Slot::setStack(ItemStack *stack) {
    if(m_stack != nullptr)
        delete m_stack;
    m_stack = stack;
}
