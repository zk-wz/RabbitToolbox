#ifndef OCTOON_PROCESS_COMMAND_H_
#define OCTOON_PROCESS_COMMAND_H_

#include <octoon/runtime/platform.h>

#include <string>
#include <vector>

namespace octoon
{
    namespace process
    {
        // a running processing
        class OCTOON_EXPORT Child
        {
        private:

        public:
            
        };

        // a command
        class OCTOON_EXPORT Command
        {
        private:
            std::string cmd_;
            std::vector<std::string> args_;
			std::string current_dir_;

        public:
            static Command run(const std::string& cmd);
            Command& arg(const std::string& arg);
            Command& args(const std::vector<std::string>& arg_list);
			Command& current_dir(const std::string& path);
            
            std::string output();
            Child spawn();
            int status();
            ~Command();
            
        };
    }
}

#endif