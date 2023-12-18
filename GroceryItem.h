#pragma once

#ifndef GROCERYITEM_H
#define GROCERYITEM_H

#include <string>
using namespace std;

class GroceryItem {
private:
    string name;
    int quantity;

public:
    GroceryItem(string itemName, int itemQuantity);

    string getName() const;
    int getQuantity() const;
    void addItem(int additionalQuantity);
};

#endif /* GROCERYITEM_H */