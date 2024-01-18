#include<vector>
#include<iostream>
#include<algorithm>
#include<array>
#include<map>
#include<algorithm>
namespace libCard
{
        enum class Value
        {
            Two = 0,Three = 1,Four = 2,Five = 3,
            Six = 4,Seven = 5,Eight = 6,Nine = 7,
            Ten = 8,Jack = 9,Queen = 10,King = 11,
            Ace = 12
        };

        enum class Color
        {
            Diamond = 0,
            Club = 1,
            Heart = 2,
            Spade = 3,
        };


        std::map<Value,std::string> valueMap
        { 
            {Value::Two,"Two"}, {Value::Three,"Three"}, {Value::Four,"Four"},
            {Value::Five,"Five"}, {Value::Six,"Six"}, {Value::Seven,"Seven"},
            {Value::Eight,"Eight"}, {Value::Nine,"Nine"}, {Value::Ten,"Ten"},
            {Value::Jack,"Jack"}, {Value::Queen,"Queen"},{Value::King,"King"} ,
            {Value::Ace,"Ace"} 
        };

        std::map<Color,std::string> colorMap
        {
            {Color::Club,"Club"},{Color::Diamond,"Diamond"},
            {Color::Heart,"Heart"},{Color::Spade,"Spade"}
        };

         std::array<Value,13> AllValue = {Value::Two,Value::Three,Value::Four,Value::Five,
                                Value::Six,Value::Seven,Value::Eight,Value::Nine
                                ,Value::Ten,Value::Jack,Value::Queen,Value::King
                                ,Value::Ace};
        // std::array allColor = {};

};


class Card
{
    friend std::ostream& operator<<(std::ostream& Output, Card& Card_in);

    private:
        libCard::Color cardColor;
        libCard::Value cardValue;
        bool is_hidden;
    public:
        Card(libCard::Color Color_in, libCard::Value Value_in)
        {
            cardValue = Value_in;
            cardColor = Color_in;
            is_hidden = true;
        }
        auto getColor()
        {
            return cardColor;
        }

        auto getValue()
        {
            return cardValue;
        }

        bool getHidden()
        {
            return is_hidden;
        }

        void Reveal()
        {
            is_hidden=false;
        }

        void Hide()
        {
            is_hidden=true;
        }

        std::string valueString()
        {
            return libCard::valueMap[cardValue];
        }
        std::string colorString()
        {
            return libCard::colorMap[cardColor];
        }
};

class Deck
{

    private:
        std::vector<Card> DeckGame; 
    public:
        Deck(){}

        void bigFulfill()
        {
            for(auto& [Color,cString] : libCard::colorMap)
                for(auto& [Value,vString] : libCard::valueMap)
                    DeckGame.emplace_back(Value,Color);
            return;
        }

        void smallFulfill()
        {
            for(auto [Color,cString]: libCard::colorMap)
                for(int i=0;i<6;i++)
                    DeckGame.emplace_back(Color,libCard::AllValue[7+i]);
            return;
        }

        ~Deck()
        {
            
        }

        void Show()
        {
            int iterator=1;
        for(Card card_iterator : DeckGame)
            {
                if(card_iterator.getHidden())
                    std::cout<<iterator<<". "<<"Card Hidden"<<std::endl;
                else
                    std::cout<<iterator<<". "<<card_iterator<<std::endl;
                iterator++;
            }
        }

        // void Shuffle()
        // {
        //     std::shuffle(DeckGame.begin(),DeckGame.end());
        // }

        void RiffleShuffle()
        {
            std::vector<Card> temp;

            for (int i = 0; i < DeckGame.size()/2; i++)
                temp.push_back(DeckGame[i*2]);
            for (int i = 0; i < DeckGame.size()/2; i++)
                temp.push_back(DeckGame[(i*2)+1]);

            std::copy(temp.begin(),temp.end(),DeckGame.begin());
            delete &temp;
            return;
            
            
        }
};

std::ostream& operator<<(std::ostream& Output, Card& Card_in)
{
    Output<<Card_in.valueString()<<" of "<<Card_in.colorString();
    return Output;
}

int main()
{
    Deck DeckTwo;
    DeckTwo.smallFulfill();
    DeckTwo.Show();
    return 0;
}