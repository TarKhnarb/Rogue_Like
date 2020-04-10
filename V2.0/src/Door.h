#ifndef GAME_DOOR_H
#define GAME_DOOR_H

class Door{

public:

    Door();

    bool getOpen() const;
    void setOpen(bool);

private:
    bool open;
};

#endif
