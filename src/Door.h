// Savoir si la porte existe ou pas, si elle necessite une clé ou un etage clear, 0 nord, 1 est, 2 sud, 3 ouest

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