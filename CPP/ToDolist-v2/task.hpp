#include <string>
#include <sstream>

using std::string;
class Task
{
    private:
        string title;
        bool done = false;
    public:
        Task(string title_in)
        {
            this->title = title_in;
        }

        ~Task(){};

        void set_done(bool state)
        {
            this->done = state;
            return;
        }

        void modify_title(string title_in)
        {
            this->title = title_in;
        }

        string get_title()
        {
            return this->title;
        }

        string state()
        {
            string str_output{};
            str_output += this->title;
            if (this->done)
                str_output += " DONE";
            else
                str_output += " NOT DONE";
            
            return str_output;
        }

        bool get_done()
        {
            return this->done;
        }


};