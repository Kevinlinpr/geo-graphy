#ifndef GEO_GRAPHY_CONVERT_H_
#define GEO_GRAPHY_CONVERT_H_

#include <vector>
#include <string>

namespace cuda_next {
    
class Convert {
public:
	struct FCTEMObject {
		std::vector<std::vector<std::string>> header; 
		std::vector<std::vector<std::string>> data; 
		std::vector<std::vector<std::string>> window;  
	};
	struct FCTEMObjectDouble {
		std::vector<std::vector<double>> header;
		std::vector<std::vector<double>> data;  
		std::vector<std::vector<double>> window;    
	};
	static std::string FCTEM2TXT(const std::string& source);
	static std::string FCTEM2TXT(const std::vector<double>& source);
	static bool IsInteger(double number);
	static double Scientific2double(const std::string& scientific);
};

} // namespace cuda_next

#endif // GEO_GRAPHY_CONVERT_H_