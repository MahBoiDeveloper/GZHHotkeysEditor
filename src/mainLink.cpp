#ifdef PROJECT_EXE_PATH

#include <cstdlib>
#include <string>

int main(int argc, char *argv[])
{
    std::string projectExecCommand = PROJECT_EXE_PATH;
    for (int i = 0; i < argc; i++)
    {
        projectExecCommand += " ";
        projectExecCommand += argv[i];
    }
    
    return system(projectExecCommand.c_str());
}

#endif