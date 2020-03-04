#ifndef DOOR_H
#define DOOR_H

class Door{

public:

    Door();
    ~Door();

    bool getKey();

    bool getOpen();
    void setOpen(bool);

private:

    bool key;
    bool open;
};

#endif
