/**
 * @addtogroup main
 *
 * @{
 *
 * @copyright Carlos Valle Torres, 2020
 * 
 * This source file is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation, either version 3 of the 
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * @file main.cpp
 * @brief (see main.h)
 * @details (see main.h)
 *
 */

/* *****************************************************************************
 * INCLUDES
 * ****************************************************************************/

/* Gtest */
#include "gtest/gtest.h"

#include <thread>

/* *****************************************************************************
 * PRIVATE DECLARATIONS
 * ****************************************************************************/


int main(int argc, char * argv[])
{
	/* Results from test */
	int iRetCode = 0;

	/* Initialization of Google Test */
	::testing::InitGoogleTest(&argc, argv);

	/* Run utests */
	iRetCode = RUN_ALL_TESTS();

	return iRetCode;

}


/**
 * @} (main)
 */
