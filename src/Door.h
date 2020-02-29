// Savoir si la porte existe ou pas, si elle necessite une clé ou un etage clear, 0 nord, 1 est, 2 sud, 3 ouest

class Door{

public:

    Door();
    ~Door();

    void openIt();
    void closeIt();

    bool getExist();
    void setExist(bool);

    bool getKey();
    void setKey(bool);

    bool getOpen();
    void setOpen(bool);

private:

    bool exist;
    bool key;
    bool open;
};