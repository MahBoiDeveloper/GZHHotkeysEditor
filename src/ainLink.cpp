#ifdef PROJECT_EXE_RELATIVE_PATH

#include <cstdlib>
#include <string>

// main for link application
int main(int argc, char *argv[])
{
    std::string projectExecCommand(PROJECT_EXE_RELATIVE_PATH);
    // replacing the forward slash with the reverse in Windows
    auto pos = 0;
    while ((pos = projectExecCommand.find('/',pos)) != std::string::npos)
    {
        projectExecCommand.replace(pos++, 1, "\\\\");
    }
    // command formation
    for (int i = 0; i < argc; i++)
    {
        projectExecCommand += " ";
        projectExecCommand += argv[i];
    }
    return system(projectExecCommand.c_str());
}

#endif
