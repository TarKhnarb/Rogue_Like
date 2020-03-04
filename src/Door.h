#ifndef DOOR_H
#define DOOR_H

class Door{

public:

    Door();
    Door(bool, bool);

    bool getKey();
    void setKey(bool);

    bool getOpen();
    void setOpen(bool);

private:

    bool key;
    bool open;
};

#endif
