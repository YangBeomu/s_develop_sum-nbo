#include <iostream>
#include <vector>
#include <string>
#include <arpa/inet.h>

std::string to_string_hex(uint32_t num);
std::string to_string_hex(uint16_t num);

int main(int argc, char* argv[]) {
	std::vector<FILE*> files;

	if(argc > 1) {
		for(int i=1; i<argc; i++) {
			auto file = fopen(argv[i], "r");
			if(file != NULL)
				files.push_back(file);
			else {
				std::cerr<<"Failed to open file : " << argv[i] <<std::endl;
				return -1;
			}
		}
	}else {
		std::cerr<<"This program requires at least one argument."<<std::endl;
		return -1;
	}
	
	std::string result;
	int size = files.size();
	uint32_t addNum = 0;

	for(int i=0; i<size; i++) {
		uint32_t buffer, tmp;
		std::string hexStr;
		FILE* file = files[i];

                if(fread(&buffer, sizeof(buffer), 1, file)) {
                        tmp = ntohl(buffer);
			addNum += tmp;

                        result.append(std::to_string(tmp));
			
			hexStr = to_string_hex(tmp);
                        if(!hexStr.empty()) {
                                result.append("(0x" + hexStr + ")");
				result.append(i == size - 1 ? " = " + std::to_string(addNum) + "(" + to_string_hex(addNum) + ")" : " + ");
                        }
                }
                else {
                        std::cerr<<"The file size is less than 4 bytes. \n";
			return -1;
		}

		fclose(file);
	}
	
	std::cout<<result<<std::endl;

	return 0;
}

std::string to_string_hex(uint32_t num) {
        char hexBuf[9];
        
        if(std::sprintf(hexBuf, "%08x", num) <= 0)
                return std::string();
	
        return std::string(hexBuf);
}

std::string to_string_hex(uint16_t num) {
        char hexBuf[9];
        
        if(std::sprintf(hexBuf, "%04x", num) <= 0)
                return std::string();

        return std::string(hexBuf);
}

