#ifndef GAME_DOOR_H
#define GAME_DOOR_H

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
