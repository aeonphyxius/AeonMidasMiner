/****************************************************************************
Copyright (c) 2016 Alejandro Santiago Varela

http://www.aeonphyxius.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef MIDAS_SERVICE_MANAGER_H
#define MIDAS_SERVICE_MANAGER_H

#include <memory>
#include <string>
#include <map>

using namespace std;

/**
* This class is a generic implementation of the dessign pattern Service Locator 
* http://gameprogrammingpatterns.com/service-locator.html
*
* uses a generic implementation to make it Service independant.
*
* Also implements the only singleton pattern in this project:
* http://gameprogrammingpatterns.com/singleton.html

*/

namespace Services
{
	static const std::string *ENGINE = new std::string ("ENGINE");
	static const std::string *AUDIO = new std::string("AUDIO");
	static const std::string *INPUT = new std::string("INPUT");
	static const std::string *EVENTS = new std::string("EVENTS");
	static const std::string *SCORE = new std::string("SCORE");

}
namespace Core
{	
	class Service {};
	class ServiceManager
	{
	public:
		static ServiceManager *getInstance();
		~ServiceManager();

		template<class T>
		void regService(const std::string * par_id){
			T *t = new T();
			serviceslist.insert(make_pair (par_id->c_str(), t));
		}

		template<class T>
		void regService(const std::string * par_id, Service * par_service) {
			T *t = new T();
			serviceslist.insert(make_pair(par_id->c_str(), par_service));
		}


		template<class T>
		T* getService ( const std::string * par_id ) {

			//servicelist_t::iterator it = serviceslist.find(par_id);

			servicelist_t::iterator it = serviceslist.find(par_id->c_str());
			if (it != serviceslist.end())
				return static_cast<T*>(it->second);
			//else{
			throw runtime_error("invalid id: ");
			//}
		}

	private:
		ServiceManager() = default;
		typedef std::map<std::string, Service *> servicelist_t;
		servicelist_t		serviceslist;		/* list of all services registered */
	};
}
#endif /* defined( MIDAS_SERVICE_MANAGER_H )*/