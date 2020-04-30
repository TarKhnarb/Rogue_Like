#ifndef GAME_DOOR_H
#define GAME_DOOR_H

class Door{

public:
    /**
     * @brief Construct the door open
     */
    Door();

    /**
 * @brief Check if the door is open
 * @return true if open, else false
 */
    bool getOpen() const;

    /**
 * @brief set the value of the door
 * @param boolean true to open door, else false
 */
    void setOpen(bool);

private:
    bool open;
};

#endif
