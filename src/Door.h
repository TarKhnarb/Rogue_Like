#ifndef DOOR_H
#define DOOR_H

class Door{

public:

    Door();
    Door(bool, bool);

    bool getKey() const;
    void setKey(bool);

    bool getOpen() const;
    void setOpen(bool);

private:

    bool key;
    bool open;
};

#endif
