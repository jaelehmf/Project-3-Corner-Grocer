#include "GroceryItem.h"
using namespace std;

//constructor
GroceryItem::GroceryItem(string itemName, int itemQuantity) : name(itemName), quantity(itemQuantity) {}

//getters
string GroceryItem::getName() const {
    return name;
}

int GroceryItem::getQuantity() const {
    return quantity;
}

//setter
void GroceryItem::addItem(int additionalQuantity) {
    quantity += additionalQuantity;
}
