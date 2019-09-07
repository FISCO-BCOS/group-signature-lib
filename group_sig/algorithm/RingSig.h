/*
	This file is part of FISCO BCOS.

	FISCO BCOS is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FISCO BCOS is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FISCO BCOS.  If not, see <http://www.gnu.org/licenses/>.
*/

/* @file: RingSig.h
 * @author:fisco-bcos
 * @date:2019.09.03
 * @function: interface of group signature algorithm 
 */
#pragma once
#include <utility>

#if !defined(__cplusplus)
extern "C"
{
#endif

#if defined(__cplusplus)
  namespace RingSigApi
  {
  namespace LinkableRingSig
  {
#endif

  /******************* notification *********************
   *                                                    *
   *  All interfaces would throw string type exception  *
   *                                                    *
   ******************** notification ********************/

  /* @function: generate params for specified ring
     * @params: 1. bit_len: length of ring param element
     *          default is 1024(1024-security)
     * @ret: param_info
     */
  std::string setup_ring(const int &bit_len = 1024);

  // c language style interface with same funtion, please ignore
  int setup_ring(std::string &param_info,
                 const int &bit_len = 1024);

  /* @function: generate private key for member of 
     *            specified ring
     * @params: 1. param_info: param info of specified ring
     *          2. pos: position of this ring member
     *
     * @ret: key pairs: the first is private key, and the second is public key
     */
  std::pair<std::string, std::string> join_ring(const std::string &param_info,
                                                const std::string &pos);

  // c language style interface with same funtion, please ignore
  int join_ring(std::string &private_key_info,
                std::string &public_key_info,
                const std::string &param_info,
                const std::string &pos);

  /* @function: generate signature with linkable ring sig
     *      algorithm for specified ring member
     * @param: 1. message: plain text
     *         2. public_key_list: public key list used to
     *            generate linkable signature
     *         3. private_key_info:private key of ring member 
     *            to generate signature
     *         4. param_info: param info of ring the member 
     *         belongs to
     * @ret: signature
     */
  std::string ring_sig(const std::string &message,
                       const std::vector<std::string> &public_key_list,
                       const std::string &private_key_info,
                       const std::string &param_info);

  // c language style interface with same funtion, please ignore
  int ring_sig(std::string &sig,
               const std::string &message,
               const std::vector<std::string> &public_key_list,
               const std::string &private_key_info,
               const std::string &param_info);

  /* @function: verify given signature is valid or not
     * @params: 1. sig: signature to be verified
     *          2. message: plain text 
     *          3. param_info: param inforamtion of ring this signature 
     *             belongs to 
     * @ret: true: signature is valid; false: signature is invalid;
     */
  bool ring_verify(const std::string &sig,
                   const std::string &message,
                   const std::string &param_info);

  // c language style interface with same funtion, please ignore
  int ring_verify(bool &valid,
                  const std::string &sig,
                  const std::string &message,
                  const std::string &param_info);

#if defined(__cplusplus)
  }
  }
#endif
#if !defined(__cplusplus)
}
#endif
