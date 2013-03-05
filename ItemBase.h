#ifndef SSVMS_ITEMBASE
#define SSVMS_ITEMBASE

#include <string>

namespace ssvms
{
	class Menu;
	class Category;
	
	class ItemBase
	{
		protected:
			Menu& menu;
			Category& category;
			std::string name;

		public:
			ItemBase(Menu& mMenu, Category& mCategory, const std::string& mName);
			virtual ~ItemBase();

			virtual void execute();
			virtual void increase();
			virtual void decrease();

			virtual std::string getName();
	};
}

#endif 
