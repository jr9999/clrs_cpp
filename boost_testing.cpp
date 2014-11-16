#include <iostream>

#include <boost/lambda/lambda.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <boost/array.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <iterator>
#include <algorithm>
#include <thread>

using namespace std;

using boost::asio::ip::tcp;

//original - void print(const boost::system::error_code& /*e*/)
void print(const boost::system::error_code& /*e*/,
    boost::asio::deadline_timer* timer, int* count)
{

  if (*count < 5)
    {
      std::cout << *count << "\n";
      ++(*count);

      timer->expires_at(timer->expires_at() + boost::posix_time::seconds(1));
      
      timer->async_wait(boost::bind(print,
				boost::asio::placeholders::error, timer, count));
    }
}

class printer
{
public:

  /*
  printer(boost::asio::io_service& io)
    : timer_(io, boost::posix_time::seconds(1)),
      count_(0)
  */
  printer(boost::asio::io_service& io)
    : strand_(io),
      timer1_(io, boost::posix_time::seconds(1)),
      timer2_(io, boost::posix_time::seconds(1)),
      count_(0)
  {
    timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));
    timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this)));
  }
  
  ~printer()
  {
    std::cout << "Final count is " << count_ << "\n";
  }

void print1()
  {
    if (count_ < 10)
    {
      std::cout << "Timer 1: " << count_ << "\n";
      ++count_;

      timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
      timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));
    }
  }

  void print2()
  {
    if (count_ < 10)
      {
	std::cout << "Timer 2: " << count_ << "\n";
	++count_;
	
	timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
	timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this)));
      }
  }
  
private:
  boost::asio::strand strand_;
  boost::asio::deadline_timer timer1_;
  boost::asio::deadline_timer timer2_;
  int count_;
};

void ThreadFunction()
{
    int counter = 0;

    for(;;)
    {
        cout << "thread iteration " << ++counter << " Press Enter to stop" << endl;

        try
        {
            // Sleep and check for interrupt.
            // To check for interrupt without sleep,
            // use boost::this_thread::interruption_point()
            // which also throws boost::thread_interrupted
            boost::this_thread::sleep(boost::posix_time::milliseconds(500));
        }
        catch(boost::thread_interrupted&)
        {
            cout << "Thread is stopped" << endl;
            return;
        }
    }
}

int main(int argc, char* argv[])
{

  using namespace boost::lambda;

  try
    {
      if (argc != 3)
	{
	  std::cerr << "Usage: client <host> <port>" << std::endl;
	  return 1;
	}
      
      //boost::asio::io_service io;
      boost::asio::io_service io_service;

      tcp::resolver resolver(io_service);

      //tcp::resolver::query query(argv[1], "daytime");
      std::string server = argv[1];
      int port = atoi(argv[2]);
      
      cout << "server = " << server << "; port = " << port << endl;
      
      tcp::resolver::query query(tcp::v4(), server, boost::lexical_cast<string>(port), boost::asio::ip::resolver_query_base::flags());
      //tcp::resolver::query query(server, port, boost::asio::ip::resolver_query_base::numeric_service);

      tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

      tcp::socket socket(io_service);
      boost::asio::connect(socket, endpoint_iterator);
      
      for (;;)
	{
	  boost::array<char, 128> buf;
	  boost::system::error_code error;
	  
	  size_t len = socket.read_some(boost::asio::buffer(buf), error);

	  if (error == boost::asio::error::eof)
	    break; // Connection closed cleanly by peer.
	  else if (error)
	    throw boost::system::system_error(error); // Some other error.
	  
	  std::cout.write(buf.data(), len);
	}

      int count = 0;
      
      boost::asio::deadline_timer timer(io_service, boost::posix_time::seconds(5));
      
      /*
	typedef std::istream_iterator<int> in;
	
	
	std::for_each(
	in(std::cin), in(), std::cout << (_1 * 3) << " " );
      */
      
      
      cout << "hello" << endl;
      
      // Start thread
      boost::thread t(&ThreadFunction);
      
      //used in this way the timer will prevent someone from stopping the threads using ENTER until 5 seconds have passed.
      //synchronous way - timer.wait();
      //async way
      //original - timer.async_wait(&print);
      //timer.async_wait(boost::bind(print,
      //			       boost::asio::placeholders::error, &timer, &count));
      printer p(io_service);
      
      //io.run();
      
      //having a thread run two timers
      boost::thread timerThread(boost::bind(&boost::asio::io_service::run, &io_service));
      io_service.run();
      timerThread.join();
      
      // Wait for Enter 
      char ch;
      cin.get(ch);
      
      // Ask thread to stop
      t.interrupt();
      
      // Join - wait when thread actually exits
      t.join();
      cout << "main: thread ended" << endl;
      std::cout << "Final count is " << count << "\n";
    
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }  
}
