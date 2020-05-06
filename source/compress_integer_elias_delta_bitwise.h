/*
	COMPRESS_INTEGER_ELIAS_DELTA_BITWISE.H
	--------------------------------------
	Copyright (c) 2018 Andrew Trotman
	Released under the 2-clause BSD license (See:https://en.wikipedia.org/wiki/BSD_licenses)

	Originally from the ATIRE codebase (where it was also written by Andrew Trotman)
*/
/*!
	@file
	@brief Elias delta encoding using bit-by-bit encoding and decoding (slow)
	@author Andrew Trotman
	@copyright 2018 Andrew Trotman
*/
#pragma once

#include "compress_integer_elias_gamma_bitwise.h"

namespace JASS
	{
	/*
		CLASS COMPRESS_INTEGER_DELTA_GAMMA_BITWISE
		------------------------------------------
	*/
	/*!
		@brief Elias delta encoding using bit-by-bit encoding and decoding (slow)
	*/
	template <typename ACCUMULATOR_TYPE, size_t MAX_DOCUMENTS, size_t MAX_TOP_K>
	class compress_integer_elias_delta_bitwise : public compress_integer_elias_gamma_bitwise<ACCUMULATOR_TYPE, MAX_DOCUMENTS, MAX_TOP_K>
		{
		protected:
			/*
				COMPRESS_INTEGER_DELTA_GAMMA_BITWISE::ENCODE()
				----------------------------------------------
			*/
			/*!
				@brief encode (and push) one integer
				@param val [in] The integer to encode
			*/
			inline void encode(document_id::integer val)
				{
				uint32_t exp = maths::floor_log2(val);

				compress_integer_elias_gamma_bitwise<ACCUMULATOR_TYPE, MAX_DOCUMENTS, MAX_TOP_K>::encode(exp + 1);
				this->bitstream.push_bits(val, exp);
				}

			/*
				COMPRESS_INTEGER_DELTA_GAMMA_BITWISE::DECODE()
				----------------------------------------------
			*/
			/*!
				@brief Decode (and pull) one integer from the stream
				@return The next integer in the stream
			*/
			inline document_id::integer decode(void)
				{
				document_id::integer exp = (document_id::integer)compress_integer_elias_gamma_bitwise<ACCUMULATOR_TYPE, MAX_DOCUMENTS, MAX_TOP_K>::decode() - 1;

				return (document_id::integer)((1ULL << exp) | this->bitstream.get_bits(exp));
				}

		public:
			/*
				COMPRESS_INTEGER_ELIAS_DELTA_BITWISE::COMPRESS_INTEGER_ELIAS_DELTA_BITWISE()
				----------------------------------------------------------------------------
			*/
			/*!
				@brief Constructor
			*/
			compress_integer_elias_delta_bitwise()
				{
				/* Nothing */
				}

			/*
				COMPRESS_INTEGER_ELIAS_DELTA_BITWISE::COMPRESS_INTEGER_ELIAS_DELTA_BITWISE()
				----------------------------------------------------------------------------
			*/
			/*!
				@brief Destructor
			*/
			virtual ~compress_integer_elias_delta_bitwise()
				{
				/* Nothing */
				}

			/*
				COMPRESS_INTEGER_ELIAS_DELTA_BITWISE::ENCODE()
				----------------------------------------------
			*/
			/*!
				@brief Encode a sequence of integers returning the number of bytes used for the encoding, or 0 if the encoded sequence doesn't fit in the buffer.
				@param encoded [out] The sequence of bytes that is the encoded sequence.
				@param encoded_buffer_length [in] The length (in bytes) of the output buffer, encoded.
				@param source [in] The sequence of integers to encode.
				@param source_integers [in] The length (in integers) of the source buffer.
				@return The number of bytes used to encode the integer sequence, or 0 on error (i.e. overflow).
			*/
			virtual size_t encode(void *encoded, size_t encoded_buffer_length, const document_id::integer *source, size_t source_integers)
				{
				this->bitstream.rewind(encoded, encoded_buffer_length);
				while (source_integers-- > 0)
					encode(*source++);
				return this->eof();
				}

			/*
				COMPRESS_INTEGER_ELIAS_DELTA_BITWISE::DECODE()
				----------------------------------------------
			*/
			/*!
				@brief Decode a sequence of integers encoded with this codex.
				@param decoded [out] The sequence of decoded integers.
				@param integers_to_decode [in] The minimum number of integers to decode (it may decode more).
				@param source [in] The encoded integers.
				@param source_length [in] The length (in bytes) of the source buffer.
			*/
			virtual void decode(document_id::integer *decoded, size_t integers_to_decode, const void *source, size_t source_length)
				{
				this->bitstream.rewind(const_cast<void *>(source));
				while (integers_to_decode-- > 0)
					*decoded++ = decode();
				}

			/*
				COMPRESS_INTEGER_ELIAS_DELTA_BITWISE::UNITTEST()
				------------------------------------------------
			*/
			/*!
				@brief Unit test this class
			*/
			static void unittest(void)
				{
				compress_integer<ACCUMULATOR_TYPE, MAX_DOCUMENTS, MAX_TOP_K>::unittest(compress_integer_elias_delta_bitwise(), 1);
				puts("compress_integer_elias_delta_bitwise::PASSED");
				}
		};
	}
