#include <octoon/process/command.h>


#include <cstdio>
#include <cstdlib>

#define OCTOON_PROCESS_OUTPUT_BUFFER_SIZE 1024

namespace octoon
{

    namespace process
    {
        Command Command::run(const std::string& cmd)
        {
            Command cmd_obj;
            cmd_obj.cmd_ = cmd;
            return cmd_obj;
        }

        Command& Command::arg(const std::string& arg)
        {
            this->args_.push_back(arg);
            return *this;
        }

        Command& Command::args(const std::vector<std::string>& arg_list)
        {
            for(auto& each :arg_list)
                this->args_.push_back(each);

            return *this;
        }

		Command& Command::current_dir(const std::string& path)
		{
			this->current_dir_ = path;
			return *this;
		}

        std::string Command::output()
        {
            std::string raw_cmd;
			if (current_dir_ != "")
			{
				raw_cmd += "cd ";
				raw_cmd += this->current_dir_;
				raw_cmd += " && ";
			}
			
            raw_cmd += this->cmd_;
            for(const auto& each: this->args_)
            {
                raw_cmd += " ";
                raw_cmd += each;
            }

            // run cmd
#if defined(_MSC_VER) || defined (_WIN32) || defined(_WIN64)
            FILE *fp = 0;
            char buf[OCTOON_PROCESS_OUTPUT_BUFFER_SIZE];
            std::string out;
            fp = _popen(raw_cmd.c_str(), "r");
            if( fp != 0)
            {
                while(std::fgets(buf, OCTOON_PROCESS_OUTPUT_BUFFER_SIZE, fp) != 0)
                {
                    out += buf;
                }
                _pclose(fp);
                fp = 0;
            }
#else
            FILE *fp = 0;
            char buf[OCTOON_PROCESS_OUTPUT_BUFFER_SIZE];
            std::string out;
            fp = popen(raw_cmd.c_str(), "r")
            if( fp != 0)
            {
                while(std::fgets(buf, OCTOON_PROCESS_OUTPUT_BUFFER_SIZE, fp) != 0)
                {
                    out += buf;
                }
                pclose(fp);
                fp = 0;
            }
#endif
            return out;
        }

        Child Command::spawn()
        {
            Child child;
            return child;
        }

        int Command::status()
        {
			std::string raw_cmd;
			if (current_dir_ != "")
			{
				raw_cmd += "cd ";
				raw_cmd += this->current_dir_;
				raw_cmd += " && ";
			}
			raw_cmd += this->cmd_;
			for (const auto& each : this->args_)
			{
				raw_cmd += " ";
				raw_cmd += each;
			}

			// run cmd
			int exit_code = 0;
			FILE *fp = 0;
#if defined(_MSC_VER) || defined (_WIN32) || defined(_WIN64)
			fp = _popen(raw_cmd.c_str(), "r");
			exit_code = _pclose(fp);
			fp = 0;

#else
			fp = popen(raw_cmd.c_str(), "r")
			exit_code = pclose(fp);
			fp = 0;
#endif
			return exit_code / 256;
        }

        Command::~Command()
        {
        }
    }
}

