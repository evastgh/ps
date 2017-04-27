#ifndef __CAT__
#define __CAT__
#include<string>
class Cat {
	public:
		std::string breed;
		int age;

		/** Default constructor */
		Cat();

		/** function that returns cat meow
		  @return the string "meow"
		  */
		// std::string talk() const;
		std::string talk(int number);

		int getAge();
		std::string getBreed();

		/** function that sets the breed
		 * @param breed_in
		 */
		void setBreed(std::string breed_in);
};
#endif
