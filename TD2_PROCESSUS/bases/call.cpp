#include <cstdlib>
#include <unistd.h> 

int main()
{
    while (true) {
        sleep(1);
        std::system( "./child" ); 
    }
}