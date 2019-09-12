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

/* @file: GroupSig.h
 * @author:fisco-bcos
 * @date:2018.03.06
 * @function: interface of group signature algorithm 
 */

#pragma once
#include <vector>
#include <string>

#if !defined(__cplusplus)
extern "C"
{
#endif

#if defined(__cplusplus)
  namespace GroupSigApi
  {
#endif

  // struct for group information
  struct GroupInfo
  {
    std::string gpk, gmsk, gamma, param;
    GroupInfo() {}
    GroupInfo(std::string &in1, std::string &in2, std::string &in3, std::string &in4) : gpk(in1), gmsk(in2), gamma(in3), param(in4) {}
  };

  /******************* notification ********************
   *                                                    *
   *  All interfaces would throw string type exception  *
   *                                                    *
   ******************** notification ********************/

  // get cert from private key
  std::string get_cert(const std::string &sk_info);

  // get g1 list after revoking members, and input is the list of new gpk
  std::string get_g1_list(std::vector<std::string> &new_gpks_info);

  /* @function: create group with default linear pair(A Linear pair)
     * @ret: GroupInfo, includes :
     *       "group public key(gpk)", 
     *       "group manager private key(gmsk)",
     *       "group private key(gamma)" and 
     *       "pbc param used in the algorithm(pbc_param)",
     */
  GroupInfo create_group_default();

  // c language style interface with same funtion, please ignore
  int create_group_default(std::string &result,
                           const std::string &algorithm_method);

  /* @function: create group with specified linear pair param 
     * @params: pbc_param: specified pbc param information:
     *         (1) A type linear param (q_bits_len and r_bits_len can be self-specified):
     *            "{\"linear_type\": \"a\", \"q_bits_len\": , \"r_bits_len\": 256, \"q_bits_len\":256}"
     *         (2) A1 type linear pair (order can be self-specified):
     *            "{\"linear_type\":\"a_one\", \"order\":512}"
     *         (3) E type linear pair (q_bits_len and r_bits_len can be self-specified):
     *            "{\"linear_type\":\"e\", \"q_bits_len\": 512, \"r_bits_len\":512}"
     *         (4) F type linear pair (bit_len can be self-specified):
     *            "{\"linear_type\":\"f\", \"bit_len\": 256}"
     *
     * @ret: GroupInfo, includes :
     *       "group public key(gpk)", 
     *       "group manager private key(gmsk)",
     *       "group private key(gamma)" and 
     *       "pbc param used in the algorithm(pbc_param)",
     */
  GroupInfo create_group(const std::string &pbc_param);

  // c language style interface with same funtion, please ignore
  int create_group(std::string &result,
                   const std::string &algorithm_method,
                   const std::string &pbc_param);

  //group  member join: group manager generate private key && cert for group members
  /* @function: generate private key and cert for joined member 
     * @params: 1. pbc_param_info: pbc param information of group to be joined
     *          (generally obtained upon group generation, and open to others) 
     *
     *          2. gmsk_info: private key of group manager
     *            (Thus, group mananger gen private key and cert for group member)
     *
     *          3. gpk_info: public key of the group
     *          (generated upon create_group)
     *
     *          4. gamma_info: private information maintained by group member 
     
     * @ret: sk: private key and cert of joined group member;
     */
  std::string group_member_join(const std::string &param_info,
                                const std::string &gmsk_info,
                                const std::string &gpk_info,
                                const std::string &gamma_info);

  // c language style interface with same funtion, please ignore
  int group_member_join(std::string &sk,
                        const std::string &algorithm_method,
                        const std::string &param_info,
                        const std::string &gmsk_info,
                        const std::string &gpk_info,
                        const std::string &gamma_info);

  /* @function: generate signature with specified group sig algorithm   
     * @params: 1. gpk_info: public key of the group 
     *          2. sk_info: private key of the member to generate signature
     *          3. param_info: pbc param information of the group  
     *          4. message: plain text to generate group signature
     *
     * @ret: signature 
     */
  std::string group_sig(const std::string &gpk_info,
                        const std::string &sk_info,
                        const std::string &param_info,
                        const std::string &message);

  // c language style interface with same funtion, please ignore
  int group_sig(std::string &result,
                const std::string &algorithm_method,
                const std::string &gpk_info,
                const std::string &sk_info,
                const std::string &param_info,
                const std::string &message);

  /* @function: verify specified signature 
     * @params: 1. message: plain text of specified signature
     *          2. sig: signature
     *          3. gpk_info: public key of the group the signature belongs to
     *          4. aram_info: pbc param information of the group the signature belongs to
     * 
     * @ret: true: signature is valid; false: signature is invalid;
     */
  bool group_verify(const std::string &sig,
                    const std::string &message,
                    const std::string &gpk_info,
                    const std::string &param_info);

  // c language style interface with same funtion, please ignore
  int group_verify(int &ret,
                   const std::string &sig,
                   const std::string &message,
                   const std::string &algorithm_method,
                   const std::string &gpk_info,
                   const std::string &param_info);

  //implementation of group open with given signature
  /* @function: get cert according to given signature
                 (only group manager can calculate the cert)
                 (generally used in regulation cases)

     * @param: 1. sig: specified signature to get its signer
     *         2. message: plain message of this signature
     *         3. gpk_info: public key of the group
     *         4. gmsk_info: private key of group manager
     *         5. param_info: pbc param information of the group the signature belongs to
     *
     * @ret: cert
     */
  std::string open_cert(const std::string &sig,
                        const std::string &message,
                        const std::string &gpk_info,
                        const std::string &gmsk_info,
                        const std::string &param_info);

  // c language style interface with same funtion, please ignore
  int open_cert(std::string &cert,
                const std::string &algorithm_method,
                const std::string &sig,
                const std::string &message,
                const std::string &gpk_info,
                const std::string &gmsk_info,
                const std::string &param_info);

  //update gpk when group memeber revoked(executed by group manager)
  /* @function: update gpk when group member revoked
     * @params: 1. gpk: public key of the group the revoked member belongs to
     *          2. param_info: pbc param of the group the revoked member belongs to
     *          3. revoke_info: private and cert information of revoked member
     *          4. gamma_info: private information of the group, it is maintained by
     *             group manager
     *
     * @ret: new gpk
     */
  std::string revoke_member(const std::string &gpk_info,
                            const std::string &param_info,
                            const std::string &revoke_info,
                            const std::string &gamma_info);

  // c language style interface with same funtion, please ignore
  int revoke_member(std::string &gpk_info,
                    const std::string &algorithm_method,
                    const std::string &param_info,
                    const std::string &revoke_info,
                    const std::string &gamma_info);

  /* @function: update group member private key after some members revoked
     *            (callback by group member when it callback group_sig and some people
     *            hava revoked from the group)
     * @params: 1. sk: origin private key of specified group member
     *          2. param_info: pbc param of the group the member belongs to
     *          3. revoked list: private keys and certs of revoked members since the 
     *             member update its private key last time
     *          4. g1_list: all new g1(part of gpk) information since the member update 
     *             its private key last time
     *          5. gpk_info: public key of group the member belongs to 
     *
     * @ret: new sk
     */
  std::string revoke_update_private_key(const std::string &sk_info,
                                        const std::string &param_info,
                                        const std::string &revoke_list,
                                        const std::string &g1_list,
                                        const std::string &gpk_info);

  // c language style interface with same funtion, please ignore
  int revoke_update_private_key(std::string &sk_info,
                                const std::string &algorithm_method,
                                const std::string &param_info,
                                const std::string &revoke_list,
                                const std::string &g1_list,
                                const std::string &gpk_info);

#if defined(__cplusplus)
  }
#endif
#if !defined(__cplusplus)
}
#endif
