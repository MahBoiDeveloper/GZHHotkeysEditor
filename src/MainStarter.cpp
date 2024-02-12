#ifdef PROJECT_EXE_RELATIVE_PATH
    
    #include <cstdlib>
    #include <string>
    
    // Links local executable to the main application of the project
    int main(int argc, char *argv[])
    {
        std::string projectExecCommand(PROJECT_EXE_RELATIVE_PATH);
    
        // Replacing the forward slash with the reverse in Windows
        size_t pos = 0;
    
        while ((pos = projectExecCommand.find('/',pos)) != std::string::npos)
            projectExecCommand.replace(pos++, 1, "\\\\");
    
        // Command formation
        for (int i = 0; i < argc; i++)
        {
            projectExecCommand += " ";
            projectExecCommand += argv[i];
        }
    
        // Calling the main executable
        return system(projectExecCommand.c_str());
    }

#endif
