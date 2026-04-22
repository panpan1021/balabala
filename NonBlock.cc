#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
void SetNonBlock(int fd)
{
    int fl = fcntl(fd, F_GETFL);
    if (fl < 0)
    {
        std::cerr << "fcntl error" << std::endl;
        return;
    }
    fcntl(fd, F_SETFL, fl | O_NONBLOCK);
}
int main()
{
    char inbuffer[1024];
    SetNonBlock(0);
    while (true)
    {
        ssize_t n = read(0, inbuffer, sizeof(inbuffer) - 1);
        if (n > 0)
        {
            inbuffer[n - 1] = 0;
            printf("echo # %s\n", inbuffer);
        }
        else if (n == 0)
        {
            std::cout << "end of file" << std::endl;
        }
        else
        {
            if (errno == EWOULDBLOCK || errno == EAGAIN)
            {
                std::cout << "data is not ready" << std::endl;
                sleep(1);
                continue;
            }
            else if (errno == EINTR)
            {
                sleep(1);
            }
            else
            {
                std::cerr << "read error ..." << errno << std::endl;
                std::cerr << "read error ..." << strerror(errno) << std::endl;
            }
        }
        sleep(1);
    }
    return 0;
}