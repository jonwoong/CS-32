

#include <iostream>
#include <string>
using namespace std;

///// USER DEFINED FUNCTIONS /////

void printString(string someString)
{
    for (int n=0; n != someString.size(); n++)
    {
        cout << someString[n];
    }
}

string intToString(int number)
{
    string returnThis = to_string(number);
    return returnThis;
}

///// FILE CLASS /////

    /// DECLARATION ///

class File
{
public:
    File(string fileName);
    virtual ~File();
    virtual void open() const = 0;
    virtual void redisplay() const;
    string name() const;
private:
    string m_Name;
};
    /// CONSTRUCTOR ///

File::File(string fileName)
: m_Name(fileName)
{
}

    /// DESTRUCTOR ///

File::~File()
{
}

    /// FUNCTION IMPLEMENTATIONS ///

string File::name() const
{
    return m_Name;
}

void File::redisplay() const
{
    string returnThis = "refresh the screen";
    printString(returnThis);
}

///// TEXTMSG CLASS ////

    /// DECLARATION ///

class TextMsg : public File
{
public:
    TextMsg(string fileName);
    ~TextMsg();
    virtual void open() const;
    virtual void redisplay() const;
private:
    string t_Name;
};

    /// CONSTRUCTOR ///
TextMsg::TextMsg(string fileName)
: File(fileName), t_Name(fileName)
{
}

    /// DESTRUCTOR ///

TextMsg::~TextMsg()
{
    string returnThis = "Destroying " + File::name() + ", a text message" + "\n";
    printString(returnThis);
}

    /// FUNCTION IMPLEMENTATIONS ///

void TextMsg::open() const
{
    string returnThis = "open text message";
    printString(returnThis);
}

void TextMsg::redisplay() const
{
    File::redisplay();
}

///// VIDEO CLASS /////

    /// DECLARATION ///

class Video : public File
{
public:
    Video(string fileName, int runTime);
    ~Video();
    virtual void open() const;
    virtual void redisplay() const;
private:
    string v_Name;
    int v_runTime;
};

    /// CONSTRUCTOR ///

Video::Video(string fileName, int runTime)
: File(fileName), v_runTime(runTime), v_Name(fileName)
{
}

    /// DESTRUCTOR ///

Video::~Video()
{
    string returnThis = "Destroying " + File::name() + ", a video" + "\n";
    printString(returnThis);
}

    /// FUNCTION IMPLEMENTATIONS ///

void Video::open() const
{
    string returnThis = "play " + intToString(v_runTime) + " second video";
    printString(returnThis);
}

void Video::redisplay() const
{
    string returnThis = "replay video";
    printString(returnThis);
}

///// PICTURE CLASS /////

    /// DECLARATION ///

class Picture : public File
{
public:
    Picture(string fileName);
    ~Picture();
    virtual void open() const;
    virtual void redisplay() const;
private:
    string p_Name;
};

    /// CONSTRUCTOR ///

Picture::Picture(string fileName)
: File(fileName), p_Name(fileName)
{
}

    /// DESTRUCTOR ///

Picture::~Picture()
{
    string returnThis = "Destroying the picture " + File::name() + "\n";
    printString(returnThis);
}

    /// FUNCTION IMPLEMENTATIONS ///

void Picture::open() const
{
    string returnThis = "show picture";
    printString(returnThis);
}

void Picture::redisplay() const
{
    File::redisplay();
}

