//
// Created by oldlonecoder on 11/19/23.
//



#include "DevTest.h"
#include <AppBook/Book/StmlText.h>
#include <csignal>

void sig_int( int s )
{
    //rem::push_interrupted() << " dump messages stream and exit:";
    //rem::clear(nullptr);
    std::cerr << "\n---------------------------------------\n sig interrupt caugh - flushing Book contents.\n ";
    AppBook::Close();
    exit(3);
}

void sig_fault( int s)
{
    //rem::push_segfault() << " dump messages stream and exit:";
    //rem::clear(nullptr);
    std::cerr << " sigfault caught...\n";
    AppBook::Close();
    exit(127);
}

void sig_abort( int s)
{
    //rem::push_aborted() << " dump messages stream and exit:";
    //rem::clear(nullptr);
    std::cerr << s << '\n';
    AppBook::Close();
    exit(127);
}


namespace Tui::Test
{

DevTest::DevTest(std::string ID): Util::Object(nullptr, ID)
{

}

DevTest::~DevTest()
{

}


auto DevTest::Exec()->Book::Result
{
    ConIO.Start();
    ConIO.Terminate();

    return Book::Result::Ok;
}




} // Tui::Test


AppBook& InitBook(std::string BookName)
{
    AppBook& Livre = AppBook::Init(BookName);
    //...
    std::string head;
    Book::STMLText MLText;

    Livre.Open();
    Livre.Descriptions =
        R"(
<Icon:School; fg:Yellow>This is the development of the <fg:BlueViolet>[<fg:HotPink4>SimpleTUI Library API<fg:BlueViolet>]<fg/>
--------------------------------------------------------
)";
    AppBook::CreateSection("Devel").Open().CreateSectionContents("Log.Ansi");
    MLText << Livre.Descriptions >> head;
    Livre["Devel"]["Log.Ansi"];
    AppBook::Out() << Book::Fn::Weekday << ' ' << Book::Fn::Stamp << Book::Fn::Endl << head << Book::Fn::Endl;

    return Livre;
}

auto main(int arc, char** argv) -> int
{
    std::signal(SIGINT, sig_int);
    std::signal(SIGSEGV, sig_fault);
    std::signal(SIGABRT, sig_abort);
    try {
        InitBook("SimpleTUI");
        Tui::Test::DevTest Test("ConIO Tests");
        Test.Exec();

    }
    catch (AppBook::Exception& e)
    {
        std::cout << "Book::exception caugh:\n[" << e.what() << "]\n";
    }

    AppBook::Close();
    return static_cast<int>(Book::Result::Ok);
}