/*
	MATHS.H
	-------
	Copyright (c) 2016 Andrew Trotman
	Released under the 2-clause BSD license (See:https://en.wikipedia.org/wiki/BSD_licenses)
*/
/*!
	@file
	@brief Basic maths functions.
	@details Some of these already exist in the C++ Standard Library or the C Runtime Library, but they are re-implemented here for portabilit and consistency reasons.
	@author Andrew Trotman
	@copyright 2016 Andrew Trotman
*/

namespace JASS
	{
	/*
		CLASS MATHS
		-----------
	*/
	/*!
		@brief Basic maths functions.
	*/
	class maths
		{
		private:
			/*
				MATHS()
				-------
			*/
			/*!
				@brief Private constructor.
				@details A private constructor makes it impossable to instantiate this class - done because all methods are static.
			*/
			maths()
				{
				/*
					Nothing
				*/
				}
			
		public:
			/*
				MAX()
				-----
			*/
			/*!
				@brief Return the maximum of the two parameters.
				@details This method is order-preserving - that is, if a == b then a is returned as the max.
				@param first [in] First of the two.
				@param second [in] Second of the two.
				@return The largest of the two (as compated using operator>=())
			*/
			template <typename TYPE>
			static const TYPE &max(const TYPE &first, const TYPE &second)
				{
				return first >= second ? first : second;
				}
			
			/*
				MAX()
				-----
			*/
			/*!
				@brief Return the maximum of the three parameters.
				@details This method is order-preserving (if a == b == c then a is returned, etc.).
				@param first [in] First of the three.
				@param second [in] Second of the three.
				@param third [in] Third of the three.
			*/
			template <typename TYPE>
			static const TYPE &max(const TYPE &first, const TYPE &second, const TYPE &third)
				{
				return max(max(first, second), third);
				}

			/*
				MIN()
				-----
			*/
			/*!
				@brief Return the minimum of the two parameters.
				@details This method is order-preserving - that is, if a == b then a is returned.
				@param first [in] First of the two.
				@param second [in] Second of the two.
				@return The smallest of the two (as compated using operator<=())
			*/
			template <typename TYPE>
			static const TYPE &min(const TYPE &first, const TYPE &second)
				{
				return first <= second ? first : second;
				}
				
			/*
				MIN()
				-----
				Return the minimum of three integers (order preserving)
			*/
			/*!
				@brief Return the minimum of the three parameters.
				@details This method is order-preserving (if a == b == c then a is returned, etc.).
				@param first [in] First of the three.
				@param second [in] Second of the three.
				@param third [in] Third of the three.
				@return The smallest of the three (as compated using operator<=())
			*/
			template <typename TYPE>
			static const TYPE &min(const TYPE &first, const TYPE &second, const TYPE &third)
				{
				return min(min(first, second), third);
				}
		};
	}

