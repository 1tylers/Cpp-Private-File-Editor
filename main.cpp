
// Libraries
#include <iomanip>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>


using namespace std;


int main(int argc, char *argv[])
{
    // Declare variables
    int fd, opt, i;
    struct stat status;
    int permissions;
    ssize_t wr;

    // check is set to true and will stay this way if there is no 'c' present
    bool check = true;

    // Use getopt to test if there is "-c" typed before the file
   while ((opt = getopt(argc, argv, "c")) != -1)
   {
    switch (opt)
    {
        // If 'c' is present, set check to false
        case 'c':
            check = false;
            break;
    }
   }

    // If '-c' is present, then i = 2, otherwise i = 1. this will be used for the argv spots
    // Since -c moves the file over one spot i is 2 when its present and 1 when its not
    if (check == false)
    {
        i = 2;
    }
    else
    {
        i = 1;
    }


    
        // Use stat function to check if there is a file
        if (stat(argv[i], &status) == -1)
        {
       
            // If there is not a file, O_CREAT creates a file for us and S_IWUSR gives us write access to it
            fd = open(argv[i], O_CREAT, S_IWUSR);

            // Change file permissions to give user write access
            chmod(argv[i], 0200);

            // Close file
            close(fd);
        }
        else
        {
        
            // Check if there are permissions on the file using st_mide, S_IRWXU gives the octal for permissions we need
            stat(argv[i], &status);
            permissions = (status.st_mode & S_IRWXU);

            // If the are permissions, meaning its not 0000 then error message permissions present
            if (permissions > 0)
            {
                perror("Permissions Present");
                exit(1);
            }


            //Change file permissions to give user write/read access
            chmod (argv[i], 0400);

            // Open the file, gives writing access and O_TRUNC truncates the file
            fd = open(argv[i], O_WRONLY, O_CREAT);

            // Change file permissions to just write access
            chmod(argv[i], 0200);

            // Close file
            close(fd);
        }

    // If '-c' is present
    if (i == 2)
    {
    
        // Open file, truncate
        fd = open(argv[i], O_WRONLY | O_TRUNC);

        // Error if open fails
        if (fd == -1)
        {
            perror("Opening Error");
            exit(1);
        }

        // get the size of the text that you are putting into the file
        int size = strlen(argv[i + 1]);

        // Write function, writes at the next spot: argv[i + 1], size is amount of bits of the text
        wr = write(fd, argv[i + 1], size);
        if (wr == -1)
        {
            perror("Writing Error");
            exit(1);
        }

        // Changes permissions back to nothing
        chmod(argv[i], 0000);

        // Close file
        close(fd);
    }
   
    // When '-c' isn't present
    else
    {
    
        // Open file, appends
        fd = open(argv[i], O_WRONLY | O_APPEND);

        // Error if open fails
        if (fd == -1)
        {
            perror("Opening Error");
            exit(1);
        }

        // Get the size of the text that you are putting into the file
        int size = strlen(argv[i + 1]);

        // Write function, writes at the next spot: argv[i+1]
        wr = write(fd, argv[i + 1], size);

        // Error if write fails
        if (wr == -1)
        {
            perror("Writing Error");
            exit(-1);
        }

        // Changers permissions back to nothing
        chmod(argv[i], 0000);

        // Close file
        close(fd);
    }

    return 0;
}

