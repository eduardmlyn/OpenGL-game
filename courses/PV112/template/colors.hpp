struct colorS
{
    int red;
    int green;
    int blue;
};

enum colorE
{
    GOLD,
    DEEP_PURPLE
};

class colors
{
private:
public:
    colors(/* args */) {}
    ~colors() {}
    colorS getColor(colorE color)
    {
        switch (color)
        {
        case GOLD:
            return colorS(218, 165, 32);
        case DEEP_PURPLE:
            return colorS(54, 1, 63);
        default:
            break;
        }
        return colorS(0, 0, 0);
    }
};
