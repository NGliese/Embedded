/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <iostream>

#include "../LibraryModule-1.0-Source/Components/Objects/Timeservice/include/Timeservice.hpp"

int main(int argc, char** argv)
{
	for(;;)
	{
		std::cout << "Running a test ! \n";

		Timeservice::wait_sec(5);
	}
}
